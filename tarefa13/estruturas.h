#ifndef ESTRUTURAS_H
    #define ESTRUTURAS_H

    typedef struct no {

        int grau;
        no** filhos;

        long int ini;
        long int fim;

    }no;

    void criar(no* raiz, int grau);
    void excluir(no* raiz);

    

#endif