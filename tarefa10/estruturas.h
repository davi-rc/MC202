#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct no {
    int valor;
    struct no* esq;
    struct no* dir;
}no;

typedef struct {
    no*** pno;
    int* data;
    int size;
    int cap;
    int mincap;
}pilha;

typedef struct {
    int* data;
    int size;
    int cap;
    int mincap;
}vetor;

typedef struct {
    no** data;
    int size;
    int cap;
}vetor_no;

pilha* criar_pilha(int cap);
void excluir_pilha(pilha** P);
void push_pilha(pilha* P, int i, no** pno);
void pop_pilha(pilha* P);

vetor* criar_vetor_dinamico(int cap);
void push_vetor_dinamico(vetor* V, int i);
void limpar_vetor_dinamico(vetor* V);
void excluir_vetor_dinamico(vetor* V);

vetor_no* criar_vetor_no(int cap);
void push_vetor_no(vetor_no* V, no* pno);
void excluir_vetor_no(vetor_no* V);

#endif