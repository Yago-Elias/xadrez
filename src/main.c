#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int main() {
    soldado *tabuleiro[8][8] = {NULL};
    soldado peca_b[16];
    soldado peca_p[16];
    coordenada_peca coord;
    int linha, des_linha, i, j, executa=1, fim_partida=1, opc_menu;
    int cor_tabuleiro[] = {104, 44}, cor_borda=45;
    char coluna, des_coluna;

    while (executa)
    {
        if (fim_partida)
        {
            opc_menu = menu (&executa);
            inicializar (tabuleiro, peca_b, peca_p);
        }
        
        if (opc_menu == 1)
        {
            interface (tabuleiro, cor_tabuleiro, cor_borda);
            fim_partida = 0;
            printf("\nLANCE: ");
            scanf(" %c%d%c%d", 
            &coord.coluna_origem, &coord.linha_origem, &coord.coluna_destino, &coord.linha_destino);
            coordenada (coord);
            mover_peca (tabuleiro, coord);
        }
        else if (opc_menu == 2)
        {
            configurar (cor_tabuleiro, &cor_borda);
            fim_partida = 1;
        }
        else if (opc_menu == 3)
        {
            printf ("SAINDO DO JOGO");
            sleep (2);
            exit (0);
        }
    }
    return 0;
}
