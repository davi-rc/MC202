#ifndef ESTRUTURAS
    #define ESTRUTURAS

    typedef struct no {

        long valor;
        int visibilidade;
        int estado;

        struct no* esq;
        struct no* dir;
        int altura;
    }no;

    int inserir(no** no, long valor, int visibilidade, int estado);

    no* procurar(no* raiz, long valor);

    void percorrer(no* raiz);
    void contar(no* raiz, int* a, int* b, int* c);
    void excluir(no* raiz);

#endif