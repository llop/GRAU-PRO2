#include <iostream>
#include "ArbIOest.hh"
using namespace std;

void cercaArbre(Arbre<Estudiant> &a, int p, int dni, bool &b, int &prof, Estudiant &est) {
  b=false;
  if (not a.es_buit()) {
    Estudiant arrel=a.arrel();
    if (arrel.consultar_DNI()==dni) {
      b=true;
      prof=p;
      est=arrel;
    } else {
      Arbre<Estudiant> fe, fd;
      a.fills(fe, fd);
      bool bfe;
      int proffe;
      Estudiant estfe;
      cercaArbre(fe, p+1, dni, bfe, proffe, estfe);
      if (bfe) {
        b=bfe;
        prof=proffe;
        est=estfe;
      } else {
        bool bfd;
        int proffd;
        Estudiant estfd;
        cercaArbre(fd, p+1, dni, bfd, proffd, estfd);
        if (bfd) {
          b=bfd;
          prof=proffd;
          est=estfd;
        }
      }
      a.plantar(arrel, fe, fd);
    }
  }
}

int main() {
  Arbre<Estudiant> a;
  llegir_arbre_est(a, 0);
  int dni;
  while (cin>>dni) {
    bool b;
    int prof;
    Estudiant est;
    cercaArbre(a, 0, dni, b, prof, est);
    cout<<"L'estudiant "<<dni;
    if (b) {
      cout<<" té profunditat "<<prof;
      if (est.te_nota()) cout<<" i la seva nota és "<<est.consultar_nota()<<endl;
      else cout<<", però no té nota"<<endl;
    } else cout<<" no hi és"<<endl;
  }
  return 0;
}