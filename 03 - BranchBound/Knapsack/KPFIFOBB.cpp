#include "../utility/header/ArrBoolInt.h"
#include "../utility/header/IntFloat.h"
#include "../utility/header/IstanzaKP.h"
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <list>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

/** Algoritmo iterativo Branch&Bound per risolvere KP in accordo con
 * politiche FIFO sia di accodamento dei live nodes e sia di scelta
 * dell'eNode in uno spazio degli stati che rappresenta sottoinsiemi.
 *
 * Il problema e' una terna:
 * < W[0..n) di pesi
 * , P[0..n) di profitti
 * , valore c di capacita' massima > .
 * */

using namespace std;

class KPFIFOBB {
public:
  void risposte(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente,
                list<ArrBoolInt> liveNodes) {
    /* Stampa la prima soluzione, ottenuta con l'algoritmo Greedy,
     * per stabilire il primo lower bound al profitto ottimo globale
     * che stiamo cercando.                                           */
    cout << "A [0..r)" << toStringENode(iKPBB, rispostaCorrente) << endl;
    cout << toStringValori(" con ", iKPBB, rispostaCorrente) << endl;

    while (!liveNodes.empty()) {
      ArrBoolInt node = eNode(iKPBB, rispostaCorrente, liveNodes);
      if (!rifiuta(iKPBB, rispostaCorrente, node)) {
        if (accetta(iKPBB, rispostaCorrente, node)) {
          rispostaCorrente = node;
          cout << "A eNode " << toStringENode(iKPBB, node) << endl;
          cout << toStringValori(" con ", iKPBB, node) << endl;
        }
        if (!completo(iKPBB, rispostaCorrente, node)) {
          espande(node, liveNodes);
        } else {
          cout << "C eNode " << toStringENode(iKPBB, node) << endl;
          cout << toStringValori(" con ", iKPBB, node) << endl;
        }
      } else {
        cout << "R eNode " << toStringENode(iKPBB, node) << endl;
        cout << toStringValori(" con ", iKPBB, node) << endl;
      }
    }
  }

protected:
  /* Restituisce un eNode, estratto in accordo con la politica implementata
   * dal metodo indiceENode. Prima dell'estrazione, stampa la lista dei
   * live nodes.                                                           */
  ArrBoolInt eNode(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente,
                   list<ArrBoolInt> &liveNodes) {
    size_t indice = indiceENode(iKPBB, liveNodes);
    auto it = liveNodes.begin();
    advance(it, indice);
    ArrBoolInt node = *it;
    liveNodes.erase(it);

    cout << toStringValori(" -> ", iKPBB, node)
         << toStringENode(iKPBB, rispostaCorrente) << endl;
    cout << toStringValori(" con ", iKPBB, node);
    return node;
  }

  /* Restituisce l'indice al live node con profitto stimato migliore,
   * cioe' inferiore, se preso con segno '-', a quello di tutti gli altri
   * liveNodes. Per ogni liveNode, la stima del profitto ottimale usa
   * il profitto assicurato dal nodo stesso e raccolto in profittoAssicurato. */

  virtual size_t indiceENode(IstanzaKP iKPBB, list<ArrBoolInt> liveNodes) { return 0; }

  /* Rifiuta eNode se non e' una soluzione: il suo peso supera quello
   * massimo ammissibile.                                              */
  bool rifiuta(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente, ArrBoolInt node) {
    IntFloat fHENode = fH(iKPBB, node);
    int pesoENode = fHENode.pi0(); /* costo noto di eNode */
    int c = iKPBB.getC();

    return pesoENode > c;
  }

  /* Accetta se il profitto dell'eNode migliora quello offerto
   * da rispostaCorrente.                                              */

  bool accetta(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente, ArrBoolInt node) {
    IntFloat fHRispostaCorrente = fH(iKPBB, rispostaCorrente);
    float profittoRispostaCorrente = fHRispostaCorrente.pi1();
    IntFloat fHENode = fH(iKPBB, node);
    float profittoENode = fHENode.pi1();

    /* usando '<' al posto di '<=' non elenca tutte le risposte */
    return profittoRispostaCorrente < profittoENode;
  }

