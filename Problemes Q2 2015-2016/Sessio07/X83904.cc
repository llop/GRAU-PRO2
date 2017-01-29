#include <iostream>
#include <set>
using namespace std;

int main() {
  set<string> totes;
  set<string> ninguna;
  string nom;
  cin>>nom;
  while (nom!=".") {
    ninguna.insert(nom);
    cin>>nom;
  }
  int n;
  cin>>n;
  if (n>0) {
    totes=ninguna;
    for (int i=0; i<n; ++i) {
      set<string> nouTotes;
      cin>>nom;
      while (nom!=".") {
        ninguna.erase(nom);
        if (totes.find(nom)!=totes.end()) {
          nouTotes.insert(nom);
        }
        cin>>nom;
      }
      totes.swap(nouTotes);
    }
  }
  cout<<"Totes les activitats:";
  set<string>::iterator it;
  for (it=totes.begin(); it!=totes.end(); ++it) {
    cout<<' '<<*it;
  }
  cout<<endl;
  cout<<"Cap activitat:";
  for (it=ninguna.begin(); it!=ninguna.end(); ++it) {
    cout<<' '<<*it;
  }
  cout<<endl;
  return 0;
}