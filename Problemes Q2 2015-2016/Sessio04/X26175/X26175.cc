#include "Cjt_estudiants.hh"

void Cjt_estudiants::afegir_estudiant(const Estudiant &est, bool& b) {
  int i=cerca_dicot(vest,0,nest-1,est.consultar_DNI());
  b=(i!=nest and vest[i].consultar_DNI()==est.consultar_DNI());
  if (not b) {
    for (int j=nest-1; j>=i; --j) vest[j+1]=vest[j];
    vest[i]=est;
    ++nest;
    if (est.te_nota()) incrementar_interval(est.consultar_nota());
  }
}

void Cjt_estudiants::esborrar_estudiant(int dni, bool& b) {
  int i=cerca_dicot(vest,0,nest-1,dni);
  b=(i!=nest and vest[i].consultar_DNI()==dni);
  if (b) {
    if (vest[i].te_nota()) decrementar_interval(vest[i].consultar_nota());
    for (int j=i; j<nest-1; ++j) vest[j]=vest[j+1];
    --nest;
  }
}