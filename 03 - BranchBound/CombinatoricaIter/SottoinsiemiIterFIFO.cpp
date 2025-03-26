#include "../utility/header/ArrBoolInt.h"
#include <list>

using namespace std;

class SottoinsiemiIterFIFO {

public:
  int conta = 0;

  /** Genera tutti i sottoinsiemi di una collezione di elementi
   * con un processo iterativo, producendo uno spazio degli stati
   * in accordo con una visita in ampiezza dell'albero che lo
   * rappresenta.
   *
   * La visita in ampiezza segue dall'accodare (politica FIFO)
   * tutti i figli di un eNode alla coda dei liveNodes.         */

  void risposte(list<ArrBoolInt> &liveNodes) {
    while (!liveNodes.empty()) {
      ArrBoolInt node = eNode(liveNodes);

      if (!completo(node)) {
        if (!rifiuta()) {
          espande(node, liveNodes);
        } else {
          cout << "R: " << toStringENode(node) << endl;
        }
      } else {
        if (accetta()) {
          cout << "A: " << toStringENode(node) << endl;
        } else {
          cout << "N: " << toStringENode(node) << endl;
        }
      }
    }
  }

private:
  /* Preleva sempre il primo elemento disponibile nello spazio
   * degli stati.                                                */
  ArrBoolInt eNode(list<ArrBoolInt> &liveNodes) {
    ArrBoolInt node = liveNodes.front();
    liveNodes.pop_front();
    return node;
  }

  /* Un eNode corrisponde and una soluzione completa se, la
   * sua componente, corrispondente ad una soluzione, e',
   * appunto, completa.                                        */
  bool completo(const ArrBoolInt &eNode) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();
    return soluzione.size() == j;
  }

  /* generando tutto lo spazio dei sottoinsiemi, non
   * si rifiuta mai . */
  bool rifiuta() { return false; }

  /* Implementa l'invariante di una visita in ampiezza dello spazio
   * degli stati. In particolare, tratta l'elenco dei liveNodes
   * come una coda, accodando i figli dell'attuale eNode.          */
  void espande(const ArrBoolInt &eNode, list<ArrBoolInt> &liveNodes) {
    vector<bool> soluzione = eNode.pi0();
    int j = eNode.pi1();

    for (bool nuovoElementoSoluzione :
         {static_cast<bool>(soluzione[j]), static_cast<bool>(!soluzione[j])}) {
      vector<bool> nuovaSoluzione = soluzione;
      nuovaSoluzione[j] = nuovoElementoSoluzione;
      ArrBoolInt nuovoLiveNode(nuovaSoluzione, j + 1);
      liveNodes.push_front(nuovoLiveNode);
    }
  }

  /* Generando tutto lo spazio dei sottoinsiemi, non appena
   * una soluzione e' completa non possiamo far altro che accettare. */
  bool accetta() { return true; }

  string toStringENode(ArrBoolInt node) {
    vector<bool> soluzione = node.pi0();
    int j = node.pi1();

    string result = "{ ";
    for (size_t i = 0; i < soluzione.size(); i++) {
      result += (soluzione[i] ? "1" : "0");
      if (i < soluzione.size() - 1) {
        result += ", ";
      }
    }
    result += " } (j = " + to_string(j) + ")";
    return result;
  }
};

void testCase(const std::vector<bool>& initialSolution) {
    cout << "\nTesting with initial solution: ";
    for (bool val : initialSolution) {
        cout << (val ? "1 " : "0 ");
    }
    cout << "\n";
    
    ArrBoolInt initialNode(initialSolution, 0);
    list<ArrBoolInt> liveNodes;
    liveNodes.push_back(initialNode);
    
    SottoinsiemiIterFIFO generator;
    generator.risposte(liveNodes);
}

int main() {
    testCase({false, false, false});
    
    testCase({true, true, true});
    
    testCase({true, false, true});
    
    testCase({true});
    
    testCase({false});
    
    return 0;
}
