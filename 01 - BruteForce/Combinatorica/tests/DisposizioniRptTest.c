#include "../header/DisposizioniRpt.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int test1[] = {1, 2};
  int test2[] = {1, 2, 3};
  int test3[] = {1, 2, 3, 4};

  int k_values[] = {1, 2, 3, 4};
  int i = 0, k;

  while (i < sizeof(k_values) / sizeof(k_values[0])) {
    k = k_values[i];

    printf("---------------\n");

    count = 0;
    int *soluzione = (int *)malloc(k * sizeof(int));
    if (!soluzione) {
      perror("Memory allocation failed");
      return EXIT_FAILURE;
    }

    if (k <= 2) {
      risposte(test1, soluzione, 0, k, sizeof(test1) / sizeof(test1[0]));
    } else if (k <= 3) {
      risposte(test2, soluzione, 0, k, sizeof(test2) / sizeof(test2[0]));
    } else {
      risposte(test3, soluzione, 0, k, sizeof(test3) / sizeof(test3[0]));
    }

    free(soluzione);
    i++;
  }

  return EXIT_SUCCESS;
}
