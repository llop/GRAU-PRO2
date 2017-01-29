#include <iostream>
#include <stack>
using namespace std;

int main() {
  string s;
  cin>>s;
  stack<int> p;
  bool b=true;
  int i=0;
  while (b and s[i]!='.') {
    if (s[i]=='(') {
      p.push(0);
    } else if (s[i]==')') {
      if (not p.empty() and p.top()==0) p.pop();
      else b=false;
    } else if (s[i]=='[') {
      p.push(1);
    } else if (s[i]==']') {
      if (not p.empty() and p.top()==1) p.pop();
      else b=false;
    }
    ++i;
  }
  if (b and p.empty()) cout<<"Correcte"<<endl;
  else cout<<"Incorrecte"<<endl;
  return 0;
}
