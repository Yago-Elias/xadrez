#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int menu (int *executa)
{
    int opc_menu;

    printf ("=============================\n");
    printf ("            XADREZ           \n");
    printf ("-----------------------------\n");
    printf ("  \033[5m1          JOGAR\033[m           \n");
    printf ("  2      CONFIGURAÇÃO        \n");
    printf ("  3          SAIR            \n");
    printf ("=============================\n>");

    scanf (" %d", &opc_menu);
    system ("clear");

    if (opc_menu == 1)
        return 1;
    else if (opc_menu == 2)
        return 2;
    else if (opc_menu == 3)
        *executa = 0;
    else
        return 3;
}

void coordenada (int linha, char coluna, int *linha_dest, int *coluna_dest)
{
    switch (coluna)
    {
        case 'a':
            *linha_dest = 8 - linha;
            *coluna_dest = 0;
            break;
        case 'b':
            *linha_dest = 8 - linha;
            *coluna_dest = 1;
            break;
        case 'c':
            *linha_dest = 8 - linha;
            *coluna_dest = 2;
            break;
        case 'd':
            *linha_dest = 8 - linha;
            *coluna_dest = 3;
            break;
        case 'e':
            *linha_dest = 8 - linha;
            *coluna_dest = 4;
            break;
        case 'f':
            *linha_dest = 8 - linha;
            *coluna_dest = 5;
            break;
        case 'g':
            *linha_dest = 8 - linha;
            *coluna_dest = 6;
            break;
        case 'h':
            *linha_dest = 8 - linha;
            *coluna_dest = 7;
            break;
    }
}

void inicializar (soldado *tabuleiro[8][8], soldado pb[], soldado pp[])
{
    int i, j, cor = 0;
    
    // preenche o nome das peças
    strcpy (pb[0].nome, "torre_d");
    strcpy (pb[1].nome, "cavalo_d");
    strcpy (pb[2].nome, "bispo_d");
    strcpy (pb[3].nome, "rainha");
    strcpy (pb[4].nome, "rei");
    strcpy (pb[5].nome, "bispo_r");
    strcpy (pb[6].nome, "cavalo_r");
    strcpy (pb[7].nome, "torre_r");
    
    strcpy (pb[8].nome, "p_d");
    strcpy (pb[9].nome, "p_d");
    strcpy (pb[10].nome, "p_d");
    strcpy (pb[11].nome, "p_d");
    strcpy (pb[12].nome, "p_r");
    strcpy (pb[13].nome, "p_r");
    strcpy (pb[14].nome, "p_r");
    strcpy (pb[15].nome, "p_r");

    strcpy (pp[0].nome, "p_torre_d");
    strcpy (pp[1].nome, "p_cavalo_d");
    strcpy (pp[2].nome, "p_bispo_d");
    strcpy (pp[3].nome, "p_rainha");
    strcpy (pp[4].nome, "p_rei");
    strcpy (pp[5].nome, "p_bispo_r");
    strcpy (pp[6].nome, "p_cavalo_r");
    strcpy (pp[7].nome, "p_torre_r");
    
    strcpy (pp[8].nome, "p_p_d");
    strcpy (pp[9].nome, "p_p_d");
    strcpy (pp[10].nome, "p_p_d");
    strcpy (pp[11].nome, "p_p_d");
    strcpy (pp[12].nome, "p_p_d");
    strcpy (pp[13].nome, "p_p_d");
    strcpy (pp[14].nome, "p_p_d");
    strcpy (pp[15].nome, "p_p_d");

    // define o tipo de cor e as posições iniciais das peças
    for (i = 0; i < 16; ++i)
    {
        pp[i].cor = cor;
        pp[i].capturada = 0;
        pb[i].cor = cor;
        pb[i].capturada = 0;

        if (cor)
            cor = 0;
        else
            cor = 1;

        if (i < 8)
        {
            pp[i].linha = 0;
            pp[i].coluna = i;
            pb[i].linha = 0;
            pb[i].coluna = i;
        }
        else
        {
            pp[i].linha = 1;
            pp[i].coluna = i;
            pb[i].linha = 1;
            pb[i].coluna = i;
        }
    }

    for (i = 0; i < 8; ++i)
    {
        tabuleiro[0][i] = &pp[i];
        tabuleiro[1][i] = &pp[i+8];
        tabuleiro[6][i] = &pb[i+8];
        tabuleiro[7][i] = &pb[i];
    }
}

