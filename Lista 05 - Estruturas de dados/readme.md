# Lista 05 - Estruturas de dados
## Questão 01
<b>Proponha um problema que precisa ser resolvido com um dicionário. Use implementações existentes de diversos tipos de dicionários para resolver o problema proposto e avalie os resultados de desempenho para as operações básicas de inserção, remoção, e busca.</b>
<br>
<br>
Dicionário é um conjunto dinâmico que admite operações de inserção, remoção, busca…

Problema: Gerenciamento da fila de atendimento de um hospital, onde um paciente pode ser classificado por diferentes gravidades (quanto menor o número, menor a gravidade).

- Tem n pessoas na sala de espera. O primeiro passo é decidir quem deve ser atendido primeiro.
- Depois do atendimento, é necessário retirar essa pessoa da lista
- Por fim, adicionar um pessoa nova a lista.

Vamos testar pilhas, uma linked list e uma heap tree.

Vamos criar uma classe para cada estrutura. Começando com a pilha.  Uma **pilha** é uma estrutura de dados linear que segue o princípio **LIFO** (*Last In, First Out*), ou seja, o último elemento a ser inserido é o primeiro a ser removido. Das estruturas que vão ser testadas, ela é a mais simples de implementar, e a mais difícil de encaixar no problema, visto que só é possível retirar o elemento que está no topo. Vamos implementar as 3 operações básicas: inserção, busca e remoção.

1. **Push (Empilhar)**: Adiciona um elemento ao topo da pilha.
2. **Pop (Desempilhar)**: Remove o elemento do topo da pilha.
3. **Peek (ou Top)**: Retorna o elemento no topo da pilha sem removê-lo.
4. **IsEmpty**: Verifica se a pilha está vazia.
5. Search: Não é muito normal em uma pilha, mas vamos colocar para manter a resolução do problema.

```python
class Stack:
    def __init__(self):
        self.stack = []

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        if not self.is_empty():
            return self.stack.pop()
        return None

    def peek(self):
        if not self.is_empty():
            return self.stack[-1]
        return None

    def is_empty(self):
        return len(self.stack) == 0

    def search(self, priority):
        for patient in self.stack:
            if patient["priority"] == priority:
                return patient
        return None

```
**A Linked List** (Lista Encadeada) também é uma estrutura de dados linear em que os elementos são armazenados em **nós**. Cada nó contém dois componentes principais: o dado armazenado no nó, que seriam nossos dados satelites e um ponteiro como chave para o próximo nó da sequencia. Só pela descrição, já dá para reparar que se encaixa bem melhor com o nosso problema do que a pilha.

Existem diferentes tipos e linked list. O livro destaca a encadeada e a duplamentente encadeada. A diferença entre elas é que a encadeada aponta para o próximo nó, e a duplamente encadeada aponta para o próximo e o anterior. 

A linkedlist tem a vantagem de ser dinâmica, ou seja, o tamanho da lista cresce e dimuni dinamicamente, alocando memória conforme necessário. Além disso, as inserções e remoções são bastante eficientes. 

1. Insert: Adiciona um novo nó (paciente) e ordena pela prioridade.
2. Delete: Remove o nó que contém o paciente com a prioridade indicada.
3. Search: Procura o nó que contém um paciente com a prioridade especificada.

```python
class LinkedListNode:
    def __init__(self, patient):
        self.patient = patient
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, patient):
        new_node = LinkedListNode(patient)
        if not self.head or patient["priority"] 
        < self.head.patient["priority"]:
            new_node.next = self.head
            self.head = new_node
            return
        current = self.head
        while current.next and current.next.patient["priority"] 
        <= patient["priority"]:
            current = current.next
        new_node.next = current.next
        current.next = new_node

    def delete(self, priority):
        if not self.head:
            return None
        if self.head.patient["priority"] == priority:
            self.head = self.head.next
            return
        current = self.head
        while current.next and current.next.patient["priority"] 
        != priority:
            current = current.next
        if current.next:
            current.next = current.next.next

    def search(self, priority):
        current = self.head
        while current:
            if current.patient["priority"] == priority:
                return current.patient
            current = current.next
        return None

```
Por fim, a heap tree, estudada em capítulos anteriores, é uma estrutura de dados baseada em uma árvore binária que segue uma **propriedade de heap**: cada nó tem um valor que é maior ou menor que os valores dos seus filhos, dependendo de ser uma **max-heap** ou **min-heap**. Ela é comumente usada para implementar **filas de prioridade**, onde o elemento de maior (ou menor) prioridade é facilmente acessível. Pela definição, podemos ver que essa é a estrutura de dados que teoricamente se encaixa melhor com nosso problema.

