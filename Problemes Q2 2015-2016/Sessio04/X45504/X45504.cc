#include "ListaPalabras.hh"

void ListaPalabras::anadir_palabra(const Palabra &p) {
  bool b;
  int i;
  buscar_palabra_posicion(p, b, i);
  if (b) ++paraules[i].freq;
  else {
    paraules[i].par=p;
    paraules[i].freq=1;
    ++nparaules;
    ++npar_long[p.long_pal()-1];
  }
  ++suma_frec_long[paraules[i].par.long_pal()-1];
}

void ListaPalabras::borrar_palabra(const Palabra &p) {
  bool b;
  int i;
  buscar_palabra_posicion(p, b, i);
  if (b) {
    --suma_frec_long[p.long_pal()-1];
    --paraules[i].freq;
    if (paraules[i].freq==0) {
      --npar_long[p.long_pal()-1];
      --nparaules;
      while (i<nparaules) {
        paraules[i]=paraules[i+1];
        ++i;
      }
    }
  }
}

void ListaPalabras::buscar_palabra_posicion(const Palabra &p, bool &b, int &i) const {
  b=false;
  i=0;
  while (i<nparaules and not b) {
    if (paraules[i].par.iguales(p)) b=true;
    else ++i;
  }
}