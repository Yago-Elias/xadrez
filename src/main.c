#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int main() {
    soldado *tabuleiro[8][8] = {NULL};
    soldado peca_b[16];
    soldado peca_p[16];
    int linha_origem, linha_dest, linha, coluna, executa=1, fim_partida=1, opc_menu;
    char coluna_origem, coluna_dest;
    int cor_tabuleiro[] = {104, 44}, cor_borda=45;

    while (executa)
    {
        if (fim_partida)
        {
            opc_menu = menu (&executa);
            //fim_partida = 0;
            inicializar (tabuleiro, peca_b, peca_p);
        }
        
        switch (opc_menu)
        {
            case 1:
                interface (tabuleiro, cor_tabuleiro, cor_borda);
                fim_partida = 0;
                printf("\nLANCE: ");
                scanf(" %c%d%c%d", &coluna_origem, &linha_origem, &coluna_dest, &linha_dest);
                coordenada (linha_dest, coluna_dest, &linha &coluna);
                mover_peca (tabuleiro, linha, coluna, i, j);
                system ("clear");
                break;
            case 2:
                configurar (cor_tabuleiro, &cor_borda);
                fim_partida = 1;
                break;
            case 3:
                printf ("SAINDO DO JOGO");
                sleep (2);
                exit (0);
                break;
            default:
                break;
        }
    }
    return 0;
}
