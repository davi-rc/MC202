#include "estruturas.h"
#include <stdio.h>
#include <string.h>

int visibilidade_to_int(char visibilidade[16]) {
    if (visibilidade[0] == 'r') return 1;
    else if (visibilidade[0] == 'i') return 2;
    else if (visibilidade[0] == 'p') return 3;
    else if (visibilidade[0] == 'b') return 4;
    return 0;
}

int estado_to_int(char estado[16]) {
    if (estado[0] == 'a') return 1;
    else if (estado[0] == 'd') return 2;
    else if (estado[0] == 'o') return 3;
    return 0;
}

char* visibilidade_to_str(int visibilidade) {
    if (visibilidade == 1) return "restrito";
    else if (visibilidade == 2) return "interno";
    else if (visibilidade == 3) return "publico";
    else if (visibilidade == 4) return "bloqueado";
    return 0;
}

char* estado_to_str(int estado) {
    if (estado == 1) return "atualizado";
    else if (estado == 2) return "desatualizado";
    else if (estado == 3) return "obsoleto";
    return 0;
}

int main(void) {
    no* raiz = NULL; no* temp; char comando; long valor; char visibilidade[16]; char estado[16]; int estadoint; int a = 0; int b = 0; int c = 0;

    while (1) {
        scanf(" %c", &comando);

        if (comando == 'i') {
            scanf(" %ld %s %s", &valor, visibilidade, estado);
            estadoint = estado_to_int(estado);
            if (inserir(&raiz, valor, visibilidade_to_int(visibilidade), estadoint)) {
                if (estadoint == 1) a++;
                else if (estadoint == 2) b++;
                else if (estadoint == 3) c++;
            }
            
        }
        else if (comando == 'a') {
            scanf(" %ld %s %s", &valor, visibilidade, estado);
            temp = procurar(raiz, valor);
            if (!temp) continue;
            if (temp->estado == 1) a--;
            else if (temp->estado == 2) b--;
            else if (temp->estado == 3) c--;

            temp->visibilidade = visibilidade_to_int(visibilidade);
            temp->estado = estado_to_int(estado);

            if (temp->estado == 1) a++;
            else if (temp->estado == 2) b++;
            else if (temp->estado == 3) c++;

        }
        else if (comando == 'b') {
            scanf(" %ld", &valor);
            temp = procurar(raiz, valor);
            if (!temp) {
                printf("%ld nao existe\n", valor);
                continue;
            }
            printf("%ld, %s, %s\n", temp->valor, visibilidade_to_str(temp->visibilidade), estado_to_str(temp->estado));
        }
        else if (comando == 'l') {
            if (!raiz) {
                printf("indice vazio\n");
                continue;
            }
            printf("documentos: ");
            percorrer(raiz);
            printf("\n");
        }
        else if (comando == 't') {
            printf("atualizado: %d, desatualizado: %d, obsoleto: %d\n", a, b, c);
        }
        else if (comando == 'f') {
            excluir(raiz);
            break;
        }

    }
}