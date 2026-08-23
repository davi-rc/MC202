#include <stdio.h>
#include <math.h>


int criar_r(int* r, int* v, int size, int n) {
    //primeiro zera o vetor r
    for (int i = 0; i < size; i ++) {
        r[i] = 0;
    }
    //cria o vetor r a partir do vetor v
    int m = 0;
    for (int i = 0; i < size - 1; i ++) {
        for (int j = 0; j < size; j ++) {
            r[i] += v[m + j];
        }
        m += size;
    }
    for (int i = 0; i < n-m; i ++) {
        r[size - 1] += v[m + i];
    }
    return 0;
}

int main(void) {

    // cria o vetor v
    int n;
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; i++) {
        scanf(" %d", &v[i]);
    }

    // cria o vetor r
    int size = ceil(sqrt(n));
    int r[size];
    criar_r(r,v,size,n);

    //roda o loop principal do programa
    int i = 3; char operacao; int arg1; int arg2;
    while (i == 3) {
        


    }

}