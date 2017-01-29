#include <iostream>
#include <vector>
using namespace std;


// Problema 1
template <class T> class Llista {
private:
  struct node {
    T info;
    node* seg;
    node* ant;
  };
  int longitud;
  node* primer;
  node* ultim;
  node* act;
  
public:
  Llista() {
    primer = ultim = act = NULL;
    longitud = 0;
  }
  // inserta un element al final de la llista
  void inserta(const T &obj) {
    node* nou = new node;
    nou->info = obj;
    nou->seg = NULL;
    nou->ant = NULL;
    if (longitud == 0) {
      primer = ultim = act = nou;
    } else {
      nou->ant = ultim;
      ultim->seg = nou;
      ultim = nou;
    }
    ++longitud;
  }
  // escriu
  void escriu() const {
    cout << "Llista: ";
    node* n = primer;
    for (int i = 0; i < longitud; ++i) {
      cout << ' ' << n->info;
      n = n->seg;
    }
    cout << "; longitud=" << longitud;
    if (primer != NULL) cout << "; primer=" << primer->info << "; ultim=" << ultim->info;
    if (act != NULL) cout << "; act=" << act->info;
    cout << endl;
  }
  
  // Pre:  v es buit, el p.i. es un llista L
  // Post: el p.i. es buit, la mida de v es el nombre de trams de L
  //       cada posicio v[i] conte una llista amb l'i-essim tram de L
  //       i el punt d'interes sobre el seu primer element
  void trams(vector<Llista<T>> &v) {
    node* n = primer;
    node* n_ant = NULL;
    for (int i = 0; i < longitud; ++i) {
      if (i == 0 or n->info < n_ant->info) {
        // actualitzar punters (tallar la llista)
        if (i != 0) {
          n_ant->seg = NULL;
          n->ant = NULL;
        }
        // insertar nova llista
        Llista<T> l;
        l.primer = l.ultim = l.act = n;
        l.longitud = 1;
        v.push_back(l); 
      } else {
        // actualitzar ultim i long
        v.back().ultim = n;
        ++v.back().longitud;
      }
      n_ant = n;
      n = n->seg;
    }
    // buidar el p.i.
    primer = ultim = act = NULL;
    longitud = 0;
  }
};


// Problema 2
template <class T> class ArbreGen {
private:
  struct node {
    T info;
    vector<node*> seg;
  };
  node* primer_node;

public:
  ArbreGen() {
    primer_node = NULL;
  }
  void plantar(const T &info, vector<ArbreGen<T>> &seg) {
    primer_node = new node;
    primer_node->info = info;
    for (auto &x : seg) {
      primer_node->seg.push_back(x.primer_node);
      x.primer_node = NULL;
    }
  }
  void escriu_i(node *n) const {
    cout << ' ' << n->info;
    for (auto &x : n->seg) {
      if (x == NULL) cout << " -";
      else escriu_i(x);
    }
  }
  void escriu() const {
    cout << "Arbre: ";
    if (primer_node == NULL) cout << " -";
    else escriu_i(primer_node);
    cout << endl;
  }
  
  // Pre:  a != NULL
  // Post: amax apunta a l'arbre de maxims corresponent a 'a'
  //       amin apunta a l'arbre de minims corresponent a 'a'
  void arbre_max_min_i(node* a, node* &amax, node* &amin) const {
    amax = new node;
    amin = new node;
    amax->info = a->info;
    amin->info = a->info;
    amax->seg = vector<node*>(a->seg.size());
    amin->seg = vector<node*>(a->seg.size());
    for (int i = 0; i < (int)a->seg.size(); ++i) {
      arbre_max_min_i(a->seg[i], amax->seg[i], amin->seg[i]);
      if (amax->seg[i]->info > amax->info) amax->info = amax->seg[i]->info;
      if (amin->seg[i]->info < amin->info) amin->info = amin->seg[i]->info;
    }
  }
  // Pre:  el p.i. no es buit, amax i amin son buits
  // Post: amax es l'arbre de maxims del p.i., amin es l'arbre de minims del p.i.
  void arbre_max_min(ArbreGen<T> &amax, ArbreGen<T> &amin) const {
    arbre_max_min_i(primer_node, amax.primer_node, amin.primer_node);
  }  
};


int main() {
  /*
  // inicialitza
  Llista<int> l;
  l.inserta(3);
  l.inserta(7);
  l.inserta(10);
  l.inserta(10);
  l.inserta(4);
  l.inserta(6);
  l.inserta(6);
  l.inserta(12);
  l.inserta(6);
  l.inserta(-2);
  l.inserta(5);
  l.escriu();
  // prova
  vector<Llista<int>> v;
  l.trams(v);
  for (auto &x : v) {
    x.escriu();
  }
  l.escriu();
  */
  /*
  // inicialitza
  vector<ArbreGen<int>> v_buit;
  ArbreGen<int> b1, b2, b3, c1, d1, d2;
  b1.plantar(-1, v_buit);
  b2.plantar(3, v_buit);
  b3.plantar(11, v_buit);
  c1.plantar(-8, v_buit);
  d1.plantar(99, v_buit);
  d2.plantar(-3, v_buit);
  vector<ArbreGen<int>> b = { b1, b2, b3 };
  vector<ArbreGen<int>> c = { c1 };
  vector<ArbreGen<int>> d = { d1, d2 };
  ArbreGen<int> a1, a2, a3, a4;
  a1.plantar(-4, b);
  a2.plantar(-9, c);
  a3.plantar(2, d);
  a4.plantar(4, v_buit);
  vector<ArbreGen<int>> a_seg = { a1, a2, a3, a4 };
  ArbreGen<int> a;
  a.plantar(1, a_seg);
  a.escriu();
  // prova
  ArbreGen<int> amax;
  ArbreGen<int> amin;
  a.arbre_max_min(amax, amin);
  a.escriu();
  amax.escriu();
  amin.escriu();
  */
  return 0;
}
