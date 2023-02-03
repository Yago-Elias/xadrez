#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define True 1
#define False 0
#define B_REI "\u2654"
#define B_RAINHA "\u2655"
#define B_TORRE "\u2656"
#define B_BISPO "\u2657"
#define B_CAVALO "\u2658"
#define B_P "\u2659"
#define P_REI "\u265a"
#define P_RAINHA "\u265b"
#define P_TORRE "\u265c"
#define P_BISPO "\u265d"
#define P_CAVALO "\u265e"
#define P_P "\u265f"

enum id_peca {PEAO=1, TORRE, CAVALO, BISPO, RAINHA, REI};
enum id_jogo {JOGAR=1, CONFIG, SAIR, BRANCA, PRETA};
enum id_atributo {NOME, COR, CAPTURADA};

typedef struct Coordenada
{
    int origem_linha, origem_coluna;
    int destino_linha, destino_coluna;
} coord;

struct Soldado {
    int nome, cor, capturada;
};

// menu do jogo
int menu ();

// configurações relacionadas a interface do jogo
void configurar (int cor_tabuleiro[]);

// função responsável por inicializar o tabuleiro de xadrez
void inicializar (struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[]);

/*
com base na entrada do usuário a função retorna a "linha" e "coluna" da matriz, correspondente 
a posição ou ao movimento da peça de xadrez
*/
void coordenada (int linha, char coluna, int *destino_linha, int *destino_coluna);

// funçao que movimenta as peças no tabuleiro
void mover_peca (struct Soldado *tabuleiro[8][8], coord crd);

// mostra o tabuleiro de xadrez
void interface (struct Soldado *tabuleiro[8][8], int cor_tabuleiro[]);
