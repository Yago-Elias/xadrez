// Definindo constantes para cada peça de xadrez com base na tabela Unicode
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

enum id_peca {
    peao_d_1=1, peao_d_2, peao_d_3, peao_d_4, peao_r_1, peao_r_2, peao_r_3, peao_r_4,
    torre_d, cavalo_d, bispo_d, rainha, rei, bispo_r, cavalo_r, torre_r
};

// Estrutura para definir uma peça de xadrez
typedef struct Soldado {
    int peca_nome, peca_cor;
} soldado;

typedef struct Coordenada
{
    int linha_origem;
    char coluna_origem;
    int linha_destino, coluna_destino;
} coordenada_peca;


// menu do jogo
int menu (int *executa);

// configurações relacionadas a interface do jogo
void configurar (int cor_tabuleiro[], int *cor_fundo);

// função responsável por inicializar o tabuleiro de xadrez
void inicializar (soldado *tabuleiro[8][8], soldado pb[], soldado pp[]);

/*
com base na entrada do usuário a função retorna a "linha" e "coluna" da matriz, correspondente 
a posição ou ao movimento da peça de xadrez
*/
void coordenada (coordenada_peca coord);

// funçao que movimenta as peças no tabuleiro
void mover_peca (soldado *tabuleiro[8][8], coordenada_peca coord);

// mostra o tabuleiro de xadrez
void interface (soldado *tabuleiro[8][8], int cor_tabuleiro[], int cor_borda);
