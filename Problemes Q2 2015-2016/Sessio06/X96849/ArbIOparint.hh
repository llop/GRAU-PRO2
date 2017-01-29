#ifndef ARBIOPARINT_HPP
#define ARBIOPARINT_HPP

#include <utility>
#include "Arbre.hh"

using namespace std;

// Lectura d'un arbre binari de pares d'enters, acci�.  Els elements 
// s'introdueixen en preordre: primer l'arrel, despr�s el subarbre
// esquerre i per �ltim el dret. Els arbres buits es
// representen amb la marca.

/* Exemple: l'arbre 

       1
     /   \
    2     3
     \
      4

   es llegeix 1 2 0 4 0 0 3 0 0 (o amb els numeros en l�nies diferents) 
*/

typedef pair<int,int> Pari;

void llegir_arbre_parint(Arbre<Pari>& a, int marca);
/* Pre: a es buit; el canal estandar d'entrada cont� el recorregut en preordre
   d'un arbre binari A d'enters marcat amb "marca" */  
/* Post: a = A */


// Escriptura d'un arbre binari d'enteros, acci�.  Els elements 
// s'escriuen en inordre: primer el subarbre 
// esquerre, despr�s l'arrel i per �ltim el dret.   

/* Exemple: l'arbre 

     1
   /   \
  2     3
   \
    4

   s'escriu 2 4 1 3 
*/

void escriure_arbre_parint(Arbre<Pari> &a); 
/* Pre: cert */ 
/* Post: El canal estandar de sortida cont� el recorregut en inordre d'a */ 

#endif
