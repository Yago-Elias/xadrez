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

// Estrutura para definir uma peça de xadrez
struct Soldado {
    char nome[10];
    int cor;
    int capturada;
    int linha;
    int coluna;
};

// menu do jogo
int menu (int *executa);

// configurações relacionadas a interface do jogo
void configurar (int cor_tabuleiro[], int *cor_fundo);

// função responsável por inicializar o tabuleiro de xadrez
void inicializar (struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[]);

/*
com base na entrada do usuário a função retorna a "linha" e "coluna" da matriz, correspondente 
a posição ou ao movimento da peça de xadrez
*/
void coordenada (int linha, char coluna, int *i, int *j);

// funçao que movimenta as peças no tabuleiro
void mover_peca (struct Soldado *tabuleiro[8][8], int ori_i, char ori_j, int i, int j);

// mostra o tabuleiro de xadrez
void interface (struct Soldado *tabuleiro[8][8], int cor_tabuleiro[], int cor_borda);
