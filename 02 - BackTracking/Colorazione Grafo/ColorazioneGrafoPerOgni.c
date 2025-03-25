#include "header/ColorazioneGrafoPerOgni.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>


/** Dato un grafo, rappresentato come matrice di adiacenza, e
 * un array di colori, rappresentati da numeri interi, a partire
 * da 0, fornisce l'elenco di sequenze (c_0,..,c_n) tali che c_i 
 * e' il colore del nodo di indice i del grafo a patto nodi 
 * adiacenti del grafo abbiano colori distinti.
 * 
 * Lo spazio degli stati e' rappresentato tramite permutazioni con
 * ripetizione dei colori disponibili che sono tanti quanti i nodi
 * del grafo. Quindi, almeno una colorazione esiste sempre.
 * Ogni livello dello spazio degli stati e' associato all'indice del 
 * nodo da colorare. Leggendo un intero ramo dello spazio degli stati 
 * si ha la tupla (c_0,..,c_n).                                      */

void risposte(bool **grafo, int *colori, int *soluzione, int j,
              int lengthSoluzione, int lengthGrafo) {
  size_t i = 0;
  bool acc;
  if (!completa(lengthSoluzione, j)) {
    if (!rifiuta(grafo, soluzione, j, lengthGrafo)) {
      while (i < lengthGrafo) {
        soluzione[j] = colori[i];
        swap(colori, i, j);
        risposte(grafo, colori, soluzione, j + 1, lengthSoluzione,
                       lengthGrafo);
        swap(colori, i, j);
        i++;
      }
    } else
      printf("Rifiuta 0: ");
    
  } else {
    acc = accetta(grafo, soluzione, j, lengthGrafo);
    if (acc) 
      printf("Accetta: ");
    else
     printf("Rifiuta 1: ");
  }
  print_solution(soluzione, j);
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