  /* Certamente eNode e' completo se rappresenta un intero ramo dello
   * spazio degli stati.
   * Tuttavia, e' completo anche quando la stima per *eccesso* del
   * profitto offerto da eNode non supera il profitto certo di
   * rispostaCorrente. In tal caso non vale la pena esplorare il
   * sottoalbero di cui e' radice alla ricerca di una soluzione
   * della migliore trovata sinora, ovvero rispostaCorrente.    */

  bool completo(IstanzaKP iKPBB, ArrBoolInt rispostaCorrente, ArrBoolInt node) {
    vector<bool> soluzione = node.pi0();
    int j = node.pi1();
    float profittoStimatoENode, profittoRispostaCorrente;

    bool completo = soluzione.size() == j;

    if (!completo) {
      IntFloat fHENode = fH(iKPBB, node);
      profittoStimatoENode = stimaCostoPerEccesso(iKPBB, fHENode, node);
      IntFloat fHRispostaCorrente = fH(iKPBB, rispostaCorrente);
      profittoRispostaCorrente = fHRispostaCorrente.pi1();
      /* Completo se rispostaCorrente assicura un profitto non peggiore
       * del miglior profitto ottenibile da eNode che approssima per
       * eccesso z*.                                                    */
      completo = profittoRispostaCorrente >= profittoStimatoENode;
      /*                   fh.z                   zLP o fh.z+g.z        */
    }

    return completo;
  }

  /* Restituisce peso e profitto assicurati dal liveNode,
   * cioe' dal sottoinsieme in soluzione[0..j).                */

  IntFloat fH(IstanzaKP iKPBB, ArrBoolInt liveNode) {
    vector<bool> soluzione = liveNode.pi0();
    int j = liveNode.pi1();
    size_t i = 0;

    vector<int> w = iKPBB.getW();
    vector<float> p = iKPBB.getP();
    int pesoLiveNode = 0;
    float profittoLiveNode = 0.0f;

    while (i < j) {
      pesoLiveNode += (soluzione[i]) ? w[i] : 0;
      profittoLiveNode += (soluzione[i]) ? p[i] : 0.0f;
      i++;
    }

    return IntFloat(pesoLiveNode, profittoLiveNode);
  }

  /* Restituisce il valore fH.z(soluzione[0..j)+g.z(soluzione[0..j)),
   * cioe' somma il profitto certo di soluzione[0..j)
   * con i profitti di tutti gli elementi non ancora inclusi in soluzione,
   * che, se aggiunti, non sforano il limite c, ovvero i profitti di tutti
   * gli elementi con indice nell'intervallo [j..split).
   *
   * Ispirato sia a Bound, cioe' Algoritmo 7.11 di Horowitz,
   * sia a Greedy-LKP, descritto da Pisinger. */

  float stimaCostoPerEccesso(IstanzaKP iKPBB, IntFloat fHLiveNode,
                             ArrBoolInt liveNode) {
    vector<int> w = iKPBB.getW();
    vector<float> p = iKPBB.getP();
    int c = iKPBB.getC();

    int pesoLiveNode = fHLiveNode.pi0();
    float profittoLiveNode = fHLiveNode.pi1();

    vector<bool> soluzione = liveNode.pi0();
    int j = liveNode.pi1();

    int pesoStimato = pesoLiveNode;                /* peso sicuro */
    float profittoStimatoENode = profittoLiveNode; /* profitto sicuro */

    int split = j;
    bool incrementa = true;
    while (split < soluzione.size() && incrementa) {
      incrementa = (pesoStimato + w[split] <= c);
      if (incrementa) {
        pesoStimato += w[split];
        profittoStimatoENode += p[split];
        split++;
      } else {
        profittoStimatoENode +=
            (float)(c - pesoStimato) * (p[split] / w[split]);
      }
    }
    return profittoStimatoENode;
  }

