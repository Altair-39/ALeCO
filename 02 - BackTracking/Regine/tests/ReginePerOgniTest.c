#include "../header/ReginePerOgni.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>  // Needed for malloc()

int main() {
  int sizes[] = {1, 2, 3, 4, 5, 8};
  int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

  for (int i = 0; i < num_sizes; i++) {
    int n = sizes[i]; 
    int *regine = (int *)malloc(n * sizeof(int));  // Use dynamic allocation
    if (!regine) {
      printf("Memory allocation failed!\n");
      return 1;
    }

    tentativi = 0;    

    for (int j = 0; j < n; j++) {
      regine[j] = -1;
    }

    printf("Attempting to solve the %d-Queens problem...\n", n);

    soluzioni(regine, 0, n);  // Call function (no need for `if` condition)

    printf("Solutions found after %ld attempts for %d-Queens problem.\n", tentativi, n);
    printf("\n");

    free(regine);  // Free allocated memory
  }

  return 0;
}
