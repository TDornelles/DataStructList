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
