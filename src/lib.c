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

    // ler a opção 1, 2, ou 3
    scanf (" %d", &opc_menu);
    system ("clear");

    // retorna o número da opção para o main, ou encerra o jogo
    if (opc_menu == 1)
        return 1;
    else if (opc_menu == 2)
        return 2;
    else if (opc_menu == 3)
        *executa = 0;
    else
        return 3;
}

// função que retorna o índice da matriz de acordo com a linha e coluna
void coordenada (int linha, char coluna, int *i, int *j)
{
    /*
    para cada letra de a-h é associado a um número da coluna equivalente
    a cada letra do tabuleiro, e para cada número da linha é calculado o
    índice na matriz que corresponde a "linha" da mesma
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

/*
tanto o tabuleiro quanto os vetores onde ficam armazenados os dados das peças,
são inicializados
*/
void inicializar (struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[])
{
    int peca, cor = 0;

    for (peca = 0; peca < 16; peca++)
    {
        pb[peca].nome = peca + 1;
        pp[peca].nome = peca + 1;

        // define a cor e o estado da peça no jogo
        pp[peca].cor = 1;
        pp[peca].capturada = 0;
        pb[peca].cor = 0;
        pb[peca].capturada = 0;

        if (cor)
            cor = 0;
        else
            cor = 1;
    }

    /*
    passa por referência as peças dos vetores para a matriz(tabuleiro) 8x8, definindo
    as posições iniciais das peças
    */
    for (peca = 0; peca < 8; ++peca)
    {
        tabuleiro[0][peca] = &pp[peca+8];
        tabuleiro[1][peca] = &pp[peca];
        tabuleiro[6][peca] = &pb[peca];
        tabuleiro[7][peca] = &pb[peca+8];
    }
}

void mover_peca (struct Soldado *tabuleiro[8][8], int ori_i, char ori_j, int des_i, int des_j)
{
    int peca, cor_peca;
    int linha, coluna;

    // converte as coordenadas de entrada do usuário em índices para identificar as peças na matriz
    coordenada (ori_i, ori_j, &linha, &coluna);

    printf ("linha %d\ncoluna %d\nlinha destino %d\ncoluna destino %d\n", linha, coluna, des_i, des_j);
    sleep (2);

    cor_peca = tabuleiro[linha][coluna]->cor;
    peca = tabuleiro[linha][coluna]->nome;

    /* ========================== MOVIMENTO DAS PEÇAS PRETAS ========================== */
    if (cor_peca == 1)
    {
        // movimento do peão a frente
        if ((peca > 0 && peca < 9) && tabuleiro[des_i][des_j] == NULL)
        {
            printf ("---> DEU CERTO <---\n");
            sleep (2);
            tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
            tabuleiro[linha][coluna] = 0;
        }
        /* else if (tabuleiro[des_i][des_j]->cor == 1)
        {
            // movimento do peão na diagonal a esquerda para capturar uma peça
            if (linha > des_i && coluna > des_j)
                //tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                //tabuleiro[linha][coluna] = 0;

            // movimento do peão na diagonal a direita para capturar uma peça
            if (linha > des_i && coluna < des_j)
                //tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                //tabuleiro[linha][coluna] = 0;
        } */
    }
    else
    {
        /* ========================== MOVIMENTO DAS PEÇAS BRANCAS ========================== */
        printf("branca\n");
    }
}

// alterna os valores para a cor de fundo para cada casa do tabuleiro
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

// configurações das cores da interface
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

// imprime o tabuleiro na tela
void interface (struct Soldado *tabuleiro[8][8], int cor_tabuleiro[], int cor_borda)
{
    int i, j, num_linha=8, cor_tabuleiro_atual;

    // limpa o termianl
    system ("clear");
    
    // dá uma pequena pausa antes de realizar qualquer operação
    sleep (0.5);

    // imprime a cor da borda superior
    printf ("\n\033[%dm                             \033[m\n", cor_borda);
    for (i = 0; i < 8; ++i)
    {
        // imprime o número da linha no tabuleiro e a cor da borda esquerdo
        printf ("\033[%dm %d \033[m", cor_borda, num_linha);

        // soma com o índice para ir para a próxima letra começando a partir de 'a'
        num_linha -= 1;

        for (j = 0; j < 8; ++j)
        {
            cor_tabuleiro_atual = inverte_cor (i, j, cor_tabuleiro);
            //printf ("%d", cor_tabuleiro);

            /*
            se a posição na matriz for diferente de NULL significa que há uma referência
            para alguma peça
            */
            if (tabuleiro[i][j] != NULL)
            {
                // imprime a peça de acordo com a cor definida na inicialização
                if (tabuleiro[i][j]->cor == 0)
                {

                    switch (tabuleiro[i][j]->nome)
                        {
                        // peças brancas
                        case peao_d_1:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                            break;
                        case peao_d_3:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                            break;
                        case peao_r_1:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                            break;
                        case peao_r_3:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_P);
                            break;
                        case torre_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                            break;
                        case bispo_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                            break;
                        case rei:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_REI);
                            break;
                        case cavalo_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                            break;
                    }
                }
                else
                {
                    //----------------------------  peças pretas  ----------------------------
                    switch (tabuleiro[i][j]->nome)
                    {
                        case peao_d_2:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                            break;
                        case peao_d_4:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                            break;
                        case peao_r_2:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                            break;
                        case peao_r_4:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_P);
                            break;
                        case cavalo_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                            break;
                        case rainha:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_RAINHA);
                            break;
                        case bispo_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                            break;
                        case torre_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                            break;
                    }
                }
            }
            else
                // imprime apenas a cor da casa do tabuleiro
                printf("\033[%dm   \033[m", cor_tabuleiro_atual);
        }
        // imprime a cor da borda direito
        printf("\033[%dm  \033[m\n", cor_borda);
    }
    // imprime os núemro das colunas e também a cor da borda inferior
    printf ("\033[%dm    a  b  c  d  e  f  g  h   \033[m\n", cor_borda);
}
