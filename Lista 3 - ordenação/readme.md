# Lista 03 - Ordenação
## Questão 1
<b>Implemente as funções da seção 6.5 do livro do Cormen 4th Ed. em sua linguagem favorita e proponha um exemplo de uso com uma demonstração. </b>
<br>
<br>
A primeira função que precisamos implementar é a de max_heapify, que garante a propriedade de heap máximo, onde o filho deve ser menor que o pai.

- A função recebe como parâmetros o vetor A, o index do elemento que será comparado e o tamanho da heap.
- Ela calcula a posição do filho a direita e a esquerda do nó e assume que o i é o maior, visto que ele é o pai.
- ele faz duas verificações para checar se a propriedade está aplicada, para o filho da direita e para o filho da esquerda.
- Caso o maior número entre os 3 testados não seja o da posição i, ele realiza as trocas necessárias e chama a função novamente (recursiva) para o próximo nó.

```python
def max_heapify(A, i, tamanho_heap):
    l = 2 * i + 1 
    r = 2 * i + 2 
    maior = i

   
    if l < tamanho_heap and A[l] > A[i]:
        maior = l
    else:
        maior = i

   
    if r < tamanho_heap and A[r] > A[maior]:
        maior = r

   
    if maior != i:
        A[i], A[maior] = A[maior], A[i]  
        max_heapify(A, maior, tamanho_heap) 
```
A função heap_maximum recebe como parâmetro uma heap e devolve o elemento com maior chave

```python
def heap_maximum(A):
    return A[0]  
```
A função heap_extract_max recebe como parâmetro uma heap e remove e retornar o elemento com maior chave.

- Verifica se a heap tem mais que um elemento
- define a raiz como maior valor
- Substitue o primeiro elemento pelo último
- Remove o último elemento
- reorganiza a heap para manter a propriedade de heap máximo
- retorna o valor que foi removido

```python
def heap_extract_max(A):
    if len(A) < 1:
        raise IndexError("Heap underflow")

    max_val = A[0]
    A[0] = A[-1]
    A.pop()
    max_heapify(A, 0) 
    return max_val
```
A função heap_increase_key recebe como parâmetros a heap A, o indice do elemento que se quer incrementar e o valor da nova chave.

- Verifica se a nova chave é maior que a atual
- Atualiza o valor da chave no indice i
- Reestrutura a heap (a partir do ponto i) para manter a propriedade de heap máximo - INSERTION SORT

```python
def heap_increase_key(A, i, chave):
    if chave < A[i]:
        raise ValueError("A nova chave é menor que a chave atual")
    
    A[i] = chave
    
    while i > 0 and A[(i - 1) // 2] < A[i]:  
        A[i], A[(i - 1) // 2] = A[(i - 1) // 2], A[i]
        i = (i - 1) // 2
```
A função max_heap_insert recebe como parâmetros a heap e o elemento novo que se deseja inserir.

- Adiciona uma nova folha na árvore.
- Inicializa a folha nova com ‘-∞’, ou seja, o menor valor possível.
- Chama a heap_increase_key para colocar o novo elemento no local certo.
  
```python
def max_heap_insert(A, chave):
    A.append(-math.inf)  
    
    heap_increase_key(A, len(A) - 1, chave)
```
A fila de prioridade tem diversos usos, como por exemplo:

- Em sistemas operacionais, processos podem ter prioridades diferentes. Processos com maior prioridade são executados antes dos outros.
- Eventos podem ser processados em ordem de prioridade, como em filas de tarefas para impressoras, onde trabalhos urgentes são impressos antes dos outros.

Vamos simular todo o processo de uma fila de prioridades. Digamos que se tenha um conjunto A com 10 registros, cada registro é marcado por uma chave, que indica a sua prioridade. Vamos usar a estrutura de heap para realizar operações com essa fila.

`A = [4, 10, 13, 67, 85, 48, 86, 15, 29, 90]` 

Essas chaves foram geradas de maneira aleatória. Vamos transformar em uma heap usando a função build_max_heap.

```python
def build_max_heap(A):
    tamanho_heap = len(A)
    for i in range(tamanho_heap // 2 - 1, -1, -1):
        max_heapify(A, i, tamanho_heap)
```
Agora A tem a seguinte ordem para as chaves:

`Heap_A = [90, 85, 86, 67, 10, 48, 13, 15, 29, 4]`

Vamos ver essa heap graficamente:

