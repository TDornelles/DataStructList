#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* fila_criar() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void fila_adicionar(Fila* fila, int dado) {
    FilaNode* temp = (FilaNode*)malloc(sizeof(FilaNode));
    temp->dado = dado;
    temp->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = fila->fim = temp;
    } else {
        fila->fim->prox = temp;
        fila->fim = temp;
    }

    fila->tamanho++;
}

int fila_tamanho(Fila* fila) {
    return fila->tamanho;
}

int fila_topo(Fila* fila) {
    if (fila->inicio != NULL) {
        return fila->inicio->dado;
    } else {
        printf("A fila está vazia.\n");
        return -1;
    }
}

void fila_remover(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("A fila está vazia. Nada para remover.\n");
        return;
    }

    FilaNode* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(temp);
    fila->tamanho--;
}

void fila_destruir(Fila* fila) {
    while (fila->inicio != NULL) {
        fila_remover(fila);
    }
    free(fila);
}

