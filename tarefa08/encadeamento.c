#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

//#define DEBUG
#ifdef DEBUG
    #include "../bibliotecas/debug.h"
#endif

int comparar(const void* a, const void* b){
    const int* x = a; const int* y = b;
    return *x - *y;
}

//insere os SIZEOFLISTA elementos de uma LISTA em ordem na lista encadeada iniciada por *PP_ELEMENTO,
//ignorando elementos repetidos
void inserir_lista(int* lista, int sizeoflista, elemento** pp_elemento) {
    if (sizeoflista == 0) return;
    qsort(lista, sizeoflista, sizeof(int), comparar);
    int i = 0;

    if ((*pp_elemento) == NULL) {
        inserir_antes(lista[i], pp_elemento);
        i++;
    }

    while ((*pp_elemento) != NULL && i < sizeoflista) {
        if (lista[i] < (*pp_elemento)->valor) {
            inserir_antes(lista[i], pp_elemento);
            i++;
        }
        else if (lista[i] == (*pp_elemento)->valor){
            i++;
        }
        else if (lista[i] > (*pp_elemento)->valor){
            pp_elemento = &(*pp_elemento)->prox;
        }
    }

    while (i < sizeoflista) {
        if (i > 0 && lista[i] == lista[i-1]) {
            i++;
            continue;
        }
        inserir_antes(lista[i], pp_elemento);
        i++;
        pp_elemento = &(*pp_elemento)->prox;
    }
    
}

//remove os SIZEOFLISTA elementos de LISTA da lista encadeada apontada por PP_ELEMENTO
void remover_lista(int* lista, int sizeoflista, elemento** pp_elemento) {
    qsort(lista, sizeoflista, sizeof(int), comparar);
    int i = 0;

    while ((*pp_elemento) != NULL && i < sizeoflista) {
        if (lista[i] < (*pp_elemento)->valor) {
            i++;
        }
        else if (lista[i] == (*pp_elemento)->valor) {
            remover_elemento(pp_elemento);
            i++;
        }
        else if (lista[i] > (*pp_elemento)->valor) {
            pp_elemento = &(*pp_elemento)->prox;
        }
    }
}

//recolhe os parametros para o comando i e roda a funcao de montar a nova lista
void comando_i(elemento** pp_elemento) {
    int param_1; int* param_alloc;

    scanf(" %d", &param_1);
    param_alloc = malloc(param_1 * sizeof(int));
    for (int i = 0; i < param_1; i ++) {
        scanf(" %d", &param_alloc[i]);
    }
    inserir_lista(param_alloc, param_1, pp_elemento);
    free(param_alloc);
}

void comando_r(elemento** pp_elemento) {
    int param_1; int* param_alloc;

    scanf(" %d", &param_1);
    param_alloc = malloc(param_1 * sizeof(int));
    for (int i = 0; i < param_1; i ++) {
        scanf(" %d", &param_alloc[i]);
    }
    remover_lista(param_alloc, param_1, pp_elemento);
    free(param_alloc);
}

//atribui a união entre a lista apontada por P_ELE_A e a lista apontada por P_ELE_B à 
//lista apontada por *PP_ELEMENTO
void comando_u(elemento** pp_elemento, elemento* p_ele_a, elemento* p_ele_b) {
    int* uniao = malloc(16 * sizeof(int));
    int maxsize = 16;
    int size = 0;
    //faz a uniao das duas listas
    while(p_ele_a != NULL || p_ele_b != NULL){
        if (size == maxsize) {
            void* temp = realloc(uniao, maxsize * 2 * sizeof(int));
            if (temp == NULL) exit(EXIT_FAILURE);
            else uniao = temp;
            maxsize *= 2;
        }
        if ((p_ele_a != NULL && p_ele_b != NULL) && p_ele_a->valor == p_ele_b->valor) {
            uniao[size] = p_ele_a->valor;
            p_ele_b = p_ele_b->prox;
            p_ele_a = p_ele_a->prox;
            size++;
        }
        else if (p_ele_a == NULL || (p_ele_b != NULL && p_ele_a->valor > p_ele_b->valor)) {
            uniao[size] = p_ele_b->valor;
            p_ele_b = p_ele_b->prox;
            size++;
        }
        else if (p_ele_b == NULL || (p_ele_a != NULL && p_ele_a->valor < p_ele_b->valor)) {
            uniao[size] = p_ele_a->valor;
            p_ele_a = p_ele_a->prox;
            size++;
        }
    }
    //atribui a uniao a outra lista
    apagar_lista(pp_elemento);
    inserir_lista(uniao, size, pp_elemento);
    free(uniao);
}

