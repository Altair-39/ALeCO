#include "../header/PermutazioniRpt.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int main() {
    size_t test1[] = {1, 2};
    printf("Test 1:\n");
        size_t *soluzione = (size_t *)malloc(2 * sizeof(size_t));
    if (!soluzione) {
      perror("Memory allocation failed");
      return EXIT_FAILURE;
    }
    risposte(test1, soluzione, 0, 2, 2); 
    free(soluzione);
    printf("---------------\n");

    size_t test2[] = {1, 2, 3};
    printf("Test 2:\n");
    soluzione = (size_t *)malloc(3 * sizeof(size_t));
    if (!soluzione) {
      perror("Memory allocation failed");
      return EXIT_FAILURE;
    }
    risposte(test2, soluzione, 0, 3, 3);
    free(soluzione);
    printf("---------------\n");

    size_t test3[] = {1, 2, 3, 4};
    printf("Test 3:\n");
    soluzione = (size_t *)malloc(4 * sizeof(size_t));
    if (!soluzione) {
      perror("Memory allocation failed");
      return EXIT_FAILURE;
    }
    risposte(test3, soluzione, 0, 4, 4); 
free(soluzione);
    return EXIT_SUCCESS;
}

