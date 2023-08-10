#include "lib.h"

int executa = True, fim_partida = True;

int main() 
{
    Peca *tabuleiro[8][8] = {NULL};
    Peca peca_b[16], peca_p[16];
    Cor cor;
    Coordenada coordenadas;
    //int cor_tabuleiro[] = {104, 44, 45};
    int linha, opc_menu;
    char coluna;

    cor.cor_1 = 104;
    cor.cor_2 = 44;
    cor.borda = 45;

    while (executa)
    {
        if (fim_partida)
        {
            inicializar(tabuleiro, peca_b, peca_p);
            opc_menu = menu();
        }
        switch (opc_menu)
        {
            case JOGAR:
                fim_partida = False;
                interface(tabuleiro, cor);
                printf("\nLANCE: ");
                scanf(" %c%d", &coluna, &linha);
                coordenada(linha, coluna, &coordenadas.origem_linha, &coordenadas.origem_coluna);
                scanf(" %c%d", &coluna, &linha);
                coordenada(linha, coluna, &coordenadas.destino_linha, &coordenadas.destino_coluna);
                mover_peca(tabuleiro, coordenadas);
            break;
            case CONFIG:
                configurar(&cor);
                fim_partida = True;
            break;
            case SAIR:
                printf("SAINDO DO JOGO\n");
                exit(EXIT_SUCCESS);
            break;
            default:
                printf("        OPÇÃO INVÁLIDA\n");
        }
    }
}
