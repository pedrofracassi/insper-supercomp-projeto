# Projeto Final SuperComp

## Exaustiva

A versão exaustiva do meu código implementa um algoritmo recursivo para encontrar a maior clique no grafo, testando todas as combinações possíveis de vértices, e verificando se cada uma delas é uma clique. O algoritmo começa com uma lista de todos os vértices como candidatos e tenta adicionar cada vértice à clique atual, verificando se ele está conectado a todos os vértices já presentes na clique. Se estiver, o vértice é adicionado à clique atual e a função recursiva é chamada novamente com os novos candidatos. Caso contrário, o vértice é descartado.

### Otimização com Poda

Para melhorar a eficiência do algoritmo exaustivo, foi implementada uma heurística de poda. A ideia é evitar explorar subárvores que não podem conter uma clique maior do que a já encontrada. A poda é realizada verificando se o número de candidatos restantes mais o tamanho da clique atual é menor ou igual ao tamanho da maior clique encontrada até o momento. Se for, a busca é interrompida para essa subárvore, economizando tempo de execução.

## Otimização com OpenMP (gulosa)

A versão otimizada com OpenMP 