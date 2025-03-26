#include "../utility/header/ArrBoolInt.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

/** Risolve il problema Subsetsum aggiungendo una fase di bound
 * all'algorimto Least-Cost search per Subsetsum in S3LC.
 *
 * Il problema e' una coppia:
 * < X[0..n) di elementi di cui formare sottoinsiemi
 * , valore S da eguagliare, sommando elementi di un sottoinsieme
 *   X[0..j) di X[0..n), se X[0..j) esiste> .
 *
 * In S3LC abbiamo sintetizzato la relazione:
 *
 *   FH(x[0..j))+G(x[0..j))-X[split]
 *           <= S <= FH(x[0..j))+G(x[0..j))
 *
 * che determina un intervallo entro il quale S, valore cercato,
 * debba trovarsi, in relazione alle seguenti quantita':
 * -) il costo noto di x[0..j), fornito da FH(x[0..j)),
 * -) il costo necessario per la minima approssimazione per
 * eccesso di S, fornito da G(x[0..j)),
 * -) il costo necessario per la massima approssimazione per
 * difetto di S, fornito da G(x[0..j))-X[split]
 *
 * Se S non puo' stare nell'intervallo che un nodo x[0..j),
 * allora non c'e' speranza di usare x[0..j) per ottenere S.
 * */

class S3LCBB {
public:
  void risposte(const vector<int> &insieme, int s,
                list<ArrBoolInt> &liveNodes) {
    while (!liveNodes.empty()) {
      ArrBoolInt node = eNode(insieme, s, liveNodes);

      if (!completo(insieme, s, node)) {
        if (!rifiuta(insieme, s, node, liveNodes)) {
          espande(node, liveNodes);
        } else {
          cout << "R: " << toStringENode(insieme, node) << endl;
        }
      } else {
        if (accetta(insieme, s, node)) {
          cout << "A: " << toStringENode(insieme, node) << endl;
        } else {
          cout << "N: " << toStringENode(insieme, node) << endl;
        }
      }
    }
  }

private:
  /* Restituisce un eNode, estratto in accordo con la politica implementata
   * dal metodo indiceENode. Prima dell'estrazione, stampa la lista dei
   * live nodes.                                                           */
  ArrBoolInt eNode(const vector<int> &insieme, int s,
                   list<ArrBoolInt> &liveNodes) {
    /* Stampa dei live nodes.    */
    cout << "Live nodes: " << toStringLiveNodes(insieme, liveNodes);

    int indice = indiceENode(insieme, s, liveNodes);
    auto it = liveNodes.begin();
    advance(it, indice);
    ArrBoolInt eNode = *it;
    liveNodes.erase(it);

    int fH = fCompostoH(insieme, s, eNode);
    std::cout << " ---> " << toStringENode(insieme, eNode) << " Costo : " << fH
              << ", Difetto: " << stimaCostoPerDifetto(insieme, fH, s, eNode)
              << ", Eccesso: " << stimaCostoPerEccesso(insieme, fH, s, eNode)
              << std::endl;

    return eNode;
  }

  /* Restituisce l'indice al live node con costo minimo
   * e stampa l'eNode estratto con costo e costo stimato.             */
  int indiceENode(const std::vector<int> &insieme, int s,
                  const std::list<ArrBoolInt> &liveNodes) {
    auto it = liveNodes.begin();
    /* Assume che il primo liveNode di liveNodes sia a costo minimo. */
    int indiceLiveNodeCostoMinimo = 0;
    ArrBoolInt liveNode = *it;

    int fH = fCompostoH(insieme, s, liveNode);
    int costoMinimo = -stimaCostoPerEccesso(insieme, fH, s, liveNode);

    int indice = 1;
    /* Cerca il liveNode a costo minimo. */
    for (++it; it != liveNodes.end(); ++it, ++indice) {
      liveNode = *it;

      fH = fCompostoH(insieme, s, liveNode);
      int costoLiveNode = -stimaCostoPerEccesso(insieme, fH, s, liveNode);

      if (costoLiveNode < costoMinimo) {
        indiceLiveNodeCostoMinimo = indice;
        costoMinimo = costoLiveNode;
      }
    }

    return indiceLiveNodeCostoMinimo;
  }

  bool completo(const vector<int> &insieme, int s, const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();
    return soluzione.size() == j;
  }

  bool rifiuta(const vector<int> &insieme, int somma, const ArrBoolInt &eNode,
               list<ArrBoolInt> &liveNodes) {
    int fHDiENode = fCompostoH(insieme, somma, eNode);
    int costoPerDifetto =
        stimaCostoPerDifetto(insieme, fHDiENode, somma, eNode);
    int costoPerEccesso =
        stimaCostoPerEccesso(insieme, fHDiENode, somma, eNode);
    return !(costoPerDifetto <= somma && somma <= costoPerEccesso);
  }

