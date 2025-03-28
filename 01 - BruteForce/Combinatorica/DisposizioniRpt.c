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

static void swap(int *a, int i, int j) {
  size_t tmp;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void print_array(int *array, int length) {
  size_t i = 0;
  while (i < length) {
    printf("%d ", array[i]);
    i++;
  }
  printf("\n");
}

static char *toString(int *a, int k) {
  size_t i = 0;
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
  while (i < k) {
    sprintf(buffer, "%d, ", a[i]);
    strcat(result, buffer);
    i++;
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

void risposte(int *a, int *soluzione, int j, int k, int length) {
  size_t i = 0;
  char *ris;
  if (j == k) {
    ris = toString(soluzione, k);
    if (ris) {
      printf("%s + n.ro: %ld \n", ris, ++count);
      free(ris);
    }
  } else {
    /* Da capo a ogni livello ==> ripetizione */
    while (i < length) {
      soluzione[j] = a[i];
      swap(a, i, j);
      risposte(a, soluzione, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  }
}
