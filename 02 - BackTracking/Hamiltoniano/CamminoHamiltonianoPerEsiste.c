#include "header/CamminoHamiltonianoPerEsiste.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/** Dato un grafo, anche orientato (diretto), con m nodi, individua
 * il primo cammino (n_1..n_m) hamiltoniano del grafo: in
 * (n_1..n_m) tutti i nodi sono distinti e n_{i} e' adiacente a
 * n_{i+1}.
 *
 * L'ipotesi sulla direzionalita' degli archi si esprime dicendo
 * che se l'arco e' (a,b), allora si puo' andare dal nodo a al
 * nodo b, ma non vice versa.                                     */

bool risposta(bool **grafo, int *soluzione, int j, int lengthSoluzione) {
  if (!completa(j, lengthSoluzione)) {
    if (!rifiuta(grafo, soluzione, j)) {
      int i = j;
      bool accetta = false;
      while (i < lengthSoluzione && !accetta) {
        swap(soluzione, i, j);
        accetta = risposta(grafo, soluzione, j + 1, lengthSoluzione);
        swap(soluzione, i, j);
        i++;
      }
      return accetta;
    } else {
      printf(" Rifiuta: ");
      print_solution(soluzione, j);
      return false;
    }
  } else {
    bool acc = accetta(grafo, soluzione, j);
    if (acc) {
      printf(" Accetta: ");
      print_solution(soluzione, j);
    }
    return acc;
  }
}

bool completa(int j, int lengthSoluzione) { return j == lengthSoluzione; }

/* Ha senso rifiutare se il grafo contiene almeno due nodi
 * e il cammino costruito in soluzione[0..j) ha almeno due nodi.
 * Altrimenti il cammino e' ovviamente Hamiltoniano, includendo
 * anche il cammino vuoto, che considerqiamo come degenere.
 * Nel caso di almeno due nodi nel grafo e in soluzione[0..j),
 * si rifiuta se non c'e' l'arco tra il penultimo nodo di
 * soluzione[0..j) e l'ultimo nodo in soluzione[0..j).           */
bool rifiuta(bool **grafo, int *soluzione, int j) {
  bool rifiuta = false;
  if (j > 1) {
    rifiuta = !grafo[soluzione[j - 2]][soluzione[j - 1]];
  }
  return rifiuta;
}

/* Se il grafo contiene meno di due nodi o soluzione[0..j) non ha
 * almeno due nodi il cammino e' Hamiltoniano, includendo anche
 * il cammino vuoto.
 * Nel caso di almeno due nodi nel grafo ed in soluzione[0..j),
 * si accetta c'e' l'arco tra il penultimo nodo dic soluzione[0..j)
 * e l'ultimo nodo in soluzione[0..j).           */
bool accetta(bool **grafo, int *soluzione, int j) {
  bool accetta = true;
  if (j > 1) {
    accetta = grafo[soluzione[j - 2]][soluzione[j - 1]];
  }
  return accetta;
}

void swap(int *a, int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void print_solution(int *soluzione, int j) {
  size_t i = 0;
  while (i < j) {
    printf("%d ", soluzione[i]);
    i++;
  }
  printf("\n");
}
