# Lista 07 - Algoritmos Paralelos
## Questão 01
<b>Estude e apresente como as primitivas de paralelismo spawn, sync, and parallel for podem ser relacionadas com o padrão e modelo de programação OpenMP.</b>
<br>
<br>
O modelo de programação fork-join é uma forma de configurar e executar programas em paralelo de tal forma que a execução das tarefas concorrentes juntam-se (join) em um ponto subsequente, onde a execução passa a ser sequencial.

O livro usa três palavras-chaves para descrever um algoritmo paralelo fork-join: parallel, spawn e sync. Ao tirar essas palavras, ainda temos um algoritmo funcional, porém de forma serial.

 O spawn permite que subrotinas sejam executadas em paralelo ao fluxo principal do programa. Em pseudocódigo, `spawn` é usado para "desmembrar" tarefas que podem ser executadas simultaneamente com a tarefa pai. No openMP, podemos usar o `#pragma omp task`, onde o sistema de runtime gerencia a distribuição das tarefas entre as threads disponíveis.
 

```C
#pragma omp parallel
{
    #pragma omp single
    {
        #pragma omp task
        task1();
        #pragma omp task
        task2();
    }
}

```
Por sua vez, o sync garante que todas as tarefas criadas por spawn sejam concluídas antes de prosseguir (join). No openMp podemos fazer isso com o #pragma omp barrier ou o #pragma omp taskwait .

```C
#pragma omp parallel
{
    #pragma omp single
    {
        #pragma omp task
        task1();
        #pragma omp task
        task2();
        #pragma omp barrier 
    }
}

```
O parallel for tem uma diretiva de mesmo nome no openMP, ele especifica que as iterações do laço seguinte podem ser executadas em paralelo. Isso elimina a necessidade de usar o spawn a cada iteração.

```C
#pragma omp parallel for
for (int i = 0; i < n; i++) {
    tasks(i);
}
```
## Questão 02
<b>Escolha um dos algoritmos que já implementou nas listas anteriores que poderiam se beneficiar de paralelismo e implemente-os utilizando OpenMP.</b>
<br>
<br>
Vamos paralelizar a multiplicação de matrizes que vimos nos primeiros capítulos. Para fins de simplificação, vamos mostrar apenas a parte que foi paralelizada:
```C
#pragma omp parallel for collapse(2)
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        result[i][j] = 0;
        for (int k = 0; k < p; k++) {
            result[i][j] += A[i][k] * B[k][j];
        }
    }
}

```
O programa recebe um tamanho n e gera, de forma aleatória, duas matrizes quadradas de tamanho n, A e B. depois as matrizes são multiplicadas pelos laços alinhados, cada elemento da multiplicação sendo armazenado na matriz `result` , que é inicializada com zero.

A diretiva `#pragma omp parallel for collapse(2)` no openMP é usada para paralelizar um laço aninhado (neste caso, dois laços `for`). A cláusula `collapse(2)` faz com que o compilador combine dois loops aninhados em um único loop, pois o normal é que o openMP paralelize apenas o primeiro.

## Questão 03
<b>Apresente uma análise experimental do algoritmo implementado na questão 2 utilizando o NPAD para realizar suas medições.</b>
<br>
<br>

Para fazer a análise do nosso algoritmo implementado na questão 2, vamos fazer testes com um aumento exponencial do número de threads (1, 2, 4, 8, 16, 32, 64, 128) e um aumento do tamanho do problema (100, 250, 500, 1000, 1500, 2000, 2500).

![image](https://github.com/user-attachments/assets/8c400447-dad6-49b1-b16f-8c40bb837591)

![image](https://github.com/user-attachments/assets/16a00766-6a0b-4030-833b-99015fbf4741)

![image](https://github.com/user-attachments/assets/8db383b7-49bc-4414-979a-30141ee6de22)

Com esses resultados, podemos gerar diferentes visualizações. Começando pelo mais simples, que é um gráfico de linhas comum, onde cada curva corresponde a um número de threads.

![image](https://github.com/user-attachments/assets/975e92d7-cda1-494a-b7e4-83761d4087a2)

Outra visualização interessante é o mesmo gráfico de linhas, sendo que ao invés de usar o tempo de execução, vamos usar o speedup (tempo com 1 thread/ tempo com n threads).

![image](https://github.com/user-attachments/assets/7e57b4f3-acdb-464c-b03b-33d4258aeaeb)

Vamos também analisar a eficiência (speedup/ n de threads):

![image](https://github.com/user-attachments/assets/bfb94050-b2ba-485b-bf95-4f9ec83d5ed2)