![img](https://i.imgur.com/18IwYMt.png)

Vamos testar todas as funções que implementamos. Primeiro vamos usar a heap_maximum.

![img](https://i.imgur.com/H6gIBYd.png)

Agora, vamos extrair o elemento raiz com a função heap_extract_max e vê qual será a nova configuração da heap:

![image](https://github.com/user-attachments/assets/114dbad4-ea02-4f82-86ab-511c79305704)


![image](https://github.com/user-attachments/assets/cdd9b2dd-b312-44eb-ae0d-2d20f22cf0e8)

Vamos usar a função heap_increase_key para aumentar o nó A[3] (67) para 100.

![image](https://github.com/user-attachments/assets/1e8777e3-6b48-4c41-9057-2d2d275f5549)
![image](https://github.com/user-attachments/assets/a7c8db33-1231-4c1d-bcf3-58b6aa1a76a5)


Agora vamos adicionar um novo elemento da nossa heap. k = 50:

![image](https://github.com/user-attachments/assets/784baf9e-48ff-4987-831f-8169aa4df725)
![image](https://github.com/user-attachments/assets/ad8d461e-9599-47ae-801d-cb931d42ec11)


## Questão 2
<b> Mostre com experimentos numéricos quando suas próprias implementações de Quicksort e do Quicksort aleatório são mais vantajosas quando comparadas uma com a outra.</b>
<br>
<br>

O Quicksort usa um pivô fixo (segundo a quarta edição do livro, o último elemento da lista), enquanto o Quicksort aleatório escolhe um pivô de forma aleatória em cada iteração.

Primeiro vamos implementar as funções de `quicksort` e `random_quicksort`.

O quicksort é um algoritmo de ordenação que usa a técnica de dividir para conquistar. Ele escolhe um elemento “pivô” e reorganiza a lista de forma que todos os elementos menores do que o pivô fiquem a sua esquerda e todos os elementos maiores fiquem à direita. Ou seja, após a readequação dos elementos, o pivô estará na sua posição correta da lista ordenada.

O quicksort é aplicado recursivamente em várias sublistas, até que todos os elementos estejam devidamente ordenados. Ou seja, a base da recursão, é quando a sublista tem apenas um elemento, pois essa lista já estará ordenada.

O passo a passo do algoritmo é:

1. Escolher um pivô - aleatório ou o último elemento da lista
2. Particionar - os menores elementos a esquerda e os maiores a direita
3. Recursão - aplicar o quicksort novamente para a sublista à esquerda e a direita
4. Combinação - combinar as sublistas


```python
def quicksort(A):
    if len(A) <= 1:
        return A
    else:
        pivot = A[-1] 
        left = [x for x in A[:-1] if x <= pivot]
        right = [x for x in A[:-1] if x > pivot]
        return quicksort(left) + [pivot] + quicksort(right)

```


```python
def quicksort_random(A):
    if len(A) <= 1:
        return A
    else:
        pivot_index = random.randint(0, len(A) - 1)
        pivot = A[pivot_index]
        A[0], A[pivot_index] = A[pivot_index], A[0]
        left = [x for x in A[1:] if x <= pivot]
        right = [x for x in A[1:] if x > pivot]
        return quicksort_random(left) + [pivot] + quicksort_random(right)

```
Vamos fazer os testes para 3 casos. Cada caso será testado vetores de 3 diferentes tamanhos: 1000, 1500 e 2000. O primeiro caso é para listas já ordenadas, o segundo caso é listas reversas e o último caso são listas aleatórias.

Os experimentos tiveram vários resultados interessantes:

- O desempenho do `quicksort_random` se mantem constante para os 3 tipos de listas: ordenadas, reversas e aleatórias. Além de que oferece bons resultado até para arrays grandes.
- O desempenho do `quicksort` é bom para listas aleatórias, mas para listas ordenadas o ambiente de desenvolvimento dá erro de execução, devido a quantidade de operações de recursividade que o algoritmo exige.

![image](https://github.com/user-attachments/assets/9fae0f03-4c98-483d-8cff-9f1fea3aad84)

![image](https://github.com/user-attachments/assets/e98dbe5d-99cc-403c-acc8-643db12cdbb6)


## Questão 3
<b>Mostre com experimentos numéricos quando o Radix-sort com o Count-sort é mais rápido que o Count-sort sozinho. Utilize suas próprias implementações ou alguma implementação existente explicando os resultados. </b>
<br>
<br>

Primeiro vamos implementar o count-sort. O countsort (ou ordenação por contagem) é um algoritmo não comparativo e possui tempo de execução linear. Para entender os casos onde o radix sort é melhor que o countsort, é preciso entender sobre o array de contagem. O array de contagem é um array com tamanho igual ao valor máximo que se quer ordenar. Ele é inicializado com zeros e cada indice do array de contagem representa um valor possível no array de entrada. 

O algoritmo tem o principio de contagem por ocorrências. Ou seja, ele percorre o array e conta quantas vezes cada valor aparece. Depois, é feita uma acumulação de contagens, para que o algoritmo saiba a posição final de cada elemento da lista ordenada.

Caso ainda não tenha ficado claro, a maior desvantagem do countsort é a necessidade de criação de um array de contagem, pois se o valor máximo do array a ser ordenado for alto, isso irá consumir muita memória, além do tempo que será gasto para as operações com esse array muito grande.


```python
def count_sort(A):
    max_val = np.max(A) if A.size > 0 else 0 
    C = np.zeros(max_val + 1, dtype=int)

    for num in A:
        C[num] += 1

    B = []
    for i in range(len(C)):
        B.extend([i] * C[i])
    
    return np.array(B)
```
O radixsort tem um funcionamento diferente, pois faz uso de um outro algoritmo de ordenação para ordenar cada um dos digitos dos números. Primeiro ele identifica o número máximo e depois executa uma passagem de ordenação para cada dígito: do menos significativo até o mais significativo. O radixsort funciona muito bem para números grandes.

```python
def radix_sort(A):
    if A.size == 0:
        return A
    
    max_num = np.max(A)
    
    exp = 1  # Começa com a unidade
    while max_num // exp > 0:
        count_sort(A, exp)
        exp *= 10
    
    return A
```
Mas quando o radixsort tem vantagem sobre o countsort? Bom, vamos fazer um teste diferente dos que geralmente é feito para avaliar os tempos de execução dos algoritmos. Ao invés de aumentar o tamanho do vetor de teste, vamos aumentar o seu range, ou seja, ao criar um vetor aleatório, os números possíveis que vão formar o vetor serão cada vez maiores.

![image](https://github.com/user-attachments/assets/f6f2831e-a9e4-4414-ab8a-27a257ab71f3)
