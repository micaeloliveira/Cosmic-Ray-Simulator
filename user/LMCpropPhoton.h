#ifndef __LMCpropPhoton__
#define __LMCpropPhoton__

//C
#include <iostream>
#include <vector>

// MY
#include "LMCgeomN.h"
#include "LMCstep.h"
#include "LMCpropagator.h"

// ROOT
#include <TParticle.h>
#include <TVector3.h>
#include <TGeoManager.h>
#include "TVector3.h"
#include <TF1.h>
#include <TMath.h>
#include "TF1.h"
#include <TRandom.h>
#include <TVirtualGeoTrack.h>
#include <TGeoTrack.h>

using namespace std;

//forward
class TGeoManager;
class TRandom3;
class LMCgeomN;
class LMCstep;

///////////////////////////////////////////////////////////////////////////////////////

class LMCpropPhoton: public LMCpropagator {

 public:

  LMCpropPhoton(TGeoManager*);
  ~LMCpropPhoton();

  int      Propagate(TParticle *photon);

  LMCstep* DoStepUser(Double_t d, Double_t E);
  Int_t GetNPhotonsSci(LMCstep*); 
  Int_t GetNPhotonsCer(LMCstep*); 
  
  
  Double_t GetLambda();
  Double_t GetDistLife();
  Double_t GetDistDone();
  Double_t GetNReflection();  
  void     SetRandGen(TRandom3* iRand);


 private:
 
   Double_t outLambda;
   Double_t outDistLife;
   Double_t outDistDone;
   Double_t outNReflection;

   TF1 *PhotonAbsortionProb;
   map<TString,Double_t> Reflectividade;
    
   TRandom3 *RandomG;  


};


class LMCReflection{

  public:

    /// Constructor
    LMCReflection(int debug=0);

    /// Destructor
    ~LMCReflection();

    /// Perform the real analysis
    TVector3 Calculate(TVector3 normal,TVector3 vIncidente);

  private: 

    int    debug;
};

class LMCFresnel{

  public:

    /// Constructor
    LMCFresnel(double n1=1,double n2=1,int debug=1);

    /// Destructor
    ~LMCFresnel();

    /// Perform the real analysis
    pair<bool,pair<TVector3,double> > Calculate(TVector3 normal,TVector3 vIncidente,double lambda);

  private: 

    double IndexN1,IndexN2;
    int    debug;

};

#endif
