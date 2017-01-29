#include <iostream>
#include <vector>
using namespace std;


// Problema 1
template <class T> class stack {
private:
  struct node {
    T info;
    node* seg;
  };
  int altura;
  node* primer;

public:
  stack() {
    primer = NULL;
    altura = 0;
  }
  void push(const T &info) {
    node* n = new node;
    n->info = info;
    n->seg = primer;
    primer = n;
    ++altura;
  }
  void escriu() const {
    cout << "Pila: ";
    node* n = primer;
    while (n != NULL) {
      cout << ' ' << n->info;
      n = n->seg;
    }
    cout << endl;
  }
  // Pre:  el p.i. es una pila P
  // Post: el p.i. conte el mateixos elements que P, 
  //       pero ordenats de petit (el cim) a gran (al fons)
  void ordena() {
    node* nova = NULL;
    // Inv: nova apunta a una cadena de nodes que conte els elenets mes grans de P ordenats de petit a gran
    //      primer apunta a una cadena de nodes que resulta d'eliminar de P els elements que son a la cadena apuntada per nova
    while (primer != NULL) {
      node* p = primer;
      node* nmax = primer;
      node* nmax_ant = NULL;
      // Inv: primer no es NULL
      //      p apunta a un node de la cadena que comença a primer
      //      nmax apunta a un node que te el valor maxim dels que son entre l'apuntat per primer i l'apuntat per p (ambdos inclosos)
      //      nmax_ant apunta al node anterior a l'apuntat per nmax (si aquest no te anterior, nmax_ant es NULL)
      while (p->seg != NULL) {
        if (p->seg->info > nmax->info) {
          nmax = p->seg;
          nmax_ant = p;
        }
        p = p->seg;
      }
      if (nmax_ant == NULL) primer = nmax->seg;
      else nmax_ant->seg = nmax->seg;
      nmax->seg = nova;
      nova = nmax;
    }
    primer = nova;
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
    for (auto &x : n->seg) escriu_i(x);
  }
  void escriu() const {
    cout << "Arbre: ";
    if (primer_node != NULL) escriu_i(primer_node);
    cout << endl;
  }
  
  // Pre:  el p.i. no es buit
  // Post: el resultat es la suma del subnode de n amb suma maxima
  //       acc es la suma de n
  T i_suma_max_subarbre(node* n, T &acc) const {
    // calcula suma arbre arrelat en n
    acc = n->info;
    T ret = n->info;
    if (not n->seg.empty()) {
      for (int i = 0; i < (int)n->seg.size(); ++i) {
        T acc_fill;
        T nmax_fill = i_suma_max_subarbre(n->seg[i], acc_fill);
        acc += acc_fill;                                 // suma total arbre
        if (i == 0 or ret < nmax_fill) ret = nmax_fill;  // suma maxima
      }
      if (ret < acc) ret = acc;                          // mirar si la suma total es > que la 'suma maxima'
    }
    return ret;
  }
  // Pre:  el p.i. no es buit
  // Post: el resultat es la suma del subarbre del p.i. amb suma maxima
  T suma_max_subarbre() const {
    T acc;
    return i_suma_max_subarbre(primer_node, acc);
  }
};


int main() {
  /*
  // inicialitza
  stack<int> s;
  s.push(5);
  s.push(6);
  s.push(9);
  s.push(2);
  s.push(4);
  s.escriu();
  // prova
  s.ordena();
  s.escriu();
  */
  /*
  // inicialitza
  vector<ArbreGen<int>> v_buit;
  ArbreGen<int> u, z, d, x, v;
  u.plantar(1, v_buit);
  z.plantar(0, v_buit);
  d.plantar(-2, v_buit);
  x.plantar(-10, v_buit);
  v.plantar(6, v_buit);
  vector<ArbreGen<int>> v_u = { u };
  vector<ArbreGen<int>> v_v = { v };
  vector<ArbreGen<int>> v_zd = { z, d };
  ArbreGen<int> mu, s, mv;
  mu.plantar(-1, v_u);
  mv.plantar(-1, v_v);
  s.plantar(7, v_zd);
  ArbreGen<int> a, b, c;
  vector<ArbreGen<int>> v_a = { mu, s, x };
  vector<ArbreGen<int>> v_b = { mu, s, x };
  vector<ArbreGen<int>> v_c = { mv, s, x };
  a.plantar(3, v_a);
  b.plantar(24, v_b);
  c.plantar(3, v_c);
  a.escriu();
  b.escriu();
  c.escriu();
  // prova
  cout << a.suma_max_subarbre() << endl;
  cout << b.suma_max_subarbre() << endl;
  cout << c.suma_max_subarbre() << endl;
  */
  return 0;
}




