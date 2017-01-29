#include "matriu.hh"


template <typename T> matriu<T>::matriu(int m, int n) {
  nfil=m;
  ncol=n;
  files=vector<list<parint> >(nfil);
}

template <typename T> void matriu<T>::modif_pos(int i, int j, T x) {
  typename list<parint>::iterator it=files[i].begin();
  while (it!=files[i].end() and it->col<j) ++it;
  if (it!=files[i].end() and it->col==j) {
    if (x==0) files[i].erase(it);
    else it->val=x;
  } else {
    parint p;
    p.col=j;
    p.val=x;
    files[i].insert(it, p);
  }
}

template <typename T> void matriu<T>::suma(const matriu& m1, const matriu& m2) {
  nfil=m1.nfil;
  ncol=m1.ncol;
  files=vector<list<parint> >(nfil);
  for (int i=0; i<nfil; ++i) {
    typename list<parint>::const_iterator it1=m1.files[i].begin();
    typename list<parint>::const_iterator it2=m2.files[i].begin();
    for (int j=0; j<ncol; ++j) {
      T x1=0;
			while (it1!=m1.files[i].end() and it1->col<j) ++it1;
      if (it1!=m1.files[i].end() and it1->col==j) x1=it1->val;
      T x2=0;
			while (it2!=m2.files[i].end() and it2->col<j) ++it2;
      if (it2!=m2.files[i].end() and it2->col==j) x2=it2->val;
      T x=x1+x2;
      if (x!=0) {
        parint p;
        p.col=j;
        p.val=x;
        files[i].insert(files[i].end(), p);
      }
    }
  }
}

template <typename T> void matriu<T>::producte(const matriu& m1, const matriu& m2) {
  nfil=m1.nfil;
  ncol=m2.ncol;
  files=vector<list<parint> >(nfil);
	vector<typename list<parint>::const_iterator> it2(m2.nfil);
	for (int i=0; i<m1.nfil; ++i) {
		for (int k=0; k<m2.nfil; ++k) it2[k]=m2.files[k].begin();
		for (int j=0; j<m2.ncol; ++j) {
      T x=0;
      typename list<parint>::const_iterator it1=m1.files[i].begin();
      for (int k=0; k<m2.nfil; ++k) {
        T x1=0;
				while (it1!=m1.files[i].end() and it1->col<k) ++it1;
		    if (it1!=m1.files[i].end() and it1->col==k) x1=it1->val;
        T x2=0;
        while (it2[k]!=m2.files[k].end() and it2[k]->col<j) ++it2[k];
        if (it2[k]!=m2.files[k].end() and it2[k]->col==j) x2=it2[k]->val;
        x+=x1*x2;
      }
      if (x!=0) {
        parint p;
        p.col=j;
        p.val=x;
        files[i].insert(files[i].end(), p);
      }
    }
  }
}

template <typename T> int matriu<T>::num_files() const {
  return nfil;
}

template <typename T> int matriu<T>::num_columnes() const {
  return ncol;
}

template <typename T> T matriu<T>::pos(int i, int j) const {
  typename list<parint>::iterator it=files[i].begin();
  while (it!=files[i].end() and it->col<j) ++it;
  if (it!=files[i].end() and it->col==j) return it->val;
  return 0;
}

template <typename T> void matriu<T>::llegeix(int m, int n) {
  nfil=m;
  ncol=n;
  files=vector<list<parint> >(nfil);
  for (int i=0; i<nfil; ++i) {
    int k;
    cin>>k;
    for (int j=0; j<k; ++j) {
      parint p;
      cin>>p.col>>p.val;
      files[i].insert(files[i].end(), p);
    }
  }
}

template <typename T> void matriu<T>::escriu() const {
  for (int i=0; i<nfil; ++i) {
    typename list<parint>::const_iterator it=files[i].begin();
    for (int j=0; j<ncol; ++j) {
      while (it!=files[i].end() and it->col<j) ++it;
      if (it!=files[i].end() and it->col==j) cout<<it->val;
      else cout<<0;
			cout<<' ';
    }
    cout<<endl;
  }
	cout<<endl;
}
