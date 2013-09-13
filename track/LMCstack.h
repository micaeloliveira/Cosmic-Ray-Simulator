#ifndef __LMCstack__
#define __LMCstack__

#include <vector>
#include <iostream>
#include <algorithm>
#include "TParticle.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
class LMCstack {
 public: 
  static LMCstack* GetInstance() {
    if (!stack) stack=new LMCstack();  
    return stack;
  }
  TParticle* NextParticle();
  void AddParticle(TParticle*);
  void AddParticle(vector<TParticle*>);
  TParticle* GetEntry(int i) {return vstack[i];}
  int Size() {return (int)vstack.size();}
  void Dump(int n=10) {
    int i = 0;
    int p = vstack.size();
    while (i<min(n,p)) {
      i++;
      cout << vstack[p-i] << "  id=" << vstack[p-i]->GetPdgCode() << endl;
    }
  }
 private:
  LMCstack() {
    CurrentParticle = NULL;
    iCurrentParticle = -1;
  }
  ~LMCstack() {delete stack;}
  LMCstack(LMCstack const&){};             
  LMCstack& operator=(LMCstack const&){};
  static LMCstack* stack;
  vector<TParticle*> vstack;
  vector<TParticle*>::iterator itvstack;
  TParticle *CurrentParticle;
  int iCurrentParticle;
};

#endif