  /* METODO LASCIATO PER COMPLETEZZA E COMODITA', MA INUTILE.
   *
   * Incrementa quanto piu' possibile il profitto generato da
   * soluzione[0..j), estendendo soluzione[0..j) con ogni
   * elemento possibile, sino allo split escluso.
   *
   * Il motivo dell'inutilita' dovrebbe essere chiaro:
   * siamo sempre e solo interessati al profitto reale di un nodo
   * o al suo al profitto stimato.
   * Nel primo caso non siamo interessati ad arrivare allo split
   * item, ma solo all'ultimo item effettivamente inserito in
   * soluzione[0..j). Nel secondo, trovato lo split item dobbiamo
   * "riempire" lo spazio rimasto e calcolare il profitto ottimale,
   * relativo al nodo che stiamo valutando.
   *
   * E' l'Algoritmo 7.11, cioe' Bound di Horowitz, quindi una
   * generalizzazione di Greedy-split in Pisinger.                */

  float stimaCostoPerDifetto(IstanzaKP iKPBB, IntFloat fHLiveNode,
                             ArrBoolInt liveNode) {
    vector<int> w = iKPBB.getW();
    vector<float> p = iKPBB.getP();
    int c = iKPBB.getC();

    int pesoLiveNode = fHLiveNode.pi0();
    float profittoLiveNode = fHLiveNode.pi1();

    vector<bool> soluzione = liveNode.pi0();
    int j = liveNode.pi1();
    int i = j;

    while (i < soluzione.size()) {
      if (pesoLiveNode + w[i] <= c) {
        pesoLiveNode += w[c];
        profittoLiveNode += p[i];
      }
      i++;
    }

    return profittoLiveNode;
  }

  /* Estende l'elenco dei liveNodes con due figli di eNode. */
  void espande(ArrBoolInt node, list<ArrBoolInt> &liveNodes) {
    vector<bool> soluzione = node.pi0();
    int j = node.pi1();
    for (bool nuovoElementoSoluzione :
         {static_cast<bool>(soluzione[j]), static_cast<bool>(!soluzione[j])}) {
      vector<bool> nuovaSoluzione = soluzione;
      nuovaSoluzione[j] = nuovoElementoSoluzione;
      ArrBoolInt nuovoLiveNode(nuovaSoluzione, j + 1);
      liveNodes.push_back(nuovoLiveNode); /* FIFO */
    }
  }

  string toStringValori(string intestazione, IstanzaKP iKPBB,
                        ArrBoolInt stato) {
    vector<bool> soluzione = stato.pi0();
    int j = stato.pi1();
    vector<int> w = iKPBB.getW();
    vector<float> p = iKPBB.getP();
    int c = iKPBB.getC();

    int peso = 0;
    float profitto = 0.0f;
    for (size_t i = 0; i < j; i++) {
      if (soluzione[i]) {
        peso += w[i];
        profitto += p[i];
      }
    }

    ostringstream oss;
    oss << intestazione << "peso: " << peso << "/" << c
        << ", profitto: " << profitto << endl;
    return oss.str();
  }

  string toStringENode(IstanzaKP iKPBB, ArrBoolInt stato) {
    vector<bool> soluzione = stato.pi0();
    int j = stato.pi1();

    ostringstream oss;
    oss << "\n[";
    for (size_t i = 0; i < soluzione.size(); i++) {
      oss << (soluzione[i] ? "1" : "0");
      if (i < soluzione.size() - 1) {
        oss << ", ";
      }
    }
    oss << "] fino a " << j << endl;
    return oss.str();
  }
};

int main() {
    int capacity = 2821;  

    IstanzaKP iKPBB = IstanzaKP( {22, 7, 16, 60, 66, 89, 86, 20, 87, 7},  {64, 28, 14, 3, 28, 26, 73, 72, 77, 18}, capacity);

    ArrBoolInt rispostaCorrente(vector<bool>(10, false), 0);  

    list<ArrBoolInt> liveNodes;
    liveNodes.push_back(rispostaCorrente);

    KPFIFOBB knapsackSolver;

    knapsackSolver.risposte(iKPBB, rispostaCorrente, liveNodes);

    return EXIT_SUCCESS;
}

