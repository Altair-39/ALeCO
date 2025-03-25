#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* L'array a contiene gli elementi di cui elencare i
 * sottoinsiemi. L'array s contiene via via le funzioni
 * caratteristiche dei sottoinsiemi di a. Ogni soluzione, e,
 * quindi ogni risposta, e' una di queste funzioni caratteristiche;
 * ciascuna di esse si ottiene quando a e' riempita in tutta
 * la sua lunghezza.
 */

static void toString(int *a, bool *r, int length) {
  size_t i = 0;
  printf("[");
  while (i < length) {
    if (r[i]) {
      printf("%d ", a[i]);
    }
    i++;
  }
  printf("]\n");
}

static void risposta(int *a, bool *r, int j, int length) {
  if (j == length) {
    toString(a, r, length);
  } else {
    risposta(a, r, j + 1, length);
    r[j] = !r[j];
    risposta(a, r, j + 1, length);
    r[j] = !r[j];
  }
}

void sottoinsiemi(int *a, int length) {
  bool r[length];
  memset(r, 0, sizeof(r)); /* metto tutto a false altrimenti valgrind piange */
  risposta(a, r, 0, length);
}
