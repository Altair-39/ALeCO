#ifndef COLORAZIONE_GRAFO_PER_ESISTE_H
#define COLORAZIONE_GRAFO_PER_ESISTE_H

#include <stdbool.h>

bool risposta(bool **grafo, int *colori, int *soluzione, int j,
              int lengthSoluzione, int lengthGrafo);

bool completa(int lengthSoluzione, int j);

bool rifiuta(bool **grafo, int *soluzione, int j, int lengthGrafo);

bool accetta(bool **grafo, int *soluzione, int j, int lengthGrafo);

void print_solution(int *soluzione, int j);

void swap(int *array, int i, int j);

#endif
