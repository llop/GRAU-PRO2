#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Equip {
  int id, punts, gols_favor, gols_contra;
  Equip() {};
  Equip(int id, int punts, int gols_favor, int gols_contra) :
    id(id), punts(punts), gols_favor(gols_favor), gols_contra(gols_contra) {}
};

bool cmp(const Equip &equip1, const Equip &equip2) {
  if (equip1.punts==equip2.punts) {
    int gols_equip1=equip1.gols_favor-equip1.gols_contra;
    int gols_equip2=equip2.gols_favor-equip2.gols_contra;
    if (gols_equip1==gols_equip2) return equip1.id<equip2.id;
    return gols_equip1>gols_equip2;
  }
  return equip1.punts>equip2.punts;
}

int main() {
  int n;
  cin>>n;
  vector<Equip> v(n);
  for (int i=0; i<n; ++i) 
    v[i]=Equip(i+1, 0, 0, 0);
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      int gols_equip1, gols_equip2;
      cin>>gols_equip1>>gols_equip2;
      if (i!=j) {
        if (gols_equip1==gols_equip2) {
          ++v[i].punts;
          ++v[j].punts;
        } else if (gols_equip1>gols_equip2) {
          v[i].punts+=3;
        } else {
          v[j].punts+=3;
        }
        v[i].gols_favor+=gols_equip1;
        v[i].gols_contra+=gols_equip2;
        v[j].gols_favor+=gols_equip2;
        v[j].gols_contra+=gols_equip1;
      }
    }
  }
  sort(v.begin(), v.end(), cmp);
  for (int i=0; i<n; ++i) 
    cout<<v[i].id<<' '<<v[i].punts<<' '<<v[i].gols_favor<<' '<<v[i].gols_contra<<endl;
  return 0;
}