#include <iostream>
#include "CuaIOEstudiant.hh"

void cercarCuaEstudiant(queue<Estudiant> q, int dni, bool &b, Estudiant &e) {
  b=false;
  while (not b and not q.empty()) {
    if (q.front().consultar_DNI()==dni) {
      b=true;
      e=q.front();
    } else {
      q.pop();
    }
  }
}

int main() {
  queue<Estudiant> q;
  LlegirCuaEstudiant(q);
  EscriureCuaEstudiant(q);
  int dni;
  cin>>dni;
  bool b;
  Estudiant e;
  cercarCuaEstudiant(q, dni, b, e);
  if (b) {
    if (e.te_nota()) cout<<"La nota es "<<e.consultar_nota()<<endl;
    else cout<<"No te nota"<<endl;
  } else {
    cout<<"No trobat"<<endl;
  }
  return 0;
}