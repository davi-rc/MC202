    #include "estruturas.h"
    #include <stdio.h>
    #include <stdlib.h>

    #define max(a, b) ((a) > (b) ? (a) : (b))
    #define altura(pno) ((pno) ? (pno)->altura : 0)

    void rotacionar_dir(no** pno) {
        no* temp = *pno;

        *pno = (*pno)->esq;

        no* temp2 = (*pno)->dir;

        (*pno)->dir = temp;

        (*pno)->dir->esq = temp2;

        (*pno)->dir->altura = max(altura((*pno)->dir->esq), altura((*pno)->dir->dir)) + 1;
        (*pno)->altura = max(altura((*pno)->esq), altura((*pno)->dir)) + 1;
        
    }

    void rotacionar_esq(no** pno) {
        no* temp = *pno;

        *pno = (*pno)->dir;

        no* temp2 = (*pno)->esq;

        (*pno)->esq = temp;

        (*pno)->esq->dir = temp2;

        (*pno)->esq->altura = max(altura((*pno)->esq->esq), altura((*pno)->esq->dir)) + 1;
        (*pno)->altura = max(altura((*pno)->esq), altura((*pno)->dir)) + 1;
        
    }

    int inserir(no** pno, long valor, int visibilidade, int estado) {

        int fator; int retorno;

        //insere o no
        if (!(*pno)) {
            (*pno) = malloc(sizeof(no));
            (*pno)->esq = NULL;
            (*pno)->dir = NULL;
            (*pno)->altura = 1;
            (*pno)->valor = valor;
            (*pno)->visibilidade = visibilidade;
            (*pno)->estado = estado;

            return 1;
        }

        if((*pno)->valor == valor) return 0;
        else if ((*pno)->valor > valor) {
            retorno = inserir(&(*pno)->esq, valor, visibilidade, estado);
        }
        else {
            retorno = inserir(&(*pno)->dir, valor, visibilidade, estado);
        }

        //volta checando os fatores e balanceando a arvore
        (*pno)->altura = max(altura((*pno)->esq), altura((*pno)->dir)) + 1;


        fator = altura((*pno)->dir) - altura((*pno)->esq);

        if (fator == 2) {
            if (altura((*pno)->dir->dir) - altura((*pno)->dir->esq) < 0) {
                rotacionar_dir(&(*pno)->dir);
            }
            rotacionar_esq(pno);
            return retorno;
        }
        else if (fator == -2) {
            if (altura((*pno)->esq->dir) - altura((*pno)->esq->esq) > 0) {
                rotacionar_esq(&(*pno)->esq);
            }
            rotacionar_dir(pno);
            return retorno;
        }

        return retorno;
    }

    no* procurar(no* raiz, long valor) {
        while(raiz) {
            if (raiz->valor == valor) return raiz;
            else if (raiz->valor < valor) raiz = raiz->dir;
            else if (raiz->valor > valor) raiz = raiz->esq;
        }
        return NULL;
    }

    void percorrer(no *raiz) {
        if (raiz->esq) percorrer(raiz->esq);
        printf("%ld ", raiz->valor);
        if (raiz->dir) percorrer(raiz->dir);
    }


    void excluir(no *raiz) {
        if (raiz->esq) excluir(raiz->esq);
        if (raiz->dir) excluir(raiz->dir);
        free(raiz);
    }