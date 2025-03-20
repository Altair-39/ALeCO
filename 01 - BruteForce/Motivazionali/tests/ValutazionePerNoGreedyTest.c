#include "../header/ValutazionePer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void initNoGreedyTest(GenPair *noGreedyTest) {
  int *v1 = malloc(sizeof(int));
  float *f1 = malloc(sizeof(float));
  *v1 = 2;
  *f1 = 2.0f;
  noGreedyTest[0].first = v1;
  noGreedyTest[0].second = f1;

  int *v2 = malloc(sizeof(int));
  float *f2 = malloc(sizeof(float));
  *v2 = 5;
  *f2 = 4.6f;
  noGreedyTest[1].first = v2;
  noGreedyTest[1].second = f2;

  int *v3 = malloc(sizeof(int));
  float *f3 = malloc(sizeof(float));
  *v3 = 4;
  *f3 = 3.9f;
  noGreedyTest[2].first = v3;
  noGreedyTest[2].second = f3;

  int *v4 = malloc(sizeof(int));
  float *f4 = malloc(sizeof(float));
  *v4 = 2;
  *f4 = 2.0f;
  noGreedyTest[3].first = v4;
  noGreedyTest[3].second = f4;
}

int main() {
  size_t i;
  GenPair noGreedyTest[4];
  GenPair *bestSolution;
  GenPair soluzione[1];
  size_t zeroInt = 0;
  float zeroFloat = 0.0f;

  initNoGreedyTest(noGreedyTest);

  printf("------------------------------------------------\n");
  printf("Tutte le permutazioni generabili da noGreedyTest:\n");
  permutazioni(noGreedyTest, 0, 4);

  printf("------------------------------------------------\n");
  printf("Tutte le soluzioni di noGreedyTest con votoMaxConsentito = 9:\n");
  soluzioni(noGreedyTest, 9, 0, 4);

  printf("------------------------------------------------\n");
  printf("Risposta estratta da noGreedyTest con votoMaxConsentito = 9:\n");

  soluzione[0].first = &zeroInt;
  soluzione[0].second = &zeroFloat;

  bestSolution = risposta(noGreedyTest, soluzione, 9, 0, 4, 1);
  printf("Risposta: %s\n", spazioStatiOut(bestSolution, 1));

  for (i = 0; i < 4; i++) {
    free(noGreedyTest[i].first);
    free(noGreedyTest[i].second);
  }

  return EXIT_SUCCESS;
}
