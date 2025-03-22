/**
 * Dato un array a, ed un valore k, stampa tutte le disposizioni di k elementi
 * presi da un 'insieme' a di length elementi.
 *
 * L'algoritmo e' una variazione di Permutazioni.risposte.
 * Produce una risposta, quando la lunghezza della soluzione
 * parziale s[0..j) coincide col limite k, ovvero j==k.
 */

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

void risposte(size_t *a, size_t j, size_t k, size_t length) {
  int i = j;
  if (j == k) {
    char *ris = toString(a, k);
    if (ris) {
      printf("%s + n.ro: %ld \n", ris, ++count);
      free(ris);
    }
  } else {
    while (i < length) {
      swap(a, i, j);
      risposte(a, j + 1, k, length);
      swap(a, i, j);
      i++;
    }
  }
}
