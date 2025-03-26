#include "../utility/header/ArrIntInt.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <random>
#include <iterator>

using namespace std;

/* Visita ricorsivamente l'elenco dei liveNodes, finche'
   * non si vuota. La terminazione e' assicurata dalla finitezza
   * dello spazio degli stati. Si assume un elenco iniziale di
   * liveNodes composto da un nodo che corrisponde alla radice
   * dello spazio degli stati.                                    */
class PermutazioniRicRandom {
public:
  void risposte(list<ArrIntInt> &liveNodes) {
    ArrIntInt node = eNode(liveNodes);
      if (!completo(node)) {
        if (!rifiuta()) {
          espande(node, liveNodes);
          while (!liveNodes.empty()) {
            risposte(liveNodes);
          }
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

private:
  /* Preleva un elemento random nello spazio
   * degli stati.                                                */
 ArrIntInt eNode(list<ArrIntInt> &liveNodes) {
    int nodeIndex = indiceENode(liveNodes);
    auto it = liveNodes.begin();
    advance(it, nodeIndex);
    ArrIntInt node = *it;
    liveNodes.erase(it); 
    return node;
  }

 /* L'eNode e' estratto a caso dai live nodes.  */
  int indiceENode(list<ArrIntInt> &liveNodes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, liveNodes.size() - 1);
    return distrib(gen);
  }
  /* Un eNode corrisponde and una soluzione completa se, la
   * sua componente, corrispondente ad una soluzione, e',
   * appunto, completa.                                        */
  bool completo(const ArrIntInt &eNode) {
    vector<int> soluzione = eNode.pi0();
    int j = eNode.pi1();
    return soluzione.size() == j;
  }

  /* Generando tutto lo spazio delle permutazioni, non
   * si rifiuta mai . */
  bool rifiuta() { return false; }

  /* Implementa l'invariante di una visita in ampiezza dello spazio
   * degli stati. In particolare, tratta l'elenco dei liveNodes
   * come una coda, accodando i figli dell'attuale eNode.          */
 
void espande(const ArrIntInt& eNode, std::list<ArrIntInt>& liveNodes) {
    vector<int> soluzione = eNode.pi0();
    int j = eNode.pi1();

    int i = j;
    while (i < soluzione.size()) {
        swap(soluzione[i], soluzione[j]);

        vector<int> nuovaSoluzione = soluzione; 
        ArrIntInt nuovoLiveNode(nuovaSoluzione, j + 1);

        liveNodes.push_back(nuovoLiveNode);

        swap(soluzione[i], soluzione[j]);
        i++;
    }
}

  /* Generando tutto lo spazio delle permutazioni, non appena
   * una soluzione e' completa non possiamo far altro che accettare. */
  bool accetta() { return true; }


string toStringENode(const ArrIntInt& node) {
    vector<int> soluzione = node.pi0(); 
    int j = node.pi1(); 

    string result = "{ ";
    for (size_t i = 0; i < soluzione.size(); i++) {
        result += to_string(soluzione[i]); 
        if (i < soluzione.size() - 1) 
            result += ", "; 
    }
    result += " } (j = " + to_string(j) + ")"; 
    return result;
}

};

void testCase1() {
  cout << "Test Case 1: {1, 2, 3}" << endl;
  vector<int> initialSolution = {1, 2, 3};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRandom generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase2() {
  cout << "Test Case 2: {4, 5}" << endl;
  vector<int> initialSolution = {4, 5};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRandom generator;
  generator.risposte(liveNodes);
  cout << endl;
}
void testCase3() {
  cout << "Test Case 3: {1, 2, 3, 4}" << endl;
  vector<int> initialSolution = {1, 2, 3, 4};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRandom generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase4() {
  cout << "Test Case 4: {10, 20, 30}" << endl;
  vector<int> initialSolution = {10, 20, 30};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRandom generator;
  generator.risposte(liveNodes);
  cout << endl;
}

void testCase5() {
  cout << "Test Case 5: {0, 1, 2, 3, 4}" << endl;
  vector<int> initialSolution = {0, 1, 2, 3, 4};
  ArrIntInt initialNode(initialSolution, 0);
  list<ArrIntInt> liveNodes;
  liveNodes.push_back(initialNode);
  PermutazioniRicRandom generator;
  generator.risposte(liveNodes);
  cout << endl;
}

int main() {
  testCase1();
  testCase2();
  testCase3();
  testCase4();
  testCase5();
  return EXIT_SUCCESS;
}
