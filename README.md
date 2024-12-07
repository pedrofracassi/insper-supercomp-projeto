# Projeto Final SuperComp

## Exaustiva

A versão exaustiva do meu código implementa um algoritmo recursivo para encontrar a maior clique no grafo, testando todas as combinações possíveis de vértices, e verificando se cada uma delas é uma clique. O algoritmo começa com uma lista de todos os vértices como candidatos e tenta adicionar cada vértice à clique atual, verificando se ele está conectado a todos os vértices já presentes na clique. Se estiver, o vértice é adicionado à clique atual e a função recursiva é chamada novamente com os novos candidatos. Caso contrário, o vértice é descartado.

### Otimização com Poda

Para melhorar a eficiência do algoritmo exaustivo, foi implementada uma heurística de poda. A ideia é evitar explorar subárvores que não podem conter uma clique maior do que a já encontrada. A poda é realizada verificando se o número de candidatos restantes mais o tamanho da clique atual é menor ou igual ao tamanho da maior clique encontrada até o momento. Se for, a busca é interrompida para essa subárvore, economizando tempo de execução.

**Tempo de execução para um grafo com 100 vértices:** `8436ms ~ 9865ms`

## Otimização com OpenMP (gulosa)

A versão otimizada com OpenMP utiliza um algoritmo guloso e paraleliza a execução da verificação de se um vértice está conectado a todos os outros candidatos à clique.

- **Tempo de execução para um grafo com 100 vértices:** `0ms`
- **Tempo de execução para um grafo com 1000 vértices:** `15ms`
- **Tempo de execução para um grafo com 10.000 vértices:** `1614ms`

## Otimização com MPI

A versão da implementação com MPI divide o grafo por vértice e distribui as partes para os processos. Cada processo executa uma busca exaustiva local e, ao final, o processo mestre reúne os resultados de todos os processos e retorna a maior clique encontrada.