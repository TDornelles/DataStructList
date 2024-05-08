#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int v;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **L;
} Grafo;

Grafo* criar_grafo(int n) {
    int i;
    Grafo *p = (Grafo *) malloc(sizeof(Grafo));
    p->n = n;
    p->L = (No**) malloc(n * sizeof(No*));
    for (i = 0; i < n; i++)
        p->L[i] = NULL;
    return p;
}

void inserir_aresta(Grafo *p, int u, int v) {
    No* novo = (No*) malloc(sizeof(No));
    novo->v = v;
    novo->prox = p->L[u];
    p->L[u] = novo;
}

void remover_aresta(Grafo *p, int u, int v) {
    No *atual = p->L[u];
    No *anterior = NULL;

    while (atual != NULL && atual->v != v) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL)
            p->L[u] = atual->prox;
        else
            anterior->prox = atual->prox;
        free(atual);
    }
}

int tem_aresta(Grafo *p, int u, int v) {
    No *atual = p->L[u];
    while (atual != NULL) {
        if (atual->v == v)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void destruir_grafo(Grafo *p) {
    int i;
    for (i = 0; i < p->n; i++) {
        No *atual = p->L[i];
        while (atual != NULL) {
            No *prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(p->L);
    free(p);
}

int e_celebridade(Grafo *g, int pessoa, int seguidores_minimos) {
    int i, seguidores = 0;
    
    for (i = 0; i < g->n; i++) {
        if (i == pessoa)
            continue; // Ignora a própria pessoa

        // Verifica se a pessoa segue alguém
        if (tem_aresta(g, pessoa, i))
            return 0;

        // Conta o número de seguidores
        if (tem_aresta(g, i, pessoa))
            seguidores++;
    }

    // Verifica se o número de seguidores é maior ou igual ao mínimo necessário
    return seguidores >= seguidores_minimos;
}


void encontrar_celebridades(Grafo *g, int seguidores_minimos) {
    int i;
    for (i = 0; i < g->n; i++) {
        if (e_celebridade(g, i, seguidores_minimos)) {
            printf("Pessoa %d é uma celebridade.\n", i);
        }
    }
}

int main() {
    int n, m, i, u, v;
    printf("Digite a quantidade de perfis e conexões, respectivamente: ");
    scanf("%d %d", &n, &m);
    Grafo *G = criar_grafo(n);
    for (i = 0; i < m; i++) {
        printf("Digite a conexão %d: ", i + 1);
        scanf("%d %d", &u, &v);
        inserir_aresta(G, u, v);
    }

    int seguidores_minimos;
    printf("Digite o número mínimo de seguidores para considerar alguém uma celebridade: ");
    scanf("%d", &seguidores_minimos);

    encontrar_celebridades(G, seguidores_minimos);

    destruir_grafo(G);
    return 0;
}