  /* Estende l'elenco dei liveNodes con due figli di eNode. */
  void espande(const ArrBoolInt &eNode, list<ArrBoolInt> &liveNodes) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    for (bool nuovoElementoSoluzione :
         {static_cast<bool>(soluzione[j]), static_cast<bool>(!soluzione[j])}) {
      vector<bool> nuovaSoluzione = soluzione;
      nuovaSoluzione[j] = nuovoElementoSoluzione;
      ArrBoolInt nuovoLiveNode(nuovaSoluzione, j + 1);
      liveNodes.push_back(nuovoLiveNode);
    }
  }

  bool accetta(const vector<int> &insieme, int somma, const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    int sommaENode = 0;
    for (int i = 0; i < j; i++) {
      sommaENode += (soluzione[i]) ? insieme[i] : 0;
    }
    return sommaENode == somma;
  }

  string toStringENode(const vector<int> &insieme, const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();
    int i = 0;
    string stringa = "[";
    while (i < j) {
      stringa += (soluzione[i]) ? " " + to_string(insieme[i]) + ","
                                : "!" + to_string(insieme[i]) + ",";
      i++;
    }

    if (stringa.back() == ',') {
      stringa.pop_back();
    }
    return stringa + "]";
  }

  /* Restituisce il costo noto di soluzione[0..j) in liveNode, ovvero
   * l'analogo di FH(soluzione[0..j)).                                       */

  int fCompostoH(const vector<int> &insieme, int s,
                 const ArrBoolInt &liveNode) {
    vector<bool> soluzione = liveNode.pi0();
    int j = liveNode.pi1();
    int i = 0;

    int fCompostoH = 0;
    while (i < j) {
      fCompostoH += (soluzione[i]) ? insieme[i] : 0;
      i++;
    }

    return fCompostoH;
  }

  /* Restituisce il valore G(soluzione[0..j))-insieme[split],
   * cioe' somma a soluzione[0..j) tutti gli elementi in
   * insieme[j..split)
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] si ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 8.1 di Horowitz di nome UBound. */
  int stimaCostoPerDifetto(const vector<int> &insieme, int fH, int s,
                           const ArrBoolInt &liveNode) {
    int j = liveNode.pi1();

    int costoLiveNode = fH;
    int i = j;
    bool incrementa = true;
    while (i < insieme.size() && incrementa) {
      incrementa = (costoLiveNode + insieme[i] < s);
      if (incrementa) {
        costoLiveNode += insieme[i];
        i++;
      }
    }

    return costoLiveNode;
  }

  /* Restituisce il valore G(soluzione[0..j)), cioe' somma
   * a soluzione[0..j) tutti gli elementi in insieme[j..split]
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 7.11 di Horowitz di nome Bound.
   * La differenza e' che non si fa alcun rilassamento lineare
   * perche' conosciamo il limite S da ottenere.                */
  int stimaCostoPerEccesso(const vector<int> &insieme, int fH, int s,
                           const ArrBoolInt &liveNode) {
    int j = liveNode.pi1();

    int costoLiveNode = fH;
    int i = j;
    bool incrementa = true;
    while (i < insieme.size() && incrementa) {
      incrementa = (costoLiveNode < s);
      if (incrementa) {
        costoLiveNode += insieme[i];
        i++;
      }
    }
    return costoLiveNode;
  }

  string toStringLiveNodes(const vector<int> &insieme,
                           const list<ArrBoolInt> &liveNodes) {
    string stringa = "{";

    for (const auto &liveNode : liveNodes) {
      stringa += toStringENode(insieme, liveNode);
    }

    return stringa + "}";
  }
};

vector<bool> initSoluzione(size_t size) { return vector<bool>(size, false); }

void testErickson() {
  vector<int> insieme = {8, 6, 7, 5, 3, 10, 9};
  int somma = 15;

  list<ArrBoolInt> liveNodes;
  vector<bool> soluzione = initSoluzione(insieme.size());
  ArrBoolInt radice(soluzione, 0);
  liveNodes.push_back(radice);

  S3LCBB s3LCBB;
  s3LCBB.risposte(insieme, somma, liveNodes);
  cout << "%---------------------------------" << endl;
}

void testHorowitz() {
  vector<int> insieme = {24, 11, 13, 7};
  int somma = 31;

  list<ArrBoolInt> liveNodes;
  vector<bool> soluzione = initSoluzione(insieme.size());
  ArrBoolInt radice(soluzione, 0);
  liveNodes.push_back(radice);

  S3LCBB s3LCBB;
  s3LCBB.risposte(insieme, somma, liveNodes);
  cout << "%---------------------------------" << endl;
}

int main() {
  testErickson();
  testHorowitz();
  return EXIT_SUCCESS;
}
