#include <iostream>
#include <vector>
#include <queue>
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
  
  // Pre:  el p.i. es una llista P, l=L, L i P ordenades creixentment
  // Post: el p.i. esta format pels elements de P i L, i esta ordenat creixentment;
  //       el punt d'interes queda al principi de tot; l es una llista buida
  void merge(Llista &l) {
    node* n = NULL;
    node* n1 = prim;
    node* n2 = l.prim;
    // tractar de 2 en 2
    while (n1 != NULL and n2 != NULL) {
      // trobar el seguent
      node* nseg = NULL;
      if (n1->info < n2->info) {
        nseg = n1;
        n1 = n1->seg;
      } else {
        nseg = n2;
        n2 = n2->seg;
      }
      // afegir el seguent
      if (n == NULL) prim = act = nseg;
      else {
        n->seg = nseg;
        nseg->ant = n;
      }
      n = nseg;
    }
    // afegir el que queda del p.i.
    if (n1 != NULL) {
      if (n == NULL) prim = act = n1;
      else {
        n->seg = n1;
        n1->ant = n;
      }
    }
    // afegir el que queda de l
    if (n2 != NULL) {
      if (n == NULL) prim = act = n2;
      else {
        n->seg = n2;
        n2->ant = n;
      }
      ult = l.ult;
    }
    longitud += l.longitud;         // corregir longitud
    l.prim = l.ult = l.act = NULL;  // buidar l (Post)
    l.longitud = 0;
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
    if (primer_node == NULL) cout << " -";
    else escriu_i(primer_node);
    cout << endl;
  }
    
  // Pre:  n != NULL; p es la profunditat del node que apunta n
  // Post: el resultat indica si x hi es a l'arbre apuntat per n: -1 si no hi es;
  //       p si x es el valor de n; p + la profunditat minima en la resta de casos
  int i_cpm(node* n, int p, const T &x) const {
    int ret = -1;
    if (n->info == x) ret = p;
    else {
      for (int i = 0; i < N; ++i) {
        if (n->seg[i] != NULL) {
          int retf = i_cpm(n->seg[i], p + 1, x);
          if (retf != -1 and (ret == -1 or retf < ret))
            ret = retf;
        }
      }
    }
    return ret;
  }
  // Pre:  cert
  // Post: el resultat indica si x hi es al p.i.: -1 si no hi es;
  //       0 si es l'arrel; la profunditat minima en la resta de casos
  int cerca_prof_min_dfs(const T &x) const {
    int ret = -1;
    if (primer_node != NULL) ret = i_cpm(primer_node, 0, x); 
    return ret;
  }
  
  // Pre:  p es la profunditat del node que apunta n, si n != NULL
  // Post: trobat indica si x hi es a l'arbre apuntat per n;
  //       si trobat, psol indica la profunditat mínima a la que s'ha trobat x
  void i_cpm2(node* n, int p, const T &x, bool &trobat, int &psol) const {
    if (n != NULL and (not trobat or psol > p)) {
      if (n->info == x) {
        trobat = true;
        psol = p;
      } else {
        for (int i = 0; i < N; ++i)
          i_cpm2(n->seg[i], p + 1, x, trobat, psol);
      }
    }
  }
  // Pre:  cert
  // Post: el resultat indica si x hi es al p.i.: -1 si no hi es;
  //       0 si es l'arrel; la profunditat minima en la resta de casos
  int cerca_prof_min_dfs2(const T &x) const {
    bool trobat = false;
    int psol;
    i_cpm2(primer_node, 0, x, trobat, psol);
    if (trobat) return psol;
    else return -1;
  }
  
  // Pre:  cert
  // Post: el resultat indica si x hi es al p.i.: -1 si no hi es;
  //       0 si es l'arrel; la profunditat minima en la resta de casos
  int cerca_prof_min(const T &x) const {
    int res = -1;
    if (primer_node != NULL) {
      if (primer_node->info == x) res = 0;
      else {
        queue<pair<int, node*>> cua;
        cua.push(make_pair(0, primer_node));
        while (res == -1 and not cua.empty()) {
          int p = cua.front().first;
          node* n = cua.front().second;
          cua.pop();
          for (int i = 0; i < N; ++i) {
            node* nseg = n->seg[i];
            if (nseg != NULL) {
              if (nseg->info == x) res = p + 1;
              else cua.push(make_pair(p + 1, nseg));
            }
          }
        }
      }
    }
    return res;
  }
};


int main() {
  /*
  // inicialitza
  Llista<int> p;
  p.inserta(1, false);
  p.inserta(5, false);
  p.inserta(6, false);
  p.inserta(9, false);
  p.inserta(13, false);
  p.escriu();
  Llista<int> l;
  l.inserta(9, false);
  l.inserta(13, false);
  l.inserta(15, false);
  l.inserta(20, false);
  l.inserta(20, false);
  l.escriu();
  // prova
  p.merge(l);
  p.escriu();
  l.escriu();
  */
  /*
  // inicialitza
  vector<ArbreNari<int>> v_buit = { ArbreNari<int>(), ArbreNari<int>(), ArbreNari<int>() };
  ArbreNari<int> buit, _25, _1, _77, _24, _9, _83, _8, _11, _31, _52, _7, _4, _13, _33, _98, _21, a;
  _25.plantar(25, v_buit);
  _1.plantar(1, v_buit);
  _77.plantar(77, v_buit);
  _24.plantar(25, v_buit);
  _9.plantar(9, v_buit);
  _83.plantar(83, v_buit);
  _8.plantar(7, v_buit);
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
  cout << a.cerca_prof_min(5) << endl;
  cout << a.cerca_prof_min(17) << endl;
  cout << a.cerca_prof_min(13) << endl;
  cout << a.cerca_prof_min(11) << endl;
  cout << a.cerca_prof_min(7) << endl;
  */
  return 0;
}




















