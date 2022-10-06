#include <stdio.h>
#include <string.h>
#include "f_26.h"

// função que retorna o índice da matriz de acordo com a linha e coluna
void coordenada (int linha, char coluna, int *i, int *j)
{
    /*
    para cada letra de a-h é associado a um número da coluna equivalente
    a cada letra do tabuleiro
    */
    switch (coluna)
    {
        case 'a':
            *i = 8 - linha;
            *j = 0;
        break;
        case 'b':
            *i = 8 - linha;
            *j = 1;
        break;
        case 'c':
            *i = 8 - linha;
            *j = 2;
        break;
        case 'd':
            *i = 8 - linha;
            *j = 3;
        break;
        case 'e':
            *i = 8 - linha;
            *j = 4;
        break;
        case 'f':
            *i = 8 - linha;
            *j = 5;
        break;
        case 'g':
            *i = 8 - linha;
            *j = 6;
        break;
        case 'h':
            *i = 8 - linha;
            *j = 7;
        break;
        
    }
}

// alterna os valores para a cor de fundo para cada peça
int cor_fundo (int i, int j)
{
    if ((i + j) % 2 == 0)
        return 104;
    else
        return 44;
}

/*
tanto o tabuleiro quanto os vetores onde ficam armazenados os dados das peças,
são inicializados
*/
void inicializar (struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[])
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
        pb[i].cor = cor;

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

    /*
    passa por referência as peças dos vetores para a matriz(tabuleiro), definindo
    as posições iniciais das peças
    */
    for (i = 0; i < 8; ++i)
    {
        tabuleiro[0][i] = &pp[i];
        tabuleiro[1][i] = &pp[i+8];
        tabuleiro[6][i] = &pb[i+8];
        tabuleiro[7][i] = &pb[i];
    }
}

void mover_peca (struct Soldado *tabuleiro[8][8], struct Soldado peca[], int des_i, int des_j)
{
    char cor = tabuleiro[des_i-1][des_j]->nome[0];

    /* ========================== MOVIMENTO DAS PEÇAS PRETAS ========================== */
    if (cor == 'p')
    {
        if (tabuleiro[des_i][des_j] == NULL)
        {
            tabuleiro[des_i][des_j] = &peca[des_i];
            tabuleiro[des_i-1][des_j] = NULL;
        }
        else if (0)
        {
            printf("0");
        }
    }
    else
    {
        /* ========================== MOVIMENTO DAS PEÇAS PRETAS ========================== */
        printf("0");
    }
}

// imprime o tabuleiro na tela
void interface (struct Soldado *tabuleiro[8][8])
{
    int i, j, bg;

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            bg = cor_fundo (i, j);

            /*
            se a posição na matriz for diferente de NULL significa que há uma referência
            para alguma peça
            */
            if (tabuleiro[i][j] != NULL)
            {
                // imprime a cor de fundo de acordo com a cor definida na inicialização
                if (tabuleiro[i][j]->cor == 0)
                {
                    // verifica qual peça está armazenada e imprime de acordo com a mesma
                    if (!strcmp (tabuleiro[i][j]->nome, "p_d"))
                        printf("\033[%dm %s \033[m", bg, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "torre_d"))
                        printf("\033[%dm %s \033[m", bg, B_TORRE);
                    if (!strcmp (tabuleiro[i][j]->nome, "bispo_d"))
                        printf("\033[%dm %s \033[m", bg, B_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "rei"))
                        printf("\033[%dm %s \033[m", bg, B_REI);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_r"))
                        printf("\033[%dm %s \033[m", bg, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "cavalo_r"))
                        printf("\033[%dm %s \033[m", bg, B_CAVALO);

                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_d"))
                        printf("\033[%dm %s \033[m", bg, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_torre_d"))
                        printf("\033[%dm %s \033[m", bg, P_TORRE);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_bispo_d"))
                        printf("\033[%dm %s \033[m", bg, P_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_rei"))
                        printf("\033[%dm %s \033[m", bg, P_REI);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_r"))
                        printf("\033[%dm %s \033[m", bg, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_cavalo_r"))
                        printf("\033[%dm %s \033[m", bg, P_CAVALO);
                }
                else
                {
                    if (!strcmp (tabuleiro[i][j]->nome, "p_d"))
                        printf("\033[%dm %s \033[m", bg, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "cavalo_d"))
                        printf("\033[%dm %s \033[m", bg, B_CAVALO);
                    if (!strcmp (tabuleiro[i][j]->nome, "rainha"))
                        printf("\033[%dm %s \033[m", bg, B_RAINHA);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_r"))
                        printf("\033[%dm %s \033[m", bg, B_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "bispo_r"))
                        printf("\033[%dm %s \033[m", bg, B_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "torre_r"))
                        printf("\033[%dm %s \033[m", bg, B_TORRE);

                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_d"))
                        printf("\033[%dm %s \033[m", bg, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_cavalo_d"))
                        printf("\033[%dm %s \033[m", bg, P_CAVALO);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_rainha"))
                        printf("\033[%dm %s \033[m", bg, P_RAINHA);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_p_r"))
                        printf("\033[%dm %s \033[m", bg, P_P);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_bispo_r"))
                        printf("\033[%dm %s \033[m", bg, P_BISPO);
                    if (!strcmp (tabuleiro[i][j]->nome, "p_torre_r"))
                        printf("\033[%dm %s \033[m", bg, P_TORRE);
                }
            }
            else
                printf("\033[%dm   \033[m", bg); // imprime apenas a cor da casa 
        }
        printf("\n");
    }
}
