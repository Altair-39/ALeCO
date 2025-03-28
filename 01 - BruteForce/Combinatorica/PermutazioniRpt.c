/**
 * Dato un array a, stampa tutte le permutazioni con
 * ripetizione dei suoi elementi .
 *
 * Rispetto a quanto fatto in Permutazioni.answer,
 * le ripetizioni si ottengono variando l'insieme
 * da cui pescare l'elemento a[j] per estendere
 * a[0..j) in a[0..j+1).
 * Per ogni nuovo valore di j, a[j] appartiene as
 * a[0..a.length), non dall'intervallo a[j..a.length).
 * */

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

void risposte(int *a, int *soluzioni, int j, int k, int length) {
  size_t i = 0;
  size_t counter = 0;
  if (j == length) {
    printf("[");
    while (counter < length) {
      printf("%d", soluzioni[counter]);
      if (counter != length - 1)
        printf(", ");
      counter++;
    }
    printf("]\n");
  } else {
    while (i < length) {
      /* Riparte da capo a ogni livello ==> ripetizione */
      soluzioni[j] = a[i];
      swap(a, i, j);
      risposte(a, soluzioni, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  }
}
