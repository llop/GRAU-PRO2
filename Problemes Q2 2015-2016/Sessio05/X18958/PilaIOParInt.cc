#include "PilaIOParInt.hh"

void llegirPilaParInt(stack<ParInt> &p) {
  ParInt q;
  q.llegir();
  while (q.primer()!=0 and q.segon()!=0){
    p.push(q);
    q.llegir();
  }
}
 
void escriurePilaParInt(stack<ParInt> p) {
  while (not p.empty()){
    p.top().escriure();
    p.pop();
  }
}

