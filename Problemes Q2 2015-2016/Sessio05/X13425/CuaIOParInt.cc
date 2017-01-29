#include "CuaIOParInt.hh"

void LlegirCuaParInt(queue<ParInt>& q){
  ParInt par;
  while (par.llegir()!=0) q.push(par); 
}

void EscriureCuaParInt(queue<ParInt> q){
  while (not q.empty()) {
    q.front().escriure();
    q.pop();
  }
}
