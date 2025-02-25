#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Função para inicializar uma matriz com valores aleatórios
void inicializaMatriz(float **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = (float)rand() / RAND_MAX; // Valores entre 0 e 1
        }
    }
}

// Função para alocar memória para uma matriz
float **alocaMatriz(int n) {
    float **matriz = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        matriz[i] = (float *)malloc(n * sizeof(float));
    }
    return matriz;
}

// Função para liberar memória da matriz
void liberaMatriz(float **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numero_de_threads> <tamanho_da_matriz>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[2]);             // Tamanho da matriz
    int num_threads = atoi(argv[1]);   // Número de threads

    // Configura o número de threads do OpenMP
    omp_set_num_threads(num_threads);

    // Aloca as matrizes
    float **A = alocaMatriz(n);
    float **B = alocaMatriz(n);
    float **C = alocaMatriz(n);

    // Inicializa as matrizes A e B com valores aleatórios
    srand(time(NULL));
    inicializaMatriz(A, n);
    inicializaMatriz(B, n);

    double start_time, end_time;

    // Inicia o tempo de execução do laço principal
    start_time = omp_get_wtime();

    // Multiplicação de matrizes com OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    // Finaliza o tempo de execução
    end_time = omp_get_wtime();

    printf("Tempo de execucao do laço principal: %.6f segundos\n", end_time - start_time);

    // Libera a memória alocada
    liberaMatriz(A, n);
    liberaMatriz(B, n);
    liberaMatriz(C, n);

    return 0;
}