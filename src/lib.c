#include "lib.h"
#define PECA(cor, pb, pp)(cor == BRANCA ? pb : pp)

int roque_branca, roque_preta;
int jogador_atual = BRANCA;

int menu()
{
    int opc_menu;

    printf("=============================\n");
    printf("            XADREZ           \n");
    printf("-----------------------------\n");
    printf("\033[5m  1\t     JOGAR\033[m\n");
    printf("  2      CONFIGURAÇÃO        \n");
    printf("  3          SAIR            \n");
    printf("=============================\n>");

    scanf(" %d", &opc_menu);
    system("clear");

    if (opc_menu > 0 && opc_menu < 4) return opc_menu;
    return False;
}

void coordenada(int linha, char coluna, int *destino_linha, int *destino_coluna)
{
    *destino_linha = 8 - linha;
    if (coluna >= 'a' && coluna <= 'h')
        *destino_coluna = coluna % 'a';
    else *destino_coluna = 24;
}

void inicializar(Peca *tabuleiro[8][8], Peca pb[], Peca pp[])
{
    int peca;

    for (peca = 0; peca < 16; peca++)
    {
        if (peca < 8)
        {
            pb[peca].nome = PEAO;
            pp[peca].nome = PEAO;
        }
        pb[peca].cor = BRANCA;
        pb[peca].capturada = False;
        pb[peca].movimento_especial = True;
        pp[peca].cor = PRETA;
        pp[peca].capturada = False;
        pp[peca].movimento_especial = True;
    }
    pb[8].nome = TORRE;
    pb[9].nome = CAVALO;
    pb[10].nome = BISPO;
    pb[11].nome = RAINHA;
    pb[12].nome = REI;
    pb[13].nome = BISPO;
    pb[14].nome = CAVALO;
    pb[15].nome = TORRE;
    pp[8].nome = TORRE;
    pp[9].nome = CAVALO;
    pp[10].nome = BISPO;
    pp[11].nome = RAINHA;
    pp[12].nome = REI;
    pp[13].nome = BISPO;
    pp[14].nome = CAVALO;
    pp[15].nome = TORRE;

    for (peca = 0; peca < 8; ++peca)
    {
        tabuleiro[0][peca] = &pp[peca+8];
        tabuleiro[1][peca] = &pp[peca];
        tabuleiro[6][peca] = &pb[peca];
        tabuleiro[7][peca] = &pb[peca+8];
    }
    roque_branca = True;
    roque_preta = True;
}

void configurar(Cor *cor)
{
    int tema;

    printf("=============================\n");
    printf("            TEMA             \n");
    printf("-----------------------------\n");
    printf("           TEMA 1            \n");
    printf("           TEMA 2            \n");
    printf("           TEMA 3            \n");
    printf("           TEMA 4            \n");
    printf("=============================\nTEMA>");

    scanf(" %d", &tema);

    switch (tema)
    {
    case 1:
        cor->cor_1 = 107;
        cor->cor_2 = 47;
        cor->borda = 40;
        break;
    case 2:
        cor->cor_1 = 103;
        cor->cor_2 = 43;
        cor->borda = 46;
        break;
    case 3:
        cor->cor_1 = 104;
        cor->cor_2 = 44;
        cor->borda = 45;
        break;
    case 4:
        cor->cor_1 = 106;
        cor->cor_2 = 46;
        cor->borda = 44;
        break;
    }
    printf("Tema %d selecionado.\n", tema);
    sleep(1);
    system("clear");
}

