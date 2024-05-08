#include<stdio.h>

//--------Implementação Fila---------------

// Definição da estrutura do nó da fila
typedef struct No {
    int dado;
    struct No* prox;
} No;

// Definição da estrutura da fila
typedef struct Fila {
    struct No *inicio, *fim;
    int tamanho;
} Fila;

// Função para criar uma nova fila
Fila* fila_criar() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

// Função para adicionar um elemento à fila
void fila_adicionar(Fila* fila, int dado) {
    No* temp = (No*)malloc(sizeof(No));
    temp->dado = dado;
    temp->prox = NULL;

    // Se a fila estiver vazia, o novo nó será tanto o início quanto o fim
    if (fila->fim == NULL) {
        fila->inicio = fila->fim = temp;
    } else {
        // Adiciona o novo nó ao final da fila e atualiza o fim
        fila->fim->prox = temp;
        fila->fim = temp;
    }

    fila->tamanho++;
}

// Função para retornar o tamanho da fila
int fila_tamanho(Fila* fila) {
    return fila->tamanho;
}

// Função para retornar o valor do topo da fila
int fila_topo(Fila* fila) {
    if (fila->inicio != NULL) {
        return fila->inicio->dado;
    } else {
        printf("A fila está vazia.\n");
        return -1; // Retornar um valor especial para indicar que a fila está vazia
    }
}

// Função para remover o primeiro elemento da fila
void fila_remover(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("A fila está vazia. Nada para remover.\n");
        return;
    }

    // Armazena o nó do início e move o início para o próximo nó
    No* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;

    // Se o início ficar NULL, o fim também precisa ser atualizado
    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(temp);
    fila->tamanho--;
}

// Função para destruir a fila, liberando a memória
void fila_destruir(Fila* fila) {
    while (fila->inicio != NULL) {
        fila_remover(fila);
    }
    free(fila);
}

//-----------------------------------------


typedef struct {
    int n; //QtdeVertices
    int **M;
} Grafo;

Grafo* criar_grafo(int n){
    int i, j;
    Grafo *p = (Grafo*) malloc(sizeof(Grafo));
    p->n = n;
    p->M = (int **) malloc(n* sizeof(int *));
    for(i = 0; i < n; i++) {
        p->M[i] = (int*) malloc(n*sizeof(int));
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            p->M[i][j] = 0;
        }
    }
    return p;
}

void destruir_grafo(Grafo *g) {
    int i;
    for(i = 0; i < g->n; i++){
        free(g->M[i]);
    }
    free(g->M);
    free(g);
}

void inserir_aresta(Grafo* g, int v1, int v2) {
    g->M[v1][v2] = 1;
    g->M[v2][v1] = 1;
}

void remover_aresta(Grafo* g, int v1, int v2) {
    g->M[v1][v2] = 0;
    g->M[v2][v1] = 0;
}

int tem_aresta(Grafo* g, int v1, int v2) {
    return g->M[v1][v2];
}

void imprimir_grafo(Grafo* g) {
    int i, j;
    for (i = 0; i < g->n; i++){
        for(j = i+1; j < g->n; j++){
            if(tem_aresta(g,i,j) == 1){
                printf("{%d,%d}\n", i,j);
            }

        }
    }
}

// Busca em profundidade
int existe_caminho(Grafo *g, int v1, int v2) {
    int *visitado = (int*) malloc(g->n * sizeof(int));
    int i;
    for(i = 0; i < g->n; i++) visitado[i] = 0;
    int encontrou = busca_recursiva(g, visitado, v1, v2);
    free(visitado);
    return encontrou;
}

int busca_recursiva(Grafo *g, int *visitados, int v1, int v2) {
    int aux;
    if(v1 == v2) return 1;
    visitados[v1] = 1;
    for(aux = 0; aux < g->n; aux++){
        if(tem_aresta(g,v1,aux) && !visitados[aux])
            if(busca_recursiva(g,visitados,aux,v2))
                return 1;
    }
    return 0;
}

//Busca em largura
int existe_caminho2(Grafo *g, int v1, int v2) {
    int *visitado = (int*) malloc(g->n * sizeof(int));
    int i;
    for(i = 0; i < g->n; i++) visitado[i] = 0;
    int encontrou = busca_largura(g, visitado, v1, v2);
    free(visitado);
    return encontrou;
}

