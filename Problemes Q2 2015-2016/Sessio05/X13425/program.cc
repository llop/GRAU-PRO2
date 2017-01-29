#include <iostream>
#include "CuaIOParInt.hh"

int main() {
  queue<ParInt> q;
  LlegirCuaParInt(q);
  queue<ParInt> q1, q2;
  int temps_q1=0;
  int temps_q2=0;
  while (not q.empty()) {
    if (temps_q2<temps_q1) {
      q2.push(q.front());
      temps_q2+=q.front().segon();
    } else {
      q1.push(q.front());
      temps_q1+=q.front().segon();
    }
    q.pop();
  }
  EscriureCuaParInt(q1);
  cout<<endl;
  EscriureCuaParInt(q2);
  return 0;
}