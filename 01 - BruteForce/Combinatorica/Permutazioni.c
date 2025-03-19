#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(size_t *array, size_t i, size_t j) {
  size_t tmp;
  tmp = array[i];
array[i] = array[j];
  array[j] = tmp;
}

/* L'array a contiene gli elementi di cui produrre le permutazioni.
 * Adottando la terminologia di Horowitz "Computer Algorithms":
 * - l'insieme di tutti i sottorami dell'intero albero e' lo
 * spazio degli stati
 * - l'insieme delle risposte e delle soluzioni coincide perche'
 * il nostro scopo e' generare tutte le permutazioni e ciascuna
 * delle permutazioni e' completa solo avendo completamente
 * percorso il ramo che individua quella permutazione.             */

void risposte(size_t *a, size_t j, size_t k, size_t length) {
  int i = j;
  int counter;
  if (j != length) {
    while (i < length) {
      /* Permutazioni dei restanti length - j elementi */
      swap(a, i, j);
      risposte(a, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  } else {
    printf("[");
    for (counter = 0; counter < length; counter++) {
      printf("%ld", a[counter]);
      if (counter != length - 1)
        printf(", ");
    }
    printf("]\n");
  }
}
