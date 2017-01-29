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
  
  // Pre:  p.i. = C1, c = C2
  // Post: el p.i. passa a ser el resultat de trenar C1 i C2; 
  //       c passa a ser buida
  void trenat(Cua &c) {
    node* n1 = prim;
    node* n2 = c.prim;
    while (n1 != NULL and n2 != NULL) {
      node* nant1 = n1;
      node* nant2 = n2;
      n1 = n1->seg;
      n2 = n2->seg;
      nant1->seg = nant2;
      if (n1 != NULL) nant2->seg = n1;
    }
    if (prim == NULL) prim = c.prim;
    if (longitud <= c.longitud) ult = c.ult;
    longitud += c.longitud;
    c.longitud = 0;
    c.prim = c.ult = NULL;
  }
};


// Problema 2
template <class T> class ArbreBin {
private:
  struct node {
    T info;
    node* segE;
    node* segD;
  };
  node* primer_node;

  static node* copia_node_arbre(node* m) {
    node* n;
    if (m==NULL) n=NULL;
    else {
      n = new node;
      n->info = m->info;
      n->segE = copia_node_arbre(m->segE);
      n->segD = copia_node_arbre(m->segD);
    }
    return n;
  }

public:
  ArbreBin() {
    primer_node = NULL;
  }
  void plantar(const T &info, ArbreBin<T> &fe, ArbreBin &fd) {
    primer_node = new node;
    primer_node->info = info;
    primer_node->segE = fe.primer_node;
    primer_node->segD = fd.primer_node;
    fe.primer_node = NULL;
    fd.primer_node = NULL;
  }
  void escriu_i(node *n) const {
    cout << ' ' << n->info;
    if (n->segE == NULL) cout << " -";
    else escriu_i(n->segE);
    if (n->segD == NULL) cout << " -";
    else escriu_i(n->segD);
  }
  void escriu() const {
    cout << "Arbre: ";
    if (primer_node != NULL) escriu_i(primer_node);
    cout << endl;
  }
  
  // Pre:  n != NULL; p es la profunditat de n; 
  //       psol es la profunditat del node nsol, o -1 si nsol es NULL
  //       nsol apunta al node amb info==x de prof. min. que hem trobat fins ara, o NULL si no hem trobat res
  // Post: psol es la profunditat profunditat del node nsol, o -1 si nsol es NULL
  //       nsol apunta al node amb info==x de prof. min. que hem trobat fins ara, o NULL si no hem trobat res
  void i_subarrel(int p, node* n, int &psol, node* &nsol, const T &x) const {
    if (nsol == NULL or p < psol) {  // nomes cal mirar si no tenim solucio, o hi ha opcio de millorar-la
      if (n->info == x) {
        nsol = n;
        psol = p;
      } else {
        if (n->segE != NULL) i_subarrel_dfs(p + 1, n->segE, psol, nsol, x);
        if (n->segD != NULL) i_subarrel_dfs(p + 1, n->segD, psol, nsol, x);
      }
    }
  }
  // Versio cerca en profunditat
  // Pre:  p.i. = A, asub es buit
  // Post: si A conte x, asub es el subarbre d'A resultat de la cerca;
  //       si A no conte x, asub es buit
  void subarrel(ArbreBin<int> &asub, const T &x) const {
    if (primer_node != NULL) {
      int psol = -1;
      node* nsol = NULL;
      i_subarrel_dfs(0, primer_node, psol, nsol, x);
      if (nsol != NULL) asub.primer_node = copia_node_arbre(nsol);
    }
  }
  
  // Versio cerca en amplada
  // Pre:  p.i. = A, asub es buit
  // Post: si A conte x, asub es el subarbre d'A resultat de la cerca;
  //       si A no conte x, asub es buit
  void subarrel_bfs(ArbreBin<int> &asub, const T &x) const {
    if (primer_node != NULL) {
      bool b = false;
      queue<node*> cua;
      cua.push(primer_node);
      while (not b and not cua.empty()) {
        node* n = cua.front();
        cua.pop();
        if (n->info == x) {
          asub.primer_node = copia_node_arbre(n);
          b = true;
        } else {
          if (n->segE != NULL) cua.push(n->segE);
          if (n->segD != NULL) cua.push(n->segD);
        }
      }
    }
  }
};


int main() {
  /*
  // inicializa
  Cua<int> c1;
  c1.push(1);
  c1.push(5);
  c1.push(14);
  c1.push(25);
  c1.push(8);
  c1.escriu();
  Cua<int> c2;
  c2.push(99);
  c2.push(3);
  c2.escriu();
  Cua<int> c3;
  c3.push(67);
  c3.push(89);
  c3.escriu();
  Cua<int> c4;
  c4.push(19);
  c4.push(24);
  c4.push(5);
  c4.push(17);
  c4.push(6);
  c4.escriu();
  // prova
  c3.trenat(c4);
  c3.escriu();
  c4.escriu();
  */
  /*
  // inicialitza
  ArbreBin<int> buit;
  ArbreBin<int> a__2, a__3, a__1, a_3, a_6, a__22, a;
  a__2.plantar(-2, buit, buit);
  a__3.plantar(-3, buit, buit);
  a__1.plantar(-1, buit, buit);
  a_3.plantar(3, buit, buit);
  a_6.plantar(6, a__2, a__3);
  a__22.plantar(-2, a__1, a_3);
  a.plantar(7, a_6, a__22);
  a.escriu();
  ArbreBin<int> b__1, b_3, b_8, b_1, b__3, b_9, b_6, b;
  b__1.plantar(-1, buit, buit);
  b_3.plantar(3, buit, buit);
  b_8.plantar(8, buit, buit);
  b_1.plantar(1, buit, buit);
  b__3.plantar(-3, b_1, buit);
  b_9.plantar(9, b__1, b_3);
  b_6.plantar(6, b_8, b__3);
  b.plantar(4, b_9, b_6);
  b.escriu();
  ArbreBin<int> c__2, c__1, c_3, c__11, c__22, c;
  c__2.plantar(-2, buit, buit);
  c__1.plantar(-1, buit, buit);
  c_3.plantar(3, buit, buit);
  c__11.plantar(-1, c__2, buit);
  c__22.plantar(-2, c__1, c_3);
  c.plantar(10, c__11, c__22);
  c.escriu();
  ArbreBin<int> d__1, d_3, d_8, d_6, d_66, d;
  d__1.plantar(-1, buit, buit);
  d_3.plantar(3, buit, buit);
  d_8.plantar(8, buit, buit);
  d_6.plantar(6, d__1, d_3);
  d_66.plantar(6, d_8, buit);
  d.plantar(-4, d_6, d_66);
  d.escriu();
  // prova
  ArbreBin<int> a1, b1, c1, d1;
  a.subarrel(a1, -2);
  b.subarrel(b1, 1);
  c.subarrel(c1, 10);
  d.subarrel(d1, 6);
  a1.escriu();
  b1.escriu();
  c1.escriu();
  d1.escriu();
  */
  return 0;
}
