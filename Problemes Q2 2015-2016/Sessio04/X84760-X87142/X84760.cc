#include "Cjt_estudiants.hh"

void Cjt_estudiants::afegir_estudiant(const Estudiant &est, bool& b) {
  int i=cerca_dicot(vest,0,nest-1,est.consultar_DNI());
  b=(i!=nest and vest[i].consultar_DNI()==est.consultar_DNI());
  if (not b) {
    for (int j=nest-1; j>=i; --j) vest[j+1]=vest[j];
    vest[i]=est;
    ++nest;
    recalcular_posicio_imax();
  }
}

void Cjt_estudiants::eliminar_estudiants_sense_nota() {
  int i=0;
  for (int j=0; j<nest; ++j) {
    if (vest[j].te_nota()) {
      vest[i]=vest[j];
      ++i;
    }
  }
  if (nest!=i) recalcular_posicio_imax();
  nest=i;
}