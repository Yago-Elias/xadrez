// Definindo constantes para cada peça de xadrez com base na tabela Unicode
#define TRUE 1
#define FALSE 0
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

enum Config {CONFIG, MENU, JOGAR};

// Estrutura para definir uma peça de xadrez
typedef struct Soldado {
    int peca_nome, peca_cor;
} soldado;

// menu do jogo
int menu ();

// configurações relacionadas a interface do jogo
void configurar ();

// função responsável por inicializar o tabuleiro de xadrez
void inicializar ();

/*
com base na entrada do usuário a função retorna a "linha" e "coluna" da matriz, correspondente 
a posição ou ao movimento da peça de xadrez
*/
void coordenada ();

// funçao que movimenta as peças no tabuleiro
void mover_peca ();

// mostra o tabuleiro de xadrez
void interface ();

// inicia o jogo
void execute();
