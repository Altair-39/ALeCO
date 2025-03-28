#include "header/ColorazioneGrafoPerEsiste.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/** Dato un grafo, rappresentato come matrice di adiacenza, e
 * un array di colori, rappresentati da numeri interi, restituisce
 * una sequenza (c_0,..,c_n) di colori con n pari al minimo necessario
 * per colorare tutti i nodi del grafo, a patto che i nodi adiacenti
 * nel grafo abbiano colori distinti.
 *
 * Lo spazio degli stati e' rappresentato tramite permutazioni con
 * ripetizione (suffisso "Per") dei colori disponibili che sono tanti
 * quanti i nodi del grafo.
 * Quindi, almeno una colorazione esiste sempre, siccome, alla peggio,
 * c'e' un colore per nodo.
 * Ogni livello dello spazio degli stati e' associato all'indice del
 * nodo da colorare. Leggendo un intero ramo dello spazio degli stati
 * si ha la tupla (c_0,..,c_n) di colori.                             */
bool risposta(bool **grafo, int *colori, int *soluzione, int j,
              int lengthSoluzione, int lengthGrafo) {
  bool acc = false;
  size_t i = 0;
  if (!completa(lengthSoluzione, j)) {
    if (!rifiuta(grafo, soluzione, j, lengthGrafo)) {
      while (i < lengthGrafo && !acc) {
        soluzione[j] = colori[i];
        swap(colori, i, j);
        acc = risposta(grafo, colori, soluzione, j + 1, lengthSoluzione,
                       lengthGrafo);
        swap(colori, i, j);
        i++;
      }
      return acc;
    } else
      return false;
  } else {
    acc = accetta(grafo, soluzione, j, lengthGrafo);
    if (acc) {
      print_solution(soluzione, j);
    }
    return acc;
  }
}

/* Un soluzione e' completa se conosciamo il colore per ogni nodo del grafo:
 * occorre, quindi, che la soluzione sia lunga quanto un intero ramo dello
 * spazio degli stati.                                                       */
bool completa(int lengthSoluzione, int j) { return j == lengthSoluzione; }

/* Ha senso rifiutare se il grafo ha almeno due nodi e sono stati colorati
 * almeno due nodi.
 * Altrimenti, il grafo e' ovviamente colorabile.
 * Avendo colorato almeno due nodi, se l'ultimo inserito in soluzione[0..j)
 * e' adiacente a qualche altro nodo gia' in soluzione[0..j-1), ed ha lo
 * stesso colore, rifiuta.                                                  */
bool rifiuta(bool **grafo, int *soluzione, int j, int lengthGrafo) {
  bool rif = false;
  size_t i = 0;
  if (lengthGrafo > 1 && 2 <= j) {
    while (i < j && !rif) {                     /* per ogni nodo già inserito */
      if (grafo[j - 1][i] || grafo[i][j - 1])   /* verifica adiacenza */
        rif = soluzione[j - 1] == soluzione[i]; /* colore uguale? */
      i++;
    }
  }
  return rif;
}
/* Ha senso chiedersi se accettare se il grafo ha almeno due nodi e sono
 * stati colorati almeno due nodi.
 * Altrimenti, il grafo e' ovviamente colorabile.
 * Avendo gia' colorato almeno due nodi, se l'ultimo inserito in
 * soluzione[0..j) e' adiacente a qualche altro nodo gia' in soluzione[0..j-1),
 * ma ha colore diverso, accetta.                                             */
bool accetta(bool **grafo, int *soluzione, int j, int lengthGrafo) {
  bool acc = true;
  size_t i = 0;
  if (lengthGrafo > 1 && 2 <= j) {
    while (i < j && acc) {                      /* per ogni nodo già inserito */
      if (grafo[j - 1][i] || grafo[i][j - 1])   /* verifica adiacenza */
        acc = soluzione[j - 1] != soluzione[i]; /* colore uguale? */
      i++;
    }
  }
  return acc;
}

void print_solution(int *soluzione, int j) {
  size_t i = 0;
  while (i < j) {
    printf("%d ", soluzione[i]);
    i++;
  }
  printf("\n");
}

void swap(int *soluzione, int i, int j) {
  int tmp = soluzione[i];
  soluzione[i] = soluzione[j];
  soluzione[j] = tmp;
}