Vamos implementar as 3 operações básicas

1. Insert: Adiciona um novo nó (paciente) - já é ordenado para manter a propriedade de max-heap
2. Delete: Remove o nó raiz (máxima prioridade) e chama o heapify para restaurar a propriedade de max-heap
3. Search: Faz uma busca de acordo com a prioridade.

```python
class BinaryHeap:
    def __init__(self):
        self.heap = []

    def insert(self, patient):
        heapq.heappush(self.heap, (patient["priority"], id(patient), patient))

    def search(self, priority):
        return [item[2] for item in self.heap if item[0] == priority]

    def delete(self, priority):
        for i, item in enumerate(self.heap):
            if item[0] == priority:
                del self.heap[i]
                heapq.heapify(self.heap)
                break

```
Vamos gerar diferentes tamanhos de problema e comparar os resultados das três operações básicas para cada um dos dicionários.

![image](https://github.com/user-attachments/assets/26db6fff-fd9f-4742-9096-f60df57b6bb2)

- A **Pilha** tem tempos muito baixos de inserção, busca e remoção, que praticamente não variam com o aumento do tamanho da entrada.  Isso se dá pelo fato de a gente só conseguir interagir com 1 único elemento - que é o que está no topo.
- A **Lista Encadeada** apresenta um crescimento mais significativo à medida que o tamanho da entrada aumenta, especialmente nas operações de busca e remoção.
- A heap tree não leva tanto tempo quanto a linked list e consegue resolver o problema de forma eficiente.

## Questão 02
<b>Implemente uma tabela hash usando encadeamento e endereçamento aberto. Realize experimentos para mostrar numericamente as vantagens e desvantagens de cada caso. </b>
<br>
<br>
Uma tabela hash é uma estrutura de dados que permite armazenar pares de chave-valor de forma eficiente, utilizando uma função hash para mapear as chaves a posições na tabela. Quando duas ou mais chaves mapeiam para o mesmo índice, ocorre uma **colisão**. Existem algumas estratégias para lidar com as colições:

- No **endereçamento aberto**, todos os elementos são armazenados diretamente na tabela hash. Quando ocorre uma colisão (ou seja, quando o índice calculado pela função de hash já está ocupado), a estratégia é procurar uma posição vazia dentro da própria tabela. Existem diferentes técnicas para realizar essa "busca" por uma posição livre.
- No **encadeamento**, em vez de armazenar diretamente os elementos na tabela, cada índice da tabela contém uma **lista ligada** (ou outra estrutura como uma fila ou lista encadeada) que armazena todos os elementos que possuem o mesmo índice calculado pela função de hash.
Vamos implementar uma tabela hash com encadeamento usando DLL - listas duplamente encadeadas - para resolver as colisões.

Vamos implementar as duas estratégias e comparar seus resultados:

```python
class DLLNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None #primeiro nó
        self.tail = None #último nó

    def prepend(self, key, value): #novo nó
        new_node = DLLNode(key, value)
        if not self.head:
            self.head = self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    def search(self, key): #procura o nó que corresponde a key
        current = self.head
        while current:
            if current.key == key:
                return current.value
            current = current.next
        return None

    def delete(self, key): #remove nó
        current = self.head
        while current: #troca tail e prev
            if current.key == key: 
                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev
                if current == self.head:
                    self.head = current.next
                if current == self.tail:
                    self.tail = current.prev
                return
            current = current.next

class ChainedHashTable:
    def __init__(self, size, hash_func=hash):
        self.size = size
        #cria uma DLL para cada posição
        self.table = [DoublyLinkedList() for _ in range(size)]
        #função python
        self.hash_func = hash_func

    def insert(self, key, value):
        index = self.hash_func(key) % self.size
        self.table[index].prepend(key, value)

    def search(self, key):
        index = self.hash_func(key) % self.size
        return self.table[index].search(key)

    def delete(self, key):
        index = self.hash_func(key) % self.size
        self.table[index].delete(key)

    def __str__(self):
        return "[" + ", ".join([str(self.table[i]) for i in range(self.size)]) + "]"
```
**`DLLNode`**: Representa um nó na lista, contendo uma chave (`key`), um valor (`value`), e ponteiros para os nós anterior (`prev`) e próximo (`next`).

**`DoublyLinkedList`**: Gerencia a lista com operações de inserção, busca e remoção.

**`ChainedHashTable`**: Contém um array onde cada posição é uma instância de `DoublyLinkedList`.

- **`insert`**: Calcula o índice com base na função hash e insere o par chave-valor na lista correspondente.
- **`search`**: Utiliza o índice calculado para buscar o valor na lista associada.
- **`delete`**: Remove o nó correspondente à chave da lista associada.
- Utiliza uma função hash (por padrão, a função `hash` do Python) para distribuir os elementos uniformemente no array.
```python
class OpenAddressingHashTable:
    def __init__(self, size, hash_func=hash):
        self.size = size
        self.table = [None] * size
        self.hash_func = hash_func

    def insert(self, key, value):
        index = self.hash_func(key) % self.size
        original_index = index
        while self.table[index] is not None:
            if self.table[index][0] == key:
                # Se a chave já existir, atualize o valor
                self.table[index] = (key, value)
                return
            index = (index + 1) % self.size
            if index == original_index:
                raise Exception("Tabela cheia")
        self.table[index] = (key, value)

    def search(self, key):
        index = self.hash_func(key) % self.size
        original_index = index
        while self.table[index] is not None:
            if self.table[index][0] == key:
                return self.table[index][1]
            index = (index + 1) % self.size  # sondagem linear
            if index == original_index:
                return None
        return None

    def delete(self, key):
        index = self.hash_func(key) % self.size
        original_index = index
        while self.table[index] is not None:
            if self.table[index][0] == key:
                self.table[index] = None
                return
            index = (index + 1) % self.size  # sondagem linear
            if index == original_index:
                return
        return None

    def __str__(self):
        return "[" + ", ".join([str(self.table[i]) if self.table[i] is not None else "None" for i in range(self.size)]) + "]"


```
- Um array fixo de tamanho `size` é inicializado, onde cada posição pode conter um par `(chave, valor)` ou `None` (indicando que está vazia).
- A função hash (por padrão, a função `hash` do Python) determina o índice inicial para cada chave.

**`insert`**:

- Calcula o índice inicial da chave com a função hash.
- Se a posição já estiver ocupada, verifica sequencialmente as próximas posições (probing linear) até encontrar uma vazia ou atualizar o valor de uma chave existente.
- Caso todas as posições tenham sido verificadas e não haja espaço, lança uma exceção indicando que a tabela está cheia.

**`search`**:

- Calcula o índice inicial e percorre a tabela usando probing linear até encontrar a chave ou verificar todas as posições possíveis.
- Retorna o valor associado à chave ou `None` caso a chave não seja encontrada.

**`delete`**:

- Remove o par `(chave, valor)` associado à chave fornecida, marcando a posição como `None`.
- Continua verificando outras posições em caso de colisões.

Vamos entender o funcionamento das duas estratégias para inserção, busca e remoção.

No encadeamento, não temos busca por slots livres, então em cenários que se tem um grande número de colisões, ele pode apresentar vantagem na inserção.

Porém, o encadeamento geralmente resulta em uma busca mais lenta. já que o tempo de busca depende do número de elementos em cada lista.

Além disso, o encademaneto costuma usar mais memória, visto que cada elemento da tabela requer um nó adicional para a lista encadeada.

Já o endereçamento aberto, o uso de memória será menor.

Porém, temos um pior desempenho com carga alta, ou seja, quando a tabela está quase cheia, vamos ter uma queda no desempenho pelo aumento das colições

![image](https://github.com/user-attachments/assets/5873697f-7ee7-4ecd-89a5-ac6faed01c10)
![image](https://github.com/user-attachments/assets/45489924-f7ca-45f9-a685-ecbfb48b70b9)
![image](https://github.com/user-attachments/assets/c8144f97-bf08-4d09-a653-08554246df83)


## Questão 03
<b>Compare implementações (existentes ou sua própria) de tabelas hash com hashing duplo e probing linear. Observe e justifique os resultados dos seus experimentos em máquinas modernas. </b>
<br>
<br>
No endereçamento aberto todos os elementos são armazenados diretamente na tabela, sem a necessidade de listas encadeadas. Quando ocorre uma colisão, a tabela hash é percorrida em busca de um slot vazio, onde o novo elemento pode ser inserido. Existem várias técnicas de endereçamento aberto para resolver colisões, como sondagem linear (probing linear), sondagem quadrática e hashing duplo.

O probing linear é uma técnica de endereçamento aberto que consiste em percorrer a tabela hash em incrementos fixos até encontrar um slot vazio. A fórmula para a sondagem linear é a seguinte:

$$h(k, i) = \left( h'(k) + i \right) \mod m$$

Onde h'(k) é a função de hash original e i é o incremento. A sondagem linear é eficiente e fácil de implementar, mas pode sofrer com o problema de agrupamento primário de chaves, o que pode afetar o desempenho da tabela hash. O agrupamento primário de chaves ocorre quando há longas sequencias de slots ocupados, o que pode resultar em colisões adicionais. 

```python
def linear_probing_hash_function(h):
	return lambda k, i, m: (h(k) + i) % m
```
O hashing duplo é uma técnica de endereçamento aberto que consiste em usar duas funções de hash para calcular o índice da tabela. A fórmula para o hashing duplo é a seguinte:

&&h(k, i) = \left( h_1(k) + i \cdot h_2(k) \right) \mod m &&

Onde h1(k) e h2(k) são funções de hash diferentes e i é o incremento. O hashing duplo é mais eficiente que a sondagem linear, pois distribui as chaves de forma mais uniforme na tabela. No entanto, ele é mais complexo de implementar e requer mais recursos computacionais.

```python
def double_hashing_hash_function(h1, h2):
	return lambda k, i, m: (h1(k) + i * h2(k)) % m
```
### Probing linear

- Vantagens:
    - Simples de implementar
    - Explora posições sequenciais, o que pode ser eficiente em tabelas pouco ocupadas.
- Desvantagens:
    - Agrupamento primário: múltiplas colisões podem causar grandes cadeias consecutivas de verificações, prejudicando o desempenho.

### Hashing duplo

- Vantagens:
    - Reduz o agrupamento primário, já que o deslocamento não é constante e depende de `h2(k)`.
    - Funciona bem mesmo em tabelas densamente ocupadas.
- Desvantagens:
    - Exige o cálculo de uma segunda função hash, o que pode aumentar o custo computacional
    - É mais complexo de implementar.

Vamos implementar essas duas funções e comparar o desempenho delas em uma tabela de endereçamento aberto.

Resultados aleatórios:
![image](https://github.com/user-attachments/assets/529f622c-dd61-41ea-aac4-a0041be93a1d)
Quando o número de colisões é pequeno, ambos os métodos podem ter desempenhos semelhantes. No entanto, com o aumento do número de elementos (e colisões), o **probing linear** pode se tornar significativamente mais lento. Já o **hashing duplo** tende a mitigar esse problema devido à segunda função de hash, o que leva a uma melhor distribuição dos elementos.

Vamos fazer experimentos forçando o aumento no número de colisões:
![image](https://github.com/user-attachments/assets/5d7b79a3-5fcc-4cfa-a493-5755805bcec9)


