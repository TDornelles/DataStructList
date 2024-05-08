#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Função para criar um grafo com n vértices
int** criarGrafo(int numVertices) {
    int** grafo = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        grafo[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(int** grafo, int origem, int destino) {
    grafo[origem][destino] = 1;
}

// Função para imprimir o grafo
void imprimirGrafo(int** grafo, int numVertices) {
    printf("Matriz de Adjacências:\n");
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

// Implementação da busca em profundidade (DFS) recursiva
void dfs(int** grafo, int numVertices, int vertice, int* visitado) {
    printf("%d ", vertice); // Imprime o vértice atual
    visitado[vertice] = 1; // Marca o vértice como visitado

    // Percorre todos os vértices adjacentes ao vértice atual
    for (int i = 0; i < numVertices; ++i) {
        if (grafo[vertice][i] && !visitado[i]) { // Se há uma aresta e o vértice adjacente não foi visitado
            dfs(grafo, numVertices, i, visitado); // Chama recursivamente DFS para o vértice adjacente
        }
    }
}

int main() {
    int numVertices, numArestas, verticeInicio;

    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);

    // Criar um grafo com o número de vértices informado pelo usuário
    int** grafo = criarGrafo(numVertices);

    printf("Digite o número de arestas: ");
    scanf("%d", &numArestas);

    // Adicionar as arestas ao grafo
    for (int i = 0; i < numArestas; ++i) {
        int origem, destino;
        printf("Digite a origem e o destino da aresta %d (separados por espaço): ", i + 1);
        scanf("%d %d", &origem, &destino);
        adicionarAresta(grafo, origem, destino);
    }

    // Imprimir o grafo
    imprimirGrafo(grafo, numVertices);

    // Solicitar ao usuário o vértice de início da busca em profundidade
    printf("\nDigite o vértice de início para a busca em profundidade (DFS): ");
    scanf("%d", &verticeInicio);

    // Executar busca em profundidade a partir do vértice de início fornecido pelo usuário
    printf("\nBusca em Profundidade (DFS) a partir do vértice %d:\n", verticeInicio);
    int* visitado = (int*)calloc(numVertices, sizeof(int)); // Vetor para marcar os vértices visitados
    dfs(grafo, numVertices, verticeInicio, visitado);

    // Liberar memória alocada
    for (int i = 0; i < numVertices; ++i) {
        free(grafo[i]);
    }
    free(grafo);
    free(visitado);

    return 0;
}
