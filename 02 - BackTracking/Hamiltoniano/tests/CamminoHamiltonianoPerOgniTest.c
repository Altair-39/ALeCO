#include "../header/CamminoHamiltonianoPerOgni.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_hamiltonian_path_exists() {
  bool *grafo[] = {
      (bool[]){false, true, true, false}, (bool[]){true, false, true, true},
      (bool[]){true, true, false, true}, (bool[]){false, true, true, false}};
  int soluzione[4] = {0, 1, 2, 3};
  int n = 4;

  printf("Test Hamiltonian Path Exists:\n");
  risposte(grafo, soluzione, 0, n);
}

void test_hamiltonian_path_does_not_exist() {
  bool *grafo[] = {
      (bool[]){false, true, false, false}, (bool[]){true, false, false, false},
      (bool[]){false, false, false, true}, (bool[]){false, false, true, false}};
  int soluzione[4] = {0, 1, 2, 3};
  int n = 4;

  printf("Test Hamiltonian Path Does Not Exist:\n");
  risposte(grafo, soluzione, 0, n);
}

void test_empty_graph() {
  bool *grafo[] = {};
  int soluzione[0] = {};
  int n = 0;

  printf("Test Empty Graph:\n");
  risposte(grafo, soluzione, 0, n);
}

void test_single_node_graph() {
  bool *grafo[] = {(bool[]){false}};
  int soluzione[1] = {0};
  int n = 1;

  printf("Test Single Node Graph:\n");
  risposte(grafo, soluzione, 0, n);
}

int main() {
  test_hamiltonian_path_exists();
  test_hamiltonian_path_does_not_exist();
  test_empty_graph();
  test_single_node_graph();
  return EXIT_SUCCESS;
}
