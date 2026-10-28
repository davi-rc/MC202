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
    int comp;
    while (raiz) {
        comp = strncmp((raiz)->palavra, prefixo, size_n);
        if (comp == 0){
            percorrer_prefixo(raiz->esq, vetor, prefixo, size_n);
            push_vetor_no(vetor, raiz);
            percorrer_prefixo(raiz->dir, vetor, prefixo, size_n);
            return;
        }
        else if (comp < 0) {
            raiz = raiz->dir;
        }
        else if (comp > 0) {
            raiz = raiz->esq;
        }
    }
}

no* achar_antecessor(no* raiz) {
    no* pai = raiz;
    raiz = raiz->esq;
    while (raiz) {
        if (raiz->dir) {
            pai = raiz;
            raiz = raiz->dir;
        }
        else break;
    }

    if (pai->esq == raiz) pai->esq = raiz->esq;
    else pai->dir = raiz->esq;

    return raiz;

}

void excluir(no** raiz, char palavra[]) {
    no* temp = NULL;
    no* pai = NULL;
    no* no = *raiz; 
    int lado = -1;
    int comp;

    while (no) {
        comp = strcmp((no)->palavra, palavra);
        if (comp == 0){
            break;
        }
        else if (comp > 0) {
            pai = no;
            lado = 0;
            no = no->esq;
        }
        else if (comp < 0) {
            pai = no;
            lado = 1;
            no = no->dir;
        }
    }
    if (!no) return;

    if (!no->dir && !no->esq) {
        if (lado == -1) *raiz = NULL;
        else if (lado == 0) pai->esq = NULL;
        else pai -> dir = NULL;
    }

    else if (!no->esq) {
        if (lado == -1) *raiz = no->dir;
        else if (lado == 0) pai->esq = no->dir;
        else pai -> dir = no->dir;
    }

    else if (!no->dir) {
        if (lado == -1) *raiz = no->esq;
        else if (lado == 0) pai->esq = no->esq;
        else pai -> dir = no->esq;
    }

    else {
        temp = achar_antecessor(no);
        if (lado == -1) *raiz = temp;
        else if (lado == 0) pai->esq = temp;
        else pai->dir = temp;

        temp->esq = no->esq;
        temp->dir = no->dir;
    }

    free(no);

}

void percorrer_crescente(no* raiz) {
    if (!raiz) return;
    percorrer_crescente(raiz->esq);
    printf("%s ", raiz->palavra);
    percorrer_crescente(raiz->dir);
}

void apagar_arvore(no* raiz) {
    if (!raiz) return;
    apagar_arvore(raiz->esq);
    apagar_arvore(raiz->dir);
    free(raiz);
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