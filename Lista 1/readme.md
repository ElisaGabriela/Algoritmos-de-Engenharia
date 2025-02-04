# Lista 01
 ## Questão 1
 <b>Escreva um pseudocódigo para a busca linear e mostre, usando invariância de laço, que o seu algoritmo está correto. </b>

 Busca linear é um algoritmo simples utilizado para encontrar um elemento em um array (ou lista). O algoritmo percorre o array do primeiro ao último elemento, verificando elemento a elemento se o elemento atual é o que se está procurando.

Sendo:

- i - posição inicial do nosso array
- x - elemento que estamos procurando
- A[] - array que vamos percorrer
- n - tamanho total do array que deve ser percorrido

Temos:

```
i = 1 
Enquanto i <= n, faça: // enquanto não chega no fim do array
	se A[i] == x: // verifica se o valor que se
	// quer achar está naquela posição
		retorna i // achou o valor 
	i = i + 1 // vai checar a próxima posição
retorna nada // se chegar aqui, 
//é porque o x não está no array

```

Uma invariante de laço é uma afirmação que é verdadeira no inicio de qualquer iteração de laço, durante e no fim de todas as iterações, e essa condição ajuda a mostrar que o algoritmo vai produzir o resultado esperado.

* Antes de cada iteração do laço ‘Enquanto i <= n, faça:’ , o elemento não foi encontrado nas primeiras i-1 = 0 posições, o que é verdade, pois não verificamos nenhuma posição ainda.
* Para a i-ésima iteração do laço, se A[i] == x, o laço termina, e encontramos o elemento correto. Se não, incrementamos i e vamos para a próxima iteração.
* O algoritmo termina se A[i] == x, onde o elemento procurado é encontrado, ou se não existem mais elementos em A, sendo que a invariante x não pertence a A[n] se mantém verdadeira para ambos os casos.

## Questão 2
<b>Implemente o algoritmo de ordenação por inserção e crie uma cópia anotada dele que mede o número de operações no modelo da Random Access Machine (RAM, seção 2.2 livro do Cormen). Usando entradas de tamanho crescente, mostre em um gráfico quando o tempo de execução no modelo RAM diverge de medições feitas em uma máquina real. </b>

A ordenação por inserção (ou insertion sort) é um algoritmo simples de ordenação que constrói uma lista ou array ordenado de forma gradual, um elemento de cada vez.

O algoritmo começa no segundo elemento do array A[1], e compara com o primeiro elemento A[0]. Se o elemento 2 for menor, ele é movido para frente. Em seguida, comparamos o tereiro elemento A[3], com os dois primeiros, e é inserido na sua colocação. Assim se segue para todos os elementos do array. Ou seja, todos os elementos são comparados com todos os elementos anteriores até se encontrar a posição correta que deve ser inserido.

``` python

def insertion_sort(A):
    for j in range(1, len(A)):
        key = A[j]
        i = j - 1
        while i >= 0 and A[i] > key:
            A[i + 1] = A[i]
            i = i - 1
        A[i + 1] = key
    return A


```
No modelo RAM, consideramos cada operação básica um custo unitário. As operações são:

- comparações
- movimentações
- atribuições

No caso do algoritmo de insertion sort, vamos considerar uma comparação toda vez que passar pelo laço while, uma movimentação sempre que um valor de A[i] é movido para A[i+1] e uma atribuição quando um valor é atribuido a uma variável.

```Python
def insertion_sort_annotated(A):
    qnt_operacoes = 0
    for j in range(1, len(A)): # 3
        qnt_operacoes = qnt_operacoes + 3
        key = A[j] # 2
        qnt_operacoes = qnt_operacoes + 2
        i = j - 1 # 2
        qnt_operacoes = qnt_operacoes + 2
        while i >= 0 and A[i] > key: # 3
            qnt_operacoes = qnt_operacoes + 3
            A[i + 1] = A[i]  # 3
            qnt_operacoes = qnt_operacoes + 3
            i -= 1 # 2
            qnt_operacoes = qnt_operacoes + 2

        A[i + 1] = key #2
        qnt_operacoes = qnt_operacoes + 2
    
    print(qnt_operacoes)
    return

```
Usando a biblioteca python time , vamos medir o tempo real que usamos para rodar a função insertion_sort e comparar com as contagens de operações do RAM. Os tamanhos testados serão: 
500, 1000, 1500, 2500, 5000, 10000, 15000, 100000

Agora fazendo a contagem de operações de RAM:

| Entrada     | Tempo (s)  | Qnt_operações |
|-------------|------------|---------------|
| A[ 500 ]    | 0.0249     | 485035        |
| A[ 1000 ]   | 0.0977     | 1977039       |
| A[ 1500 ]   | 0.2121     | 4359563       |
| A[ 2500 ]   | 0.6060     | 12210923      |
| A[ 5000 ]   | 2.6452     | 49150439      |
| A[ 10000 ]  | 10.7847    | 198088879     |
| A[ 15000 ]  | 23.4518    | 446618111     |
| A[ 100000 ] | 1210.5580  | 19822742591   |

