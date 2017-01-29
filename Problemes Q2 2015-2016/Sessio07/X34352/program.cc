#include <iostream>
#include <map>
using namespace std;

int main() {
  map<string, int> diccionari;
  char codi;
  while (cin>>codi) {
    string paraula;
    cin>>paraula;
    if (codi=='a') ++diccionari[paraula];
    else cout<<diccionari[paraula]<<endl;
  }
  return 0;
}