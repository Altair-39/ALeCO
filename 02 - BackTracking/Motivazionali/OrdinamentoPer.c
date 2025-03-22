#include "header/OrdinamentoPer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void swap(int *a, int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

/* Una soluzione e' completa quando include tutti gli elementi.
 */
bool completa(int lengthA, int j) { return j == lengthA; }

/* La precondizione di applicazione e' che j < a.length, ovvero non
 * abbiamo una soluzione completa.
 *
 * Rifiuta se gli ultimi due elementi nella soluzione sono fuori ordine.
 */
bool rifiuta(int *a, int j) { return 2 <= j && a[j - 2] > a[j - 1]; }

/*
 * La precondizione di applicazione e' che j == a.length, ovvero abbiamo
 * completato la soluzione in a[0..j) che coincide con a[0..a.length)
 * e che puo' contenere una risposta, ovvero tutti gli elementi ordinati
 * in ordine non decrescente.
 * Siccome siamo arrivati sino a questo punto, a[0..a.length-2] deve
 * necessariamente essere ordinata, altrimenti l'avremmo gia' scartata.
 * Quindi, se a.length e' almeno 2, e' necessario controllare che
 * l'ultimo elemento inserito, ovvero a[a.length-1] sia nell'ordine giusto
 * rispetto ad a[a.length-2]. Accettare in questo punto, e' confermare che
 * a[0]<=a[1]<=..<=a[a.length-2]<=a[a.length-1], ovvero che siamo di fronte
 * ad una risposta.
 */
bool accetta(int *a, int j) { return 2 <= j && a[j - 2] <= a[j - 1]; }

void risposta(int *a, int j) {
  size_t i = 0;
  printf("[");
  while (i < j) {
    printf("%d", a[i]);
    if (i < j - 1) 
      printf(", ");
    i++;
  }
  printf("]\n");
}

bool ordinamento(int *a, int j, int lengthA) {
  bool ordinato = false;
  bool acc;
  int i = j;
  if (!completa(lengthA, j)) {
    if (!rifiuta(a, j)) {
      while (i < lengthA && !ordinato) {
        swap(a, i, j);
        ordinato = ordinamento(a, j + 1, lengthA);
        swap(a, i, j);
        i++;
      }
      return ordinato;
    } else
      return false;
  } else {
    acc = accetta(a, j);
    if (acc)
      risposta(a, j);
    return acc;
  }
}
