#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int run=TRUE, end_game=FALSE;
int linha_origem_ent, linha_destino_ent, linha_destino, coluna_destino;
int cor_tabuleiro[] = {104, 44}, cor_borda=45;
char coluna_origem_ent, coluna_destino_ent;
soldado *tabuleiro[8][8] = {0};
soldado peca_b[16];
soldado peca_p[16];

int menu ()
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
    printf("\033[1J\033[1;1H");

    if (opc_menu == 1)
        return JOGAR;
    else if (opc_menu == 2)
        return CONFIG;
    else if (opc_menu == 3)
        run = FALSE;
}

void coordenada ()
{
    switch (coluna_origem_ent)
    {
        case 'a':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 0;
        break;
        case 'b':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 1;
        break;
        case 'c':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 2;
        break;
        case 'd':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 3;
        break;
        case 'e':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 4;
        break;
        case 'f':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 5;
        break;
        case 'g':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 6;
        break;
        case 'h':
            linha_destino = 8 - linha_origem_ent;
            coluna_destino = 7;
        break;
        default:
            printf("valor inválido\n"); // return ERRO_COLUNA_INVALIDA
    }
}

void inicializar ()
{
    int peca;

    for (peca = 0; peca < 16; peca++)
    {
        peca_b[peca].peca_nome = peca + 1;
        peca_p[peca].peca_nome = peca + 1;

        peca_b[peca].peca_cor = 0;
        peca_p[peca].peca_cor = 1;

        if (peca < 8)
        {
            tabuleiro[0][peca] = &peca_p[peca+8];
            tabuleiro[1][peca] = &peca_p[peca];
            tabuleiro[6][peca] = &peca_b[peca];
            tabuleiro[7][peca] = &peca_b[peca+8];
        }
    }
}

/*
int move_vertical(soldado *tabuleiro[8][8], int ori_i, char ori_j, int des_i, int des_j)
{
    int peca, cor_peca, linha, coluna;
    int limite_des, casa_livre;

    coordenada (ori_i, ori_j, &linha, &coluna);
    limite_des = des_i >= 0 && des_j >= 0;

    printf ("origem  [%d, %d]\ndestino [%d, %d]\nlimite %d\n", linha, coluna, des_i, des_j, limite_des);

    cor_peca = tabuleiro[linha][coluna]->peca_cor;
    peca = tabuleiro[linha][coluna]->peca_nome;
    casa_livre = tabuleiro[des_i][des_j] == NULL;

    if (cor_peca == 0)
    {
        if (limite_des)
        {
            if ((peca > 0 && peca < 9) && casa_livre && des_i == linha - 1 && des_j == coluna)
            {
                printf ("---> FRENTE <---\n");
                sleep (1);
                tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                tabuleiro[linha][coluna] = 0;
            }
            else if (tabuleiro[des_i][des_j]->peca_cor == 1)
            {
                printf("entrou\n");
                sleep (1);
                if (des_i == linha - 1 && des_j == coluna + 1)
                {
                    printf ("---> DIA DIR <---\n");
                    sleep (1);
                    tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                    tabuleiro[linha][coluna] = 0;
                }
                else if (des_i == linha - 1 && des_j == coluna - 1)
                {
                    printf ("---> DIA ESQ <---\n");
                    sleep (1);
                    tabuleiro[des_i][des_j] = tabuleiro[linha][coluna];
                    tabuleiro[linha][coluna] = 0;
                }
            }
            else
                printf("Movimento inválido\n");
        }
        else
        {
            printf("Movimento inválido\n");
            sleep (1);
        }
    }
}

int move_horizontal(soldado *tabuleiro[8][8], int ori_i, char ori_j, int des_i, int des_j)
{

}

int move_diagonal(soldado *tabuleiro[8][8], int ori_i, char ori_j, int des_i, int des_j)
{

}
*/
void mover_peca ()
{
    int peca, cor_peca, linha, coluna;
    int limite_des, d_linha, d_coluna, casa_livre;

    coordenada ();
    limite_des = linha_destino >= 0 && coluna_destino >= 0;
    linha = linha_origem_ent;
    coluna = coluna_origem_ent;
    d_linha = linha_destino;
    d_coluna = coluna_destino;

    printf ("origem  [%d, %d]\ndestino [%d, %d]\nlimite %d\n", linha, coluna, d_linha, d_coluna, limite_des);

    cor_peca = tabuleiro[linha][coluna]->peca_cor;
    peca = tabuleiro[linha][coluna]->peca_nome;
    casa_livre = tabuleiro[d_linha][d_coluna] == NULL;

    if (cor_peca == 0)
    {
        if (limite_des)
        {
            if ((peca > 0 && peca < 9) && casa_livre && d_linha == linha - 1 && d_coluna == coluna)
            {
                printf ("---> FRENTE <---\n");
                sleep (1);
                tabuleiro[d_linha][d_coluna] = tabuleiro[linha][coluna];
                tabuleiro[linha][coluna] = 0;
            }
            else if (tabuleiro[d_linha][d_coluna]->peca_cor == 1)
            {
                printf("entrou\n");
                sleep (1);
                if (d_linha == linha - 1 && d_coluna == coluna + 1)
                {
                    printf ("---> DIA DIR <---\n");
                    sleep (1);
                    tabuleiro[d_linha][d_coluna] = tabuleiro[linha][coluna];
                    tabuleiro[linha][coluna] = 0;
                }
                else if (d_linha == linha - 1 && d_coluna == coluna - 1)
                {
                    printf ("---> DIA ESQ <---\n");
                    sleep (1);
                    tabuleiro[d_linha][d_coluna] = tabuleiro[linha][coluna];
                    tabuleiro[linha][coluna] = 0;
                }
            }
            else
                printf("Movimento inválido\n");
        }
        else
        {
            printf("Movimento inválido\n");
            sleep (1);
        }
    }
    else
    {
        /* ========================== MOVIMENTO DAS PEÇAS BRANCAS ========================== */
        printf("branca\n");
        sleep (1);
    }
}

