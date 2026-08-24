#include <stdio.h>

int comparar() {

  int n_copos, n_latas;

  scanf("%d %d", &n_latas, &n_copos);
  if (n_latas > n_copos) {
    return n_copos;
  }

  return 0;
}

int main(void) {

  int n_bandeijas;
  int total_copos = 0;

  scanf("%d", &n_bandeijas);

  for (int i = 0; i < n_bandeijas; i++) {
    total_copos += comparar();
  }

  printf("%d\n", total_copos);

  return 0;
}