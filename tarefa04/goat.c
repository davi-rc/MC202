#include <stdio.h>

int is_vogal(char character) {
  // retorna 1 se for vogal
  if (character == 'a' || character == 'e' || character == 'i' ||
      character == 'o' || character == 'u' || character == 'A' ||
      character == 'E' || character == 'I' || character == 'O' ||
      character == 'U') {
    return 1;
  }
  return 0;
}

int is_letra(int ascii) {
  // retorna 1 se for letra
  if ((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122) ||
      ascii == 32) {
    return 1;
  }
  return 0;
}

int is_numero(int ascii) {
  // retorna 1 se for numero
  if (ascii >= 48 && ascii <= 57) {
    return 1;
  }
  return 0;
}

int printar_array(char *array) {
  for (int i = 0;; i++) {
    printf("%c", array[i]);
    if (array[i] == '\0') {
      break;
    }
  }
  printf("|\n");

  return 0;
}

void printar_sufixo(char consoante, int n_letras) {
  if (consoante != '*') {
    printf("%c", consoante);
  }
  if (n_letras > 0) {
    printf("ma");
  }
  for (int i = 0; i < n_letras; i++) {
    printf("a");
  }
}

int main(void) {

  // le a entrada
  char frase[400000];
  int ascii;
  int ascii_temp;
  long long somatorio;
  long long somatorio_temp;
  int escrevendo_palavra;
  int n_letras;
  char consoante;
  // variavel de debugar
  // int p = 0;

  while (fgets(frase, sizeof(frase), stdin) != NULL) {

    // trecho para debugar
    // if (p == 6) {return 0;}

    somatorio = 0;
    somatorio_temp = 0;
    escrevendo_palavra = 0;
    n_letras = 0;
    consoante = '*';

    // passa pela string retirando simbolos e numeros, enquanto soma os numeros
    for (int i = 0;; i++) {
      ascii = frase[i];
      if (frase[i] == '\0') {
        break;
      }
      if (ascii == 1) {
        continue;
      }

      if (!is_letra(ascii)) {
        if (is_numero(ascii)) {
          for (int j = 0;; j++) {
            ascii_temp = frase[i + j];
            if (is_numero(ascii_temp)) {
              somatorio_temp *= 10;
              somatorio_temp += (ascii_temp - 48);
              frase[i + j] = '\x01';
              continue;
            }
            break;
          }
          somatorio += somatorio_temp;
          somatorio_temp = 0;
        }
        frase[i] = '\x01';
      }
    }

    if (somatorio == 1) {
      printf("1 goat says:");
    } else {
      printf("%lld goats say:", somatorio);
    }

    // passa pela string aplicando as regras 1, 2 e 3 enquanto printa

    for (int i = 0;; i++) {
      ascii = frase[i];
      if (frase[i] == '\0') {
        printar_sufixo(consoante, n_letras);
        break;
      } else if (frase[i] == '\x01') {
        continue;
      } else if (ascii == 32) {
        if (frase[i + 1] == ' ') {
          continue;
        } else if (frase[i + 1] == '\0') {
          continue;
        } else if (escrevendo_palavra) {
          printar_sufixo(consoante, n_letras);
          n_letras = 0;
          consoante = '*';
          escrevendo_palavra = 0;
          continue;
        }
        continue;
      }

      if (!escrevendo_palavra) {
        printf(" ");
        n_letras = 0;
        if (!is_vogal(frase[i])) {
          consoante = frase[i];
        } else {
          consoante = '*';
          printf("%c", frase[i]);
        }
        escrevendo_palavra = 1;
      } else {
        printf("%c", frase[i]);
      }
      n_letras++;
    }

    printf("\n");

    // p ++; para debugar
  }

  return 0;
}