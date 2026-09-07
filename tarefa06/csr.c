#include <stdio.h>
#include <stdlib.h>

//#define DEBUG
#ifdef DEBUG
    #include "../bibliotecas/debug.h"
#endif

typedef struct {
    int i;
    int j;
    int val;
}vcc_tripla;

int comparar(const void* x, const void* y) {
    //compara se o elemento vem antes ou depois na matriz para o qsort
    const vcc_tripla* a = x;
    const vcc_tripla* b = y;

    if (a->i > b->i) return 1;
    else if (a->i < b->i) return -1;

    if (a->j > b->j) return 1;
    else if (a->j < b->j) return -1;

    return 0;
    
}

vcc_tripla* montar_vcc(int k) {
    //monta a representação da matriz em vcc e retorna o apontador para o malloc
    
    vcc_tripla* vcc = malloc(k * sizeof(vcc_tripla));

    for (int i = 0; i < k; i++) {
        scanf(" %d %d %d", &vcc[i].i, &vcc[i].j, &vcc[i].val);
    }

    qsort(vcc, k, sizeof(vcc_tripla), comparar);

    return vcc;
}

void atualizar_R(int* R, int m, int inicial) {
    //soma mais um para todos os R's depois da nova entrada
    for (int i = inicial + 1; i < m; i++) {
        R[i] ++;
    }
}

void montar_csr(vcc_tripla* vcc, int k, int m, int* A, int* C, int* R) {
    //a partir da representação em vcc cria os vetores de representação em csr
    
    for (int i = 0; i < k; i++) {
        A[i] = vcc[i].val;
        C[i] = (vcc[i].j);
        atualizar_R(R, m, vcc[i].i);
    }

}

int achar(int m, int sizem, int n, int* A, int* C, int* R) {
    //retorna o valor em m,n da matriz

    if (m > sizem - 2) {
        return 0;
    }
    if (R[m+1] - R[m] != 0) {
        for (int i = R[m]; i < R[m+1]; i++) {
            if (C[i] == n) return A[i];
        }
    }
    return 0;
}

int main(void) {

    int k;
    scanf("%d", &k);

    vcc_tripla* vcc = montar_vcc(k);

    int sizem = vcc[k-1].i + 2;
    int* A = malloc(k * sizeof(int));
    int* C = malloc(k * sizeof(int));
    int* R = calloc(sizem , sizeof(int));

    montar_csr(vcc, k, sizem, A, C, R);

    free(vcc);

    //loop principal do codigo
    int m; int n; int valor;
    while (1) {
        scanf(" %d %d", &m, &n);
        if (m == -1 && n == -1) break;
        else valor = achar(m, sizem, n, A, C, R);
        printf("(%d,%d) = %d\n", m, n, valor);
    }
    
    free(A);
    free(C);
    free(R); 
}