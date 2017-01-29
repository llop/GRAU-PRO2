#include <iostream>
#include <vector>
using namespace std;


// Problema 1
class Llista_doble_ordre {
private:
  struct node {
    string nom;
    int valor1;
    int valor2;
    node* seg1;
    node* seg2;
  };
  node* prim1;
  node* prim2;
  
public:
  Llista_doble_ordre() {
    prim1 = prim2 = NULL;
  }
  void escriu() const {
    cout << "Primera: ";
    node* n1 = prim1;
    while (n1 != NULL) {
      cout << " (" << n1->nom << ", " << n1->valor1 << ", " << n1->valor2 << ")";
      n1 = n1->seg1;
    }
    cout << endl;
    cout << "Segona: ";
    node* n2 = prim2;
    while (n2 != NULL) {
      cout << " (" << n2->nom << ", " << n2->valor1 << ", " << n2->valor2 << ")";
      n2 = n2->seg2;
    }
    cout << endl;
  }
  
  // Pre:  Cert
  // Post: b indica si existeix un element al p.i. amb nom igual a s;
  //       si b es cert, el p.i. no canvia; si b es fals, s'ha afegit al p.i. 
  //       un nou element amb nom igual a s, valor1 igual a v1, i valor2 igual a v2
  void afegir(const string &s, int v1, int v2, bool &b) {
    b = false;               // b = nom repetit?
    node* n1 = prim1;        // nodes anterior i seguent per le 2 cadenes
    node* n2 = prim2;
    node* nant1 = NULL;
    node* nant2 = NULL;
    bool falta_seg1 = true;
    bool falta_seg2 = true;
    node* n = prim1;         // node per iterar tota la llista: mirarem la 1ª cadena (pero la 2ª tambe valdria)
    while (not b and n != NULL) {
      // mirar si repetim
      if (s == n->nom) b = true;
      else {
        // mirar si podem insertar ara en la 1ª cadena
        if (falta_seg1 and (n1->valor1<v1 or (n1->valor1==v1 and n1->nom<s))) {
          nant1 = n1;
          n1 = n1->seg1;
        } else falta_seg1 = false;
        // mirar si podem insertar ara en la 2ª cadena
        if (falta_seg2 and (n2->valor2<v2 or (n2->valor2==v2 and n2->nom<s))) {
          nant2 = n2;
          n2 = n2->seg2;
        } else falta_seg2 = false;
        // seguent!
        n = n->seg1;
      }
    }
    if (not b) {
      // reassignar punters, si cal
      node* nou = new node;
      nou->nom = s;
      nou->valor1 = v1;
      nou->valor2 = v2;
      if (n1 == prim1) prim1 = nou;
      else nant1->seg1 = nou;
      nou->seg1 = n1;      
      if (n2 == prim2) prim2 = nou;
      else nant2->seg2 = nou;
      nou->seg2 = n2;      
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
  
  // Pre:  el p.i. te tots els elements diferents, y != z
  // Post: b indica si y i z hi son al p.i.; si b, llavors x
  //       es l'antecessor comu mes proper d'y i z
  void antecessor_comu_mes_proper(const T &y, const T &z, T &x, bool &b) const {
    b = false;
    if (primer_node != NULL) {
      bool te_y, te_z;
      i_acmp(primer_node, te_y, te_z, y, z, x, b);
    }
  }
  // Pre:  n != NULL, y != z
  // Post: te_y indica si y es la info del node n, o algun dels seus fills
  //       te_z indica si z es la info del node n, o algun dels seus fills
  //       b indica si hem trobat l'antecessor comu mes proper d'y i z en el p.i.; 
  //       si b, llavors x es l'antecessor comu mes proper d'y i z
  void i_acmp(node* n, bool &te_y, bool &te_z, const T &y, const T &z, T &x, bool &b) const {
    te_y = n->info == y;
    te_z = n->info == z;
    for (int i = 0; not b and i < N; ++i) {
      node* seg = n->seg[i];
      if (seg != NULL) {
        bool te_y_seg, te_z_seg;
        i_acmp(seg, te_y_seg, te_z_seg, y, z, x, b);
        if (te_y_seg) te_y = true;      // actualitzar te_y i te_z del node 'n'
        if (te_z_seg) te_z = true;
        if (not b and te_y and te_z) {  // mirar si tenim solucio
          b = true;
          x = n->info;
        }
      }
    }    
  }
};


int main() {
  /*
  // inicialitza
  bool b;
  Llista_doble_ordre l;
  l.afegir("fusta", 3, 1, b);
  l.afegir("casa", 3, 6, b);
  l.afegir("fama", 8, 1, b);
  l.afegir("llibre", 5, 6, b);
  l.escriu();
  // prova
  l.afegir("hola", 4, 7, b);
  cout << (not b ? "BE" : "REPETIT") << endl;
  l.escriu();
  l.afegir("data", 5, 1, b);
  cout << (not b ? "BE" : "REPETIT") << endl;
  l.escriu();
  l.afegir("llibre", 3, 14, b);
  cout << (not b ? "BE" : "REPETIT") << endl;
  l.escriu();
  */
  /*
  // inicialitza
  vector<ArbreNari<int>> v_buit = { ArbreNari<int>(), ArbreNari<int>(), ArbreNari<int>() };
  ArbreNari<int> buit, _25, _1, _77, _24, _9, _83, _8, _11, _31, _52, _7, _4, _13, _33, _98, _21, a;
  _25.plantar(25, v_buit);
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
  _21.plantar(21, v_21);
  vector<ArbreNari<int>> v_17 = { _21, _13, _98 };
  a.plantar(17, v_17);
  a.escriu();
  // prova
  int x;
  bool b;
  a.antecessor_comu_mes_proper(25, 77, x, b);
  if (b) cout << "b=true, x=" << x << endl;
  else cout << "b=false" << endl;
  a.antecessor_comu_mes_proper(4, 11, x, b);
  if (b) cout << "b=true, x=" << x << endl;
  else cout << "b=false" << endl;
  a.antecessor_comu_mes_proper(98, 52, x, b);
  if (b) cout << "b=true, x=" << x << endl;
  else cout << "b=false" << endl;
  a.antecessor_comu_mes_proper(13, 3, x, b);
  if (b) cout << "b=true, x=" << x << endl;
  else cout << "b=false" << endl;
  a.antecessor_comu_mes_proper(25, 4, x, b);
  if (b) cout << "b=true, x=" << x << endl;
  else cout << "b=false" << endl;
  */
  return 0;
}











