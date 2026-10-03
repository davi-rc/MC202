#include "estruturas.h"
#include <stdlib.h>

pilha* criar_pilha(int cap) {
    pilha* P = malloc(sizeof(pilha));
    P->data = malloc(cap * sizeof(int));
    P->pno = malloc(cap * sizeof(no**));
    P->size = 0;
    P->cap = cap;
    P->mincap = cap;
    return P;
}

void excluir_pilha(pilha** P){
    if(P) {
        free((*P)->data);
        free((*P)->pno);
        free(*P);
        *P = NULL;
    }
}

void push_pilha(pilha *P, int i, no** pno){
    if (P->size == P->cap) {
        int* temp = realloc(P->data, 2 * P->cap * sizeof(int));
        if (temp) {
            P->data = temp;
            P->cap *= 2;
        }
        no*** temp2 = realloc(P->pno, P->cap * sizeof(no**));
        if (temp2) {
            P->pno = temp2;
        }
    }
    P->data[P->size] = i;
    P->pno[P->size] = pno;
    P->size ++;
}

void pop_pilha(pilha *P) {
    if ((P->size-1) < (P->cap/4) && P->cap > P->mincap){
        int* temp = realloc(P->data, (P->cap/2) * sizeof(int));
        if (temp) {
            P->data = temp;
            P->cap /= 2;
        }
        no*** temp2 = realloc(P->pno, (P->cap) * sizeof(no**));
        if (temp2) {
            P->pno = temp2;
        }
    }
    if (P->size) P->size --;
}

vetor* criar_vetor_dinamico(int cap) {
    vetor* V = malloc(sizeof(vetor));
    V->data = malloc(sizeof(int) * cap);
    V->size = 0;
    V->cap = cap;
    V->mincap = cap;
    return V;
}

void limpar_vetor_dinamico(vetor *V) {
    int* temp = realloc(V->data, sizeof (int) * V->mincap);
    V->data = temp;
    V->cap = V->mincap;
    V->size = 0;
}

void push_vetor_dinamico(vetor* V, int i) {
    if (V->size == V->cap) {
        int* temp = realloc(V->data, sizeof (int) * V->cap * 2);
        V->data = temp;
        V->cap *= 2;
    }
    V->data[V->size] = i;
    V->size ++;
}

void excluir_vetor_dinamico(vetor *V) {
    free(V->data);
    free(V);
}

vetor_no* criar_vetor_no(int cap) {
    vetor_no* V = calloc(1, sizeof(vetor_no));
    V->data = malloc(sizeof(no*) * cap);
    V->size = 0;
    V->cap = cap;
    return V;
}

void push_vetor_no(vetor_no* V, no* pno) {
    if (V->size == V->cap) {
        no** temp = realloc(V->data, sizeof (no*) * V->cap * 2);
        V->data = temp;
        V->cap *= 2;
    }
    V->data[V->size] = pno;
    V->size ++;
}

void excluir_vetor_no(vetor_no* V) {
    free(V->data);
    free(V);
}