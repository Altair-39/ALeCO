#include "header/CamminoHamiltonianoPerOgni.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/** Dato un grafo, anche orientato (diretto), con m nodi elenca
 * tutti i cammini (n_1..n_m) hamiltoniani del grafo: in
 * (n_1..n_m) tutti i nodi sono distinti e n_{i} e' adiacente a
 * n_{i+1}.
 *
 * L'ipotesi sulla direzionalita' degli archi si esprime dicendo
 * che se l'arco e' (a,b), allora si puo' andare dal nodo a al
 * nodo b, ma non vice versa.                                     */
void risposte(bool **grafo, int *soluzione, int j, int n) {
  if (!completa(soluzione, j, n)) {
    if (!rifiuta(grafo, soluzione, j)) {
      int i = j;
      while (i < n) {
        swap(soluzione, i, j);
        risposte(grafo, soluzione, j + 1, n);
        swap(soluzione, i, j);
        i++;
      }
    } else {
      printf("Rifiuta: ");
      printSolution(soluzione, j);
    }
  } else {
    if (accetta(grafo, soluzione, j)) {
      printf("Accetta: ");
      printSolution(soluzione, j);
    }
  }
}

bool completa(int *soluzione, int j, int n) { return j == n; }

/* Ha senso rifiutare se il grafo contiene almeno due nodi
 * e il cammino costruito in soluzione[0..j) ha almeno due nodi.
 * Altrimenti il cammino e' ovviamente Hamiltoniano, includendo
 * anche il cammino vuoto.
 * Nel caso di almeno due nodi nel grafo ed in soluzione[0..j),
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
 * si accetta c'e' l'arco tra il penultimo nodo di soluzione[0..j)
 * e l'ultimo nodo in soluzione[0..j).           */
bool accetta(bool **grafo, int *soluzione, int j) {
  bool accetta = true;
  if (j > 1) {
    accetta = grafo[soluzione[j - 2]][soluzione[j - 1]];
  }
  return accetta;
}

void swap(int *soluzione, int i, int j) {
  int tmp = soluzione[i];
  soluzione[i] = soluzione[j];
  soluzione[j] = tmp;
}

void printSolution(int *soluzione, int j) {
  for (int i = 0; i < j; i++) {
    printf("%d ", soluzione[i]);
  }
  printf("\n");
}
