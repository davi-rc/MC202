#include <stdio.h>

int printar_grafico(int numero, int frequencia, char caractere) {

  printf("%4d |", numero);
  for (int i = 0; i < frequencia; i++) {
    printf("%c", caractere);
  }
  printf(" %d\n", frequencia);

  return 0;
}

int main() {
  int numero, frequencia, i;
  char caractere;

  while (1) {

    i = scanf(" (%d,%d,%c)", &numero, &frequencia, &caractere);

    if (i != 3) {
      break;
    }

    printar_grafico(numero, frequencia, caractere);
  }

  return 0;
}