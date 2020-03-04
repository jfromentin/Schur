#include <chrono>
#include <fstream>
#include <iostream>
#include "word.hpp"

using namespace std;

int main(){
#ifdef STRONG
  string name="Schur";
#else
  string name="weak_Schur";
#endif
  name=name+"_"+to_string(K)+"_"+to_string(N)+"_"+to_string(S)+".data";
  ofstream out(name.c_str());
  size_t lmax=0;
  size_t n=0;
  size_t nmax=0;
  size_t sumlc=0;
  size_t maxlc=0;
  size_t nc=0;
  Word w;
  w.fill();
  auto start = std::chrono::system_clock::now();
  out<<"n\tmoy\tmax"<<endl;
  while(w.next()){
    ++n;
    if(w.l>=lmax){
      if(w.l==lmax){
	++nmax;
      }
      else{
	nmax=1;
	lmax=w.l;
      }
    }
    maxlc=max(maxlc,w.l);
    sumlc+=w.l;
    if(n%S==0){
      ++nc;
      double moy=sumlc;
      moy=moy/S;
      out<<nc<<'\t'<<moy<<'\t'<<maxlc<<endl;
      cout<<"***********************************"<<endl;
      cout<<"*         Cluster "<<nc<<endl;
      cout<<"***********************************"<<endl;
      cout<<endl;
      cout<<"Average cluster = "<<moy<<endl;
      cout<<"Maximum cluster = "<<maxlc<<endl;
      auto cur = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed = cur-start;
      cout<<"Terminals partitions = "<<n<<endl;
      double speed=(double)n/elapsed.count();
      cout<<"Speed = "<<(int)(speed/1000)<<" (thousand term. part.)/second "<<endl;
      cout<<"Max length = "<<lmax<<endl;
      cout<<"Number of max length = "<<nmax<<endl;
      cout<<endl;
      sumlc=0;
      maxlc=0;
    }
  }
  double moy=sumlc;
  moy=moy/(n%S);
  out<<nc+1<<'\t'<<moy<<'\t'<<maxlc<<endl;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end-start;
  cout<<"Terminals partitions = "<<n<<endl;
  double speed=(double)n/elapsed.count();
  cout<<"Speed = "<<(int)(speed/1000)<<" (thousand term. part.)/second "<<endl;
  cout<<"Max length = "<<lmax<<endl;
  cout<<"Number of max length = "<<nmax<<endl;
  out.close();
}
