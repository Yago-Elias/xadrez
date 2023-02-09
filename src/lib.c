#include "lib.h"
#define PECA(cor, pb, pp) (cor == BRANCA? pb : pp)

int roque = True;

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
    if (coluna == 'a') *destino_coluna = 0;
    else if (coluna == 'b') *destino_coluna = 1;
    else if (coluna == 'c') *destino_coluna = 2;
    else if (coluna == 'd') *destino_coluna = 3;
    else if (coluna == 'e') *destino_coluna = 4;
    else if (coluna == 'f') *destino_coluna = 5;
    else if (coluna == 'g') *destino_coluna = 6;
    else if (coluna == 'h') *destino_coluna = 7;
}

void inicializar(struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[])
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
    roque = True;
}

void configurar(int cor_tabuleiro[])
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
        cor_tabuleiro[0]  = 107;
        cor_tabuleiro[1] = 47;
        cor_tabuleiro[2] = 40;
        break;
    case 2:
        cor_tabuleiro[0] = 103;
        cor_tabuleiro[1] = 43;
        cor_tabuleiro[2] = 46;
        break;
    case 3:
        cor_tabuleiro[0] = 104;
        cor_tabuleiro[1] = 44;
        cor_tabuleiro[2] = 45;
        break;
    case 4:
        cor_tabuleiro[0] = 106;
        cor_tabuleiro[1] = 46;
        cor_tabuleiro[2] = 44;
        break;
    }
    printf("Tema %d selecionado.\n", tema);
    sleep(2);
    system("clear");
}

void interface(struct Soldado *tabuleiro[8][8], int cor_tabuleiro[])
{
    int i, j, num_linha=8, cor_atual;
    int cor_borda = cor_tabuleiro[2];
    system("clear");
    sleep(0.5);

    printf("\n\033[%dm                             \033[m\n", cor_borda);
    for (i = 0; i < 8; ++i)
    {
        printf("\033[%dm %d \033[m", cor_borda, num_linha--);

        for (j = 0; j < 8; ++j)
        {
            if ((i + j) % 2 == 0) cor_atual = cor_tabuleiro[0];
            else cor_atual = cor_tabuleiro[1];

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
        printf("\033[%dm  \033[m\n", cor_borda);
    }
    printf ("\033[%dm    a  b  c  d  e  f  g  h   \033[m\n", cor_borda);
}

int atributo(struct Soldado *peca, enum id_atributo atributo)
{
    if (peca != NULL)
        if (atributo == NOME) return peca->nome;
        else if (atributo == COR) return peca->cor;
        else if (atributo == CAPTURADA) return peca->capturada;
        else if (atributo == ESPECIAL) return peca->movimento_especial;
    else return 50;
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

void peao(struct Soldado *tabuleiro[8][8], coord crd)
{
    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int pular_2_casas=False;
    int actl = ol, actc = oc;
    int adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
    int movimento = (tabuleiro[ol][oc]->cor == BRANCA) ? ol - dl : dl - ol;

    if (ol == 1 || ol == 6) pular_2_casas = True;

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

void torre(struct Soldado *tabuleiro[8][8], coord crd)
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
    struct Soldado *p_torre = tabuleiro[ol][oc], *p_peca = tabuleiro[dl][dc];

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

    if (livre)
    {
        if (tabuleiro[dl][dc] == NULL || adversario == cor_adversario)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
            if (roque) roque = False;
        }
    }
    
    if ((leste || oeste) && p_peca != NULL && roque)
    {
        auxc = oc;
        while (auxc < 3 || auxc > 5)
        {
            if (oc == 0) auxc++;
            else auxc--;
            if (tabuleiro[dl][auxc] != NULL)
            {
                livre = False;
                break;
            }
        }
        if (livre && p_peca->nome == REI)
        {
            roque = False;
            tabuleiro[ol][oc] = NULL;
            tabuleiro[dl][dc] = NULL;
            auxc = (oc == 0) ? 3 : 5;
            tabuleiro[dl][auxc] = p_torre;
            auxc = (oc == 0) ? 2 : 6;
            tabuleiro[dl][auxc] = p_peca;
        }
    }
}

void cavalo(struct Soldado *tabuleiro[8][8], coord crd)
{
    printf("\033[2;35HCAVALO\033[1H");

    int ol = crd.origem_linha;
    int oc = crd.origem_coluna;
    int dl = crd.destino_linha;
    int dc = crd.destino_coluna;
    int adversario = atributo(tabuleiro[dl][dc], COR);
    int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
    int auxl = ol - dl;
    int auxc = oc - dc;
    int mover = tabuleiro[dl][dc] == NULL || adversario == cor_adversario;

    if (auxl == 2 || auxl == -2)
    {
        if ((auxc == 1 || auxc == -1) && mover)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
    else if (auxl == 1 || auxl == -1)
    {
        if ((auxc == 2 || auxc == -2) && mover)
        {
            tabuleiro[dl][dc] = tabuleiro[ol][oc];
            tabuleiro[ol][oc] = NULL;
        }
    }
}

void bispo(struct Soldado *tabuleiro[8][8], coord crd)
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

void rainha(struct Soldado *tabuleiro[8][8], coord crd)
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

void rei(struct Soldado *tabuleiro[8][8], coord crd)
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
    int mover_vertical = (oc - dc == 1 || oc - dc == -1);
    int mover_horizontal = (ol - dl == 1 || ol - dl == -1);

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

void mover_peca(struct Soldado *tabuleiro[8][8], coord crd)
{
    int peca, ol, oc;

    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    peca = atributo(tabuleiro[ol][oc], NOME);

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
}
