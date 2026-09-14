#include "lista_encadeada.h"
#include <stdlib.h>


void criar(elemento** pp_elemento) {
    if (*pp_elemento != NULL) {
        apagar_lista(pp_elemento);
    }
}

//apaga um lista encadeada inteira e troca o valor do apontador inicial para NULL
void apagar_lista(elemento** pp_elemento) {
    elemento* apontador = *pp_elemento; elemento* apontador_prox;

    while (apontador != NULL) {
        apontador_prox = apontador->prox;
        free(apontador);
        apontador = apontador_prox;
    }

    *pp_elemento = NULL;
}

//retorna 1 se o valor esta presente na lista iniciada por p_elemento, 0 caso contrário
int is_in(int valor, elemento* p_elemento){
    elemento* apontador = p_elemento;

    while(apontador != NULL) {
        if (apontador->valor == valor) return 1;
        apontador = apontador->prox;
    }
    return 0;
}

//insere um elemento com VALOR na lista encadeada antes do elemento apontado por 
//PP_ELEMENTO
void inserir_antes(int valor, elemento** pp_elemento){
    if (*pp_elemento == NULL) {
        *pp_elemento = calloc(1, sizeof(elemento));
        (*pp_elemento)->valor = valor;
        (*pp_elemento)->prox = NULL;
    }else{
        elemento* prox = *pp_elemento;
        *pp_elemento = calloc(1, sizeof(elemento));
        (*pp_elemento)->valor = valor;
        (*pp_elemento)->prox = prox;
    }
}

//remove o elemento apontado por PP_ELEMENTO da lista encadeada
void remover_elemento(elemento** pp_elemento) {
    elemento* p_prox = (*pp_elemento)->prox;
    free(*pp_elemento);
    *pp_elemento = p_prox;
}