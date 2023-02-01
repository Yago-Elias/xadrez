#include "lib.h"

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
        pb[peca].nome = peca + 1;
        pb[peca].cor = BRANCA;
        pb[peca].capturada = False;
        pp[peca].nome = peca + 1;
        pp[peca].cor = PRETA;
        pp[peca].capturada = False;
    }

    for (peca = 0; peca < 8; ++peca)
    {
        tabuleiro[0][peca] = &pp[peca+8];
        tabuleiro[1][peca] = &pp[peca];
        tabuleiro[6][peca] = &pb[peca];
        tabuleiro[7][peca] = &pb[peca+8];
    }
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
    int i, j, num_linha=8, cor_tabuleiro_atual;
    int cor_borda = cor_tabuleiro[2];
    system("clear");
    sleep(0.5);

    printf("\n\033[%dm                             \033[m\n", cor_borda);
    for (i = 0; i < 8; ++i)
    {
        printf("\033[%dm %d \033[m", cor_borda, num_linha--);

        for (j = 0; j < 8; ++j)
        {
            if ((i + j) % 2 == 0) cor_tabuleiro_atual = cor_tabuleiro[0];
            else cor_tabuleiro_atual = cor_tabuleiro[1];

            if (tabuleiro[i][j] != NULL)
            {
                if (tabuleiro[i][j]->cor == BRANCA)
                {
                    switch (tabuleiro[i][j]->nome)
                    {
                    case PEAO_D_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_D_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_D_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_D_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_R_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_R_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_R_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case PEAO_R_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case TORRE_D:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                        break;
                    case CAVALO_D:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                        break;
                    case BISPO_D:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                        break;
                    case REI:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_REI);
                        break;
                    case RAINHA:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_RAINHA);
                        break;
                    case BISPO_R:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                        break;
                    case CAVALO_R:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                        break;
                    case TORRE_R:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                        break;
                    }
                }
                else
                {
                    switch (tabuleiro[i][j]->nome)
                    {
                    case PEAO_D_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_D_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_D_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_D_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_R_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_R_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_R_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case PEAO_R_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case TORRE_D:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                        break;
                    case CAVALO_D:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                        break;
                    case BISPO_D:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                        break;
                    case REI:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_REI);
                        break;
                    case RAINHA:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_RAINHA);
                        break;
                    case BISPO_R:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                        break;
                    case CAVALO_R:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                        break;
                    case TORRE_R:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                        break;
                    }
                }
            }
            else printf("\033[%dm   \033[m", cor_tabuleiro_atual);
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
    else return 50;
}

