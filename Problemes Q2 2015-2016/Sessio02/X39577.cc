#include <iostream>
#include <vector>
#include "Estudiant.hh"
using namespace std;

void tracta_estudiant(vector<Estudiant> &est, int n, const vector<int> &ass) {
  int dni;
  cin>>dni;
  vector<double> notas(n);
  for (int i=0; i<n; ++i) cin>>notas[i];
  double mitja=0.0;
  for (int i=0; i<ass.size(); ++i) mitja+=notas[ass[i]];
  mitja/=ass.size();
  Estudiant e(dni);
  e.afegir_nota(mitja);
  est.push_back(e);
}

int main() {
  int m, n, s;
  cin>>m>>n>>s;
  vector<Estudiant> est;
  vector<int> ass(s);
  for (int i=0; i<s; ++i) {
    cin>>ass[i];
    --ass[i];
  }
  for (int i=0; i<m; ++i) tracta_estudiant(est, n, ass);
  for (int i=0; i<m; ++i) est[i].escriure();
  return 0;
}