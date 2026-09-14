#ifndef DEBUG_H
#define DEBUG_H

void printar_matriz(int m, int n, int matriz[m][n]);
void printar_matriz_alloc(int m, int n, int** matriz);
void printar_string(char* string);
void printar_vetor_alloc(int size, int* vetor);

#define encadeada
#ifdef encadeada
    #include "../tarefa08/lista_encadeada.h"
    void printar_lista_encadeada(elemento* p_elemento);
#endif

#endif