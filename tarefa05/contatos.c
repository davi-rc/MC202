#include <stdio.h>
#include <string.h>

typedef struct {
  char nome[51];
  char endereco[101];
  char numero[16];
  char dia[3];
  char mes[3];
  char ano[5];
} contato;

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

int achar_espaco_vazio(contato contatos[]) {
  // acha a posição do primeiro contato sem ninguem
  for (int i = 0; i < 1000; i++) {
    if (contatos[i].nome[0] == '\0')
      return i;
  }
  return 999;
}

void inserir(contato contatos[]) {

  int i = achar_espaco_vazio(contatos);

  scanf(" ");

  fgets(contatos[i].nome, 51, stdin);
  contatos[i].nome[strcspn(contatos[i].nome, "\n")] = '\0';
  fgets(contatos[i].endereco, 101, stdin);
  contatos[i].endereco[strcspn(contatos[i].endereco, "\n")] = '\0';
  scanf(" %s", contatos[i].numero);
  scanf(" %[^/]/%[^/]/%s", contatos[i].dia, contatos[i].mes, contatos[i].ano);

  printf("Contato para %s inserido.\n\n", contatos[i].nome);
}

void passar_tras(contato contatos[], int i) {
  // passa para tras todos os contatos depois do que foi removido (i), não
  // deixando espaço vazio no array

  for (int j = i; j < 999; j++)
    contatos[j] = contatos[j + 1];
  memset(contatos[999].nome, 0, 51);
}

void remover(contato contatos[]) {
  // vai rodar todos os contatos mesmo que não tenha 1000 contatos, possivel
  // melhora de otimização

  char contato_rev[51] = {0};

  scanf(" ");
  fgets(contato_rev, 51, stdin);
  contato_rev[strcspn(contato_rev, "\n")] = '\0';

  int broke = 0;
  int contagem = 0;

  for (int i = 0; i < 1000; i++) {
    broke = 0;
    for (int j = 0;; j++) {
      if (contatos[i].nome[j] != contato_rev[j]) {
        broke = 1;
        break;
      }
      if (contatos[i].nome[j] == '\0') {
        contagem++;
        break;
      }
    }
    if (!broke) {
      passar_tras(contatos, i);
      i--;
    }
  }

  printf("Contatos de %s removidos: %d.\n\n", contato_rev, contagem);
}

void buscar(contato contatos[]) {

  char contato_busca[51] = {0};

  scanf(" ");
  fgets(contato_busca, 51, stdin);
  contato_busca[strcspn(contato_busca, "\n")] = '\0';

  printf("Resultado da busca:\n");

  int contagem = 1;
  int impresso = 0;
  char *achou;

  for (int i = 0; i < 1000; i++) {
    achou = strstr(contatos[i].nome, contato_busca);
    if (achou != NULL) {
      printf("(%d) %s\t%s\t%s\t%s/%s/%s\n", contagem, contatos[i].nome,
             contatos[i].endereco, contatos[i].numero, contatos[i].dia,
             contatos[i].mes, contatos[i].ano);
      impresso = 1;
    }
    if (contatos[i].nome[0] != '\0')
      contagem++;
  }

  if (!impresso)
    printf("Nenhum contato.\n");

  printf("\n");
}

void imprimir(contato contatos[]) {

  printf("Listagem:\n");

  int contagem = 1;
  int printado = 0;

  for (int i = 0; i < 1000; i++) {
    if (contatos[i].nome[0] != '\0') {
      printado = 1;
      printf("(%d) %s\t%s\t%s\t%s/%s/%s\n", contagem, contatos[i].nome,
             contatos[i].endereco, contatos[i].numero, contatos[i].dia,
             contatos[i].mes, contatos[i].ano);
      contagem++;
    }
  }

  if (!printado)
    printf("Nenhum contato.\n");

  printf("\n");
}

int main(void) {
  contato contatos[1000] = {0};

  char comando;

  while (1) {
    scanf(" %c", &comando);

    if (comando == 'f')
      break;
    else if (comando == 'i')
      inserir(contatos);
    else if (comando == 'r')
      remover(contatos);
    else if (comando == 'b')
      buscar(contatos);
    else if (comando == 'p')
      imprimir(contatos);
  }
}