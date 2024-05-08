#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um grafo
typedef struct {
    int n;        // Número de vértices
    int **matriz; // Matriz de adjacências
} Digrafo;

// Função para criar um novo digrafo
Digrafo *criar_digrafo(int n) {
    Digrafo *grafo = (Digrafo *)malloc(sizeof(Digrafo));
    grafo->n = n;
    grafo->matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grafo->matriz[i] = (int *)calloc(n, sizeof(int));
    }
    return grafo;
}

// Função para adicionar uma aresta ao digrafo
void adicionar_aresta(Digrafo *grafo, int u, int v) {
    grafo->matriz[u][v] = 1;
}

// Função para imprimir a matriz de adjacências do digrafo
void imprimir_digrafo(Digrafo *grafo) {
    for (int i = 0; i < grafo->n; i++) {
        for (int j = 0; j < grafo->n; j++) {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para transformar um digrafo G em G' invertendo as arestas
Digrafo *transformar_em_grafo_invertido(Digrafo *grafo) {
    Digrafo *grafo_invertido = criar_digrafo(grafo->n);
    for (int i = 0; i < grafo->n; i++) {
        for (int j = 0; j < grafo->n; j++) {
            if (grafo->matriz[i][j] == 1) {
                adicionar_aresta(grafo_invertido, j, i); // Inverte a direção da aresta
            }
        }
    }
    return grafo_invertido;
}

int main() {
    int n, u, v;
    printf("Digite o número de vértices do digrafo: ");
    scanf("%d", &n);

    // Criar um digrafo G de exemplo
    Digrafo *G = criar_digrafo(n);
    printf("Digite as arestas do digrafo (digite -1 -1 para parar):\n");
    while (1) {
        printf("Digite a aresta (u, v): ");
        scanf("%d %d", &u, &v);
        if (u == -1 || v == -1) {
            break;
        }
        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Vértices inválidos. Por favor, tente novamente.\n");
            continue;
        }
        adicionar_aresta(G, u, v);
    }

    // Imprimir digrafo G original
    printf("\nMatriz de adjacências do digrafo G:\n");
    imprimir_digrafo(G);

    // Transformar G em G'
    Digrafo *G_invertido = transformar_em_grafo_invertido(G);

    // Imprimir digrafo G' invertido
    printf("\nMatriz de adjacências do digrafo G' (invertido):\n");
    imprimir_digrafo(G_invertido);

    // Liberar memória alocada
    for (int i = 0; i < G->n; i++) {
        free(G->matriz[i]);
    }
    free(G->matriz);
    free(G);
    
    for (int i = 0; i < G_invertido->n; i++) {
        free(G_invertido->matriz[i]);
    }
    free(G_invertido->matriz);
    free(G_invertido);

    return 0;
}

