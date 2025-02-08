# Lista 04 - Estatística de ordem
# Questão 1
<b>Implemente o algoritmo de mínimo e máximo simultâneos da seção 9.1 do livro do Cormen, 4a Ed na sua linguagem favorita e mostre através de medição de tempo que é mais rápido que a abordagem não-simultânea para um vetor de entrada suficientemente grande.  </b>
<br>
<br>

Primeiro vamos implementar uma função que ache o valor mínimo e o valor máximo de um vetor A de forma não-simultânea .

```python
def MINIMUM_MAXIMUM(A):
    max_val = A[0]
    for num in A:
        if num > max_val:
            max_val = num
    
    min_val = A[0]
    for num in A:
        if num < min_val:
            min_val = num
    
    return max_val, min_val
```
Agora, vamos adaptar a função para, de forma simuntanea, achar o valor máximo e mínimo, fazendo o menor número possível de comparações, processando os elementos em pares.

Primeiro o algoritmo verifica a paridade, se `n` (número de elementos do vetor) é par ou ímpar. Se for ímpar, o algoritmo define tanto minimo (`mini`)  quanto máximo (`maxi`) como o primeiro elemento do vetor A (`A[0]`). Se for par, ele compara os dois primeiros elementos e atribui o maior ao máximo e o menor ao mínimo.

Depois de determinar `mini` e `maxi` iniciais, o algoritmo processa o restante do vetor em **pares**. Para cada par de elementos, ele compara entre si. Após encontrar o mínimo e máximo do par atual, o algoritmo compara esses valores com `mini` e `maxi` atuais e os atualiza se necessário.

```python
def MINIMUM_AND_MAXIMUM(A):
    
    n = len(A)
    
    # VERIFICANDO A PARIDADE 
    if n % 2 == 1:  # n é ímpar
        mini = A[0]
        maxi = A[0]
        start_index = 1  # segundo elemento
    else:  # n é par
        if A[0] < A[1]:
            mini = A[0]
            maxi = A[1]
        else:
            mini = A[1]
            maxi = A[0]
        start_index = 2  # Começa a processar do terceiro elemento

    # processando o resto do vetor em pares
    for i in range(start_index, n, 2):
        if i + 1 < n:
            # comparando o par (A[i], A[i + 1])
            if A[i] < A[i + 1]:
                pair_min, pair_max = A[i], A[i + 1]
            else:
                pair_min, pair_max = A[i + 1], A[i]

            # atualiza o mini e maxi, se precisar
            if mini > pair_min:
                mini = pair_min
            if maxi < pair_max:
                maxi = pair_max

    return mini, maxi

```
A maneira mais usual de encontrar o minimo e máximo (forma não simuntânea), é usando Θ(n) comparações.

- para achar o mínimo se faz n-1 comparações
- para achar o máximo se faz n-1 comparações
- um total de 2n-2 comparações

Embora 2n−2 comparações sejam assimptoticamente ótimas, o algoritmo de minimo e máximo simuntâneo faz no máximo 3[n/2] comparações (números ímpares).

Porém, a comparação não é o único custo do algoritmo. Existe custos de atribição e declaração que podem compensar o ganho obtido nas comparações. Segundo os testes realizados por mim, o tempo de execução do algoritmo simuntâneo não foi inferior ao não simuntâneo.

