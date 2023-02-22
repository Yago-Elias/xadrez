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
enum id_atributo {NOME, COR, CAPTURADA, ESPECIAL};

typedef struct Coordenada
{
    int origem_linha, origem_coluna;
    int destino_linha, destino_coluna;
} coord;

struct Soldado {
    int nome, cor, capturada, movimento_especial;
};

extern int roque;

// menu do jogo
int menu ();

// configurações relacionadas a interface do jogo
void configurar (int cor_tabuleiro[]);

// função responsável por inicializar o tabuleiro de xadrez
void inicializar (struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[]);

// converte as coordenadas da entrada do usuário para os índices corretos da matriz
void coordenada (int linha, char coluna, int *destino_linha, int *destino_coluna);

// funçao que movimenta as peças no tabuleiro
void mover_peca (struct Soldado *tabuleiro[8][8], coord crd);

// mostra o tabuleiro de xadrez
void interface (struct Soldado *tabuleiro[8][8], int cor_tabuleiro[]);

// regra en passant
void reiniciar_en_passant(struct Soldado *tabuleiro[8][8], int adversario);

// busca a posição atual do rei
coord localiza_rei (struct Soldado *tabuleiro[8][8], int cor);

// xeque da peça torre
int xeque_torre (struct Soldado *tabuleiro[8][8], coord posicao, int cor);

// xeque da peça bispo
int xeque_bispo (struct Soldado *tabuleiro[8][8], coord posicao, int cor);

// xeque da peça cavalo
int xeque_cavalo (struct Soldado *tabuleiro[8][8], coord posicao, int cor);

// xeque da peça peao
int xeque_peao (struct Soldado *tabuleiro[8][8], coord posicao, int cor);

// xeque da peça rainha
int xeque_rainha (struct Soldado *tabuleiro[8][8], coord posicao, int cor);

// rei em xeque
int em_xeque (struct Soldado *tabuleiro[8][8], coord posicao, int cor);

// rei em xeque mate
int xeque_mate (struct Soldado *tabuleiro[8][8], coord posicao_rei);