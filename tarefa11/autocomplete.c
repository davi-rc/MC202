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
    const no* x = a; const no* y = b;
    return x->freq - y->freq;
}

int main(void) {
    no* raiz = NULL; char comando[15]; char palavra[50]; int param; no* no; int size_n; vetor_no* vetor = NULL;

    while (1) {
        scanf(" %s", comando);
        if (!strcmp(comando, "INSERT")) {
            scanf(" %s, %d", palavra, &param);
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
            size_n = length_string(palavra);
            no = procurar_prefixo(raiz, palavra, size_n);
            if (!no) continue;
            vetor = criar_vetor_no(16);
            percorrer_prefixo(no, vetor, palavra, size_n);
            qsort(vetor->data, vetor->size, sizeof(int *), comparar);
            for (int i = 0; i < param; i++) {
                if (i == vetor->size) break;
                printf("(%s,%d) ", vetor->data[i]->palavra, vetor->data[i]->freq);
            }printf("\n");
            excluir_vetor_no(vetor);
        }
        else if (!strcmp(comando, "DELETE")) {
            
        }
        else if (!strcmp(comando, "PRINT")) {
            percorrer_crescente(raiz);
        }
        else if (!strcmp(comando, "EXIT")) {
            break;
        }
    }
}