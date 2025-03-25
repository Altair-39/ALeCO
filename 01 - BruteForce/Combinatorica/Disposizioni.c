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

static void swap(int *a, int i, int j) {
  size_t tmp;
  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void print_array(int *array, int length) {
  size_t i = 0;
  while (i < length) {
    printf("%d", array[i]);
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

void risposte(int *a, int j, int k, int length) {
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
