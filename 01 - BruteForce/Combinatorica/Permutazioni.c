#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void swap(int *array, int i, int j) {
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

void risposte(int *a, int j, int k, int length) {
  size_t i = j;
  size_t counter = 0;
  if (j == length) {
    printf("[");
    while (counter < length) {
      printf("%d", a[counter]);
      if (counter != length - 1)
        printf(", ");
      counter++;
    }
    printf("]\n");
  } else {
    while (i < length) {
      /* Permutazioni dei restanti length - j elementi */
      swap(a, i, j);
      risposte(a, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  }
}
