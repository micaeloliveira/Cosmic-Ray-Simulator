#include <iostream>
#include "LMCstack.h"
using namespace std;

LMCstack* LMCstack::stack = NULL;


//////////////////////////////////////////////////////////////////////////////////
void LMCstack::AddParticle(TParticle *p) {
  vstack.push_back(p);
}

/////////////////////////////////////////////////////////////////////////////////
void LMCstack::AddParticle(vector<TParticle*> v) {
  for (uint i=0; i<v.size(); i++) {
    vstack.push_back(v[i]);
  }
}


//////////////////////////////////////////////////////////////////////////////////
TParticle* LMCstack::NextParticle() {
  cout << "[LMCstack::NextParticle] BEGIN: --------------------------------------> " << CurrentParticle << endl;
  if (CurrentParticle) {
    itvstack = vstack.begin()+iCurrentParticle;
    cout << "[LMCstack::NextParticle] deleting current particle [pointer=" << CurrentParticle << "]" 
         << " [PdgCode=" << CurrentParticle->GetPdgCode() << "]"  
         << " [iterator PdgCode=" << (*itvstack)->GetPdgCode() << "]"  << flush;
    vstack.erase(itvstack);    
    CurrentParticle = NULL;
    cout << "done!!" << endl;
  }
  if (vstack.size() != 0) {
    cout << "[LMCstack::NextParticle] next particle ..." << flush;
    iCurrentParticle = vstack.size()-1;
    itvstack = vstack.begin()+iCurrentParticle;
    CurrentParticle = vstack[iCurrentParticle];  
    cout << "CurrentParticle=" << CurrentParticle << " iCurrentParticle=" << iCurrentParticle << " [stack size=" << vstack.size() << "]" 
    << " [iterator PdgCode=" << (*itvstack)->GetPdgCode() << "]"  << endl;
    return CurrentParticle;
  } else {
    return NULL;
  }
}
