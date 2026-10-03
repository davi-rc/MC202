#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"

no** adicionar_pai(no** pno, int i) {
    no* temp = *pno;
    *pno = malloc(sizeof(no));
    (*pno)->valor = i;
    (*pno)->esq = temp;
    (*pno)->dir = NULL;
    return pno;
}

no** adicionar_filho (no** pno, int i) {
    (*pno)->dir = malloc(sizeof(no));
    (*pno)->dir->valor = i;
    (*pno)->dir->esq = NULL;
    (*pno)->dir->dir = NULL;
    return &((*pno)->dir);
}

void criar(int* A, no** raiz) {

    int i = 0; int m = 0; int k = 0; pilha* P = criar_pilha(16); no** temp;
    
    while (A[i] != -1) {
        k = P->size;
        m = P->size;
        while (m > 0 && A[i] < P->data[m-1]) {
            m--;
            pop_pilha(P);
        }
        if (m == 0) {
            temp = adicionar_pai(raiz, i);
            push_pilha(P, A[i], temp);
        }
        else if (m == k) {
            temp = adicionar_filho(P->pno[m-1], i);
            push_pilha(P, A[i], temp);
        }
        else {
            temp = adicionar_pai(P->pno[m], i);
            push_pilha(P, A[i], temp);
        }
        i++;
    }
    excluir_pilha(&P);
}

void printar_arvore(no* R) {

    int inicial = 0; int size = 1; int temp = 0;

    vetor_no* V = criar_vetor_no(16); 
    push_vetor_no(V, R);

    while(size != 0) {
        temp = 0;
        for (int i = 0; i < size; i ++) {
            printf("%d ", V->data[inicial + i]->valor);
            if(V->data[inicial + i]->esq) {
                push_vetor_no(V, V->data[inicial + i]->esq);
                temp++;
            }
            if(V->data[inicial + i]->dir) {
                push_vetor_no(V, V->data[inicial + i]->dir);
                temp++;
            }
        }
        printf("\n");
        inicial += size;
        size = temp;
    }

    printf("\n");
    excluir_vetor_no(V);
}

void excluir_arvore (no* R) {
    if (!R) return;
    excluir_arvore(R->esq);
    excluir_arvore(R->dir);
    free(R);
}

int main(void) {

    int n; int a;

    vetor* A = criar_vetor_dinamico(16);
    no* R;

    while (1) {
        R = NULL;

        scanf(" %d", &n);
        if (n <= 0) break;        
        for (int i = 0; i < n; i ++) {
            scanf(" %d", &a);
            push_vetor_dinamico(A, a);
        }push_vetor_dinamico(A, -1);

        criar(A->data,&R);
        limpar_vetor_dinamico(A);

        printar_arvore(R);

        excluir_arvore(R);
    }

    excluir_vetor_dinamico(A);
}