void interface(Peca *tabuleiro[8][8], Cor cor)
{
    int i, j, num_linha=8, cor_atual;
    //int cor_borda = cor.borda;
    system("clear");
    sleep(0.5);

    printf("\n\033[%dm                             \033[m\n", cor.borda);
    for (i = 0; i < 8; ++i)
    {
        printf("\033[%dm %d \033[m", cor.borda, num_linha--);

        for (j = 0; j < 8; ++j)
        {
            // cor_atual = ((i + j) % 2 == 0)?cor.cor_1:cor.cor_2;

            if ((i + j) % 2 == 0) cor_atual = cor.cor_1;
            else cor_atual = cor.cor_2;

            if (tabuleiro[i][j] != NULL)
            {
                int cor = tabuleiro[i][j]->cor;
                switch (tabuleiro[i][j]->nome)
                {
                case PEAO:
                    printf("\033[%dm\033[30m %s \033[m", cor_atual, PECA(cor, B_P, P_P));
                    break;
                case TORRE:
                    printf("\033[%dm\033[30m %s \033[m", cor_atual, PECA(cor, B_TORRE, P_TORRE));
                    break;
                case CAVALO:
                    printf("\033[%dm\033[30m %s \033[m", cor_atual, PECA(cor, B_CAVALO, P_CAVALO));
                    break;
                case BISPO:
                    printf("\033[%dm\033[30m %s \033[m", cor_atual, PECA(cor, B_BISPO, P_BISPO));
                    break;
                case REI:
                    printf("\033[%dm\033[30m %s \033[m", cor_atual, PECA(cor, B_REI, P_REI));
                    break;
                case RAINHA:
                    printf("\033[%dm\033[30m %s \033[m", cor_atual, PECA(cor, B_RAINHA, P_RAINHA));
                    break;
                }
            }
            else printf("\033[%dm   \033[m", cor_atual);
        }
        printf("\033[%dm  \033[m\n", cor.borda);
    }
    printf ("\033[%dm    a  b  c  d  e  f  g  h   \033[m\n", cor.borda);
}

int atributo(Peca *peca, enum id_atributo atributo)
{
    if (peca != NULL)
        if (atributo == NOME) return peca->nome;
        else if (atributo == COR) return peca->cor;
        else if (atributo == CAPTURADA) return peca->capturada;
        else if (atributo == ESPECIAL) return peca->movimento_especial;
    else return False;
}

int promacao_peao()
{
    int peca;
    printf(
        "\033[13H  ---= PEÃO PROMOVIDO =---   \n"
        "       [1]   TORRE \n"
        "       [2]   CAVALO\n"
        "       [3]   BISPO \n"
        "       [4]   RAINHA\n"
        " PROMOVER PARA > "
    );
    do
    {
        printf("\033[18;18H   \033[18;18H");
        scanf(" %d", &peca);
    } while (peca < 1 || peca > 4);
    return peca;
}

void peao(Peca *tabuleiro[8][8], Coordenada crd)
{
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int pular_2_casas = (ol == 1 || ol == 6) ? True : False;
    int actl = ol, actc = oc;
    int adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
    int movimento = abs(ol - dl);

    if (oc == dc && tabuleiro[dl][dc] == NULL)
    {
        if (movimento == 1)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            actl = dl;
            actc = dc;
            tabuleiro[ol][oc] = NULL;
        }
        else if (pular_2_casas && movimento == 2)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            actl = dl;
            actc = dc;
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (atributo(tabuleiro[dl][dc], COR) == adversario && movimento == 1)
    {
        int avanco = (tabuleiro[ol][oc]->cor == BRANCA) ? ol > dl : ol < dl;

        if (avanco && oc < dc)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            actl = dl;
            actc = dc;
            tabuleiro[ol][oc] = NULL;
        }
        else if (avanco && oc > dc)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            actl = dl;
            actc = dc;
            tabuleiro[ol][oc] = NULL;
        }
    }
    if ((actl == 0 || actl == 7) && movimento == 1)
    {
        switch (promacao_peao())
        {
            case 1:
                tabuleiro[actl][actc]->nome = TORRE;
                break;
            case 2:
                tabuleiro[actl][actc]->nome = CAVALO;
                break;
            case 3:
                tabuleiro[actl][actc]->nome = BISPO;
                break;
            case 4:
                tabuleiro[actl][actc]->nome = RAINHA;
                break;
        }
    }
}

