#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

int length_string(char palavra[]) {
    int i = 0;
    while (palavra[i] != '\0') i ++;
    return i;
}

int comparar(const void* a, const void* b) {
    const no* x = *(const no**)a;
    const no* y = *(const no**)b;

    if (x->freq != y->freq) return y->freq - x->freq; 
    return strcmp(x->palavra, y->palavra);
}

void printar(vetor_no* vetor, int n) {
    for (int i = 0; i < n && i < vetor->size; i++) {
        printf("(%s,%d) ", vetor->data[i]->palavra, vetor->data[i]->freq);
    }
    printf("\n");
}



int main(void) {
    no* raiz = NULL; char comando[15]; char palavra[50]; int param; no* no; int size_pref; vetor_no* vetor = NULL;

    while (1) {
        scanf(" %s", comando);
        if (!strcmp(comando, "INSERT")) {
            scanf(" %s %d", palavra, &param);
            inserir(&raiz, palavra, param);
        }
        else if (!strcmp(comando, "SEARCH")) {
            scanf(" %s", palavra);
            no = procurar(raiz, palavra);
            if (no) printf("%s %d\n", no->palavra, no->freq);
            else printf("%s not found.\n", palavra);
        }
        else if (!strcmp(comando, "AUTOCOMPLETE")) {
            scanf(" %s %d", palavra, &param);
            size_pref = length_string(palavra);
            no = procurar_prefixo(raiz, palavra, size_pref);
            if (!no) {
                printf("nothing for %s.\n", palavra);
                continue;
            }
            vetor = criar_vetor_no(16);
            percorrer_prefixo(no, vetor, palavra, size_pref);
            qsort(vetor->data, vetor->size, sizeof(vetor->data[0]), comparar);
            printar(vetor, param);
            excluir_vetor_no(vetor);
        }
        else if (!strcmp(comando, "DELETE")) {
            scanf(" %s", palavra);
            excluir(&raiz, palavra);
        }
        else if (!strcmp(comando, "PRINT")) {
            if (!raiz) {
                printf("the dictionary is empty.\n");
                continue;
            }
            percorrer_crescente(raiz);
            printf("\n");
        }
        else if (!strcmp(comando, "EXIT")) {
            apagar_arvore(raiz);
            break;
        }
    }
}