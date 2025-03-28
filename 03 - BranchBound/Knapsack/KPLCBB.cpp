#include "../utility/header/ArrBoolInt.h"
#include "../utility/header/IntFloat.h"
#include "../utility/header/IstanzaKP.h"
#include "header/KPFIFOBB.h"
#include <cstddef>
#include <iterator>
#include <list>
/** Algoritmo iterativo Branch&Bound per risolvere KP in accordo con
 * una politica FIFO per l'accodamento dei live nodes e di una politica
 * Least Cost per la scelta dell'eNode in uno spazio degli stati che
 * rappresenta sottoinsiemi.
 *
 * Il problema e' una terna:
 * < W[0..n) di pesi
 * , P[0..n) di profitti
 * , valore c di capacita' massima > .
 *
 * La funzione costo e' l'approssimazione per eccesso del lavoro da compiere
 * per produrre una eventuale risposta, partendo dal live node considerato.
 * Quindi, essa valuta il lavoro noto, usando soluzione[0..j) cui aggiunge
 * sia il costo di tutti gli elementi di indice [j..split), sia la porzione
 * del costo p_split, proporzionale al peso w_split che serve per saturare
 * la capacita'.  */
using namespace std;

class KPLCBB : public KPFIFOBB {
private:
  /* Restituisce l'indice al live node con profitto stimato migliore,
   * cioe' inferiore, se preso con segno '-', a quello di tutti gli altri
   * liveNodes. Per ogni liveNode, la stima del profitto ottimale usa
   * il profitto assicurato dal nodo stesso e raccolto in profittoAssicurato. */

  virtual size_t indiceENode(IstanzaKP iKPBB, list<ArrBoolInt> liveNodes) {
     /* Assume che il primo liveNode di liveNodes sia a costo minimo. */
    auto it = liveNodes.begin();
    ArrBoolInt liveNode = *it;

    IntFloat f = fH(iKPBB, liveNode);
    float migliorProfittoMinimo = -stimaCostoPerEccesso(iKPBB, f, liveNode);
    size_t indiceLiveNodeMigliore = 0;

    size_t i = 1;
    /* Cerca il liveNode a costo minimo */
    for (auto it = next(liveNodes.begin()); it != liveNodes.end(); ++it, ++i) {
      liveNode = *it;
      float stimaProfittoLiveNode = -stimaCostoPerEccesso(iKPBB, f, liveNode);

      if (stimaProfittoLiveNode < migliorProfittoMinimo) {
        indiceLiveNodeMigliore = i;
        migliorProfittoMinimo = stimaProfittoLiveNode;
      }
    }

    return indiceLiveNodeMigliore;
  }
};

int main() {
  int capacity = 2821;

  IstanzaKP iKPBB =
      IstanzaKP({22, 7, 16, 60, 66, 89, 86, 20, 87, 7},
                {64, 28, 14, 3, 28, 26, 73, 72, 77, 18}, capacity);

  ArrBoolInt rispostaCorrente(vector<bool>(10, false), 0);

  list<ArrBoolInt> liveNodes;
  liveNodes.push_back(rispostaCorrente);

  KPLCBB knapsackSolver;

  knapsackSolver.risposte(iKPBB, rispostaCorrente, liveNodes);

  return EXIT_SUCCESS;
}
