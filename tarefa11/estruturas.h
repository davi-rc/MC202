#ifndef ESTRUTURAS_H
    #define ESTRUTURAS_H

    typedef struct no{
        struct no* esq;
        struct no* dir;
        char palavra[50];
        int freq;
    }no;

    typedef struct {
    no** data;
    int size;
    int cap;
    }vetor_no;

    void inserir(no** p_raiz, char palavra[], int freq);
    void remover(no** p_raiz, char palavra[]);
    no* procurar(no* raiz, char palavra[]);
    no* procurar_prefixo(no* raiz, char prefixo[], int size_n);
    void percorrer_prefixo(no* raiz, vetor_no* vetor, char prefixo[], int size_n);
    void percorrer_crescente(no* raiz);

    vetor_no* criar_vetor_no(int cap);
    void push_vetor_no(vetor_no* V, no* pno);
    void excluir_vetor_no(vetor_no* V);

#endif