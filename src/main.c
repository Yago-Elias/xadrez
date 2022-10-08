#include <stdio.h>
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
    int linha, des_linha, i, j;

    /*
    peca receberá uma letra que representa cada peça, coluna equivale a letra que representa
    cada coluna do tabuleiro de xadrz, e des_coluna á a coluna de destino da peça
    */
    char peca, coluna, des_coluna;

    while (1)
    {
        // posiciona todas as peças no tabuleiro, no incio da partida
        inicializar (tabuleiro, peca_b, peca_p);

        // lances do jogador
        printf("\nLance: ");
        scanf("%c%c%d%c%d", &peca, &coluna, &linha, &des_coluna, &des_linha);

        // calcula o índice da matriz com relação a linha e coluna
        coordenada (linha, coluna, &i, &j);

        // imprime na tela o tabuleiro e as peças do jogo
        interface (tabuleiro);
    }
    
    return 0;
}
