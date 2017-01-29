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
  node* prim;
  node* ult;
  node* act;
  
public:
  Llista() {
    longitud = 0;
    prim = ult = act = NULL;
  }
  void inserta(const T& x, bool es_act) {
    node* nou = new node;
    nou->info = x;
    nou->seg = nou->ant = NULL;
    if (prim == NULL) {
      prim = ult = act = nou;
    } else {
      nou->ant = ult;
      ult->seg = nou;
      ult = nou;
    }
    if (es_act) act = nou;
    ++longitud;
  }
  void escriu() const {
    cout << "Llista: ";
    node* n = prim;
    for (int i = 0; i < longitud; ++i) {
      cout << ' ' << n->info;
      n = n->seg;
    }
    cout << "; longitud=" << longitud;
    if (prim != NULL) cout << "; prim=" << prim->info << "; ult=" << ult->info;
    if (act != NULL) cout << "; act=" << act->info;
    else cout << "; act=null";
    cout << endl;
  }
  
  // Pre:  p.i. = P
  // Post: s'han eliminat del p.i. totes les aparicions d'x (la resta
  //       d'elements queda en el mateix ordere que a P); si el punt d'interes de P
  //       referenciava a una aparicio d'x, passa a referenciar al primer element 
  //       diferent d'x posterior a aquesta (si no hi ha cap element diferent d'x, passa
  //       a la dreta del tot); en cas contrari, el punt d'interes no canvia
  void esborrar_tots(const T &x) {
    node* n = prim;
    while (n != NULL) {
      node* nseg = n->seg;
      if (n->info == x) {
        if (n == act) act = nseg;
        if (n == prim) prim = nseg;
        else n->ant->seg = nseg;
        if (nseg != NULL) nseg->ant = n->ant;
        else ult = n->ant;
        delete n;
        --longitud;
      }
      n = nseg;
    }
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
    if (primer_node == NULL)  cout << " -";
    else escriu_i(primer_node);
    cout << endl;
  }
  
  // Pre:  el p.i. no es buit
  // Post: el resultat es la suma del cami de suma maxima del p.i.
  T max_suma_cami() const {
    return i_msc(primer_node);
  }
  // Pre:  n != NULL
  // Post: retorna la suma del cami de suma maxima del node n
  T i_msc(node* n) const {
    T mx = n->info;
    if (not n->seg.empty()) {
      for (int i = 0; i < (int)n->seg.size(); ++i) {
        T mx_tmp = i_msc(n->seg[i]);
        if (i == 0 or mx < n->info + mx_tmp) 
          mx = n->info + mx_tmp;
      }
    }
    return mx;
  }
};


int main() {
  
  // inicialitza
  Llista<int> l1;
  l1.inserta(1, false);
  l1.inserta(3, false);
  l1.inserta(5, false);
  l1.inserta(7, true);
  l1.inserta(12, false);
  l1.inserta(5, false);
  l1.inserta(5, false);
  l1.inserta(5, false);
  l1.inserta(25, false);
  l1.escriu();
  Llista<int> l2;
  l2.inserta(1, false);
  l2.inserta(3, false);
  l2.inserta(5, false);
  l2.inserta(7, false);
  l2.inserta(12, false);
  l2.inserta(5, false);
  l2.inserta(5, false);
  l2.inserta(5, true);
  l2.inserta(5, false);
  l2.escriu();
  // prova
  l1.esborrar_tots(5);
  l1.escriu();
  l2.esborrar_tots(5);
  l2.escriu();
  
  /*
  // inicialitza
  vector<ArbreGen<int>> v_buit;
  ArbreGen<int> a_10, a__1, a_3, a_6, a__5, a_8, a_12, a_13, a__2, a_2, a_4, a_9, a;
  a_10.plantar(10, v_buit);
  a__1.plantar(-1, v_buit);
  a_3.plantar(3, v_buit);
  a_6.plantar(6, v_buit);
  a__5.plantar(-5, v_buit);
  a_8.plantar(8, v_buit);
  a_12.plantar(1, v_buit);
  a_13.plantar(-2, v_buit);
  //a_12.plantar(12, v_buit);
  //a_13.plantar(13, v_buit);
  vector<ArbreGen<int>> v__2 = { a_3 };
  a__2.plantar(-2, v__2);
  vector<ArbreGen<int>> v_2 = { a_10, a__1, a__2, a_6 };
  a_2.plantar(2, v_2);
  vector<ArbreGen<int>> v_4 = { a_8 };
  a_4.plantar(4, v_4);
  vector<ArbreGen<int>> v_9 = { a_12, a_13 };
  a_9.plantar(9, v_9);
  vector<ArbreGen<int>> v = { a_2, a__5, a_4, a_9 };
  a.plantar(7, v);
  a.escriu();
  // prova
  cout << a.max_suma_cami() << endl;
  */
  return 0;
}





  