#include <iostream>
#include "PilaIOParInt.hh"

void cercarPilaParInt(stack<ParInt> p, int n, bool &b, int &segon) {
  b=false;
  while (not b and not p.empty()){
    if (p.top().primer()==n) {
      segon=p.top().segon();
      b=true;
    } else {
      p.pop();
    }
  }
}

int main() {
  stack<ParInt> p;
  llegirPilaParInt(p);
  int n;
  cin>>n;
  escriurePilaParInt(p);
  bool b;
  int segon;
  cercarPilaParInt(p, n, b, segon);
  if (b) cout<<segon<<endl;
  else cout<<"No trobat"<<endl;
  return 0;
}