![img](https://i.imgur.com/EVNBV3z.png)

## Questão 3

<b>Mostre numericamente com suas implementações dos algoritmos de insertion-sort e merge-sort como se comporta o desempenho de cada algoritmo utilizando entradas de tamanho crescente, considerando entradas de pior caso, melhor caso e caso médio. Análise, para cada tipo de entrada, se existe algum ponto a partir do qual um algoritmo passa a ser mais rápido que o outro. </b>

A ordenação por inserção (ou insertion sort) é um algoritmo simples de ordenação que constrói uma lista ou array ordenado de forma gradual, um elemento de cada vez.

O algoritmo começa no segundo elemento do array A[1], e compara com o primeiro elemento A[0]. Se o elemento 2 for menor, ele é movido para frente. Em seguida, comparamos o tereiro elemento A[3], com os dois primeiros, e é inserido na sua colocação. Assim se segue para todos os elementos do array. Ou seja, todos os elementos são comparados com todos os elementos anteriores até se encontrar a posição correta que deve ser inserido.

```python
def insertion_sort(A):
    for j in range(1, len(A)):
        key = A[j]
        i = j - 1
        while i >= 0 and A[i] > key:
            A[i + 1] = A[i]
            i = i - 1
        A[i + 1] = key
    return A

```
O merge sort funciona como um tipo de dividir para conquistar. A ideia base dele é separar a lista em várias listas menores e depois que tudo tiver separado, unir de forma ordenada. 

Então para o algoritmo, vamos dividir primeiro a lista na metade (isso se o tamanho do vetor for maior que 1). e vamos ter o lado direito e o lado esquerdo. e então, vamos aplicar o merge sort no lado esquerdo e direito, de forma recursiva.

Vamos usar 3 indices: i - para percorrer left_half, j - para percorrer right_half e o k para percorrer a lista original A, onde os elementos ordenados vão ser armazenados.

O primeiro while compara os elementos das duas primeiras metades enquanto i e j estiverem dentro dos limites das suas sublistas

dentro do loop. o algoritmo verifica se o elemento atual de left_half é menor do que o elemento atual de right_half, se for, o elemento de left_half é copiado para posição k, e então i e k são incrementados. Caso contrário, o elemento de right_half é copiado para A[k], e j e k são incrementados. Esse processo continua até que um dos índices alcance o final de sua respectiva sublista.

Após essa mistura, pode haver elementos restantes em uma das sublistas. Os próximos dois while loops garantem que todos os elementos restantes sejam copiados para a lista original A.

```python
def merge_sort(A):
    if len(A) > 1:
        mid = len(A) // 2
        left_half = A[:mid]
        right_half = A[mid:]
        
        merge_sort(left_half)
        merge_sort(right_half)
        
        i = j = k = 0
        
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                A[k] = left_half[i]
                i += 1
            else:
                A[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            A[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            A[k] = right_half[j]
            j += 1
            k += 1

    return A
```

* Melhor caso: A lista já está ordenada
* Pior caso: Lista ordenada de forma inversa
* Caso médio: Lista aleatória

Entradas utilizadas: A[1000], A[1500], A[10000], A[15000] e A[100000]

Primeiro vamos testar o melhor caso::::

| Tamanho da entrada | insertion_sort | merge_sort |
|--------------------|----------------|------------|
| A[1000]            | 0.0            | 0.0029     |
| A[1500]            | 0.0            | 0.0075     |
| A[10000]           | 0.0039         | 0.0311     |
| A[15000]           | 0.0020         | 0.0720     |
| A[100000]          | 0.0147         | 0.4191     |


Agora vamos testar o pior caso:


| Tamanho da entrada | insertion_sort | merge_sort |
|--------------------|----------------|------------|
| A[1000]            | 0.0914         | 0.0020     |
| A[1500]            | 0.1622         | 0.0119     |
| A[10000]           | 6.7533         | 0.0288     |
| A[15000]           | 15.7051        | 0.0759     |
| A[100000]          | 721.5004       | 0.4122     |

Por fim, o caso médio:

| Tamanho da entrada | insertion_sort | merge_sort |
|--------------------|----------------|------------|
| A[1000]            | 0.0458         | 0.0030     |
| A[1500]            | 0.0988         | 0.0070     |
| A[10000]           | 3.5332         | 0.0426     |
| A[15000]           | 9.4463         | 0.0713     |
| A[100000]          | 347.6270       | 0.5694     |

Portanto, temos:

![img](https://i.imgur.com/u1ObFcq.png)

O insetion sort se destaca no melhor caso pois só precisa ‘percorrer’ a lista uma vez, enquanto o merge sort precisa repatir a lista.
