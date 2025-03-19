#include "../header/DisposizioniRpt.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  size_t test1[] = {1, 2};
  size_t test2[] = {1, 2, 3};
  size_t test3[] = {1, 2, 3, 4};

  size_t k_values[] = {1, 2, 3, 4};

  for (size_t i = 0; i < sizeof(k_values) / sizeof(k_values[0]); i++) {
    size_t k = k_values[i];

    printf("---------------\n");

    count = 0;
    size_t *soluzione = (size_t *)malloc(k * sizeof(size_t));
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
  }

  return EXIT_SUCCESS;
}
