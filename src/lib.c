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
        pb[peca].cor = branca;
        pb[peca].capturada = False;
        pp[peca].nome = peca + 1;
        pp[peca].cor = preta;
        pp[peca].capturada = False;
        if (peca <= 7)
        {
            pb[peca].pular_2_casas = True;
            pp[peca].pular_2_casas = True;
        }
        else
        {
            pb[peca].pular_2_casas = False;
            pp[peca].pular_2_casas = False;
        }
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
                if (tabuleiro[i][j]->cor == branca)
                {
                    switch (tabuleiro[i][j]->nome)
                    {
                    case peao_d_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_d_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_d_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_d_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_r_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_r_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_r_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case peao_r_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                        break;
                    case torre_d:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                        break;
                    case cavalo_d:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                        break;
                    case bispo_d:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                        break;
                    case rei:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_REI);
                        break;
                    case rainha:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_RAINHA);
                        break;
                    case bispo_r:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                        break;
                    case cavalo_r:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                        break;
                    case torre_r:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                        break;
                    }
                }
                else
                {
                    switch (tabuleiro[i][j]->nome)
                    {
                    case peao_d_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_d_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_d_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_d_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_r_1:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_r_2:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_r_3:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case peao_r_4:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                        break;
                    case torre_d:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                        break;
                    case cavalo_d:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                        break;
                    case bispo_d:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                        break;
                    case rei:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_REI);
                        break;
                    case rainha:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_RAINHA);
                        break;
                    case bispo_r:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                        break;
                    case cavalo_r:
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                        break;
                    case torre_r:
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

void frente(struct Soldado *tabuleiro[8][8], int ol, int oc, int dl, int dc)
{
    if (oc == dc && ol > dl)
    {
        tabuleiro[dl][dc] = tabuleiro[ol][oc];
        tabuleiro[ol][oc] = NULL;
    }
}

void peao(struct Soldado *tabuleiro[8][8], int ol, int oc, int dl, int dc)
{
    if (tabuleiro[ol][oc] != NULL && tabuleiro[dl][dc] == NULL)
        {
            printf("\033[4;35HEM FRENTE\033[1H");
            sleep(1);
            if (ol - dl == 1)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                if (tabuleiro[ol][oc]->pular_2_casas)
                    tabuleiro[ol][oc]->pular_2_casas = False;
                tabuleiro[ol][oc] = NULL;
            }
            else if (tabuleiro[ol][oc]->pular_2_casas && ol - dl == 2)
            {
                tabuleiro[dl][dc] = tabuleiro[ol][oc];
                if (tabuleiro[ol][oc]->pular_2_casas)
                    tabuleiro[ol][oc]->pular_2_casas = False;
                tabuleiro[ol][oc] = NULL;
            }
        }
}

void mover_peca(struct Soldado *tabuleiro[8][8], coord crd)
{
    int peca, ol, oc, dl, dc;

    ol = crd.origem_linha;
    oc = crd.origem_coluna;
    dl = crd.destino_linha;
    dc = crd.destino_coluna;
    peca = tabuleiro[ol][oc]->nome;

    if (peca > 0 && peca < 9)
        peao(tabuleiro, ol, oc, dl, dc);
    // else if (peca == torre_d || peca == torre_r)
    // else if (peca == cavalo_d || peca == cavalo_r)
    // else if (peca == bispo_d || peca == bispo_r)
    // else if (peca == rainha)
    // else (peca == rei)
}
