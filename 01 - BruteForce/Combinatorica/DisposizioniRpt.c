/**
 * Dato un array a, ed un valore k, stampa
 * tutte le disposizioni con ripetizioni
 * formate da k elementi presi da un 'insieme'
 * a di length elementi.
 *
 *
 * Rispetto a quanto fatto in Disposizioni.answer,
 * le ripetizioni si ottengono variando l'insieme
 * da cui pescare l'elemento a[j] per estendere
 * a[0..j) in a[0..j+1).
 * Per ogni nuovo valore di j, a[j] appartiene as
 * a[0..a.length), non dall'intervallo a[j..a.length). */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count = 0;

void swap(size_t *a, size_t i, size_t j) {
  size_t tmp;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void print_array(size_t *array, size_t length) {
  for (size_t i = 0; i < length; i++) {
    printf("%zu ", array[i]);
  }
  printf("\n");
}

char *toString(size_t *a, int k) {
  if (k == 0) {
    char *emptyResult = (char *)malloc(3);
    strcpy(emptyResult, "[]");
    return emptyResult;
  }

  char *result = (char *)malloc(3 + k * 12);
  if (!result)
    return NULL;

  strcpy(result, "[");

  char buffer[12];
  for (int i = 0; i < k; i++) {
    sprintf(buffer, "%ld, ", a[i]);
    strcat(result, buffer);
  }

  result[strlen(result) - 2] = ']';
  result[strlen(result) - 1] = '\0';

  return result;
}

/*
 * L'array a contiene gli elementi di cui produrre le disposizioni. E'
 * necessario un array di supporto s in cui costruire la permutazione s[0..j).
 * Senza l'array s, si sovrascriverebbe s[0..j) ad ogni cambio di livello nella
 * visita dell'albero degli stati.
 */

void risposte(size_t *a, size_t *soluzione, size_t j, size_t k, size_t length) {
  int i = 0;
  if (j != k) {
    /* Da capo a ogni livello ==> ripetizione */
    while (i < length) {
      soluzione[j] = a[i];
      swap(a, i, j);
      risposte(a, soluzione, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  } else {
    printf("%s + n.ro: %ld \n", toString(soluzione, k), ++count);
  }
}