void peao(struct Soldado *tabuleiro[8][8], coord crd)
{
    int ol, oc, dl, dc, peca, adversario, pular_2_casas = False;
    int move_branca, move_preta, aux;

    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    dl = crd.destino_linha;
    dc = crd.destino_coluna;


    if (tabuleiro[ol][oc] != NULL)
    {
        int pular_2_casas = False;
        int adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;
        int movimento = (tabuleiro[ol][oc]->cor == BRANCA) ? ol - dl : dl - ol;

        if (ol == 1 || ol == 6) pular_2_casas = True;

        if (oc == dc && tabuleiro[dl][dc] == NULL)
        {
            printf("\033[2;35HEM FRENTE\033[1H");
            if (movimento == 1)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
            else if (pular_2_casas && movimento == 2)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (atributo(tabuleiro[dl][dc], COR) == adversario)
        {
            int avanco = (atributo(tabuleiro[ol][oc], COR) == BRANCA) ? ol > dl : ol < dl;

            if (avanco && oc < dc)
            {
                if (ol > dl && oc < dc)
                {
                    tabuleiro[dl][dc] = tabuleiro[ol][oc];
                    tabuleiro[ol][oc] = NULL;
                }
                else if (ol > dl && oc > dc)
                {
                    tabuleiro[dl][dc] = tabuleiro[ol][oc];
                    tabuleiro[ol][oc] = NULL;
                }
            }
            else if (avanco && oc > dc)
            {
                if (ol < dl && oc < dc)
                {
                    tabuleiro[dl][dc] = tabuleiro[ol][oc];
                    tabuleiro[ol][oc] = NULL;
                }
                else if (ol < dl && oc > dc)
                {
                    tabuleiro[dl][dc] = tabuleiro[ol][oc];
                    tabuleiro[ol][oc] = NULL;
                }
            }
        }
    }
}

void torre(struct Soldado *tabuleiro[8][8], coord crd)
{
    int ol, oc, dl, dc;
    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    dl = crd.destino_linha;
    dc = crd.destino_coluna;

    if (tabuleiro[ol][oc] != NULL)
    {
        printf("\033[2;35HTORRE\033[1H");
        int auxl=ol, auxc=oc, adversario, cor_adversario, livre=True;
        int norte, leste, sul, oeste;

        norte = ol > dl && oc == dc;
        leste = ol == dl && oc < dc;
        sul = ol < dl && oc == dc;
        oeste = ol == dl && oc > dc;
        adversario = atributo(tabuleiro[dl][dc], COR);
        cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;

        if (norte)
        {
            while (auxl > dl)
            {
                printf("\033[%d;35HFRENTE [%d, %d]\033[1H", auxl, auxl, auxc);
                auxl--;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            if (livre || (auxl == dl && adversario == cor_adversario))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (sul)
        {
            while (auxl < dl)
            {
                printf("\033[%d;35HTRÁS [%d, %d]\033[1H", auxl, auxl, auxc);
                auxl++;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            if (livre || (auxl == dl && adversario == cor_adversario))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (oeste)
        {
            while (auxc > dc)
            {
                printf("\033[%d;35HESQUERDA [%d, %d]\033[1H", auxl, auxl, auxc);
                auxc--;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            if (livre || (auxc == dc && adversario == cor_adversario))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (leste)
        {
            while (auxc < dc)
            {
                printf("\033[%d;35HESQUERDA [%d, %d]\033[1H", auxl, auxl, auxc);
                auxc++;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            if (livre || (auxc == dc && adversario == cor_adversario))
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
    }
}

void cavalo(struct Soldado *tabuleiro[8][8], coord crd)
{
    int ol, oc, dl, dc;
    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    dl = crd.destino_linha;
    dc = crd.destino_coluna;

    if (tabuleiro[ol][oc] != NULL)
    {
        printf("\033[2;35HCAVALO\033[1H");
        int auxl, auxc, peca, mover;
        int adversario = atributo(tabuleiro[dl][dc], COR);
        int cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;

        auxl = ol - dl;
        auxc = oc - dc;
        mover = tabuleiro[dl][dc] == NULL || adversario == cor_adversario;
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
}

void bispo(struct Soldado *tabuleiro[8][8], coord crd)
{
    int ol, oc, dl, dc;
    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    dl = crd.destino_linha;
    dc = crd.destino_coluna;

    if (tabuleiro[ol][oc] != NULL)
    {
        printf("\033[2;35HBISPO\033[1H");
        int nordeste, sudeste, sudoeste, noroeste;
        int auxl=ol, auxc=oc, adversario, cor_adversario, livre=True, capturar;
        
        nordeste = ol > dl && oc < dc;
        sudeste = ol < dl && oc < dc;
        sudoeste = ol < dc && oc > dc;
        noroeste = ol > dl && oc > dc;
        adversario = atributo(tabuleiro[dl][dc], COR);
        cor_adversario = (tabuleiro[ol][oc]->cor == PRETA) ? BRANCA : PRETA;

        if (nordeste)
        {
            while (auxl > dl && auxc < dc)
            {
                printf("\033[%d;35HSENTIDO NORDESTE[%d, %d]\033[1H", auxl, auxl, auxc);
                auxl--;
                auxc++;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            capturar = (auxl == dl && auxc == dc && adversario == cor_adversario);
            if (livre || capturar)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (sudeste)
        {
            while (auxl < dl && auxc < dc)
            {
                printf("\033[%d;35HSENTIDO SUDESTE[%d, %d]\033[1H", auxl, auxl, auxc);
                auxl++;
                auxc++;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            capturar = (auxl == dl && auxc == dc && adversario == cor_adversario);
            if (livre || capturar)
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
                printf("\033[%d;35HSENTIDO SUDOESTE[%d, %d]\033[1H", auxl, auxl, auxc);
                auxl++;
                auxc--;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            capturar = (auxl == dl && auxc == dc && adversario == cor_adversario);
            if (livre || capturar)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
        else if (noroeste)
        {
            while (auxl > dl && auxc > dc)
            {
                printf("\033[%d;35HSENTIDO NOROESTE[%d, %d]\033[1H", auxl, auxl, auxc);
                auxl--;
                auxc--;
                if (tabuleiro[auxl][auxc] != NULL)
                {
                    livre = False;
                    break;
                }
            }
            capturar = (auxl == dl && auxc == dc && adversario == cor_adversario);
            if (livre || capturar)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                tabuleiro[ol][oc] = NULL;
            }
        }
    }
}

void rainha(struct Soldado *tabuleiro[8][8], coord crd)
{}

void rei(struct Soldado *tabuleiro[8][8], coord crd)
{}

void mover_peca(struct Soldado *tabuleiro[8][8], coord crd)
{
    int peca, ol, oc;

    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    peca = atributo(tabuleiro[ol][oc], NOME);

    if (peca >= PEAO_D_1 && peca <= PEAO_R_4)
        peao(tabuleiro, crd);
    else if (peca == TORRE_D || peca == TORRE_R)
        torre(tabuleiro, crd);
    else if (peca == CAVALO_D || peca == CAVALO_R)
        cavalo(tabuleiro, crd);
    else if (peca == BISPO_D || peca == BISPO_R)
        bispo(tabuleiro, crd);
    // else if (peca == RAINHA)
    //     rainha(tabuleiro, crd);
    // else if (peca == REI)
    //     rei(tabuleiro, crd);
}
