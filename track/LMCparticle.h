#ifndef _LMCparticle_
#define _LMCparticle_

//ROOT
#include "TParticle.h"

//forward
class TParticlePDG;


///////////////////////////////////////////////////////////////////////

class LMCparticle: public TParticle {

 public:

  LMCparticle(Int_t, Double_t *mom,  Double_t *vtx);
  LMCparticle(const TParticle&);
  ~LMCparticle() {;}

  Int_t PdgCode();
  Double_t Mass();
  Double_t* GetMomentum();
  Double_t* GetVertex();
  Double_t* GetDir();

 private:
};

#endif
