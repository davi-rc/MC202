#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inserir(no** p_raiz, char palavra[], int freq) {
    int comp;
    while (*p_raiz) {
        comp = strcmp((*p_raiz)->palavra, palavra);
        if (comp == 0){
            (*p_raiz)->freq = freq;
            return;
        }
        else if (comp < 0) {
            p_raiz = &(*p_raiz)->dir;
        }
        else if (comp > 0) {
            p_raiz = &(*p_raiz)->esq;
        }
    }
    *p_raiz = malloc(sizeof(no));
    (*p_raiz)->dir = NULL;
    (*p_raiz)->esq = NULL;
    strcpy((*p_raiz)->palavra, palavra);
    (*p_raiz)->freq = freq;

}

void remover(no** p_raiz, char palavra[]){
    
}

no* procurar(no* raiz, char palavra[]) {
    int comp;
    while (raiz) {
        comp = strcmp((raiz)->palavra, palavra);
        if (comp == 0){
            return raiz;
        }
        else if (comp < 0) {
            raiz = raiz->dir;
        }
        else if (comp > 0) {
            raiz = raiz->esq;
        }
    }
    return NULL;
}

no* procurar_prefixo(no* raiz, char prefixo[], int size_n) {
    int comp;
    while (raiz) {
        comp = strncmp((raiz)->palavra, prefixo, size_n);
        if (comp == 0){
            return raiz;
        }
        else if (comp < 0) {
            raiz = raiz->dir;
        }
        else if (comp > 0) {
            raiz = raiz->esq;
        }
    }
    return NULL;
}

void percorrer_prefixo(no* raiz, vetor_no* vetor, char prefixo[], int size_n) {
    if (!raiz || strncmp(raiz->palavra, prefixo, size_n )) return;
    percorrer_prefixo(raiz->esq, vetor, prefixo, size_n);
    percorrer_prefixo(raiz->dir, vetor, prefixo, size_n);
    push_vetor_no(vetor, raiz); 
}

void percorrer_crescente(no* raiz) {
    if (!raiz) return;
    percorrer_crescente(raiz->esq);
    printf("%s ", raiz->palavra);
    percorrer_crescente(raiz->dir);
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