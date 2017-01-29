#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// Problema 1
template <class T> class Cua {
private:
  struct node {
    T info;
    node* seg;
  };
  int longitud;
  node* prim;
  node* ult;
  
public:
  Cua() {
    longitud = 0;
    prim = ult = NULL;
  }
  void push(const T &x) {
    node* nou = new node;
    nou->info = x;
    if (prim == NULL) prim = nou;
    else ult->seg = nou;
    ult = nou;
    ++longitud;
  }
  void escriu() const {
    node* n = prim;
    cout << "Cua: ";
    while (n != NULL) {
      cout << ' ' << n->info;
      n = n->seg;
    }
    cout << "; longitud=" << longitud;
    if (prim != NULL) cout << "; prim=" << prim->info << "; ult=" << ult->info;
    cout << endl;
  }
  
  // Pre:  el p.i. es buit; c=C
  // Post: s'han eliminat de c i afegit al parametre implicit tots els elements de c
  //       mes grans que k, en el mateix ordre relatiu en que apareixien a C;
  //       c conte la resta d'elements de C en l'ordre relatiu original
  void mou_grans_cua(Cua &c, const T &k) {
    node* n = c.prim;
    node* nant = NULL;
    while (n != NULL) {
      node* nseg = n->seg;
      if (n->info > k) {
        // eliminar de c
        if (n == c.prim) c.prim = nseg;
        else nant->seg = nseg;
        if (nseg == NULL) c.ult = nant;
        else n->seg = NULL;
        --c.longitud;
        // afegir al p.i.
        if (longitud == 0) prim = ult = n;
        else {
          ult->seg = n;
          ult = n;
        }
        ++longitud;
      } else nant = n;
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
  void fills(vector<ArbreGen<T>> &v) {
    if (primer_node != NULL) {
      for (auto &nseg : primer_node->seg) {
        ArbreGen a;
        a.primer_node = nseg;
        v.push_back(a);
      }
      delete primer_node;
      primer_node = NULL;
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
  bool es_buit() const {
    return primer_node == NULL;
  }
  int nombre_fills() const {
    return primer_node->seg.size();
  }
  T arrel() const {
    return primer_node->info;
  }
};

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
    if (primer_node != NULL) escriu_i(primer_node);
    cout << endl;
  }
  
  // Pre:  g no es buit, g=G
  // Post: retorna un punter a un node d'arbre N-ari que aproxima l'arbre general g
  node* i_arbre_gen(ArbreGen<T> &g) {
    node* n = new node;
    n->info = g.arrel();
    n->seg = vector<node*>(N, NULL);
    int m = min(N, g.nombre_fills());
    vector<ArbreGen<T>> seg;
    g.fills(seg);
    for (int i = 0; i < m; ++i) n->seg[i] = i_arbre_gen(seg[i]);
    //g.plantar(n->info, seg);  // No cal perque g=G!
    return n;
  }
  // Pre:  n >= 2; g=G
  // Post: el resultat es un arbre N-ari que aproxima l'arbre general G
  ArbreNari(int n, ArbreGen<T> &g) {
    N = n;
    if (g.es_buit()) primer_node = NULL;
    else primer_node = i_arbre_gen(g);
  }  
};


int main() {
  /*
  // inicialitza
  Cua<int> cua;
  Cua<int> c;
  c.push(1);
  c.push(14);
  c.push(2);
  c.push(15);
  c.push(3);
  cua.escriu();
  c.escriu();
  // prova
  cua.mou_grans_cua(c, 10);
  cua.escriu();
  c.escriu();
  */
  /*
  // inicialitza
  vector<ArbreGen<int>> v_b;
  ArbreGen<int> a_10, a_1, a_2, a_6, a_5, a_8, a_12, a_13, a_22, a_4, a_9, a;
  a_10.plantar(10, v_b);
  a_1.plantar(1, v_b);
  a_2.plantar(2, v_b);
  a_6.plantar(6, v_b);
  a_5.plantar(5, v_b);
  a_8.plantar(8, v_b);
  a_12.plantar(12, v_b);
  a_13.plantar(13, v_b);
  vector<ArbreGen<int>> v_22 = { a_10, a_1, a_2, a_6 };
  a_22.plantar(2, v_22);
  vector<ArbreGen<int>> v_4 = { a_8 };
  a_4.plantar(4, v_4);
  vector<ArbreGen<int>> v_9 = { a_12, a_13 };
  a_9.plantar(9, v_9);
  vector<ArbreGen<int>> v_a = { a_22, a_5, a_4, a_9 };
  a.plantar(7, v_a);
  a.escriu();
  // prova
  ArbreNari<int> b(3, a);
  b.escriu();
  a.escriu();
  */
  return 0;
}













