#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define SUBGRIDSIZE 3
#define EMPTY 0
#define RECORDS_FILE "records.txt"

// Função para exibir o grid
void exibirGrid(int grid[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        if (i % SUBGRIDSIZE == 0 && i != 0) {
            printf("- - - - - - - - - - - -\n");
        }
        for (int j = 0; j < SIZE; j++) {
            if (j % SUBGRIDSIZE == 0 && j != 0) {
                printf("| ");
            }
            if (grid[i][j] == EMPTY) {
                printf(". ");
            } else {
                printf("%d ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para verificar se um número pode ser colocado na posição (linha, coluna)
int podeColocar(int grid[SIZE][SIZE], int linha, int coluna, int num) {
    // Verificar a linha
    for (int i = 0; i < SIZE; i++) {
        if (grid[linha][i] == num) {
            return 0;
        }
    }
    
    // Verificar a coluna
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][coluna] == num) {
            return 0;
        }
    }

    // Verificar o quadrante 3x3
    int startRow = linha - linha % SUBGRIDSIZE;
    int startCol = coluna - coluna % SUBGRIDSIZE;
    for (int i = startRow; i < startRow + SUBGRIDSIZE; i++) {
        for (int j = startCol; j < startCol + SUBGRIDSIZE; j++) {
            if (grid[i][j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Função para resolver o Sudoku usando backtracking
int resolverSudoku(int grid[SIZE][SIZE]) {
    int linha, coluna;
    int num;
    int encontrado = 0;

    for (linha = 0; linha < SIZE; linha++) {
        for (coluna = 0; coluna < SIZE; coluna++) {
            if (grid[linha][coluna] == EMPTY) {
                for (num = 1; num <= SIZE; num++) {
                    if (podeColocar(grid, linha, coluna, num)) {
                        grid[linha][coluna] = num;
                        if (resolverSudoku(grid)) {
                            return 1;
                        }
                        grid[linha][coluna] = EMPTY;
                    }
                }
                return 0; // Se nenhum número é válido, retorna 0
            }
        }
    }

    return 1; // Sudoku resolvido
}

// Função para gerar um Sudoku válido com uma solução única
void gerarSudoku(int grid[SIZE][SIZE]) {
    // Inicializar o grid com zeros
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = EMPTY;
        }
    }

    // Preencher o grid usando backtracking
    resolverSudoku(grid);

    // Remover alguns valores para criar um Sudoku com pistas
    int numRemovidos = 0;
    while (numRemovidos < SIZE * SIZE / 2) { // Remover metade das células
        int linha = rand() % SIZE;
        int coluna = rand() % SIZE;
        if (grid[linha][coluna] != EMPTY) {
            grid[linha][coluna] = EMPTY;
            numRemovidos++;
        }
    }
}

// Função para escolher a dificuldade
int dificuldade() {
    int dif;
    printf("Escolha a dificuldade:\n");
    printf("1. Fácil\n");
    printf("2. Médio\n");
    printf("3. Difícil\n");
    scanf("%d", &dif);
    return dif;
}

// Função para ajustar o nível de dificuldade
void level(int dif, int grid[SIZE][SIZE]) {
    gerarSudoku(grid);

    int numPistas;
    switch (dif) {
        case 1: // Fácil
            numPistas = SIZE * SIZE / 2; // 50% preenchido
            break;
        case 2: // Médio
            numPistas = SIZE * SIZE * 2 / 3; // ~67% preenchido
            break;
        case 3: // Difícil
            numPistas = SIZE * SIZE * 5 / 6; // ~83% preenchido
            break;
        default:
            numPistas = SIZE * SIZE / 2; // Padrão fácil
            break;
    }

    // Remover algumas pistas para ajustar a dificuldade
    int numRemovidos = SIZE * SIZE - numPistas;
    while (numRemovidos > 0) {
        int linha = rand() % SIZE;
        int coluna = rand() % SIZE;
        if (grid[linha][coluna] != EMPTY) {
            grid[linha][coluna] = EMPTY;
            numRemovidos--;
        }
    }
}

// Função para remover numeros
void removerNumeros(int grid[SIZE][SIZE], char continuar) {
    int linha, coluna, num;
    char continuarAlterando;

    if(continuar == 's' || continuar == 'S'){
        do{
            exibirGrid(grid);

            printf("Digite a linha (0-8): ");
            scanf("%d", &linha);
            printf("Digite a coluna (0-8): ");
            scanf("%d", &coluna);
            printf("Digite o número (1-9): ");
            scanf("%d", &num);

            if (linha < 0 || linha >= SIZE || coluna < 0 || coluna >= SIZE || num < 1 || num > SIZE) {
                printf("Entrada inválida. Tente novamente.\n");
                continue;
            }else{
                for(int i = 0; i<SIZE; i++){
                    for(int j= 0; j <SIZE; j++){
                        if(grid[i][j] == num){
                            grid[i][j] = num;
                        }
                    }
                }

            }

            printf("Deseja fazer mais alteracoes? (s/n): ");
            scanf("%c", &continuarAlterando);

        }while (continuarAlterando == 's' || continuarAlterando == 'S');
    }

}
// Função para permitir que o usuário jogue
void jogar(int grid[SIZE][SIZE]) {
    int linha, coluna, num;
    char continuar, continuarAlterando;
    
    do {
        exibirGrid(grid);

        printf("Digite a linha (0-8): ");
        scanf("%d", &linha);
        printf("Digite a coluna (0-8): ");
        scanf("%d", &coluna);
        printf("Digite o número (1-9): ");
        scanf("%d", &num);

        if (linha < 0 || linha >= SIZE || coluna < 0 || coluna >= SIZE || num < 1 || num > SIZE) {
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        if (grid[linha][coluna] == EMPTY) {
            if (podeColocar(grid, linha, coluna, num)) {
                grid[linha][coluna] = num;
            } else {
                printf("Número inválido para essa posição. Tente novamente.\n");
            }
        } else {
            printf("A célula já está preenchida. Tente novamente.\n");
        }

        printf("Deseja continuar? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    printf("Deseja fazer alguma alteracao? ");
    scanf("%c", &continuarAlterando);

    removerNumeros(grid, continuarAlterando);

    printf("Jogo encerrado.\n");
}



// Função para exibir o menu e obter a escolha do usuário
int menu(char *nome) {
    int escolha = 0;

    printf("***************************************\n");
    printf("*                                     *\n");
    printf("*           Escreva seu nick          *\n");
    printf("*                                     *\n");
    printf("***************************************\n");
    printf("\n-> ");
    scanf(" %s", nome);
    printf("\n*\n\n\n\n");

    printf("******** Seja bem vindo %s ********\n", nome);
    printf("*                                     *\n");
    printf("********* Escolha o modo de jogo ******\n");
    printf("*                                     *\n");
    printf("*     1 Novo jogo                     *\n");
    printf("*     2 Escolher jogo                 *\n");
    printf("*     3 Ranking                       *\n");
    printf("*     4 Sair                          *\n");
    printf("*                                     *\n");
    printf("***************************************\n");
    printf("*\n\n");
    scanf("%d", &escolha);

    return escolha;
}

// Função para escolher um jogo (não implementada)
void escolherJogo() {
    printf("Função para escolher um jogo (não implementada).\n");
}

// Função para mostrar ranking
void mostrarRanking() {
    FILE *file = fopen(RECORDS_FILE, "r");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo de records.\n");
        return;
    }

    char nome[100];
    int tempo;

    printf("Ranking atual:\n");
    while (fscanf(file, "%s %d", nome, &tempo) != EOF) {
        printf("%s - %d segundos\n", nome, tempo);
    }

    fclose(file);
}

// Função para atualizar e salvar records
void records(char *nome, int tempo) {
    FILE *file = fopen(RECORDS_FILE, "a");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo de records.\n");
        return;
    }

    fprintf(file, "%s %d\n", nome, tempo);
    fclose(file);
}

// Função para lidar com o tempo do jogo atual (exemplo simplificado)
int tempoJogo() {
    // Simular o tempo de jogo (em segundos)
    // No código real, você deve calcular o tempo real
    int tempo = rand() % 300; // Tempo aleatório entre 0 e 299 segundos
    return tempo;
}

int main() {
    int dif = 0, opcaoMenu = 0;
    int grid[SIZE][SIZE];
    char nome[100];

    srand(time(0)); // Inicializar o gerador de números aleatórios

    while (opcaoMenu != 4) {
        opcaoMenu = menu(nome);

        if (opcaoMenu == 1) {
            dif = dificuldade();
            level(dif, grid);
            jogar(grid);
            int tempo = tempoJogo();
            printf("Seu tempo: %d segundos\n", tempo);
            records(nome, tempo);
        } else if (opcaoMenu == 2) {
            escolherJogo();
        } else if (opcaoMenu == 3) {
            mostrarRanking();
        } else if (opcaoMenu == 4) {
            printf("***************************************\n");
            printf("*            OBRIGADO POR JOGAR       *\n");
            printf("***************************************\n");
        } else {
            printf("*             ERRO 404                *\n\n");
        }
    }

    return 0;
}