void mover_peca (soldado *tabuleiro[8][8], int ori_i, char ori_j, int des_i, int des_j)
{
    int cor_peca;
    int linha, coluna;

    coordenada (ori_i, ori_j, &linha, &coluna);
    printf ("%d %d %d %d\n", linha, coluna, des_i, des_j);
    cor_peca = tabuleiro[linha][coluna]->cor;

    /* ========================== MOVIMENTO DAS PEÇAS PRETAS ========================== */
    if (cor_peca == 0)
    {
        // movimento do peão a frente
        if (tabuleiro[des_i][des_j] == NULL)
        {
            //tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
            tabuleiro[linha][coluna] = 0;
        }
        else if (tabuleiro[des_i][des_j]->cor == 1)
        {
            if (linha > des_i && coluna > des_j)
                //tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                tabuleiro[linha][coluna] = 0;

            if (linha > des_i && coluna < des_j)
                //tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                tabuleiro[linha][coluna] = 0;
        }
    }
    else
    {
        /* ========================== MOVIMENTO DAS PEÇAS BRANCAS ========================== */
        printf("branca\n");
    }
}

int inverte_cor (int i, int j, int cor_tabuleiro[])
{
    if ((i + j) % 2 == 0)
    {
        // cor mais clara, exemplo (44 + 60)
        return cor_tabuleiro[0];
    }
    else
    {
        //cor mais escura, exemplo (104 - 60)
        return cor_tabuleiro[1];
    }
}

void configurar (int cor_tabuleiro[], int *cor_borda)
{
    int tema;

    printf ("=============================\n");
    printf ("            TEMA             \n");
    printf ("-----------------------------\n");
    printf ("           TEMA 1            \n");
    printf ("           TEMA 2            \n");
    printf ("           TEMA 3            \n");
    printf ("           TEMA 4            \n");
    printf ("=============================\nTEMA>");

    scanf (" %d", &tema);

    switch (tema)
    {
    case 1:
        cor_tabuleiro[0]  = 107;
        cor_tabuleiro[1] = 47;
        *cor_borda = 40;
        printf ("Tema 1 selecionado.\n");
        break;
    case 2:
        cor_tabuleiro[0] = 103;
        cor_tabuleiro[1] = 43;
        *cor_borda = 46;
        printf ("Tema 2 selecionado.\n");
        break;
    case 3:
        cor_tabuleiro[0] = 104;
        cor_tabuleiro[1] = 44;
        *cor_borda = 45;
        printf ("Tema 3 selecionado.\n");
        break;
    case 4:
        cor_tabuleiro[0] = 106;
        cor_tabuleiro[1] = 46;
        *cor_borda = 44;
        printf ("Tema 4 selecionado.\n");
        break;
    }
    sleep (2);
    system ("clear");
}

void interface (soldado *tabuleiro[8][8], int cor_tabuleiro[], int cor_borda)
{
    int i, j, cor_tabuleiro_atual;
    char letra=104;
    system ("clear");
    sleep (0.5);

    printf ("\n\033[%dm                             \033[m\n", cor_borda);
    for (i = 0; i < 8; ++i)
    {
        printf ("\033[%dm %c \033[m", cor_borda, letra);
        letra -= 1;

        for (j = 0; j < 8; ++j)
        {
            cor_tabuleiro_atual = inverte_cor (i, j, cor_tabuleiro);
            //printf ("%d", cor_tabuleiro);

            if (tabuleiro[i][j] != NULL)
            {
                if (tabuleiro[i][j]->cor == 0)
                {
                    if (!strcmp (tabuleiro[i][j]->nome, "p_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "torre_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                    if (!strcmp (tabuleiro[i][j]->nome, "bispo_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "rei"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_REI);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "cavalo_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);

                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_torre_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_bispo_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_rei"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_REI);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_cavalo_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                }
                else
                {
                    if (!strcmp (tabuleiro[i][j]->nome, "p_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "cavalo_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                    if (!strcmp (tabuleiro[i][j]->nome, "rainha"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_RAINHA);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "bispo_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "torre_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);

                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_cavalo_d"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_rainha"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_RAINHA);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_bispo_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_torre_r"))
                        printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                }
            }
            else
                printf("\033[%dm   \033[m", cor_tabuleiro_atual);
        }
        printf("\033[%dm  \033[m\n", cor_borda);
    }
    printf ("\033[%dm    1  2  3  4  5  6  7  8   \033[m\n", cor_borda);
}
