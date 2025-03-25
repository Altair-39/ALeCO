#include "../header/CamminoHamiltonianoPerEsiste.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_hamiltonian_path_exists() {
  bool *grafo[] = {
      (bool[]){false, true, false, true}, (bool[]){true, false, true, false},
      (bool[]){false, true, false, true}, (bool[]){true, false, true, false}};
  int soluzione[4] = {0, 1, 2, 3};
  int m = 4;

  printf("Test Hamiltonian Path Exists:\n");
  bool result = risposta(grafo, soluzione, 0, m);
  if (result) {
    printf("Test Passed: Hamiltonian path exists as expected.\n");
  } else {
    printf("Test Failed: Hamiltonian path should exist.\n");
  }
  printf("\n");
}

void test_hamiltonian_path_does_not_exist() {
  bool *grafo[] = {(bool[]){false, true, false, false},
                   (bool[]){true, false, true, false},
                   (bool[]){false, true, false, false},
                   (bool[]){false, false, false, false}};
  int soluzione[4] = {0, 1, 2, 3};
  int m = 4;

  printf("Test Hamiltonian Path Does Not Exist:\n");
  bool result = risposta(grafo, soluzione, 0, m);
  if (!result) {
    printf("Test Passed: Hamiltonian path does not exist as expected.\n");
  } else {
    printf("Test Failed: Hamiltonian path should not exist.\n");
  }
  printf("\n");
}

void test_empty_graph() {
  bool *grafo[] = {(bool[]){false, false, false}, (bool[]){false, false, false},
                   (bool[]){false, false, false}};
  int soluzione[3] = {0, 1, 2};
  int m = 3;

  printf("Test Empty Graph:\n");
  bool result = risposta(grafo, soluzione, 0, m);
  if (!result) {
    printf("Test Passed: No Hamiltonian path in an empty graph as expected.\n");
  } else {
    printf(
        "Test Failed: Hamiltonian path should not exist in an empty graph.\n");
  }
  printf("\n");
}

void test_single_node_graph() {
  bool *grafo[] = {(bool[]){false}};
  int soluzione[1] = {0};
  int m = 1;

  printf("Test Single Node Graph:\n");
  bool result = risposta(grafo, soluzione, 0, m);
  if (result) {
    printf("Test Passed: Single node graph has a trivial Hamiltonian path.\n");
  } else {
    printf("Test Failed: Single node graph should have a trivial Hamiltonian "
           "path.\n");
  }
  printf("\n");
}

int main() {
  test_hamiltonian_path_exists();
  test_hamiltonian_path_does_not_exist();
  test_empty_graph();
  test_single_node_graph();
  return EXIT_SUCCESS;
}
