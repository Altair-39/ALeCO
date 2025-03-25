#include "../header/ColorazioneGrafoPerOgni.h"
#include <stdio.h>
#include <stdlib.h>

void test_no_edges() {
  int lengthGrafo = 3;
  int colori[] = {0, 1, 2};
  int soluzione[3] = {0};
  bool **grafo = (bool **)malloc(lengthGrafo * sizeof(bool *));
  for (int i = 0; i < lengthGrafo; i++) {
    grafo[i] = (bool *)calloc(lengthGrafo, sizeof(bool));
  }
  printf("Test no edges:\n");
  risposte(grafo, colori, soluzione, 0, lengthGrafo, lengthGrafo);
  for (int i = 0; i < lengthGrafo; i++)
    free(grafo[i]);
  free(grafo);
}

void test_complete_graph() {
  int lengthGrafo = 3;
  int colori[] = {0, 1, 2};
  int soluzione[3] = {0};
  bool **grafo = (bool **)malloc(lengthGrafo * sizeof(bool *));
  for (int i = 0; i < lengthGrafo; i++) {
    grafo[i] = (bool *)malloc(lengthGrafo * sizeof(bool));
    for (int j = 0; j < lengthGrafo; j++) {
      grafo[i][j] = (i != j);
    }
  }
  printf("Test complete graph:\n");
  risposte(grafo, colori, soluzione, 0, lengthGrafo, lengthGrafo);
  for (int i = 0; i < lengthGrafo; i++)
    free(grafo[i]);
  free(grafo);
}

void test_some_edges() {
  int lengthGrafo = 3;
  int colori[] = {0, 1, 2};
  int soluzione[3] = {0};
  bool adjacencyMatrix[3][3] = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  bool **grafo = (bool **)malloc(lengthGrafo * sizeof(bool *));
  for (int i = 0; i < lengthGrafo; i++) {
    grafo[i] = (bool *)malloc(lengthGrafo * sizeof(bool));
    for (int j = 0; j < lengthGrafo; j++) {
      grafo[i][j] = adjacencyMatrix[i][j];
    }
  }
  printf("Test some edges:\n");
  risposte(grafo, colori, soluzione, 0, lengthGrafo, lengthGrafo);
  for (int i = 0; i < lengthGrafo; i++)
    free(grafo[i]);
  free(grafo);
}

void test_single_node() {
  int lengthGrafo = 1;
  int colori[] = {0};
  int soluzione[1] = {0};
  bool **grafo = (bool **)malloc(lengthGrafo * sizeof(bool *));
  grafo[0] = (bool *)calloc(lengthGrafo, sizeof(bool));
  printf("Test single node:\n");
  risposte(grafo, colori, soluzione, 0, lengthGrafo, lengthGrafo);
  free(grafo[0]);
  free(grafo);
}

void test_two_disconnected_nodes() {
  int lengthGrafo = 2;
  int colori[] = {0, 1};
  int soluzione[2] = {0};
  bool **grafo = (bool **)malloc(lengthGrafo * sizeof(bool *));
  for (int i = 0; i < lengthGrafo; i++) {
    grafo[i] = (bool *)calloc(lengthGrafo, sizeof(bool));
  }
  printf("Test two disconnected nodes:\n");
  risposte(grafo, colori, soluzione, 0, lengthGrafo, lengthGrafo);
  for (int i = 0; i < lengthGrafo; i++)
    free(grafo[i]);
  free(grafo);
}

void test_two_connected_nodes() {
  int lengthGrafo = 2;
  int colori[] = {0, 1};
  int soluzione[2] = {0};
  bool **grafo = (bool **)malloc(lengthGrafo * sizeof(bool *));
  for (int i = 0; i < lengthGrafo; i++) {
    grafo[i] = (bool *)malloc(lengthGrafo * sizeof(bool));
  }
  grafo[0][1] = 1;
  grafo[1][0] = 1;
  printf("Test two connected nodes:\n");
  risposte(grafo, colori, soluzione, 0, lengthGrafo, lengthGrafo);
  for (int i = 0; i < lengthGrafo; i++)
    free(grafo[i]);
  free(grafo);
}

int main() {
  test_no_edges();
  test_complete_graph();
  test_some_edges();
  test_single_node();
  test_two_disconnected_nodes();
  test_two_connected_nodes();
  return EXIT_SUCCESS;
}
