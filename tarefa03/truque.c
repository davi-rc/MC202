#include <math.h>
#include <stdio.h>

int criar_r(int *r, int *v, int size, int n) {
  // primeiro zera o vetor r
  for (int i = 0; i < size; i++) {
    r[i] = 0;
  }
  // cria o vetor r a partir do vetor v
  int m = 0;
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size && m + j < n; j++) { 
      r[i] += v[m + j];
    }
    m += size;
  }
  for (int i = 0; i < n - m; i++) {
    r[size - 1] += v[m + i];
  }
  return 0;
}

int soma(int *v, int *r, int arg1, int arg2, int size) {
  // faz a operacao s e retorna o resultado
  int resultado = 0;

  int i = arg1;
  for (; (i % size != 0) && i <= arg2; i++) {
    resultado += v[i];
  }

  if (i % size == 0) {
    i = i / size;
  } else {
    i = i / size;
    i++;
  }

  for (; (i + 1) * size < arg2; i++) {
    resultado += r[i];
  }

  i = i * size;

  for (; i < arg2 + 1; i++) {
    resultado += v[i];
  }

  return resultado;
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
  criar_r(r, v, size, n);

  // roda o loop principal do programa
  int j = 3;
  char operacao;
  int arg1;
  int arg2;
  int resultado;
  int temporaria;
  while (1) {

    j = scanf(" %c %d %d", &operacao, &arg1, &arg2);
    if (j != 3) {
      break;
    }

    if (operacao == 's') {

      resultado = soma(v, r, arg1, arg2, size);
      printf("%d\n", resultado);

    } else if (operacao == 'a') {

      temporaria = arg1 / size;
      r[temporaria] += (arg2 - v[arg1]);
      v[arg1] = arg2;
    }
  }

  return 0;
}