#include <stdio.h>
#include "debug.h"

void printar_matriz(int m, int n, int matriz[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; i++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void printar_matriz_alloc(int m, int n, int** matriz) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void printar_string(char* string) {
  for (int i = 0;; i++) {
    printf("%c", string[i]);
    if (string[i] == '\0') {
      break;
    }
  }
  printf("|\n");
}

void printar_vetor_alloc(int size, int *vetor) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}