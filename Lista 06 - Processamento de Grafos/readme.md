# Lista 06 - Processamento de Grafos
## Questão 1
<b>Defina um grafo acíclico direcionado relacionado a área do seu mestrado/doutorado e use a sua implementação para ordenar topologicamente esse grafo. </b>
<br>
<br>

Um **grafo acíclico direcionado** (ou **DAG**, do inglês *Directed Acyclic Graph*) é um tipo de grafo que possui as seguintes características:

1. **Direcionado**: Cada aresta possui um sentido, ou seja, conecta um vértice a outro de forma direcionada. Isso é representado como uma seta de um vértice u para v (ou u→v).
2. **Acíclico**: Não contém ciclos direcionados. Isso significa que não é possível iniciar em um vértice, seguir as arestas na direção indicada, e retornar ao mesmo vértice. Em outras palavras, o grafo não possui caminhos fechados.

**Ordenação topológica**: Em um DAG, é possível ordenar os vértices de modo que, para cada aresta u→v, o vértice u aparece antes de v na ordenação. Isso é útil para determinar dependências ou a ordem de execução.

![image](https://github.com/user-attachments/assets/f534c622-96b6-4f47-9b05-e8287201ca39)

O DAG acima foi criado baseado nos pipelines de processamento de dados em ML ou BI, com cada nó representando uma etapa do processo, e as arestas direcionadas indicando as dependências entre as etapas.

Vamos fazer a ordenação topológica usando o DFS - busca em profundidade. O processo consiste em realizar uma busca nos nós do grafo e adicionar os nós à lista de ordenação no momento em que retornamos de uma visita recursiva (isto é, quando não há mais nós a explorar a partir de um nó).

Os passos são:

1. marcar os nós como não visitados;
2. para cada nó não visitado, iniciar a DFS. Durante a busca, marque os nós como visitados.
3. Após a visita a todos os filhos de um nó, adicione esse nó ao stack - A ideia é que um nó só é adicionado à ordenação quando todos os seus predecessores já tiverem sido processados.

```python
def topological_sort_dfs(graph):
    visited = set() 
    stack = []       
    on_stack = set()

    def dfs(node):
        if node in visited:
            return
  
        on_stack.add(node)
        
        for neighbor in graph.get(node, []):
            dfs(neighbor)
        
        visited.add(node)
        on_stack.remove(node)
        stack.append(node)

    for node in graph:
        if node not in visited:
            dfs(node)
    
    return stack[::-1]

```
- **DFS**: A função `dfs()` é chamada para cada nó ainda não visitado. Durante a execução da DFS, verificamos se um nó está na pilha recursiva `on_stack`, o que indicaria um ciclo no grafo (isto é, o grafo não seria um DAG).
- **Stack**: A lista `stack` armazena a ordenação topológica. Ela é preenchida à medida que retornamos da DFS, ou seja, depois de visitar todos os vizinhos de um nó.
- **Visita e Remoção da Pilha**: Quando a DFS termina para um nó, ele é removido da pilha recursiva `on_stack` e é adicionado à lista `stack`.

![image](https://github.com/user-attachments/assets/964b5b15-1fd2-4a7f-bbed-061568a93293)

## Questão 2
<b> Implemente e aponte vantagens e desvantagens dos algoritmos de Kruskal e Prim para gerar uma árvore de abrangência mínima. Use exemplos práticos da sua área para demonstrar suas conclusões.</b>
<br>
<br>

- Os algoritmos de **Kruskal** e **Prim** são dois métodos populares para resolver o problema da **Árvore de Abrangência Mínima (MST)** em grafos ponderados. Ambos encontram uma árvore que conecta todos os vértices de um grafo com o menor custo total possível.
- O **algoritmo de Kruskal** é um algoritmo guloso que funciona em um grafo desconexo ou conexo. Ele constrói a árvore de abrangência mínima selecionando arestas em ordem crescente de peso, garantindo que a adição de cada aresta não forme um ciclo. Isso é feito usando a estrutura de **conjunto disjunto** (ou **Union-Find**) para verificar e manter a propriedade de que as arestas selecionadas não formem ciclos.
    1. Ordenar todas as arestas do grafo em ordem crescente de peso.
    2. Iterar pelas arestas, adicionando-as à MST se não formarem um ciclo (usando um algoritmo de união-encontro - Union-Find).
    3. Parar quando todas as arestas necessárias estiverem na MST.

```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)

        if root_u != root_v:
            # Union by rank
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1
            return True
        return False

def kruskal(n, edges):
    # edges é uma lista de tuplas (peso, u, v)
    edges.sort()  
    uf = UnionFind(n)
    mst = []

    for weight, u, v in edges:
        if uf.union(u, v):
            mst.append((u, v, weight))  
    return mst

```
- O **algoritmo de Prim** é outro algoritmo guloso que também encontra uma árvore de abrangência mínima. Ele começa a partir de um vértice arbitrário e adiciona a aresta de menor peso que conecta um vértice já na árvore a um vértice fora dela, repetindo isso até que todos os vértices estejam na árvore.
    1. Escolher um vértice inicial
    2. Adicionar a menor aresta conectando um vértice dentro da MST a um vértice fora dela.
    3. Repetir até que todos os vértices sejam incluídos

```python
def prim(n, adj):
    mst = []
    min_heap = [(0, 0)]  # (peso, vértice)
    visited = [False] * n
    total_weight = 0

    while min_heap:
        weight, u = heapq.heappop(min_heap)
        
        if visited[u]:
            continue

        visited[u] = True
        total_weight += weight

        for v, w in adj[u]:
            if not visited[v]:
                heapq.heappush(min_heap, (w, v))
                mst.append((u, v, w))

    return mst, total_weight


```
### **Algoritmo de Kruskal:**

**Vantagens**:

- **Fácil de entender e implementar**: O algoritmo é simples e intuitivo, baseado em operações de união e busca.
- **Adequado para grafos esparsos**: Kruskal é eficiente quando o número de arestas é muito menor que o número de vértices, pois a complexidade está mais ligada ao número de arestas.
- **Funciona bem em grafos desconexos**: Kruskal pode ser usado em grafos desconexos, onde ele encontrará uma MST para cada componente conectado.

**Desvantagens**:

- **Complexidade de ordenação**: A necessidade de ordenar todas as arestas pode levar a um custo elevado em grafos densos.
- **Uso de Union-Find**: A eficiência do algoritmo depende de uma implementação eficiente da estrutura Union-Find (ou conjunto disjunto), especialmente para grafos grandes.

### **Algoritmo de Prim:**

**Vantagens**:

- **Boa performance em grafos densos**: Em grafos densos, onde o número de arestas é grande, o algoritmo de Prim pode ser mais eficiente, pois ele expande a árvore progressivamente.
- **Pode ser otimizado com estruturas de dados**: Usando uma **fila de prioridade** (como uma heap), o algoritmo pode ser implementado de forma eficiente em termos de tempo, especialmente para grafos densos.
- **Não requer a ordenação das arestas**: Ao contrário de Kruskal, Prim não precisa ordenar todas as arestas, o que pode ser uma vantagem em alguns cenários.

**Desvantagens**:

- **Requer a manutenção de uma fila de prioridade**: Embora o Prim seja eficiente, ele depende de uma estrutura de dados adicional (como heap ou fila de prioridade), o que pode adicionar complexidade de implementação.
- **Não é ideal para grafos desconexos**: O algoritmo de Prim só funciona para grafos conectados. Para grafos desconexos, é necessário adaptar o algoritmo ou usar Kruskal.

**Kruskal** é mais eficiente em grafos esparsos e quando o grafo está desconexo, mas depende de uma operação de ordenação de arestas e de operações com a estrutura Union-Find.

**Prim** é mais eficiente para grafos densos e usa uma abordagem incremental, que pode ser otimizada com a fila de prioridade. No entanto, ele não pode ser diretamente aplicado a grafos desconexos sem adaptação.

Um exemplo de aplicação prática de MSTs no machine learning é no **agrupamento hierárquico** (hierarchical clustering). Ao usar MSTs, podemos encontrar os "grupos naturais" em um conjunto de dados conectando amostras próximas. Imagine um conjunto de dados onde os pontos representam clusters de dados, e as arestas são calculadas com base em uma métrica de distância, como a distância euclidiana ou Manhattan. Ao construir a MST do grafo dos dados:

- **Kruskal** é útil quando temos uma lista de distâncias precomputada (e.g., grafo esparso).
- **Prim** é útil quando queremos construir a MST dinamicamente (e.g., grafo denso).

**Exemplo:**

- Use o algoritmo MST para encontrar os clusters e definir agrupamentos cortando as arestas mais longas.
- **Kruskal** é eficiente quando o grafo tem muitas arestas, mas não é muito conectado, como em grafos de similaridade em clustering hierárquico.
- **Prim** se destaca em grafos densos, como redes de similaridade em redes neurais (kNN).

O algoritmo de Prim é significativamente mais rápido no limite quando você tem um gráfico realmente denso com muitas mais arestas do que vértices. Kruskal funciona melhor em situações típicas (gráficos esparsos) porque usa estruturas de dados mais simples.

Sobre as vantagens e desvantagens:

- Ambos são simples e encontram uma boa solução para o problema, sendo que na maioria das vezes é a solução ótima.

## Questão 3
<b>Implemente o algoritmo do Dijkstra e utilize-o para resolver um problema prático da sua área de interesse. </b>
<br>
<br>

O algoritmo de Dijkstra é um algoritmo guloso utilizado para encontrar o caminho mais curto de um vértice de origem para todos os outros vértices em um grafo com arestas de peso não negativo. Ele é eficiente em grafos densos e pode ser implementado utilizando uma fila de prioridade (min-heap) para garantir que sempre estamos explorando o caminho de menor custo.

```python
def dijkstra(n, adj, source):
    """
    
    Parâmetros:
    n -- número de vértices
    adj -- lista de adjacência do grafo, 
    onde adj[u] é uma lista de pares (v, peso)
    representando arestas (u, v) com peso
    source -- vértice de origem
    
    Retorna:
    dist -- lista com as distâncias mínimas
    do vértice origem para cada vértice
    prev -- lista com o vértice anterior de 
    cada vértice no caminho mais curto
    """
    dist = [float('inf')] * n
    dist[source] = 0
    prev = [None] * n
    
    min_heap = [(0, source)]  

    while min_heap:
        current_dist, u = heapq.heappop(min_heap)
        
        if current_dist > dist[u]:
            continue
        
        for v, weight in adj[u]:
            alt = dist[u] + weight  
            
            if alt < dist[v]:
                dist[v] = alt
                prev[v] = u
                heapq.heappush(min_heap, (alt, v))  

    return dist, prev

def reconstruct_path(prev, source, target):
    """
    Reconstrói o caminho mais curto de source para target.
    
    Parâmetros:
    prev -- lista de vértices anteriores
    source -- vértice de origem
    target -- vértice destino
    
    Retorna:
    path -- lista com os vértices no caminho mais curto
    """
    path = []
    current = target
    while current is not None:
        path.append(current)
        current = prev[current]
    path.reverse()
    if path[0] == source:
        return path
    else:
        return None  

```
- **Função `dijkstra`**:
    - Recebe o número de vértices `n`, o grafo representado pela lista de adjacência `adj` (onde `adj[u]` contém uma lista de pares `(v, peso)` representando as arestas do vértice `u` para o vértice `v` com peso `peso`), e o vértice de origem `source`.
    - Inicializa uma lista `dist` para armazenar a distância mínima de cada vértice para o vértice origem. Inicialmente, todas as distâncias são definidas como infinito, exceto a distância do vértice origem, que é 0.
    - Também é inicializada uma lista `prev` para armazenar o vértice anterior de cada vértice no caminho mais curto.
    - A fila de prioridade (`min_heap`) é usada para sempre escolher o próximo vértice com a menor distância conhecida. A cada iteração, o algoritmo explora os vizinhos de um vértice `u` e relaxa as arestas, atualizando as distâncias e os predecessores.
- **Função `reconstruct_path`**:
    - Dada a lista `prev`, que armazena os predecessores de cada vértice no caminho mais curto, esta função reconstrói o caminho mais curto do vértice de origem até o destino.
    - O caminho é reconstruído de trás para frente, começando do vértice destino e subindo até o vértice de origem.

### Problema prático

**Seleção de features usando um grafo de similaridade**

Na seleção de features, os dados podem ser modelados como um grafo, onde os nós representam as features, e as arestas representam a similaridade entre elas. Usando o algoritmo de Dijkstra, podemos determinar um conjunto de features mais relevantes minimizando redundâncias

- Você tem 5 features representadas por nós.
- O peso das arestas reflete a similaridade (mais próximo de 0 é mais dissimilar, mais próximo de 1 é mais similar).
- O objetivo é encontrar o subconjunto de features mais dissimilares para garantir variabilidade no modelo.

![image](https://github.com/user-attachments/assets/9c9b84c5-9764-476b-b638-23252cd5b361)

```python
Distâncias das features de 0: 
{0: 0, 
1: 0.9, 
2: 0.2, 
3: 0.4, 
4: 0.9}
Caminhos mínimos para cada feature: 
{0: [0], 
1: [0, 1], 
2: [0, 2], 
3: [0, 3], 
4: [0, 1, 4]}
```
