#include "../header/ValutazioniSot.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  int a_values[10];
  float b_values[10];
  GenPair a[10];
  size_t i = 0;
  int votoMaxConsentito = 50;

  bool soluzione[10] = {false, false, false, false, false,
                        false, false, false, false, false};
  bool risp[10] = {false, false, false, false, false,
                   false, false, false, false, false};

  while (i < 10) {
    a_values[i] = rand() % 100 + 1;
    b_values[i] = (rand() % 100 + 1) / 10.0f;

    a[i].first = &a_values[i];
    a[i].second = &b_values[i];

    i++;
  }

  valutazioni(a, votoMaxConsentito, risp, soluzione, 0, 10, 10, 10);

  return EXIT_SUCCESS;
}