int inverte_cor (int i, int j)
{
    if ((i + j) % 2 == 0)
        // cor mais clara, exemplo (44 + 60)
        return cor_tabuleiro[0];
    else
        //cor mais escura, exemplo (104 - 60)
        return cor_tabuleiro[1];
}

void configurar ()
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
        cor_borda = 40;
        printf ("Tema 1 selecionado.\n");
        break;
    case 2:
        cor_tabuleiro[0] = 103;
        cor_tabuleiro[1] = 43;
        cor_borda = 46;
        printf ("Tema 2 selecionado.\n");
        break;
    case 3:
        cor_tabuleiro[0] = 104;
        cor_tabuleiro[1] = 44;
        cor_borda = 45;
        printf ("Tema 3 selecionado.\n");
        break;
    case 4:
        cor_tabuleiro[0] = 106;
        cor_tabuleiro[1] = 46;
        cor_borda = 44;
        printf ("Tema 4 selecionado.\n");
        break;
    }
    sleep (2);
    system ("clear");
}

void interface ()
{
    int i, j, num_linha=8, cor_tabuleiro_atual;

    printf("\033[1J\033[1;1H");
    sleep (0.5);
    printf ("\n\033[%dm                             \033[m\n", cor_borda);
    
    for (i = 0; i < 8; ++i)
    {
        printf ("\033[%dm %d \033[m", cor_borda, num_linha);
        num_linha -= 1;

        for (j = 0; j < 8; ++j)
        {
            cor_tabuleiro_atual = inverte_cor (i, j);
            //printf ("%d", cor_tabuleiro);

            if (tabuleiro[i][j] != NULL)
            {
                if (tabuleiro[i][j]->peca_cor == 0)
                {
                    //----------------------------  peças brancas  ----------------------------
                    switch (tabuleiro[i][j]->peca_nome)
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
                        case torre_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                        break;
                        case torre_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_TORRE);
                        break;
                        case bispo_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                        break;
                        case bispo_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_BISPO);
                        break;
                        case rainha:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_RAINHA);
                        break;
                        case rei:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_REI);
                        break;
                        case cavalo_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                        break;
                        case cavalo_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, B_CAVALO);
                        break;
                    }
                }
                else
                {
                    //----------------------------  peças pretas  ----------------------------
                    switch (tabuleiro[i][j]->peca_nome)
                    {
                        //----------------------------  peças brancas  ----------------------------
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
                        case torre_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                        break;
                        case torre_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_TORRE);
                        break;
                        case bispo_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                        break;
                        case bispo_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_BISPO);
                        break;
                        case rainha:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_RAINHA);
                        break;
                        case rei:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_REI);
                        break;
                        case cavalo_r:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                        break;
                        case cavalo_d:
                            printf("\033[%dm\033[30m %s \033[m", cor_tabuleiro_atual, P_CAVALO);
                        break;
                    }
                }
            }
            else
                printf("\033[%dm   \033[m", cor_tabuleiro_atual);
        }
        printf("\033[%dm  \033[m\n", cor_borda);
    }
    printf ("\033[%dm    a  b  c  d  e  f  g  h   \033[m\n", cor_borda);
}

void execute()
{
    int opc_menu;

    while (run)
    {
        if (end_game)
        {
            opc_menu = menu();
            inicializar();
        }
        
        if (opc_menu == 1)
        {
            interface();
            end_game = FALSE;
            printf("\nLANCE: ");
            scanf(" %c%d%c%d", 
            &coluna_origem_ent, &linha_origem_ent, &coluna_destino_ent, &linha_destino_ent);
            coordenada();
            mover_peca();
        }
        else if (opc_menu == 2)
        {
            configurar();
            end_game = TRUE;
        }
        else if (opc_menu == 3)
        {
            printf("SAINDO DO JOGO");
            sleep(2);
            exit(0);
        }
    }
}