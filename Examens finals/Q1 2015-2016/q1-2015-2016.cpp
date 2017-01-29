#include <iostream>
#include <vector>
#include <list>
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
  
  void transferir(Llista<T> &dest) {
    // desar referencia del node que transferirem
    node* n = prim;

    // desenganxar n del p.i.
    if (act == prim) act = prim->seg;
    prim = prim->seg;
    if (prim != NULL) prim->ant = NULL;
    else ult = NULL;
    --longitud;

    // enganxar n a dest
    n->ant = dest.ult;
    n->seg = NULL;

    // arreglar dest
    if (dest.prim == NULL) dest.prim = n;
    else dest.ult->seg = n;
    dest.ult = n;
    ++dest.longitud;
  }

  void concat_per_nivells(vector<Llista<T>> &v) {
    bool alguna_no_buida = true;
    while (alguna_no_buida) {
      alguna_no_buida = false;
      for (int i=0; i<v.size(); ++i) {
        if (v[i].prim != NULL) v[i].transferir(*this);
        if (v[i].prim != NULL) alguna_no_buida = true;
      }
    }
  }

  void concat_per_nivells2(vector<Llista<T>> &v) {
    list<int> l;
    for (int i=0; i<v.size(); ++i) if (v[i].prim != NULL) l.push_back(i);

    while (not l.empty()) {
      list<int>::iterator it = l.begin();
      while (it != l.end()) {
        v[*it].transferir(*this);
        if (v[*it].prim != NULL) ++it;
        else it = l.erase(it);
      }
    }
  }
};


// Problema 2
template <class T> class ArbreNari {
private:
  struct node {
    T info;
    vector<node*> seg;
  };
  int N;
  node* primer_node;

public:
  ArbreNari() {
    N = 0;
    primer_node = NULL;
  }
  void plantar(const T &info, vector<ArbreNari<T>> &seg) {
    N = seg.size();
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
  
  int iguals() const {
    if (primer_node == NULL) return 0;
    return rec_iguals(primer_node);
  }

  // Pre:  n != NULL
  // Post: retorna el numero de nodes del subarbre arrelat en n
  //       que tenen la mateixa info que el seu pare
  static int rec_iguals(node* n) {
    int ret = 0;
    for (int i=0; i<n->seg.size(); ++i) {
      if (n->seg[i] != NULL) {
        ret += rec_iguals(n->seg[i]);
        if (n->seg[i]->info == n->info) ++ret;
      }
    }
    return ret;
  }

};


int main() {
  
  // inicialitza
  /*
  vector<Llista<char>> v(5);
  v[0].inserta('a', false);
  v[0].inserta('b', false);
  v[0].inserta('c', false);
  
  v[1].inserta('d', false);
  v[1].inserta('e', false);
  v[1].inserta('f', false);
  v[1].inserta('g', false);

  v[2].inserta('h', false);

  v[4].inserta('x', false);
  v[4].inserta('y', false);
  v[4].inserta('z', false);
  
  Llista<char> l;
  l.concat_per_nivells2(v);
  l.escriu();
  */

  
  // inicialitza
  vector<ArbreNari<int>> v_buit = { ArbreNari<int>(), ArbreNari<int>(), ArbreNari<int>() };
  ArbreNari<int> buit, _25, _1, _77, _24, _9, _83, _8, _11, _31, _52, _7, _4, _13, _33, _98, _21, a;
  _25.plantar(7, v_buit);
  _1.plantar(1, v_buit);
  _77.plantar(77, v_buit);
  _24.plantar(24, v_buit);
  _9.plantar(9, v_buit);
  _83.plantar(83, v_buit);
  _8.plantar(8, v_buit);
  _11.plantar(11, v_buit);
  _31.plantar(31, v_buit);
  _52.plantar(52, v_buit);
  vector<ArbreNari<int>> v_7 = { _25, _1, _77 };
  _7.plantar(7, v_7);
  vector<ArbreNari<int>> v_4 = { _24, buit, _9 };
  _4.plantar(4, v_4);
  vector<ArbreNari<int>> v_13 = { buit, _83, buit };
  _13.plantar(13, v_13);
  vector<ArbreNari<int>> v_33 = { _8, _11, _31 };
  _33.plantar(33, v_33);
  vector<ArbreNari<int>> v_98 = { _33, _52, buit };
  _98.plantar(98, v_98);
  vector<ArbreNari<int>> v_21 = { _7, buit, _4 };
  _21.plantar(7, v_21);
  vector<ArbreNari<int>> v_17 = { _21, _13, _98 };
  a.plantar(17, v_17);
  //a.escriu();
  // prova
  cout << "Iguals: " << a.iguals() << endl;
  
  return 0;
}





  