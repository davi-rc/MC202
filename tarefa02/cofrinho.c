#include <stdio.h>

int rodar_teste(int n_depositos, int teste) {

    int J, Z;

    int diferenca = 0;

    printf("Teste %d\n", teste);

    for (int i = 0; i < n_depositos; i++) {
        scanf("%d %d", &J, &Z);
        diferenca += J - Z;
        printf("%d\n", diferenca);
    }

    printf("\n");
    
    return 0;
}

int main(void) {

    int n_depositos;
    scanf("%d", &n_depositos);

    int teste = 1;

    while (n_depositos != 0) {
        rodar_teste(n_depositos, teste);
        teste ++;
        scanf("%d", &n_depositos);
    }

}

