#ifndef _LMCphysGen_
#define _LMCphysGen_

//C
#include "math.h"
#include <string>
#include <iostream>
#include <map>

//ROOT
#include <TMath.h>
#include <TParticle.h>
#include <TVector3.h>
#include <TRotation.h>
#include <TRandom.h>
#include <TF1.h>
#include <TH1D.h>

//MY
#include "LMCstep.h"
#include <vector>

using namespace std;

class TParticle;
class LMCstep;

/////////////////////////////////////////////////////////////////////////////////

class LMCphysGen {

 public:
  LMCphysGen();
  ~LMCphysGen();

  TParticle* GenSingleMuon(Double_t,Double_t,Double_t,Double_t,Double_t,Double_t); ///< generate single muon
  TParticle* GenRandomMuon();

  vector<TParticle*> GenCerPhotons(TParticle*, LMCstep*, Int_t); ///< generate cerenkov photons(mother particle, step, nb of photons to geenerate) 

  void               setRandGen(TRandom* iRand);
  map<TString,TH1D*> GetPlots();

 private:

  map<TString,TH1D*> fH;

  TRandom *RandGen;
  string  FuncTheta;
  string  FuncPhi;
  string  FuncP;

};

#endif
