#ifndef VALUTAZIONEPER_H
#define VALUTAZIONEPER_H

#include "common.h"
#include <stddef.h>

void permutazioni(GenPair *a, size_t j, size_t length);

void soluzioni(GenPair *a, size_t votoMaxConsentito, size_t j, size_t length);

char *spazioStatiOut(GenPair *a, size_t length);

GenPair *risposta(GenPair *a, GenPair *r, float votoMaxConsentito, size_t j,
                  size_t lengthA, size_t lengthRisposta);

GenPair *rispostaOut(GenPair *a, GenPair *risposta, size_t votoMaxConsentito,
                     size_t lengthA, size_t lengthRisposta);

char *soluzioniOut(GenPair *a, size_t votoMaxConsentito, size_t length);

#endif /* VALUTAZIONEPER_H */