//atribui a interseção entre a lista apontada por P_ELE_A e a lista apontada por P_ELE_B
//à lista apontada por *PP_ELEMENTO
void comando_n(elemento** pp_elemento, elemento* p_ele_a, elemento* p_ele_b) {
    int* intersecao = malloc(16 * sizeof(int));
    int maxsize = 16;
    int size = 0;
    //faz a interseção das listas
    while(p_ele_a != NULL && p_ele_b != NULL){
        if (size == maxsize) {
            void* temp = realloc(intersecao, maxsize * 2 * sizeof(int));
            if (temp == NULL) exit(EXIT_FAILURE);
            else intersecao = temp;
            maxsize *= 2;
        }
        if (p_ele_a->valor == p_ele_b->valor) {
            intersecao[size] = p_ele_a->valor;
            p_ele_b = p_ele_b->prox;
            p_ele_a = p_ele_a->prox;
            size++;
        }
        else if (p_ele_a->valor > p_ele_b->valor) {
            p_ele_b = p_ele_b->prox;
        }
        else if (p_ele_a->valor < p_ele_b->valor) {
            p_ele_a = p_ele_a->prox;
        }
    }
    //atribui a interseção a outra lista
    apagar_lista(pp_elemento);
    inserir_lista(intersecao, size, pp_elemento);
    free(intersecao);
}

//atribui a diferenca entre a lista apontada por P_ELE_A e a lista apontada por P_ELE_B
//à lista apontada por *PP_ELEMENTO
void comando_m(elemento** pp_elemento, elemento* p_ele_a, elemento* p_ele_b) {
    int* diferenca = malloc(16 * sizeof(int));
    int maxsize = 16;
    int size = 0;
    //faz a interseção das listas
    while(p_ele_a != NULL){
        if (size == maxsize) {
            void* temp = realloc(diferenca, maxsize * 2 * sizeof(int));
            if (temp == NULL) exit(EXIT_FAILURE);
            else diferenca = temp;
            maxsize *= 2;
        }
        if ((p_ele_b != NULL) && p_ele_a->valor == p_ele_b->valor) {
            p_ele_b = p_ele_b->prox;
            p_ele_a = p_ele_a->prox;
        }
        else if ((p_ele_b == NULL) || (p_ele_a->valor < p_ele_b->valor)) {
            diferenca[size] = p_ele_a->valor;
            p_ele_a = p_ele_a->prox;
            size ++;
        }
        else if ((p_ele_b != NULL) && p_ele_a->valor > p_ele_b->valor) {
            p_ele_b = p_ele_b->prox;
        }
    }
    //atribui a interseção a outra lista
    apagar_lista(pp_elemento);
    inserir_lista(diferenca, size, pp_elemento);
    free(diferenca);
}

void printar_lista_encadeada(elemento* p_elemento) {
    printf("{");
    if (p_elemento != NULL){
        printf("%d", (*p_elemento).valor);
        p_elemento = (*p_elemento).prox;
    }
    while (p_elemento != NULL) {
        printf(", %d", (*p_elemento).valor);
        p_elemento = (*p_elemento).prox;
    }printf("}\n");
}

int main() {

    elemento* p_elemento[128] = {NULL}; char comando; int param; int param_a; int param_b;
    
    //loop principal do programa
    while (1){
        scanf(" %c", &comando);

        if (comando == 'c') {
            scanf(" %d", &param);
            criar(&p_elemento[param]);
        }
        else if (comando == 'i') {
            scanf(" %d", &param);
            comando_i(&p_elemento[param]);
        }
        else if (comando == 'r') {
            scanf(" %d", &param);
            comando_r(&p_elemento[param]);
        }
        else if (comando == 'u') {
            scanf(" %d %d %d", &param, &param_a, &param_b);
            comando_u(&p_elemento[param], p_elemento[param_a], p_elemento[param_b]);
        }
        else if (comando == 'n') {
            scanf(" %d %d %d", &param, &param_a, &param_b);
            comando_n(&p_elemento[param], p_elemento[param_a], p_elemento[param_b]);
        }
        else if (comando == 'm') {
            scanf(" %d %d %d", &param, &param_a, &param_b);
            comando_m(&p_elemento[param], p_elemento[param_a], p_elemento[param_b]);
        }
        else if (comando == 'e') {
            scanf(" %d %d", &param, &param_a);
            if(is_in(param_a, p_elemento[param])) printf("%d esta em C%d\n", param_a, param);
            else printf("%d nao esta em C%d\n", param_a, param);
        }
        else if (comando == 'p') {
            scanf(" %d", &param);
            printf("C%d = ", param);
            printar_lista_encadeada(p_elemento[param]);
        }
        else if(comando == 't') {
            for (int i = 0; i < 128; i++) apagar_lista(&p_elemento[i]);
            break;
        }
    }

}