#ifndef BANDO_DIS_REP_H
#define BANDO_DIS_REP_H
#include "common.h"
#include <stddef.h>

void swap(size_t *a, size_t i, size_t j);

char *spazioStatiOut(GenPair *area0, GenPair *area1, GenPair *area2,
                     size_t *disposizione, size_t length);

void spazioStati(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
                 size_t j, size_t *disposizione, size_t k, size_t length);

char *soluzioniOut(GenPair *area0, GenPair *area1, GenPair *area2,
                   size_t *soluzione, size_t finanziabileTotale,
                   size_t length_soluzione);

void soluzioni(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
               size_t length_a, size_t *soluzione, size_t length_soluzione,
               size_t finanziabileTotale, size_t j);

char *rispostaOut(GenPair *area0, GenPair *area1, GenPair *area2,
                  size_t finanziabileTotale, size_t *r, size_t length_risposta,
                  size_t *soluzione, size_t length_soluzione);

void risposta(GenPair *area0, GenPair *area1, GenPair *area2, size_t *a,
              size_t *r, size_t length_risposta, size_t *soluzione,
              size_t length_soluzione, size_t finanziabileTotale, size_t j,
              size_t k, size_t length);

#endif // BANDO_DIS_REP_H
