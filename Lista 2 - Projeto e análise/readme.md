# Lista 02 - Projeto e análise

## Questão 1
<b> 
Mostre numericamente com suas implementações dos algoritmos de multiplicação de matrizes que o algoritmo de Strassen é mais rápido que o algoritmo convencional.
</b>
O algoritmo convencional de matrizes pode ser observado abaixo:

```python
def multiplicacao_convencional(A, B):
    C = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]
    for i in range(len(A)):  
        for j in range(len(B[0])):  
            for k in range(len(B)):  
                C[i][j] += A[i][k] * B[k][j]
    
    return C
```

A função multiplicacao_convencional implementa o algoritmo clássico de multiplicação de matrizes, onde cada elemento da matriz resultante é calculado como a soma dos produtos dos elementos correspondentes de A e B.

```python
def strassen(A, B):
    n = len(A)
    if n == 1:
        return A * B

    mid = n // 2
    A11 = A[:mid, :mid]
    A12 = A[:mid, mid:]
    A21 = A[mid:, :mid]
    A22 = A[mid:, mid:]

    B11 = B[:mid, :mid]
    B12 = B[:mid, mid:]
    B21 = B[mid:, :mid]
    B22 = B[mid:, mid:]

    M1 = strassen(A11 + A22, B11 + B22)
    M2 = strassen(A21 + A22, B11)
    M3 = strassen(A11, B12 - B22)
    M4 = strassen(A22, B21 - B11)
    M5 = strassen(A11 + A12, B22)
    M6 = strassen(A21 - A11, B11 + B12)
    M7 = strassen(A12 - A22, B21 + B22)

    C11 = M1 + M4 - M5 + M7
    C12 = M3 + M5
    C21 = M2 + M4
    C22 = M1 - M2 + M3 + M6

    C = np.zeros((n, n))
    C[:mid, :mid] = C11
    C[:mid, mid:] = C12
    C[mid:, :mid] = C21
    C[mid:, mid:] = C22

    return C
```

```python
def strassen_multiply(A, B):

    A = np.array(A)
    B = np.array(B)
    n = max(A.shape[0], A.shape[1], B.shape[0], B.shape[1])
    m = 2**int(np.ceil(np.log2(n)))
    A_pad = np.zeros((m, m))
    B_pad = np.zeros((m, m))
    A_pad[:A.shape[0], :A.shape[1]] = A
    B_pad[:B.shape[0], :B.shape[1]] = B
    C_pad = strassen(A_pad, B_pad)
    return C_pad[:A.shape[0], :B.shape[1]]
```
* A função começa verificando o tamanho de A. Se for uma matriz de 1x1 (caso base), multiplica os dois números diretamente.
* A matriz A (e B) é dividida em quadrantes. Se A for uma matriz 4x4, por exemplo, os quadrantes são 2x2.
* A11, A12, A21 e A22 são as quatro submatrizes de A. O mesmo acontece com B11, B12, B21 e B22 para B.
* São calculados 7 produtos intermediários, M1 a M7, usando combinações dos quadrantes de A e B. Cada produto é calculado recursivamente usando o próprio algoritmo de Strassen. Isso é uma parte importante do método, pois reduz o número de multiplicações necessárias em comparação à multiplicação convencional.
* Após calcular M1 a M7, os quadrantes da matriz resultante C são obtidos combinando esses valores de acordo com as fórmulas acima. Estes cálculos resultam na composição da matriz resultante após a multiplicação.
* A matriz resultante C é construída unindo os quadrantes C11, C12, C21, e C22 em uma matriz de tamanho n x n.
* a matriz C, que é o produto de A e B de acordo com o método de Strassen, é retornada.

Foram geradas matrizes aleatórias de diferentes tamanhos, para entender em que casos a implementação por Strassen se destaca.

| Tamanho  | Tempo (s) - Strassen | Tempo (s) - convencional |
|----------|----------------------|--------------------------|
| A[1]     | 0.000000             | 0.000000                 |
| A[2]     | 0.000512             | 0.000000                 |
| A[4]     | 0.000000             | 0.000541                 |
| A[5]     | 0.003772             | 0.004482                 |
| A[8]     | 0.009346             | 0.000000                 |
| A[10]    | 0.024350             | 0.001257                 |
| A[16]    | 0.028963             | 0.011273                 |
| A[32]    | 0.234402             | 0.055154                 |
| A[64]    | 1.415057             | 0.445314                 |
| A[100]   | 9.192576             | 1.388547                 |
| A[128]   | 9.551798             | 3.372339                 |
| A[256]   | 66.614134            | 9.551798                 |
| A[1000]  | 3066.775945          | 1400.275653              |

![img](https://i.imgur.com/ixzD2u8.png)

## Questão 2
<b>
Escolha um algoritmo recorrente para aplicar um dos 4 métodos de resolução de recorrência descritos no capítulo 4 para medir o custo da recorrência do algoritmo escolhido. 
</b>

O método mestre fornece uma receita para resolver recorrências na forma:

$$
T(n) = aT\left(\frac{n}{b}\right) + f(n)
$$

O custo da recorrência do algoritmo de Strassen pode ser dado pela relação descrita abaixo:

$$
T(n) = 7T\left(\frac{n}{2}\right) + \Theta(n^2)
$$

Para essa recorrência, temos \( a = 7 \), \( b = 2 \) e $$\( f(n) = \Theta(n^2) \)$$. Portanto, temos que:

$$
\log_b a = \log_2 7 \approx 2.81
$$

Como $$\( f(n) = \Theta(n^2) \)$$, temos a seguinte parte do teorema mestre:

Se $$\( f(n) = O\left(n^{\log_b a - \epsilon}\right) \)$$ para alguma constante $$\( \epsilon > 0 \)$$, então $$\( T(n) = \Theta\left(n^{\log_b a}\right) \)$$.

Ou seja, para esse caso, o tempo de execução será dominado pelas recursões, e então, podemos definir que:

$$
T(n) = O\left(n^{\log_b a}\right)
$$

Então a solução para a recorrência do algoritmo de Strassen é:

$$
T(n) = O\left(n^{\log_2 7}\right) \approx O\left(n^{2.81}\right)
$$

## Questão 3
<b>
O problema de balanceamento de cargas busca atribuir tarefas de tamanhos diferentes a trabalhadores, de modo a minimizar a carga máxima que um trabalhador irá executar. Em um problema em que temos n tarefas e k trabalhadores (n > k),  considere que o balanceador irá distribuir as n/k primeiras tarefas para o primeiro trabalhador,  as n/k tarefas seguintes para o segundo trabalhador, e assim por diante. Mostre numericamente como permutar aleatoriamente os dados de entrada, que são as cargas de cada tarefa, pode influenciar na solução desse balanceador.

</b>

* Vamos distribuir n tarefas de diferentes tamanhos entre k trabalhadores, de forma que a carga máxima atribuída a qualquer trabalhador seja minimizada
* Forma sem permutação : as n/k primeiras tarefas são atribuidas ao primeiro trabalhador, n/k tarefas ao segundo e assim por diante:
* Se as tarefas forem permutadas (ou seja, suas cargas forem embaralhadas aleatoriamente), a ordem em que as tarefas são distribuídas entre os trabalhadores muda.

Primeiro teste: 100 tarefas para 4 trabalhadores:

![img](https://i.imgur.com/XnfZ9hH.png)

Segundo teste: 10 tarefas para 4 trabalhadores:

![img](https://i.imgur.com/UD2qkbX.png)

Terceiro teste: 10 mil tarefas para 4 trabalhadores:

![img](https://i.imgur.com/XHULUoa.png)



