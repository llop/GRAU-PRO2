#include <iostream>
#include <vector>
using namespace std;

void get_max_min(const vector<int> &v, int &maxim, int &minim) {
  maxim = minim = v[0];
  for (int i=1; i<v.size(); ++i) {
    if (maxim<v[i]) maxim=v[i];
    if (minim>v[i]) minim=v[i];
  }
}

int main() {
  int n;
  cin>>n;
  vector<int> v(n);
  for (int i=0; i<n; ++i) cin>>v[i];
  int maxim, minim;
  get_max_min(v, maxim, minim);
  cout<<maxim<<' '<<minim<<endl;
  return 0;
}