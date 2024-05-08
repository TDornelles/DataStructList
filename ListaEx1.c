#include<stdio.h>

// -----------Implementação Lista------------------
typedef struct  {
    int v;
    struct No *prox;
} No;

No* criar_lista()
{
    return NULL;
}

void destruir_lista(No* p)
{
    if (p != NULL)
    {
        destruir_lista(p->prox);
    }
    free(p);
}

No* inserir_na_lista(No *p, int x)
{
    No* novo = malloc(sizeof(No));
    novo->v = x;
    novo->prox = p;
    return novo;
}

No* remover_da_lista(No* p, int x)
{
    No *proximo;
    if (p == NULL) return NULL;
    else if (p->v == x)
    {
        proximo = p->prox;
        free(p);
        return proximo;
    }
    else
    {
        p->prox = remover_da_lista(p->prox, x);
        return p;
    }
}

int buscar_valor(No *p, int x)
{
    while (p!=NULL)
    {
        if (p->v == x) return 1;
        p = p->prox;
    }
    return 0;
}

int imprimir_lista (No *p)
{
    while(p != NULL)
    {
        printf("%d ", p->v);
        if(p->prox != NULL) printf("-> ");
        p = p-> prox;
    }
    printf("\n");
    return 0;
}
// -----------Fim da Implementação Lista------------------

typedef struct
{
    int n;
    No **L;
} Grafo;

Grafo* criar_grafo(int n)
{
    int i;
    Grafo *p = (Grafo *) malloc(sizeof(Grafo));
    p->n = n;
    p->L = (No**) malloc(n*sizeof(No*));
    for(i=0; i < n; i++)
        p->L[i] = criar_lista();
    return p;
}

void destruir_grafo(Grafo *p)
{
    int i;
    for(i = 0; i < p->n; i++)
    {
        destruir_lista(p->L[i]);
    }
    free(p->L);
    free(p);
}

void inserir_aresta(Grafo *p, int u, int v)
{
    p->L[v] = inserir_na_lista(p->L[v], u);
    p->L[u] = inserir_na_lista(p->L[u], v);
}

void remover_aresta(Grafo *p, int u, int v)
{
    p->L[v] = remover_da_lista(p->L[v], u);
    p->L[u] = remover_da_lista(p->L[u], v);
}

int tem_aresta(Grafo *p, int u, int v)
{
    return buscar_valor(p->L[u], v);
}

void imprimir_arestas(Grafo *p)
{
    int u;
    for(u = 0; u < p->n; u++)
    {
        printf("%d: ", u);
        imprimir_lista(p->L[u]);
    }
}

// Busca em Profundidade
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
    No* atual = g->L[v1];
    while(atual != NULL) {
        if(!visitados[atual->v] && busca_recursiva(g, visitados, atual->v, v2))
            return 1;
        atual = atual->prox;
    }
    return 0;
}

// Busca em Largura
int existe_caminho2(Grafo *g, int v1, int v2) {
    int *visitado = (int*) malloc(g->n * sizeof(int));
    int i;
    for(i = 0; i < g->n; i++) visitado[i] = 0;
    int encontrou = busca_largura(g, visitado, v1, v2);
    free(visitado);
    return encontrou;
}

int busca_largura(Grafo *g, int *visitados, int v1, int v2) {
    if (v1 == v2) return 1;
    Fila *fila = fila_criar();
    fila_adicionar(fila, v1);
    visitados[v1] = 1;
    while (fila_tamanho(fila) > 0) {
        int u = fila_topo(fila);
        fila_remover(fila);
        No* atual = g->L[u];
        while (atual != NULL) {
            if (!visitados[atual->v]) {
                if (atual->v == v2) return 1;
                fila_adicionar(fila, atual->v);
                visitados[atual->v] = 1;
            }
            atual = atual->prox;
        }
    }
    return 0;
}

// Componentes Conexas
void visita_recursiva(Grafo *g, int *C, int comp, int u) {
    C[u] = comp;
    No* atual = g->L[u];
    while (atual != NULL) {
        if (C[atual->v] == -1)
            visita_recursiva(g, C, comp, atual->v);
        atual = atual->prox;
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

// Determinar Caminhos
void visita_recursiva2(Grafo* g, int *pai, int v1, int v2) {
    pai[v2] = v1;
    No* atual = g->L[v2];
    while (atual != NULL) {
        if (pai[atual->v] == -1)
            visita_recursiva2(g, pai, v2, atual->v);
        atual = atual->prox;
    }
}

int * encontra_caminhos(Grafo *g, int u) {
    int i, *pai = (int *)malloc(g->n * sizeof(int));
    for(i=0; i < g->n; i++) pai[i] = -1;
    visita_recursiva2(g, pai, u, u);
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
    int n, m, i, u, v;
    printf("Digite a quantidade de vertices e arestas, respectivamente: ");
    scanf("%d %d", &n, &m);
    Grafo *G = criar_grafo(n);
    for(i=0; i < m; i++) {
        printf("Digite a aresta %d: ", i+1);
        scanf("%d %d", &u, &v);
        inserir_aresta(G, u, v);
    }
    imprimir_arestas(G);
    printf("Digite a aresta que sera removida: ");
    scanf("%d %d", &u, &v);
    remover_aresta(G,u,v);
    imprimir_arestas(G);
    destruir_grafo(G);
    return 0;
}
