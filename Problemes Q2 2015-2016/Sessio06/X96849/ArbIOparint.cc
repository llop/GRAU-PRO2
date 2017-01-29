
#include "ArbIOparint.hh"

void llegir_arbre_parint(Arbre<Pari>& a, int marca){
/* Pre: a es buit; el canal estandar d'entrada conté el recorregut en preordre
   d'un arbre binari A d'enters marcat amb "marca" */  
/* Post: a = A */

  Arbre<Pari> a1;
  Arbre<Pari> a2;
  int f, s;
  cin >> f >> s;
 
  Pari x(f,s);
  if (x.first != marca) {
    llegir_arbre_parint(a1, marca);
    llegir_arbre_parint(a2, marca);
    a.plantar(x,a1,a2);
  }
}

void escriure_arbre_parint(Arbre<Pari> &a) {
/* Pre: cert */ 
/* Post: El canal estandar de sortida conté el recorregut en inordre d'a */ 

  if (not a.es_buit()) {
    Arbre<Pari> a1;
    Arbre<Pari> a2;
    Pari x = a.arrel();
    a.fills(a1,a2);
    escriure_arbre_parint(a1); 
    cout << " (" << x.first << "," << x.second << ")";
    escriure_arbre_parint(a2);
    a.plantar(x,a1,a2);
  }
}

