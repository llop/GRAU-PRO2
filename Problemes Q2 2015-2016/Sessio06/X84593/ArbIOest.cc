
#include "ArbIOest.hh"

void llegir_arbre_est(Arbre<Estudiant>& a, int marca){
/* Pre: a es buit; el canal estandar d'entrada conté el recorregut en preordre
   d'un arbre binari A d'enters marcat amb "marca" */  
/* Post: a = A */
  Arbre<Estudiant> a1;
  Arbre<Estudiant> a2;
  Estudiant x;
  x.llegir();
  if (x.consultar_DNI() != marca) {
    llegir_arbre_est(a1, marca);
    llegir_arbre_est(a2, marca);
    a.plantar(x,a1,a2);
  }
}

void escriure_arbre_est(Arbre<Estudiant> &a) {
/* Pre: cert */ 
/* Post: El canal estandar de sortida conté el recorregut en inordre d'a */ 
  if (not a.es_buit()) {
    Arbre<Estudiant> a1;
    Arbre<Estudiant> a2;
    Estudiant x = a.arrel();
    a.fills(a1,a2);
    escriure_arbre_est(a1); 
    x.escriure();
    escriure_arbre_est(a2);
    a.plantar(x,a1,a2);
  }
}

