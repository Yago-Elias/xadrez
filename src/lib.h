#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define True 1
#define False 0
#define B_REI    "\u2654"
#define B_RAINHA "\u2655"
#define B_TORRE  "\u2656"
#define B_BISPO  "\u2657"
#define B_CAVALO "\u2658"
#define B_P      "\u2659"
#define P_REI    "\u265a"
#define P_RAINHA "\u265b"
#define P_TORRE  "\u265c"
#define P_BISPO  "\u265d"
#define P_CAVALO "\u265e"
#define P_P      "\u265f"

enum id_peca {PEAO=1, TORRE, CAVALO, BISPO, RAINHA, REI};
enum id_jogo {JOGAR=1, CONFIG, SAIR, BRANCA, PRETA};
enum id_atributo {NOME, COR, CAPTURADA, ESPECIAL};

typedef struct Coordenada
{
    int origem_linha, origem_coluna;
    int destino_linha, destino_coluna;
} Coordenada;

typedef struct Peca {
    int nome, cor, capturada, movimento_especial;
} Peca;

typedef struct Cor
{
    int cor_1, cor_2, borda;
} Cor;

// menu do jogo
int menu();

// configurações de cores da interface do jogo
void configurar(Cor *cor);

// função responsável por inicializar o tabuleiro de xadrez
void inicializar(Peca *tabuleiro[8][8], Peca pb[], Peca pp[]);

// converte as coordenadas da entrada do usuário para os índices corretos da matriz
void coordenada(int linha, char coluna, int *destino_linha, int *destino_coluna);

// funçao que movimenta as peças no tabuleiro
void mover_peca(Peca *tabuleiro[8][8], Coordenada crd);

// mostra o tabuleiro de xadrez
void interface(Peca *tabuleiro[8][8], Cor cor);

// regra en passant
void reiniciar_en_passant(Peca *tabuleiro[8][8], int adversario);

// busca a posição atual do rei
Coordenada localiza_rei(Peca *tabuleiro[8][8], int cor);

// xeque da peça torre
int xeque_torre(Peca *tabuleiro[8][8], Coordenada posicao, int cor);

// xeque da peça bispo
int xeque_bispo(Peca *tabuleiro[8][8], Coordenada posicao, int cor);

// xeque da peça cavalo
int xeque_cavalo(Peca *tabuleiro[8][8], Coordenada posicao, int cor);

// xeque da peça peao
int xeque_peao(Peca *tabuleiro[8][8], Coordenada posicao, int cor);

// xeque da peça rainha
int xeque_rainha(Peca *tabuleiro[8][8], Coordenada posicao, int cor);

// rei em xeque
int em_xeque(Peca *tabuleiro[8][8], Coordenada posicao, int cor);

// rei em xeque mate
int xeque_mate(Peca *tabuleiro[8][8], Coordenada posicao_rei);

// inicializa de fato o jogo
void execute();