![image](https://github.com/user-attachments/assets/325be583-0888-4e22-8984-b9cbc5d16623)

# Questão 2
<b>Implemente os algoritmos de seleção aleatória e seleção das seções 9.2 2 9.3 do livro do Cormen, 4a Ed., e realize experimentos numéricos para demonstrar em quais casos um tem vantagens com relação ao outro. </b>
<br>
<br>
A randomized_select recebe o vetor, o indice inicial e o indice final e o número da ordem desejada (i-ésimo menor elemento no vetor). Ela escolhe um pivô aleatório e particiona o array, fazendo um “meio quicksort”. Os elementos menores que o pivô ficam à esquerda e os maiores ficam à direita. A ideia é encontrar o i-ésimo menor elemento sem precisar ordenar todo o vetor.

- Se `p == r`, significa que o subarray tem apenas um elemento e ele é o que estamos procurando.
- A função `randomized_partition` (a mesma do quicksort) é chamada para particionar o array e retornar um índice `q` que separa os menores do pivô (à esquerda) e maiores (à direita).
- `k` é o número de elementos à esquerda do índice `q`, e ajuda a determinar se o elemento desejado está antes ou depois do pivô.
- Se `i == k`, então o pivô é o elemento desejado. Se `i < k`, a busca continua no subarray à esquerda. Se `i > k`, a busca continua no subarray à direita.

```python
def randomized_select(A, p, r, i):
	if p == r:
		return A[p]  
	q = randomized_partition(A, p, r)
	k = q - p + 1  
	if i == k:  
		return A[q]
	elif i < k:
		return randomized_select(A, p, q-1, i)  
	else:
		return randomized_select(A, q+1, r, i-k) 

```
A função select, tem a mesma finalidade que a randomized_select , mas como o próprio nome já diz, na randomized_select o pivô é selecionado de maneira aleatória, enquanto no select, uma estratégia é usada para escolher um “bom pivô”. 

Obviamente que um “bom pivô” é um termo bem relativo… o que acontece na prática, é que o randomized_select pode ser melhor que o pivô calculado pelo select, mas também pode ser pior… o select garante que o pior caso do randomized_select, que é quando o pivô sorteado acaba sendo o maior elemento do vetor, não aconteça.

Também conhecido como Mediana das medianas, o select é uma versão determinística do algoritmo de seleção. Ele tem as mesmas entradas da função anterior: o vetor, o índice atual, o final e o ordinal para o i-ésimo valor.

- A função garante que o vetor tenha um número múltiplo de 5 de elementos, adicionando elementos extras para ajustar.
    - O loop inicial: se o número de elementos entre `p` e `r` não for múltiplo de 5, a função ajusta a entrada para que fique múltipla de 5. Ela faz isso rearranjando a lista para mover o menor valor atual para o início e removendo-o da análise posterior, caso não estejamos procurando o menor valor.
    - Se `i` for 1 (ou seja, queremos o menor elemento), a função retorna `A[p]`. Caso contrário, ela ajusta `p` e `i` para continuar a busca.
- Divide o array em grupos de 5 elementos e ordena cada grupo.
    - Após garantir que temos um múltiplo de 5 elementos, a função calcula `g`, o número de grupos de 5 elementos.
    - Em seguida, ela aplica a função `strided_insertion_sort_five` para ordenar esses grupos de 5 elementos, de forma que os valores medianos desses grupos possam ser encontrados facilmente.
- Encontra a mediana de cada grupo e usa a mediana das medianas como pivô.
    - Encontra a mediana dos valores medianos dos grupos de 5.
    - Ele chama a própria função `select` recursivamente para encontrar esse valor de pivô, usando `ceil(g / 2)` para determinar a posição mediana.
- Usa `partition_around` para particionar o array em torno desse pivô e recursivamente encontra o i-ésimo menor elemento.
    - A função `partition_around` é chamada para rearranjar a lista em torno do pivô encontrado. Ela garante que todos os elementos menores ou iguais ao pivô fiquem à esquerda e os maiores, à direita.


```python

def select(A, p, r, i):

	while (r-p+1) % 5 != 0:
		for j in range(p+1, r+1):  
			if A[p] > A[j]:
				A[p], A[j] = A[j], A[p]

		if i == 1:
			return A[p]

		p += 1
		i -= 1

	# Quantos grupos de 5
	g = (r-p+1) // 5  
	
	# Ordenar os grupos entre si
	for j in range(p, p+g): 
		strided_insertion_sort_five(A, p, g)

	# Recursividade para achar a mediana das medianas
	x = select(A, p + 2*g, p + 3*g - 1, ceil(g / 2))
	
	# A partir daqui, é igual ao anterior
	q = partition_around(A, p, r, x)  

	k = q - p + 1  
	if i == k:
		return A[q]  
	elif i < k:
		return select(A, p, q - 1, i) 
	else:
		return select(A, q + 1, r, i - k)  

```

```python
def strided_insertion_sort_five(A, p, g):
	for i in range(1, 5):
		key = A[p + i*g]
		j = i - 1
		while j >= 0 and A[p + j*g] > key:
			A[p + (j + 1)*g] = A[p + j*g]
			j -= 1
		A[p + (j + 1)*g] = key

```
Ao comparar os tempos de execução dos algoritmos, podemos gerar o seguinte gráfico:
![image](https://github.com/user-attachments/assets/14e2ac4c-2001-4542-9ecc-8cf3681b9286)

É interessante reparar que:

- Em muitos casos, o random select possui um tempo de execução menor em comparação com o select
- Porém, o crescimento do select é quase que constante, enquanto o random select possui um desempenho mais “imprevisível”, visto que o pivô pode ser bom ou ruim.
  
# Questão 3
<b> Implemente o algoritmo da mediana ponderada e use-o para resolver o item e do Problema 9-3 do Cormen, 4a Ed. </b>
<br>
<br>

É necessário resolver o problema da localização ideal de uma agência de correios - achar um ponto que minimiza a soma das distâncias de Manhattan até um conjunto de pontos em um plano bidimensional. O problema da localização do posto de correio é definido da seguinte forma: a entrada consiste em n pontos com pesos associados. A solução é um ponto p que minimiza a soma :


$$\sum_{i=1}^{n} w_i \cdot d(p, p_i)$$


- A distância de Manhattan entre dois pontos é dada por:


$$d(a, b) = |x_1 - x_2| + |y_1 - y_2|$$

- No caso de Manhattan, se tratarmos cada eixo separadamente (ou seja, calculando a mediana ponderada de x e de y separadamente),  vamos encontrar um ponto que minimiza a soma total das distâncias.
- Vamos gerar pesos aleatórios para cada casa e uma localização aleatória para elas
- A mediana ponderada é o ponto onde a soma cumulativa dos pesos ultrapassa metade do total dos pesos.
- O primeiro passo é ordenar os valores de x (e seus pesos correspondentes) em ordem crescente
- Depois, calcular a soma total dos pesos.
- O próximo passo é encontrar o menor valor de x onde a soma cumulativa dos pesos atinge pelo menos w/2. Esse valor vai ser a mediana ponderada de x
- Repete os passos para achar a mediana ponderada de y
- E assim, teremos nosso par ordenado da localização dos bombeiros.
- O livro usa o insertion sort para ordenar, então faremos o mesmo.

```python

def insertion_sort(valores, pesos):
    for i in range(1, len(valores)):
        k_valor = valores[i]
        k_peso = pesos[i]
        j = i - 1
       
        while j >= 0 and valores[j] > k_valor :
            valores[j + 1] = valores[j]
            pesos[j + 1] = pesos[j]
            j -= 1
        valores[j + 1] = k_valor 
        pesos[j + 1] = k_peso 


```



```python
def mediana_ponderada(valores, pesos):
    insertion_sort(valores, pesos)
    
    soma_pesos = sum(pesos)
    
    peso_acumulado = 0
    for valor, peso in zip(valores, pesos):
        peso_acumulado += peso 
        if peso_acumulado >= soma_pesos / 2:
            return valor

```

![image](https://github.com/user-attachments/assets/9a0ea9b6-af90-456b-b7ba-f69e2a4d3438)
![image](https://github.com/user-attachments/assets/6e0ad77a-b799-4fa5-b676-16b957d358ca)
![image](https://github.com/user-attachments/assets/51b3592a-25f9-428f-b052-6d4bf89f8f79)


