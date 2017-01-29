#include <iostream>
#include <list>
using namespace std;

void llegirList(list<pair<int, int> > &li) {
  pair<int, int> p;
  cin>>p.first>>p.second;
  while (p.first!=0 and p.second!=0) {
    li.insert(li.end(), p);
    cin>>p.first>>p.second;
  }
}

void tractarList(list<pair<int, int> > &li, int n, int &aparicions, int &suma) {
  aparicions=0;
  suma=0;
  for (list<pair<int, int> >::iterator it=li.begin(); it!=li.end(); ++it) {
    pair<int, int> p=*it;
    if (p.first==n) {
      ++aparicions;
      suma+=p.second;
    }
  }
}

int main() {
  list<pair<int, int> > li;
  llegirList(li);
  int n;
  cin>>n;
  int aparicions, suma;
  tractarList(li, n, aparicions, suma);
  cout<<n<<' '<<aparicions<<' '<<suma<<endl;
  return 0;
}