int busca_largura(Grafo *g, int *visitados, int v1, int v2) {
    int encontrou = 0;
    Fila *F = fila_criar();
    fila_adicionar(F, v1);
    visitados[v1] = 1;
    while(fila_tamanho(F) > 0) {
        int i = fila_topo(F);
        fila_remover(F);
        int aux;
        for(aux = 0; aux < g->n; aux++) {
            if(tem_aresta(g,i,aux) && !visitados[aux]) {
                if(aux == v2) {
                    encontrou = 1;
                    break;
                }
                visitados[aux] = 1;
                fila_adicionar(F, aux);
            }
        } if (encontrou) break;
    }
    fila_destruir(F);
    return encontrou;
}

//Componentes conexas
void visita_recursiva(Grafo *g, int *C, int comp, int u) {
    C[u] = comp;
    int aux;
    for(aux = 0; aux < g->n; aux++) {
        if(tem_aresta(g,u,aux) && C[aux] == -1)
            visita_recursiva(g,C,comp,aux);
    }
}

int* encontra_componentes(Grafo *g) {
    int *C = (int *) malloc(g->n * sizeof(int));
    int u;
    for(u = 0; u < g->n; u++) C[u] = -1;
    int comp = 0;
    for(u=0; u < g->n; u++) {
        if(C[u] == -1) {
            visita_recursiva(g,C,comp,u);
            comp++;
        }
    }
    return C;
}

int encontrar_maior(int *C, int tam) {
    int maior = C[0],i; // Assumindo que o primeiro elemento é o maior inicialmente

    for (i = 1; i < tam; i++) {
        if (C[i] > maior) {
            maior = C[i];
        }
    }

    return maior;
}

//Determinar caminhos
void visita_recursiva2(Grafo* g, int *pai, int v1, int v2) {
    pai[v2] = v1;
    int aux;
    for(aux = 0; aux < g->n; aux++) {
        if(tem_aresta(g,v2,aux) && pai[aux] == -1)
            visita_recursiva2(g,pai,v2,aux);
    }
}

int * encontra_caminhos(Grafo *g, int u) {
    int i, *pai = (int *)malloc(g->n * sizeof(int));
    for(i=0; i < g->n; g++) pai[i] = -1;
    visita_recursiva2(g,pai,u,u);
    return pai;
}

void imprimir_caminho_reverso(int *pai, int v) {
    printf("%d ", v);
    if(pai[v]!=v)
        imprimir_caminho_reverso(pai,pai[v]);
}

void imprimir_caminho(int *pai, int v) {
    if(pai[v] != v)
        imprimir_caminho(pai,pai[v]);
    printf("%d ", v);
}

int main() {
    int qtde_arestas, qtde_vertices, i, j, v1, v2;
    Grafo * grafo;

    printf("Digite a qtde de vertices: ");
    scanf("%d", &qtde_vertices);
    printf("Digite a qtde de arestas: ");
    scanf("%d", &qtde_arestas);
    Grafo* g = criar_grafo(qtde_vertices);

    for(i = 0; i < qtde_arestas; i++) {
        printf("Digite a aresta %d: ", i+1);
        scanf("%d%d", &v1, &v2);
        inserir_aresta(g, v1, v2);
    }
    imprimir_grafo(g);
    //Imprimir todos os caminhos
    for(v1 = 0; v1 < qtde_vertices; v1++) {
        for(v2 = v1+1; v2 < qtde_vertices; v2++) {
            if(existe_caminho2(g,v1,v2))
                printf("%d <-> %d\n", v1, v2);
        }
    }
    // Encontra as componentes conexas
    int *C = encontra_componentes(g);
    int c = encontrar_maior(C, qtde_vertices);
    for(i = 0; i <= c; i++) {
        printf("Componente %d: ", i+1);
        for(j = 0; j < qtde_vertices; j++)
            if(C[j] == i) printf("%d ", j);
        printf("\n");
    }

    //Imprimir caminhos
    int *pai = encontra_caminhos(g, 0);
    imprimir_caminho(pai, 2);

    destruir_grafo(g);
    return 0;
}
