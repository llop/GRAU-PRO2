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
  
  // pre:  el p.i. conté una cua C, sub és buida
  // post: sub es una cua amb els elements de la subcua més llarga entre dues 
  //       aparicions d'elem a C; el p.i. és com C però sense aquesta subcua
  void subcua_mes_llarga(const T &elem, Cua &sub) {
    
    // n apuntara a la primera aparicio d'elem
    node* nelem = prim;
    while (nelem != NULL and nelem->info != elem) nelem = nelem->seg;
    if (nelem != NULL) {
      // para la cua sub
      node* prim_sub = NULL;
      node* ult_sub = NULL;
      int len_sub = 0;
      // para cada iteracion
      node* prim_tmp = nelem;
      node* ult_tmp = NULL;
      int len_tmp = 0;
      nelem = nelem->seg;
      // Invariant:
      // entre prim_sub i ult_sub hi ha la subcua mes llarga entre dues aparicions d'elem que son abans de nelem
      // len_sub es la longitud de la subcua
      // prim_tmp apunta a la darrera aparicio d'elem
      // nelem apunta a l'element seguent a prim_tmp
      while (nelem != NULL) {
        // troba la seguent aparicio de elem
        while (nelem != NULL and nelem->info != elem) {
          ++len_tmp;
          ult_tmp = nelem;
          nelem = nelem->seg;
        }
        if (nelem != NULL) {
          if (len_tmp > len_sub) {    // si trobem una subcua més llarga que la que tenim ara
            prim_sub = prim_tmp;      // establim els nodes per sub
            ult_sub = ult_tmp;
            len_sub = len_tmp;
          }
          len_tmp = 0;
          prim_tmp = nelem;           // complir l'invariant
          nelem = nelem->seg;
        }
      }
      
      if (prim_sub != NULL) {
        sub.prim = prim_sub->seg;     // establir els punters de la cua sub
        sub.ult = ult_sub;
        sub.longitud = len_sub;
        prim_sub->seg = ult_sub->seg;   // treure els elements del p.i.
        sub.ult->seg = NULL;            // tallar l'ultim de la nova cua
        longitud -= len_sub;
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
  
  // pre:  cert
  // post: el resultat indica si la jerarquia apuntada per p representa 
  //       un arbre complet. Si és cert, h conté l'altura d'aquesta jerarquia
  bool i_es_complet(node* p, int &h) const {
    bool ok = true;
    if (p == NULL) {                          // cas base: un arbre buit te altura 0, i es considera complet
      h = 0;
    } else {                                  // cas recursiu:
      ok = i_es_complet(p->seg[0], h);        // trobar la altura del primer subarbre, i si és complet
      for (int i = 1; ok and i < N; ++i) {
        int htmp;
        ok = i_es_complet(p->seg[i], htmp);   // comprovar que la resta de subarbres son complets també
        if (h != htmp) ok = false;            // i que tots tenen la mateixa altura
      }
      h = h + 1;                              // la altura de p és 1 més que la del seus fills
    }
    return ok;
  }
  
  int altura(node* n) const {
    if (n == NULL) return 0;
    int h = 0;
    for (int i = 0; i < N; ++i) h = max(h, altura(n->seg[i]));
    return h + 1;
  }
  
  // pre:  h >= altura(p), n és l'aritat de l'ArbreNari<T> al que pertany la jerarquia apuntada per p
  // post: la jerarquia apuntada per p ha estat completada a un arbre complet d'altura h,
  //       afegint els nodes necesaris amb v al camp info
  void i_completa(node* &p, int n, int h, const T &v) {
    if (h != 0) {           // si h es 0, p ha de ser null i la post ja es compleix
      if (p == NULL) {                        // si p és NULL,
        p = new node;
        p->info = v;                          // el plenem amb el valor p,
        p->seg = vector<node*>(n, NULL);      // i n nodes buits
      }
      for (int i = 0; i < n; ++i)             // completem els subarbres
        i_completa(p->seg[i], n, h - 1, v);
    }
  }

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
  
  // pre:  cert
  // post: retorna si el p.i. es un arbre n-ari complet
  bool es_complet() const {
    int h;
    return i_es_complet(primer_node, h);
  }
  
  // pre:  el p.i. es un arbre N-ari A
  // post: el p.i. es l'arbre complet que completa A amb el mínim nombre de nodes;
  //       esl nodes que són al p.i. però no eren a A contenen el valor v
  void completa(const T &v) {
    int h = altura(primer_node);
    i_completa(primer_node, N, h, v);
  }
};


int main() {
  /*
  // inicializa
  Cua<int> c1;
  c1.push(2);
  c1.push(1);
  c1.push(2);
  c1.push(3);
  c1.push(4);
  c1.push(1);
  c1.push(2);
  c1.push(3);
  c1.push(4);
  c1.push(5);
  c1.push(1);
  c1.push(2);
  c1.push(1);
  c1.push(2);
  c1.push(3);
  c1.push(4);
  c1.escriu();
  Cua<int> c2;
  c1.subcua_mes_llarga(1, c2);
  c1.escriu();
  c2.escriu();
  Cua<int> c3;
  c3.push(2);
  c3.push(3);
  c3.push(4);
  c3.push(1);
  c3.push(5);
  c3.push(6);
  c3.escriu();
  Cua<int> c4;
  c3.subcua_mes_llarga(1, c4);
  c3.escriu();
  c4.escriu();
  Cua<int> c5;
  c5.push(1);
  c5.push(1);
  c5.push(1);
  c5.escriu();
  Cua<int> c6;
  c5.subcua_mes_llarga(1, c6);
  c5.escriu();
  c6.escriu();
  */
  /*
  // inicialitza
  vector<ArbreNari<int>> v_buit = { ArbreNari<int>(), ArbreNari<int>(), ArbreNari<int>() };
  ArbreNari<int> a1, a2, a3;
  a1.plantar(25, v_buit);
  vector<ArbreNari<int>> bseg = { a1, a2, a3 };
  ArbreNari<int> b1;
  b1.plantar(30, bseg);
  // prova
  a1.escriu();
  cout << "a1 " << (a1.es_complet() ? "complet" : "no complet") << endl;
  b1.escriu();
  cout << "b1 " << (b1.es_complet() ? "complet" : "no complet") << endl;
  b1.completa(10);
  b1.escriu();
  cout << "b1 " << (b1.es_complet() ? "complet" : "no complet") << endl;
  ArbreNari<int> c0, c8, c4, c7, c3;
  c0.plantar(0, v_buit);
  c8.plantar(-8, v_buit);
  vector<ArbreNari<int>> c4seg = { c0, ArbreNari<int>(), c8 };
  c4.plantar(-4, c4seg);
  c7.plantar(7, v_buit);
  vector<ArbreNari<int>> c3seg = { c4, ArbreNari<int>(), c7 };
  c3.plantar(3, c3seg);
  c3.escriu();
  cout << "c3 " << (c3.es_complet() ? "complet" : "no complet") << endl;
  c3.completa(0);
  c3.escriu();
  cout << "c3 " << (c3.es_complet() ? "complet" : "no complet") << endl;
  */
  
  return 0;
}




