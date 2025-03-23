#include "../header/ColorazioneGrafoPerEsiste.h"
#include <stdbool.h>
#include <stdio.h>

// Helper function to print the adjacency matrix
void print_adj_matrix(bool **grafo, int lengthGrafo) {
  for (int i = 0; i < lengthGrafo; i++) {
    for (int j = 0; j < lengthGrafo; j++) {
      printf("%d ", grafo[i][j]);
    }
    printf("\n");
  }
}

// Test case 1: Graph with no edges (all nodes can have the same color)
void test_no_edges() {
  printf("Running test_no_edges...\n");

  int lengthGrafo = 3;
  bool *grafo[3] = {(bool[]){false, false, false},
                    (bool[]){false, false, false},
                    (bool[]){false, false, false}};

  int colori[] = {1, 2, 3};
  int soluzione[3] = {0};
  int lengthSoluzione = 3;

  bool result =
      risposta(grafo, colori, soluzione, 0, lengthSoluzione, lengthGrafo);

  if (result) {
    printf("Solution found: ");
    print_solution(soluzione, lengthSoluzione);
  } else {
    printf("No solution found.\n");
  }
  printf("\n");
}

// Test case 2: Graph with all nodes connected (complete graph)
void test_complete_graph() {
  printf("Running test_complete_graph...\n");

  int lengthGrafo = 3;
  bool *grafo[3] = {(bool[]){false, true, true}, (bool[]){true, false, true},
                    (bool[]){true, true, false}};

  int colori[] = {1, 2, 3};
  int soluzione[3] = {0};
  int lengthSoluzione = 3;

  bool result =
      risposta(grafo, colori, soluzione, 0, lengthSoluzione, lengthGrafo);

  if (result) {
    printf("Solution found: ");
    print_solution(soluzione, lengthSoluzione);
  } else {
    printf("No solution found.\n");
  }
  printf("\n");
}

// Test case 3: Graph with some edges
void test_some_edges() {
  printf("Running test_some_edges...\n");

  int lengthGrafo = 4;
  bool *grafo[4] = {
      (bool[]){false, true, false, true}, (bool[]){true, false, true, false},
      (bool[]){false, true, false, true}, (bool[]){true, false, true, false}};

  int colori[] = {1, 2, 3, 4};
  int soluzione[4] = {0};
  int lengthSoluzione = 4;

  bool result =
      risposta(grafo, colori, soluzione, 0, lengthSoluzione, lengthGrafo);

  if (result) {
    printf("Solution found: ");
    print_solution(soluzione, lengthSoluzione);
  } else {
    printf("No solution found.\n");
  }
  printf("\n");
}

// Test case 4: Graph with a single node
void test_single_node() {
  printf("Running test_single_node...\n");

  int lengthGrafo = 1;
  bool *grafo[1] = {(bool[]){false}};

  int colori[] = {1};
  int soluzione[1] = {0};
  int lengthSoluzione = 1;

  bool result =
      risposta(grafo, colori, soluzione, 0, lengthSoluzione, lengthGrafo);

  if (result) {
    printf("Solution found: ");
    print_solution(soluzione, lengthSoluzione);
  } else {
    printf("No solution found.\n");
  }
  printf("\n");
}

// Test case 5: Graph with two disconnected nodes
void test_two_disconnected_nodes() {
  printf("Running test_two_disconnected_nodes...\n");

  int lengthGrafo = 2;
  bool *grafo[2] = {(bool[]){false, false}, (bool[]){false, false}};

  int colori[] = {1, 2};
  int soluzione[2] = {0};
  int lengthSoluzione = 2;

  bool result =
      risposta(grafo, colori, soluzione, 0, lengthSoluzione, lengthGrafo);

  if (result) {
    printf("Solution found: ");
    print_solution(soluzione, lengthSoluzione);
  } else {
    printf("No solution found.\n");
  }
  printf("\n");
}

// Test case 6: Graph with two connected nodes
void test_two_connected_nodes() {
  printf("Running test_two_connected_nodes...\n");

  int lengthGrafo = 2;
  bool *grafo[2] = {(bool[]){false, true}, (bool[]){true, false}};

  int colori[] = {1, 2};
  int soluzione[2] = {0};
  int lengthSoluzione = 2;

  bool result =
      risposta(grafo, colori, soluzione, 0, lengthSoluzione, lengthGrafo);

  if (result) {
    printf("Solution found: ");
    print_solution(soluzione, lengthSoluzione);
  } else {
    printf("No solution found.\n");
  }
  printf("\n");
}

int main() {
  test_no_edges();
  test_complete_graph();
  test_some_edges();
  test_single_node();
  test_two_disconnected_nodes();
  test_two_connected_nodes();

  return 0;
}
