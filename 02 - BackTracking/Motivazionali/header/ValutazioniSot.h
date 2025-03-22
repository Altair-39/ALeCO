#ifndef VALUTAZIONI_SOT_H
#define VALUTAZIONI_SOT_H

#include "common.h"
#include <stdbool.h>
#include <stddef.h>

void valutazioni(GenPair *a, int votoMaxConsentito, bool *risp, bool *soluzione,
                 int j, int lengthSoluzione, int lengthRisposta, int lengthA);

bool completa(int lengthSoluzione, int j);

bool rifiuta(GenPair *a, int votoMaxConsentito, bool *soluzione, int j);

bool accetta(GenPair *a, int votoMaxConsentito, bool *risp, bool *soluzione,
             int j);

void risposta(GenPair *a, int votoMaxConsentito, bool *risp, bool *soluzione,
              int j, int lengthRisposta, int lengthA);

#endif 
