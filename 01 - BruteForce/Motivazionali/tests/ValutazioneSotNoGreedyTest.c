#include "../header/ValutazioneSot.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

GenPair createGenPair(int votoMax, float votazione) {
    GenPair p;
    p.first = malloc(sizeof(int));
    p.second = malloc(sizeof(float));
    *(int *)p.first = votoMax;
    *(float *)p.second = votazione;
    return p;
}

int main() {
    GenPair a[4];

    a[0] = createGenPair(2, 2.0f);
    a[1] = createGenPair(5, 4.6f);
    a[2] = createGenPair(4, 3.9f);
    a[3] = createGenPair(2, 2.0f);

    size_t length = 4;
    size_t votoMaxConsentito = 9;  

    bool soluzione[4] = {false, false, false, false};
    bool r[4] = {false, false, false, false};

    printf("Testing risposta function:\n");
    risposta(a, votoMaxConsentito, r, soluzione, 0, length);

    printf("\nTesting soluzioni function:\n");
    soluzioni(a, soluzione, votoMaxConsentito, 0, length);

    printf("\nTesting spazioStati function:\n");
    bool sottoinsieme[4] = {false, false, false, false};
    spazioStati(a, sottoinsieme, 0, length);

    for (size_t i = 0; i < length; i++) {
        free(a[i].first);
        free(a[i].second);
    }

    return EXIT_SUCCESS;
}
