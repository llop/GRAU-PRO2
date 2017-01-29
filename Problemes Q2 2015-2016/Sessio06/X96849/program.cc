#include <iostream>
#include "ArbIOparint.hh"
using namespace std;

void cercaArbre(Arbre<Pari> &a, int p, int x, bool &b, int &prof, Pari &par) {
  b=false;
  if (not a.es_buit()) {
    Pari arrel=a.arrel();
    if (arrel.first==x) {
      b=true;
      prof=p;
      par=arrel;
    } else {
      Arbre<Pari> fe, fd;
      a.fills(fe, fd);
      bool bfe;
      int proffe;
      Pari parfe;
      cercaArbre(fe, p+1, x, bfe, proffe, parfe);
      if (bfe) {
        b=bfe;
        prof=proffe;
        par=parfe;
      } else {
        bool bfd;
        int proffd;
        Pari parfd;
        cercaArbre(fd, p+1, x, bfd, proffd, parfd);
        if (bfd) {
          b=bfd;
          prof=proffd;
          par=parfd;
        }
      }
      a.plantar(arrel, fe, fd);
    }
  }
}

int main() {
  Arbre<Pari> a;
  llegir_arbre_parint(a, 0);
  int x;
  while (cin>>x) {
    bool b;
    int prof;
    Pari par;
    cercaArbre(a, 0, x, b, prof, par);
    if (b) cout<<par.first<<' '<<par.second<<' '<<prof<<endl;
    else cout<<-1<<endl;
  }
  return 0;
}