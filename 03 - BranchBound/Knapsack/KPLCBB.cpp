#include "../utility/header/ArrBoolInt.h"
#include "../utility/header/IstanzaKP.h"
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

class KPLCBB {};

int main(int argc, char *argv[]) { return 0; }
