#include <iostream>
#include <list>
using namespace std;

void afegir(list<int> &li, int nombre) {
  li.insert(li.end(), nombre);
}

void eliminar(list<int> &li, int nombre) {
  for (list<int>::iterator it=li.begin(); it!=li.end(); ++it) {
    if (*it==nombre) {
      li.erase(it);
      return;
    }
  }
}

void tractarList(list<int> &li, int &minim, int &maxim, double &mitjana) {
  list<int>::iterator it=li.begin();
  minim=*it;
  maxim=*it;
  int suma=*it;
  ++it;
  while (it!=li.end()) {
    int nombre=*it;
    if (minim>nombre) minim=nombre;
    if (maxim<nombre) maxim=nombre;
    suma+=nombre;
    ++it;
  }
  mitjana=double(suma)/li.size();
}

int main() {
  list<int> li;
  int codi, nombre;
  cin>>codi>>nombre;
  while (codi!=0 and nombre!=0) {
    if (codi==-1) afegir(li, nombre);
    else if (codi==-2) eliminar(li, nombre);
    if (li.empty()) cout<<0<<endl;
    else {
      int minim, maxim;
      double mitjana;
      tractarList(li, minim, maxim, mitjana);
      cout<<minim<<' '<<maxim<<' '<<mitjana<<endl;
    }
    cin>>codi>>nombre;
  }
  return 0;
}