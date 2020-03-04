#ifndef WORD_HPP
#define WORD_HPP
#include <iostream>

using namespace std;

#include "config.hpp"

class Word{
public:
  size_t l;
  size_t w[N+1];
  size_t kmin[K+1];
  Word();
  bool can_color(size_t x,size_t k);
  bool next();
  void fill();
  void display() const;
};


inline Word::Word(){
  w[0]=0;
  w[1]=1;
  l=1;
  for(size_t k=2;k<=K;++k){
    kmin[k]=N+1;
  }
  kmin[0]=0;
  kmin[1]=1;
}



#endif
