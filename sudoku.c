    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    #define SIZE 9
    #define SUBGRIDSIZE 3
    #define EMPTY 0
    #define RECORDS_FILE "records.txt"

    // Função para exibir o grid
    void exibirGrid(int grid[SIZE][SIZE])
    {
        printf("\n");
        printf(" --------------------------------\n");
                printf(" *           SUDOKU            *\n");
                printf(" --------------------------------\n");
        for (int i = 0; i < SIZE; i++)
        {
            if (i % SUBGRIDSIZE == 0 && i != 0){   

                printf(" --------------------------------\n");
            }
            for (int j = 0; j < SIZE; j++)
            {
                if (j % SUBGRIDSIZE == 0 && j != 0)
                {
                    printf(" | ");
                }
                if (grid[i][j] == EMPTY)
                {
                    printf(" . ");
                }
                else
                {
                    printf(" %d ", grid[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    // Função para verificar se um número pode ser colocado na posição (linha, coluna)
    int podeColocar(int grid[SIZE][SIZE], int linha, int coluna, int num)
    {
        // Verificar a linha
        for (int i = 0; i < SIZE; i++)
        {
            if (grid[linha][i] == num)
            {
                return 0;
            }
        }

        // Verificar a coluna
        for (int i = 0; i < SIZE; i++)
        {
            if (grid[i][coluna] == num)
            {
                return 0;
            }
        }

        // Verificar o quadrante 3x3
        int startRow = linha - linha % SUBGRIDSIZE;
        int startCol = coluna - coluna % SUBGRIDSIZE;
        for (int i = startRow; i < startRow + SUBGRIDSIZE; i++)
        {
            for (int j = startCol; j < startCol + SUBGRIDSIZE; j++)
            {
                if (grid[i][j] == num)
                {
                    return 0;
                }
            }
        }

        return 1;
    }

    // Função para verificar o numero usando backtracking
    int resolverSudoku(int grid[SIZE][SIZE])
    {
        int linha, coluna;
        int num;
        int encontrado = 0;

        for (linha = 0; linha < SIZE; linha++)
        {
            for (coluna = 0; coluna < SIZE; coluna++)
            {
                if (grid[linha][coluna] == EMPTY)
                {
                    for (num = 1; num <= SIZE; num++)
                    {
                        if (podeColocar(grid, linha, coluna, num))
                        {
                            grid[linha][coluna] = num;
                            if (resolverSudoku(grid))
                            {
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
    void gerarSudoku(int grid[SIZE][SIZE])
    {
        // Inicializar o grid com zeros
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                grid[i][j] = EMPTY;
            }
        }

        // Preencher o grid usando backtracking
        resolverSudoku(grid);

        // Remover alguns valores para criar um Sudoku com pistas
        int numRemovidos = 0;
        while (numRemovidos < SIZE * SIZE / 2)
        { // Remover metade das células
            int linha = rand() % SIZE;
            int coluna = rand() % SIZE;
            if (grid[linha][coluna] != EMPTY)
            {
                grid[linha][coluna] = EMPTY;
                numRemovidos++;
            }
        }
    }

int verificarSudoku(int grid[SIZE][SIZE])
{
    int numeros[SIZE];
    
    // Verificar linhas e colunas
    for (int i = 0; i < SIZE; i++)
    {
        // Reinicializar o array de verificação
        for (int j = 0; j < SIZE; j++) numeros[j] = 0;

        // Verificação da linha
        for (int j = 0; j < SIZE; j++)
        {
            int num = grid[i][j];
            if (num < 1 || num > SIZE || numeros[num - 1] != 0)
            {
                return 0; // Número inválido ou repetido na linha
            }
            numeros[num - 1] = 1;
        }

        // Reinicializar o array de verificação para a coluna
        for (int j = 0; j < SIZE; j++) numeros[j] = 0;

        // Verificação da coluna
        for (int j = 0; j < SIZE; j++)
        {
            int num = grid[j][i];
            if (num < 1 || num > SIZE || numeros[num - 1] != 0)
            {
                return 0; // Número inválido ou repetido na coluna
            }
            numeros[num - 1] = 1;
        }
    }

    // Verificar subgrades 3x3
    for (int linha = 0; linha < SIZE; linha += 3)
    {
        for (int coluna = 0; coluna < SIZE; coluna += 3)
        {
            // Reinicializar o array de verificação para a subgrade
            for (int j = 0; j < SIZE; j++) numeros[j] = 0;

            // Verificação da subgrade
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int num = grid[linha + i][coluna + j];
                    if (num < 1 || num > SIZE || numeros[num - 1] != 0)
                    {
                        return 0; // Número inválido ou repetido na subgrade
                    }
                    numeros[num - 1] = 1;
                }
            }
        }
    }

    return 1; // Sudoku válido
}


    // Função para escolher a dificuldade
    int dificuldade()
    {
        int dif;
        printf(" ----------------------------\n");
        printf(" *  Escolha a dificuldade:  *\n");
        printf(" ----------------------------\n");
        printf(" *                          *\n");
        printf(" *        1. Facil          *\n");
        printf(" *        2. Medio          *\n");
        printf(" *        3. Dificil        *\n");
        printf(" *                          *\n");
        printf(" ----------------------------\n\n");
        printf(" -> ");
        scanf("%d", &dif);
        return dif;
    }

    // Função para ajustar o nível de dificuldade
    void level(int dif, int grid[SIZE][SIZE])
    {
        gerarSudoku(grid);

        int numPistas;
        switch (dif)
        {
        case 1:                          // Fácil
            numPistas = SIZE * SIZE * 2 / 3; // ~67% preenchido
            break;
        case 2:                              // Médio
            numPistas = SIZE * SIZE * 2 / 2; // 50% preenchido
            break;
        case 3:                              // Difícil
            numPistas = SIZE * SIZE * 5 / 6; // ~83% preenchido
            break;
        default:
            numPistas = SIZE * SIZE / 2; // Padrão fácil
            break;
        }

        // Remover algumas pistas para ajustar a dificuldade
        int numRemovidos = SIZE * SIZE - numPistas;
        while (numRemovidos > 0)
        {
            int linha = rand() % SIZE;
            int coluna = rand() % SIZE;
            if (grid[linha][coluna] != EMPTY)
            {
                grid[linha][coluna] = EMPTY;
                numRemovidos--;
            }
        }
    }

    // Função pra remover nmrs

    int removerNumeros(int grid[SIZE][SIZE]){
        int linha, coluna;
        char continuarRemovendo; 
        do
        {
            printf(" Digite a linha a ser alterada (0-8): ");
            printf("\n -> ");
            scanf("%d", &linha);
            printf(" Digite a coluna a ser alterada(0-8): ");
            printf("\n -> ");
            scanf("%d", &coluna);
            
             if (grid[linha][coluna] != EMPTY)
            {
                grid[linha][coluna] = EMPTY;
                exibirGrid(grid);
                printf("\nNumero removido.");
            }
            else
            {
                printf("\n A celula já está vazia. Tente novamente.");
                continue;
            }

                printf("\n Deseja continuar removendo? (s/n)");
                printf("\n -> ");
                scanf(" %c", &continuarRemovendo);
                if(continuarRemovendo == 'n' || continuarRemovendo == 'N'){
                    return 0;
                }
        
        } while (continuarRemovendo == 'S' || continuarRemovendo == 's');
    }
       

    // Função para permitir que o usuário jogue
    int jogar(int grid[SIZE][SIZE])
    {
        int linha, coluna, num;
        char continuarJogando, removerNum;
        
        exibirGrid(grid);


        do
        {
            printf("Digite a linha (0-8): ");
            printf("\n -> ");
            scanf("%d", &linha);
            printf("Digite a coluna (0-8): ");
            printf("\n -> ");
            scanf("%d", &coluna);
            printf("Digite o numero (1-9): ");
            printf("\n -> ");
            scanf("%d", &num);


            if (linha < 0 || linha >= SIZE || coluna < 0 || coluna >= SIZE || num < 1 || num > SIZE)
            {
                printf("Entrada invalida. Tente novamente.\n");
                continue;
            }

            if (grid[linha][coluna] == EMPTY)
            {
                grid[linha][coluna] = num;
                exibirGrid(grid);
            }
            else
            {
                printf("\n A celula ja esta preenchida. Tente novamente.\n");
                continue;
            }

            do
            {
                printf("\n Deseja remover algum numero? (s/n): ");
                printf("\n -> ");
                scanf(" %c", &removerNum);

                if (removerNum == 's' || removerNum == 'S'){
                    removerNumeros(grid);
                    break;
                }
                if (removerNum == 'n' || removerNum == 'N')
                {
                    break;
                } else {
                    printf("\n Caracter invalido. Tente Novamente.");
                }

            } while (removerNum == 's' || removerNum == 'S');

            do{
                printf("\n Deseja continuar jogando? (s/n): \n");
                printf("\n -> ");
                scanf(" %c", &continuarJogando);
                
                    if (continuarJogando == 'n' || continuarJogando == 'N'){
                    char verificar;
                    
                    printf("\n Deseja verificar o sudoku? ");
                    printf("\n -> ");
                    scanf(" %c", &verificar);
                    if(verificar == 's' || verificar == 'S'){
                        for(int i = 0; i < SIZE; i++){
                            for(int j = 0; j < SIZE; j++){
                                if(grid[i][coluna] == EMPTY || grid[linha][j] == EMPTY){
                                    printf("\n Jogo incompleto. Tente Novamente.\n");
                                    break;
                                }
                                if(grid[i][coluna] != EMPTY && grid[linha][j] != EMPTY){
                                    int verificar = verificarSudoku(grid);
                                        if(verificar == 1){
                                            printf("\n Sudoku preenchido com sucesso!");
                                            return 1;
                                        } else {
                                            printf("\n Sudoku incorreto.");
                                            return 0;
                                        }                          
                                }
                            }
                        }
                        
                    } 

                    return 0;
                }
                    if (continuarJogando == 's' || continuarJogando == 'S'){
                        break;
                    }
                    else{
                        printf("\n Entrada invalida. Tente novamente.");
                        continue;
                    }
            } while (continuarJogando != 's' && continuarJogando != 'S');

        } while (continuarJogando == 's' || continuarJogando == 'S');
    }

    // Função para exibir o menu e obter a escolha do usuário
    int menu(char *nome)
    {
        int escolha = 0;

        printf("\n -> Ola %s! \n\n", nome);
        printf(" --------------------------------------\n");
        printf(" ---------------- Menu ----------------\n");
        printf(" *                                    *\n");
        printf(" *       1. Novo jogo                 *\n");
        printf(" *       2. Escolher jogo             *\n");
        printf(" *       3. Ranking                   *\n");
        printf(" *       4. Sair                      *\n");
        printf(" *                                    *\n");
        printf(" --------------------------------------\n\n");
        printf(" -> ");
        scanf("%d", &escolha);
        printf("\n");

        return escolha;
    }

    // Função para escolher um jogo (não implementada)
    void escolherJogo()
    {
        printf("Função para escolher um jogo (não implementada).\n");
    }

    // Função para mostrar ranking
    void mostrarRanking()
    {
        FILE *file = fopen(RECORDS_FILE, "r");
        if (file == NULL)
        {
            printf("Não foi possível abrir o arquivo de records.\n");
            return;
        }

        char nome[100];
        int tempo;

        printf("Ranking atual:\n");
        while (fscanf(file, "%s %d", nome, &tempo) != EOF)
        {
            printf("%s - %d segundos\n", nome, tempo);
        }

        fclose(file);
    }

    // Função para atualizar e salvar records
    void records(char *nome, int tempo)
    {
        FILE *file = fopen(RECORDS_FILE, "a");
        if (file == NULL)
        {
            printf("Não foi possível abrir o arquivo de records.\n");
            return;
        }

        fprintf(file, "%s %d\n", nome, tempo);
        fclose(file);
    }

    int main()
    {
        int dif = 0, opcaoMenu = 0;
        int grid[SIZE][SIZE];
        srand(time(0)); // Inicializar o gerador de números aleatórios
        FILE *nome;
        char nick[25];

        nome = fopen("nome.txt", "w");
        if (nome == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
        }  
        printf("\n"); 
        printf(" -----------------------------------------\n");
        printf(" *                                       *\n");
        printf(" *            Insira seu nick            *\n");
        printf(" *                                       *\n");
        printf(" -----------------------------------------\n");
        printf("\n-> ");
        scanf(" %s", &nick);
        fprintf(nome, "%s", nick);
        fclose(nome);
        printf("\n");
        while (opcaoMenu != 4)
        {
            opcaoMenu = menu(nick);

            if (opcaoMenu == 1)
            {
                dif = dificuldade();
                level(dif, grid);
                clock_t start_time = clock();
                jogar(grid);
                clock_t end_time = clock();

                int tempo = (int)(end_time - start_time) / CLOCKS_PER_SEC;
                printf("Seu tempo: %d segundos\n", tempo);
                records(nick, tempo);
            }
            else if (opcaoMenu == 2)
            {
                escolherJogo();
            }
            else if (opcaoMenu == 3)
            {
                mostrarRanking();
            }
            else if (opcaoMenu == 4)
            {
                printf(" --------------------------------------\n");
                printf("*      >>  OBRIGADO POR JOGAR  <<     *\n");
                printf(" --------------------------------------\n");
            }
            else
            {   
                printf(" --------------------------------------\n");
                printf("*           >> ERRO 404 <<            *\n\n");
                printf(" --------------------------------------\n");
            }
        }

        return 0;
    }