#include "word.hpp"



bool
Word::can_color(size_t n,size_t k){
  if(kmin[k-1]>=n) return false;
#ifdef STRONG
  for(size_t x=1;x<=n-x;++x){
#else
  for(size_t x=1;x<n-x;++x){
#endif
    if(w[x]==k and w[n-x]==k){
      return false;
    }
  }
  return true;
}

//***********************************************
//* Fill current partition until it is terminal *
//***********************************************

void
Word::fill(){
  while(l<N){
    int k=1;
    for(;k<=K;++k){
      if(can_color(l+1,k)){
	w[++l]=k;
	kmin[k]=min(kmin[k],l);
	break;
      }
    }
    if(k==K+1) return;
  }
}

//****************************************************
//* Set current partition to next terminal partition *
//****************************************************

bool
Word::next(){
  while(true){
    int k=w[l];
    if(k<K){
      //We can try change the color of last element
      for(size_t nk=k+1;nk<=K;++nk){
	if(can_color(l,nk)){
	  w[l]=nk;
	  kmin[nk]=min(kmin[nk],l);
	  fill();
	  return true;
	}
      }
    }
    //We can't change the color of l
    if(kmin[k]==l){
      kmin[k]=N+1;
    }
    --l;
    if(l==0) return false;
  }
  return false;
}

void
Word::display() const{
  for(size_t k=1;k<=l;++k){
    cout<<w[k];
  }
}
