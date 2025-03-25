#ifndef COLORAZIONE_GRAFO_PER_OGNI_H
#define COLORAZIONE_GRAFO_PER_OGNI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void risposte(bool **grafo, int *colori, int *soluzione, int j,
              int lengthSoluzione, int lengthGrafo);

bool completa(int lengthSoluzione, int j);

bool rifiuta(bool **grafo, int *soluzione, int j, int lengthGrafo);

bool accetta(bool **grafo, int *soluzione, int j, int lengthGrafo);

void print_solution(int *soluzione, int j);

void swap(int *soluzione, int i, int j);

#endif /* COLORAZIONE_GRAFO_PER_OGNI_H */
