#include "../header/ReginePerEsiste.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int tentativi;

int main() {
  int sizes[] = {1, 2, 3, 4, 5, 8};
  int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

  for (int i = 0; i < num_sizes; i++) {
    int n = sizes[i];
    int regine[n];
    tentativi = 0;

    for (int j = 0; j < n; j++) {
      regine[j] = -1;
    }

    printf("Attempting to solve the %d-Queens problem...\n", n);

    if (soluzione(regine, 0, n)) {
      printf("Solution found after %d attempts for %d-Queens problem.\n",
             tentativi, n);
    } else {
      printf("No solution found after %d attempts for %d-Queens problem.\n",
             tentativi, n);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
