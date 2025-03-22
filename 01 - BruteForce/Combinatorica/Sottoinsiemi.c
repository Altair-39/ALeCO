#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* L'array a contiene gli elementi di cui elencare i
 * sottoinsiemi. L'array s contiene via via le funzioni
 * caratteristiche dei sottoinsiemi di a. Ogni soluzione, e,
 * quindi ogni risposta, e' una di queste funzioni caratteristiche;
 * ciascuna di esse si ottiene quando a e' riempita in tutta
 * la sua lunghezza.
 */

void toString(size_t *a, bool *r, size_t length) {
  size_t i = 0;
  printf("[");
  while (i < length) {
    if (r[i]) {
      printf("%zu ", a[i]);
    }
    i++;
  }
  printf("]\n");
}

void risposta(size_t *a, bool *r, size_t j, size_t length) {
  if (j == length) {
    toString(a, r, length);
  } else {
    risposta(a, r, j + 1, length);
    r[j] = !r[j];
    risposta(a, r, j + 1, length);
    r[j] = !r[j];
  }
}

void sottoinsiemi(size_t *a, size_t length) {
  bool r[length];
  risposta(a, r, 0, length);
}
