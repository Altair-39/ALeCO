
#include "../header/ValutazioneSot.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

GenPair createGenPair(int votoMax, float votazione) {
  GenPair p;
  p.first = malloc(sizeof(int));
  p.second = malloc(sizeof(float));
  if (p.first && p.second) {
    *(int *)p.first = votoMax;
    *(float *)p.second = votazione;
  } else {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

void printBooleanArray(const char *label, bool *arr, size_t length) {
  printf("%s: [", label);
  for (size_t i = 0; i < length; i++) {
    printf("%s", arr[i] ? "true" : "false");
    if (i < length - 1)
      printf(", ");
  }
  printf("]\n");
}

int main() {
  GenPair a[4];

  a[0] = createGenPair(4, 3.0f);
  a[1] = createGenPair(10, 8.0f);
  a[2] = createGenPair(3, 1.5f);
  a[3] = createGenPair(2, 2.0f);

  size_t length = 4;
  size_t votoMaxConsentito = 13;

  bool soluzione[4] = {false, false, false, false};
  bool r[4] = {false, false, false, false};

  printf("\n-----------------------------------\n");
  printf(" Spazio degli stati di smallTest.\n");
  printf("-----------------------------------\n");
  bool sottoinsieme[4] = {false, false, false, false};
  spazioStati(a, sottoinsieme, 0, length);

  printf("\n--------------------------------\n");
  printf(" Tutte le soluzioni di smallTest,\n");
  printf(" ponendo a 13 la votazione massima.\n");
  printf("--------------------------------\n");
  soluzioni(a, soluzione, votoMaxConsentito, 0, length);

  printf("\n----------------------------------\n");
  printf(" Risposta (answer) ottenuta da smallTest,\n");
  printf(" ponendo a 13 la votazione massima.\n");
  printf("----------------------------------\n");
  risposta(a, votoMaxConsentito, r, soluzione, 0, length);
  printBooleanArray("Risposta", r, length);

  for (size_t i = 0; i < length; i++) {
    free(a[i].first);
    free(a[i].second);
  }

  return 0;
}
