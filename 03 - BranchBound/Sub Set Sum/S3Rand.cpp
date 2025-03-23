#include "../utility/header/ArrBoolInt.h"
#include <cstddef>
#include <ctime>
#include <iterator>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class S3Rand {

public:
  void risposte(int *insieme, int s, list<ArrBoolInt> liveNodes) {
    list<ArrBoolInt>::iterator it = liveNodes.begin();
    while (it != liveNodes.end()) {

      ++it;
    }
  }

private:
  /* Restituisce un eNode, estratto in accordo con la politica implementata
   * dal metodo indiceENode. Prima dell'estrazione, stampa la lista dei
   * live nodes.
   */
  ArrBoolInt eNode(int *insieme, int s, list<ArrBoolInt> liveNodes) {
    int indiceENode, fH;
    auto it = liveNodes.begin();

    cout << "Live nodes: " + toStringLiveNodes(insieme, liveNodes);

    indiceENode = getIndiceEnode(insieme, s, liveNodes);
    advance(it, indiceENode);
    ArrBoolInt eNode = *it;

    liveNodes.erase(it);

    fH = fCompostoH(insieme, s, eNode);

    cout << "---> " << toStringENode(insieme, eNode) << " Costo: " << fH
         << ", Difetto: " << stimaCostoPerDifetto(insieme, fH, s, eNode)
         << ", Eccesso: " << stimaCostoPerEccesso(insieme, fH, s, eNode);
    return eNode;
  }

  /* Restituisce il valore G(soluzione[0..j))-insieme[split],
   * cioe' somma a soluzione[0..j) tutti gli elementi in
   * insieme[j..split)
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] si ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 8.1 di Horowitz di nome UBound.
   */
  int stimaCostoPerDifetto(int *insieme, int fH, int s, ArrBoolInt liveNode) {}

  /* Restituisce il valore G(soluzione[0..j)), cioe' somma
   * a soluzione[0..j) tutti gli elementi in insieme[j..split]
   * dove split e' il minimo indice per cui
   * aggiungendo insieme[j..split) non si supera S, mentre
   * aggiungendo insieme[j..split] ottiene almeno S.
   *
   * E' ispirato all'Algoritmo 7.11 di Horowitz di nome Bound.
   * La differenza e' che non si fa alcun rilassamento lineare
   * perche' conosciamo il limite S da ottenere.
   */

  int stimaCostoPerEccesso(int *insieme, int fH, int s, ArrBoolInt liveNode) {}

  /* Restituisce il costo noto di soluzione[0..j) in liveNode, ovvero
   * l'analogo di FH(soluzione[0..j)).
   */
  int fCompostoH(int *insieme, int s, ArrBoolInt liveNodes) {
    vector<bool> soluzione = liveNodes.pi0();
    int j = liveNodes.pi1();
    int fCompostH = 0;
    size_t i = 0;

    while (i < j) {
      fCompostH += (soluzione[i]) ? insieme[i] : 0;
      i++;
    }

    return fCompostH;
  }

  /* L'eNode e' estratto a caso dai live nodes.  */
  int getIndiceEnode(int *insieme, int s, list<ArrBoolInt> liveNodes) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(0, liveNodes.size() - 1);

    auto it = liveNodes.begin();
    advance(it, distrib(gen));

    return distance(liveNodes.begin(), it);
  }

  string intToString(int num) {
    ostringstream oss;
    oss << num;
    return oss.str();
  }

  string toStringENode(int *insieme, ArrBoolInt eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    string stringa = "[";
    size_t i = 0;

    while (i < j) {
      if (soluzione[i]) {
        stringa += " " + intToString(insieme[i]) + ",";
      } else {
        stringa += "!" + intToString(insieme[i]) + ",";
      }
      i++;
    }

    if (!stringa.empty() && stringa.back() == ',') {
      stringa = stringa.substr(0, stringa.length() - 1);
    }

    stringa += "]";
    return stringa;
  }

  string toStringLiveNodes(int *insieme, const list<ArrBoolInt> &liveNodes) {
    string stringa = "{";

    for (auto it = liveNodes.begin(); it != liveNodes.end(); ++it) {
      ArrBoolInt liveNode = *it;
      stringa += toStringENode(insieme, liveNode);
    }

    stringa += "}";
    return stringa;
  }
};
