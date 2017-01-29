#include <iostream>
#include "CuaIOEstudiant.hh"

void LlegirCuaEstudiant(queue<Estudiant> &q) {
  int n;
  cin>>n;
  for (int i=0; i<n; ++i) {
    Estudiant e;
    e.llegir();
    q.push(e);
  }
}

void EscriureCuaEstudiant(queue<Estudiant> q) {
  while (not q.empty()){
    q.front().escriure();
    q.pop();
  }
}
