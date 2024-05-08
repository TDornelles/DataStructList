#ifndef FILA_H
#define FILA_H

typedef struct FilaNode {
    int dado;
    struct FilaNode* prox;
} FilaNode;

typedef struct {
    FilaNode *inicio, *fim;
    int tamanho;
} Fila;

Fila* fila_criar();
void fila_adicionar(Fila* fila, int dado);
int fila_tamanho(Fila* fila);
int fila_topo(Fila* fila);
void fila_remover(Fila* fila);
void fila_destruir(Fila* fila);

#endif /* FILA_H */

