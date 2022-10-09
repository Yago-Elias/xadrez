#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int main() {
    // declarando uma matriz de ponteiros para representar o tabuleiro de xadrez
    struct Soldado *tabuleiro[8][8] = {NULL};

    // vetor que guarda as peças brancas
    struct Soldado peca_b[16];

    // vetor que guarda as peças pretas
    struct Soldado peca_p[16];

    /*
    linha representa a posição da peça e des_linha a posição de destino da peça, apenas
    em relação a linha onde se encontra a peça
    */
    int linha, des_linha, i, j, executa=1, fim_partida=1, opc_menu;

    // cores do tabuleiro
    int cor_tabuleiro[] = {104, 44}, cor_borda=45;

    /*
    peca receberá uma letra que representa cada peça, coluna equivale a letra que representa
    cada coluna do tabuleiro de xadrez, e des_coluna á a coluna de destino da peça
    */
    char peca, coluna, des_coluna;

    while (executa)
    {
        if (fim_partida)
        {
            // menu do jogo
            opc_menu = menu (&executa);
            //fim_partida = 0;

            // posiciona todas as peças no tabuleiro, no incio da partida
            inicializar (tabuleiro, peca_b, peca_p);
        }
        
        if (opc_menu == 1)
        {
            // imprime na tela o tabuleiro e as peças do jogo
            interface (tabuleiro, cor_tabuleiro, cor_borda);

            // lances do jogador
            fim_partida = 0;
            printf("\nLANCE: ");
            scanf(" %c%c%d%c%d", &peca, &coluna, &linha, &des_coluna, &des_linha);

            // calcula o índice da matriz com relação a linha e coluna
            coordenada (des_linha, des_coluna, &i, &j);

            // mudar a posição das peças conforme as jogadas
            mover_peca (tabuleiro, linha, coluna, i, j);

            // condição apenas para teste de jogo, ou seja, o jogo não depende dessa condição
            if (peca == 'h')
            {
                system ("clear");
                fim_partida = 1;
            }
        }
        else if (opc_menu == 2)
        {
            // configurações do jogo
            configurar (cor_tabuleiro, &cor_borda);
            fim_partida = 1;
        }
        else if (opc_menu == 3)
        {
            // encerra o jogo
            printf ("SAINDO DO JOGO");
            sleep (2);
            exit (0);
        }
        
        
    }
    
    return 0;
}
