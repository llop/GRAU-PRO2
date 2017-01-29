#include <iostream>
#include <list>
#include "Estudiant.hh"
using namespace std;

void llegirList(list<Estudiant> &li) {
  Estudiant e;
  e.llegir();
  while (e.consultar_DNI()!=0 and (not e.te_nota() or e.consultar_nota()!=0)) {
    li.insert(li.end(), e);
    e.llegir();
  }
}

void tractarList(list<Estudiant> &li, int dni, int &aparicions) {
  aparicions=0;
  for (list<Estudiant>::iterator it=li.begin(); it!=li.end(); ++it) {
    if (it->consultar_DNI()==dni) {
      ++aparicions;
    }
  }
}

int main() {
  list<Estudiant> li;
  llegirList(li);
  int dni;
  cin>>dni;
  int aparicions;
  tractarList(li, dni, aparicions);
  cout<<dni<<' '<<aparicions<<endl;
  return 0;
}