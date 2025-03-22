#include "../header/PermutazioniRpt.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int *soluzione = (int *)malloc(2 * sizeof(int));
  int test1[] = {1, 2};
  int test2[] = {1, 2, 3};
  int test3[] = {1, 2, 3, 4};

  printf("Test 1:\n");
  if (!soluzione) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }
  risposte(test1, soluzione, 0, 2, 2);
  free(soluzione);
  printf("---------------\n");

  printf("Test 2:\n");
  soluzione = (int *)malloc(3 * sizeof(int));
  if (!soluzione) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }
  risposte(test2, soluzione, 0, 3, 3);
  free(soluzione);
  printf("---------------\n");

  printf("Test 3:\n");
  soluzione = (int *)malloc(4 * sizeof(int));
  if (!soluzione) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }
  risposte(test3, soluzione, 0, 4, 4);
  free(soluzione);
  return EXIT_SUCCESS;
}