void torre(Peca *tabuleiro[8][8], Coordenada crd)
{
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int auxl=ol, auxc=oc, livre=True;
    int norte = ol > dl && oc == dc;
    int leste = ol == dl && oc < dc;
    int sul = ol < dl && oc == dc;
    int oeste = ol == dl && oc > dc;
    int adversario = atributo(tabuleiro[dl][dc], COR);
    int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
    int roque = (cor_adversario == PRETA) ? roque_branca : roque_preta;
    Peca *p_torre = tabuleiro[ol][oc], *p_peca = tabuleiro[dl][dc];

    if (norte)
    {
        while (auxl > (dl + 1))
        {
            auxl--;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
    }
    else if (leste)
    {
        while (auxc < (dc - 1))
        {
            auxc++;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
    }
    else if (sul)
    {
        while (auxl < (dl - 1))
        {
            auxl++;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
    }
    else if (oeste)
    {
        while (auxc > (dc + 1))
        {
            auxc--;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
    }

    if (livre && (norte || leste || sul || oeste))
    {
        if (tabuleiro[dl][dc] == NULL || adversario == cor_adversario)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
            if (roque)
                if (tabuleiro[dl][dc]->cor == PRETA)
                    roque_preta = False;
                else
                    roque_branca = False;
        }
    }

    if ((leste || oeste) && p_peca != NULL && roque)
    {
        auxc = oc;
        while (auxc < 3 || auxc > 5)
        {
            oc == 0 ? auxc++ : auxc--;
            if (tabuleiro[dl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        if (livre && p_peca->nome == REI)
        {
            if (tabuleiro[ol][oc]->cor == PRETA)
                roque_preta = False;
            else
                roque_branca = False;
            tabuleiro[ol][oc] = NULL;
            tabuleiro[dl][dc] = NULL;
            auxc = (oc == 0) ? 3 : 5;
            tabuleiro[dl][auxc] = p_torre;
            auxc = (oc == 0) ? 2 : 6;
            tabuleiro[dl][auxc] = p_peca;
        }
    }
}

void cavalo(Peca *tabuleiro[8][8], Coordenada crd)
{
    printf("\033[2;35HCAVALO\033[1H");

    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int adversario = atributo(tabuleiro[dl][dc], COR);
    int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
    int auxl = abs(ol - dl);
    int auxc = abs(oc - dc);
    int mover = tabuleiro[dl][dc] == NULL || adversario == cor_adversario;

    if (auxl == 2)
    {
        if ((auxc == 1) && mover)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (auxl == 1)
    {
        if ((auxc == 2) && mover)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
}

void bispo(Peca *tabuleiro[8][8], Coordenada crd)
{
    printf("\033[2;35HBISPO\033[1H");

    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int auxl=ol, auxc=oc, livre=True, capturar;
    int nordeste = ol > dl && oc < dc;
    int sudeste = ol < dl && oc < dc;
    int sudoeste = ol < dl && oc > dc;
    int noroeste = ol > dl && oc > dc;
    int adversario = atributo(tabuleiro[dl][dc], COR);
    int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;

    if (nordeste)
    {
        printf("\033[3;35HSENTIDO NORDESTE\033[1H");
        while (auxl > dl && auxc < dc)
        {
            auxl--;
            auxc++;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (sudeste)
    {
        printf("\033[3;35HSENTIDO SUDESTE\033[1H");
        while (auxl < dl && auxc < dc)
        {
            auxl++;
            auxc++;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (sudoeste)
    {
        printf("\033[3;35HSENTIDO SUDOESTE\033[1H");
        while (auxl < dl && auxc > dc)
        {
            auxl++;
            auxc--;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (noroeste)
    {
        printf("\033[3;35HSENTIDO NOROESTE\033[1H");
        while (auxl > dl && auxc > dc)
        {
            auxl--;
            auxc--;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
}

void rainha(Peca *tabuleiro[8][8], Coordenada crd)
{
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int auxl=ol, auxc=oc, livre=True, capturar;
    int norte = ol > dl && (oc == dc || oc < dc);
    int leste = (ol == dl || ol < dl) && oc < dc;
    int sul = ol < dl && (oc == dc || oc > dc);
    int oeste = (ol == dl || ol > dl) && oc > dc;
    int adversario = atributo(tabuleiro[dl][dc], COR);
    int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;

    if (norte)
    {
        printf("\033[3;35HSENTIDO NORDESTE\033[1H");
        int nordeste = ol > dl && oc < dc;
        while (auxl > dl && (auxc == dc || auxc < dc))
        {
            auxl--;
            if (nordeste) auxc++;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (leste)
    {
        printf("\033[3;35HSENTIDO SUDESTE\033[1H");
        int sudeste = ol < dl && oc < dc;
        while ((auxl == dl || auxl < dl) && auxc < dc)
        {
            if (sudeste) auxl++;
            auxc++;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (sul)
    {
        printf("\033[3;35HSENTIDO SUDOESTE\033[1H");
        int sudoeste = ol < dc && oc > dc;
        while (auxl < dl && (auxc == dc || auxc > dc))
        {
            auxl++;
            if (sudoeste) auxc--;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (oeste)
    {
        printf("\033[3;35HSENTIDO NOROESTE\033[1H");
        int noroeste = ol > dl && oc > dc;
        while ((auxl == dl || auxl > dl) && auxc > dc)
        {
            if (noroeste) auxl--;
            auxc--;
            if (tabuleiro[auxl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        capturar = (adversario == cor_adversario);
        if (auxl == dl && auxc == dc && (livre || capturar))
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
}

void rei(Peca *tabuleiro[8][8], Coordenada crd)
{
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int auxl=ol, auxc=oc, livre=True, capturar;
    int norte = ol > dl && (oc == dc || oc < dc);
    int leste = (ol == dl || ol < dl) && oc < dc;
    int sul = ol < dl && (oc == dc || oc > dc);
    int oeste = (ol == dl || ol > dl) && oc > dc;
    int adversario = atributo(tabuleiro[dl][dc], COR);
    int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
    int mover_vertical = abs(oc - dc) == 1;
    int mover_horizontal = abs(ol - dl) == 1;

    if (mover_horizontal || mover_vertical)
        if (norte)
        {
            printf("\033[3;35HSENTIDO NORDESTE\033[1H");
            int nordeste = ol > dl && oc < dc;
            auxl--;
            if (nordeste) auxc++;
            if (tabuleiro[auxl][auxc] != NULL) livre = False;
            capturar = (adversario == cor_adversario);
            if (auxl == dl && auxc == dc && (livre || capturar))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (leste)
        {
            printf("\033[3;35HSENTIDO SUDESTE\033[1H");
            int sudeste = ol < dl && oc < dc;
            if (sudeste) auxl++;
            auxc++;
            if (tabuleiro[auxl][auxc] != NULL) livre = False;
            capturar = (adversario == cor_adversario);
            if (auxl == dl && auxc == dc && (livre || capturar))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (sul)
        {
            printf("\033[3;35HSENTIDO SUDOESTE\033[1H");
            int sudoeste = ol < dl && oc > dc;
            auxl++;
            if (sudoeste) auxc--;
            if (tabuleiro[auxl][auxc] != NULL) livre = False;
            capturar = (adversario == cor_adversario);
            if (auxl == dl && auxc == dc && (livre || capturar))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (oeste)
        {
            printf("\033[3;35HSENTIDO NOROESTE\033[1H");
            int noroeste = ol > dl && oc > dc;
            if (noroeste) auxl--;
            auxc--;
            if (tabuleiro[auxl][auxc] != NULL) livre = False;
            capturar = (adversario == cor_adversario);
            if (auxl == dl && auxc == dc && (livre || capturar))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
}

void mover_peca(Peca *tabuleiro[8][8], Coordenada crd)
{
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    
    if (tabuleiro[ol][oc] != NULL)
    {
        int peca = tabuleiro[ol][oc]->nome;
        int adversario = (tabuleiro[ol][oc]->cor == BRANCA) ? PRETA : BRANCA;

        if (peca == PEAO)
            peao(tabuleiro, crd);
        else if (peca == TORRE)
            torre(tabuleiro, crd);
        else if (peca == CAVALO)
            cavalo(tabuleiro, crd);
        else if (peca == BISPO)
            bispo(tabuleiro, crd);
        else if (peca == RAINHA)
            rainha(tabuleiro, crd);
        else if (peca == REI)
            rei(tabuleiro, crd);
        
        reiniciar_en_passant (tabuleiro, adversario);

        Coordenada posicao_rei = localiza_rei(tabuleiro, adversario);
        int xeque_cont = xeque_mate(tabuleiro, posicao_rei);
        char cor_adversario[10];
        if (adversario == BRANCA)
            strcpy(cor_adversario, "BRANCAS");
        else
            strcpy(cor_adversario, "PRETAS");
        if (xeque_cont > 0 && xeque_cont < 9)
            printf("\033[5;35H%s EM CHEQUE!\033[1H", cor_adversario);
        else if (xeque_cont == 9)
            printf("\033[5;35H%s EM CHEQUE MATE!\033[1H", cor_adversario);
    }
}

int coordenada_valida(Peca *tabuleiro[8][8] , Coordenada crd) {
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    
    if (ol < 0 || ol > 7 || oc < 0 || oc > 7 || dl < 0 || dl > 7 || dc < 0 || dc > 7) {
        printf("\033[5;35HMOVIMENTO INVÁLIDO!\033[1H");
        return False;
    }
    
    int peca = tabuleiro[ol][oc]->nome;
    int movimento = (tabuleiro[ol][oc]->cor == BRANCA) ? ol - dl : dl - ol;
    
    
    switch (peca) {
        case PEAO:
            if (movimento == 1 || (movimento == 2 && (ol == 6 || ol == 1)))
                return True;
            break;
        case TORRE:
            if (ol == dl || oc == dc)
                return True;
            break;
        case CAVALO:
            if ((abs(dl - ol) == 1 && abs(dc - oc) == 2) || (abs(dc - oc) == 1 && abs(dl - ol) == 2))
                return True;
            break;
        case BISPO:
            if (abs(dl - ol) == abs(dc - oc))
                return True;
            break;
        case RAINHA:
            if (ol == dl || oc == dc)
                return True;
            else if (abs(dl - ol) == abs(dc - oc))
                return True;
            break;
        case REI:
            if (abs(dl - ol) == 1 || abs(dc - oc) == 1)
                return True;
            break;
    }
    
    return False;
}

int verificar_jogador_atual(Peca *tabuleiro[8][8], Coordenada crd) {
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    
    if(!coordenada_valida(tabuleiro, crd)) return False;
    
    // usar a função atributo, se necessário, para evitar falha de fragmentação
    int peca = tabuleiro[ol][oc]->nome;
    
    if (tabuleiro[ol][oc]->cor == jogador_atual) {
        jogador_atual = (jogador_atual == BRANCA) ? PRETA : BRANCA;
        return True;
    }
    
    printf("\033[5;35HAINDA NÃO É SUA VEZ DE JOGAR!\033[1H");
    return False;
}

void reiniciar_en_passant(Peca *tabuleiro[8][8], int adversario)
{
    int linha, coluna;
    
    for (int linha = 0; linha < 8; linha++) {
        for (int coluna = 0; coluna < 8; coluna++) {
            if (tabuleiro[linha][coluna] != NULL && tabuleiro[linha][coluna]->cor == adversario) {
                tabuleiro[linha][coluna]->movimento_especial = False;
            }
        }
    }
}

Coordenada localiza_rei (Peca *tabuleiro[8][8], int cor)
{
    Coordenada posicao_rei;
    
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (tabuleiro[i][j] != NULL)
            {
                if (tabuleiro[i][j]->nome == REI && tabuleiro[i][j]->cor == cor)
                {
                    posicao_rei.origem_linha = i;
                    posicao_rei.origem_coluna = j;
                    break;
                }
            }
    return posicao_rei;
}

int xeque_torre (Peca *tabuleiro[8][8], Coordenada posicao, int cor)
{
  int ol = posicao.origem_linha;
  int oc = posicao.origem_coluna;
  int auxl = ol;
  int auxc = oc;
  int somador_linha = 1;
  int somador_coluna = 1;
  int adversario = cor == BRANCA ? PRETA : BRANCA;
  
  for (int i = 0; i < 2; i++, somador_linha *= -1) 
    {
        auxl += somador_linha;
        if (auxl >= 0 && auxl <= 7) {
            while (tabuleiro[auxl][auxc] == NULL)
            {
                auxl += somador_linha;
                if (auxl < 0 || auxl > 7)
                {
                    auxl -= somador_linha;
                    break;
                }
            }
            
            if (auxl >= 0 && auxl <= 7 && tabuleiro[auxl][auxc] != NULL)
            {
                if (tabuleiro[auxl][auxc]->cor == adversario && tabuleiro[auxl][auxc]->nome == TORRE)
                {
                    return True;
                }     
            }
        }
        
        auxl = ol;        
    } 
    
    for (int i = 0; i < 2; i++, somador_coluna *= -1) 
    {
        auxc += somador_coluna;
        if (auxc >= 0 && auxc <= 7) {
            while (tabuleiro[auxl][auxc] == NULL)
            {
                auxc += somador_coluna;
                if (auxc < 0 || auxc > 7)
                {
                    auxc -= somador_coluna;
                    break;
                }
            }
            
            if (auxc >= 0 && auxc <= 7 && tabuleiro[auxl][auxc] != NULL)
            {
                if (tabuleiro[auxl][auxc]->cor == adversario && tabuleiro[auxl][auxc]->nome == TORRE)
                {
                    return True;
                }     
            }
        }
        
        auxc = oc;        
    } 
    
    return False;
}

int xeque_bispo (Peca *tabuleiro[8][8], Coordenada posicao, int cor)
{
    int ol = posicao.origem_linha;
    int oc = posicao.origem_coluna;
    int auxl = ol;
    int auxc = oc;
    int somador_linha = 1;
    int somador_coluna = 1;
    int adversario = cor == BRANCA ? PRETA : BRANCA;
    
    for (int i = 0; i < 4; i++, somador_linha *= (i==2) ? -1: 1, somador_coluna *= -1)
    {
        auxl += somador_linha;
        auxc += somador_coluna;
        
        if (auxl >= 0 && auxl <= 7 && auxc >=0 && auxc <= 7)
        {
            while (tabuleiro[auxl][auxc] == NULL)
            {
                auxl += somador_linha;
                auxc += somador_coluna;
                
                if (auxl < 0 || auxl > 7 || auxc < 0 || auxc > 7)
                {
                    auxl -= somador_linha;
                    auxc -= somador_coluna;
                    break;
                }
            } 
            
            if (auxl >= 0 && auxl <= 7 && auxl >= 0 && auxl <= 7 && tabuleiro[auxl][auxc] != NULL)
            {
                if (tabuleiro[auxl][auxc]->cor == adversario && tabuleiro[auxl][auxc]->nome == BISPO)
                {
                    return True;
                    break;
                }        
            }       
        }
        
        auxl = ol;
        auxc = oc;    
    }
    
    return False;  
}

int xeque_cavalo (Peca *tabuleiro[8][8], Coordenada posicao, int cor)
{
    int ol = posicao.origem_linha;
    int oc = posicao.origem_coluna;
    int auxl = ol;
    int auxc = oc;
    Peca *aux;
    int adversario = cor == BRANCA ? PRETA : BRANCA;
    
    int varia_linha[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int varia_coluna[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    for (int i=0; i<8; i++)
    {
        aux = (ol+varia_linha[i]>=0 && ol+varia_linha[i]<=7 && oc+varia_coluna[i]>=0 && oc+varia_coluna[i]<=7)?tabuleiro[ol+varia_linha[i]][oc+varia_coluna[i]]:NULL;
        
        if (aux != NULL)
            if (aux->nome == CAVALO && aux->cor == adversario)
                return True;
    } 
    
    return False;  
}

int xeque_peao (Peca *tabuleiro[8][8], Coordenada posicao, int cor)
{
    int ol = posicao.origem_linha;
    int oc = posicao.origem_coluna;
    int auxl = ol;
    int auxc = oc;
    Peca *aux;
    int avanco = cor == BRANCA ? -1 : 1;
    int adversario = cor == BRANCA ? PRETA : BRANCA; 
    
    aux = (ol+avanco>=0 && ol+avanco<=7 && oc-1>=0) ? tabuleiro[ol+avanco][oc-1] : NULL;
    
    if (aux != NULL)
        if (aux->nome == PEAO && aux->cor == adversario)
            return True;
    
    aux = (ol+avanco>=0 && ol+avanco<=7 && oc+1<=7) ? tabuleiro[ol+avanco][oc+1] : NULL;
    
    if (aux != NULL)
        if (aux->nome == PEAO && aux->cor == adversario)
            return True;
            
    return False;           
}

int xeque_rainha (Peca *tabuleiro[8][8], Coordenada posicao, int cor)
{
  int ol = posicao.origem_linha;
  int oc = posicao.origem_coluna;
  int auxl = ol;
  int auxc = oc;
  int somador_linha = 1;
  int somador_coluna = 1;
  int adversario = cor == BRANCA ? PRETA : BRANCA;
  
  for (int i = 0; i < 2; i++, somador_linha *= -1) 
    {
        auxl += somador_linha;
        if (auxl >= 0 && auxl <= 7) {
            while (tabuleiro[auxl][auxc] == NULL)
            {
                auxl += somador_linha;
                if (auxl < 0 || auxl > 7)
                {
                    auxl -= somador_linha;
                    break;
                }
            }
            
            if (auxl >= 0 && auxl <= 7 && tabuleiro[auxl][auxc] != NULL)
            {
                if (tabuleiro[auxl][auxc]->cor == adversario && tabuleiro[auxl][auxc]->nome == RAINHA)
                {
                    return True;
                }     
            }
        }
        
        auxl = ol;        
    } 
    
    for (int i = 0; i < 2; i++, somador_coluna *= -1) 
    {
        auxc += somador_coluna;
        if (auxc >= 0 && auxc <= 7) {
            while (tabuleiro[auxl][auxc] == NULL)
            {
                auxc += somador_coluna;
                if (auxc < 0 || auxc > 7)
                {
                    auxc -= somador_coluna;
                    break;
                }
            }
            
            if (auxc >= 0 && auxc <= 7 && tabuleiro[auxl][auxc] != NULL)
            {
                if (tabuleiro[auxl][auxc]->cor == adversario && tabuleiro[auxl][auxc]->nome == RAINHA)
                {
                    return True;
                }     
            }
        }
        
        auxc = oc;        
    } 
    
    auxl = ol;
    auxc = oc;
    somador_linha = 1;
    somador_coluna = 1;
    
    for (int i = 0; i < 4; i++, somador_linha *= (i==2) ? -1 : 1, somador_coluna *= -1)
    {
        auxl += somador_linha;
        auxc += somador_coluna;
        
        if (auxl >= 0 && auxl <= 7 && auxc >=0 && auxc <= 7)
        {
            while (tabuleiro[auxl][auxc] == NULL)
            {
                auxl += somador_linha;
                auxc += somador_coluna;
                
                if (auxl < 0 || auxl > 7 || auxc < 0 || auxc > 7)
                {
                    auxl -= somador_linha;
                    auxc -= somador_coluna;
                    break;
                }
            } 
            
            if (auxl >= 0 && auxl <= 7 && auxl >= 0 && auxl <= 7 && tabuleiro[auxl][auxc] != NULL)
            {
                if (tabuleiro[auxl][auxc]->cor == adversario && tabuleiro[auxl][auxc]->nome == RAINHA)
                {
                    return True;
                    break;
                }        
            }       
        }
        
        auxl = ol;
        auxc = oc;    
    }
    
    return False;        
}

int em_xeque (Peca *tabuleiro[8][8], Coordenada posicao, int cor)
{
    int xeques = 0;
    
    xeques+= xeque_torre(tabuleiro, posicao, cor);
    xeques+= xeque_bispo(tabuleiro, posicao, cor);
    xeques+= xeque_cavalo(tabuleiro, posicao, cor);
    xeques+= xeque_peao(tabuleiro, posicao, cor);
    xeques+= xeque_rainha(tabuleiro, posicao, cor);
    return xeques;
}

int xeque_mate (Peca *tabuleiro[8][8], Coordenada posicao_rei)
{
    int ol = posicao_rei.origem_linha;
    int oc = posicao_rei.origem_coluna;
    int posicoes_invalidas = 0;
    Peca *aux;
    Coordenada auxcoord;
    int cor = tabuleiro[ol][oc]->cor;
    int xeques = 1;
    int varia_linha[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int varia_coluna[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    
    
    if (!(em_xeque(tabuleiro, posicao_rei, cor)))
    {
        return False;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            int auxl = ol+varia_linha[i];
            int auxc = oc+varia_coluna[i];
            if (auxl>=0 && auxl<=7 && auxc>=0 && auxc<=7)
            {
                if (tabuleiro[auxl][auxc] != NULL && tabuleiro[auxl][auxc]->nome != REI)
                {
                    xeques+= 1;
                }
                else
                {
                    auxcoord.origem_linha = auxl;
                    auxcoord.origem_coluna = auxc;
                    xeques+= (em_xeque(tabuleiro, auxcoord, cor)) ? 1 : 0;
                }   
            }
            else {
                posicoes_invalidas++;
            }   
        }
    }
    
    return xeques + posicoes_invalidas;
}
