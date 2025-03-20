#ifndef VALUTAZIONESOT_H
#define VALUTAZIONESOT_H

#include "common.h"
#include <stdbool.h>
#include <stddef.h>

void soluzioni(GenPair *a, bool *soluzione, size_t votoMaxConsentito, size_t j,
               size_t length);

void spazioStati(GenPair *a, bool *sottoinsieme, size_t j, size_t length);

char *spazioStatiOut(GenPair *a, bool *sottoinsieme, size_t length);

void risposta(GenPair *a, size_t votoMaxConsentito, bool *risposta,
              bool *soluzione, size_t j, size_t length);

char *rispostaOut(GenPair *a, size_t votoMaxConsentito, bool *soluzione,
                  bool *risposta, size_t length);

char *soluzioniOut(GenPair *a, bool *soluzione, size_t votoMaxConsentito,
                   size_t length);

#endif /* VALUTAZIONESOT_H */
