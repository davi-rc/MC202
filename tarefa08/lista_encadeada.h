#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

struct elemento{
    int valor;
    struct elemento* prox;
};typedef struct elemento elemento;

void criar(elemento** pp_elemento);
void apagar_lista(elemento** pp_elemento);
int is_in(int valor, elemento* p_elemento);
void inserir_antes(int valor, elemento** pp_elemento);
void remover_elemento(elemento** pp_elemento);

#endif