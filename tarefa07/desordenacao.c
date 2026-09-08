#include <stdio.h>  
#include <stdlib.h>

typedef struct {
    char sequencia[51];
    int desordenação;
}dna;

int achar_desordenacao(dna cadeia, int tamanho) {
    int desordem = 0;
    int a = 0; int c = 0; int g = 0; int t = 0;
    for (int i = tamanho-1; i >= 0; i--) {
        if (cadeia.sequencia[i] == 'A'){
            a++;
        }else if (cadeia.sequencia[i] == 'C'){
            c++;
            desordem += a;
        }else if (cadeia.sequencia[i] == 'G'){
            g++;
            desordem += a + c;
        }else if (cadeia.sequencia[i] == 'T'){
            t++;
            desordem += a + c + g;
        }
    }
    return desordem;
}

int comparar(const void* a, const void* b) {
    const dna* x = a;
    const dna* y = b;

    return x->desordenação - y->desordenação;
}

int main(void) {
    int entradas; int n_cadeias; int tamanho;

    scanf(" %d", &entradas);

    dna cadeias[100];

    for (int entrada = 0; entrada < entradas; entrada++) {
        scanf(" %d %d", &tamanho, &n_cadeias);

        for (int j = 0; j < n_cadeias; j ++) {
            scanf(" %s", cadeias[j].sequencia);
        }
        for (int j = 0; j < n_cadeias; j ++) {
            cadeias[j].desordenação = achar_desordenacao(cadeias[j], tamanho);
        }

        qsort(cadeias, n_cadeias, sizeof(dna), comparar);
        
        for(int j = 0; j < n_cadeias; j++) {
            printf("%s\n", cadeias[j].sequencia);
        }
        printf("\n");
    }
}