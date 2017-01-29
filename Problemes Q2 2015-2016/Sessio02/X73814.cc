#include <iostream>
#include <vector>
#include "Estudiant.hh"
using namespace std;

int main() {
  int n;
  cin>>n;
  vector<Estudiant> entrada(n);
  for (int i=0; i<n; ++i) entrada[i].llegir();
  vector<Estudiant> sortida;
  for (int i=0; i<n; ++i) {
    if (i==0 or entrada[i].consultar_DNI()!=entrada[i-1].consultar_DNI()) {
      sortida.push_back(entrada[i]);
    } else {
      if (entrada[i].te_nota()) {
        if (sortida[sortida.size()-1].te_nota()) {
          if (entrada[i].consultar_nota()>sortida[sortida.size()-1].consultar_nota()) {
            sortida[sortida.size()-1].modificar_nota(entrada[i].consultar_nota());
          }
        } else {
          sortida[sortida.size()-1].afegir_nota(entrada[i].consultar_nota());
        }
      }
    }
  }
  for (int i=0; i<sortida.size(); ++i) sortida[i].escriure();
  return 0;
}