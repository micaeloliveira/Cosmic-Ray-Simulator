#ifndef __LMCpropagator__
#define __LMCpropagator__

//C++

// ROOT
#include <TParticle.h>
#include <TVector3.h>
#include <TGeoManager.h>
#include <TGeoVolume.h>

// MY
#include "LMCgeomN.h"
#include "LMCstep.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

//forward
class TGeoManager;

//class TParticle;
//class LMCgeomN;
//class TGeoNode;
//class TGeoVolume;
//class TGeoMaterial;
//class LMCstep;

///////////////////////////////////////////////////////////////////////////////////////

class LMCpropagator {

 public:

  LMCpropagator(TGeoManager*);
  ~LMCpropagator();

  void        SetParticle(TParticle*);
  TParticle*  GetParticle();

  void        SetPhysProcesses(string node, vector<string> vint); ///<geom node, interaction processes ("SCI", "CER",...) 
  void        DumpPhysProcesses(); 

  vector<LMCstep*> Follow(); ///< debug: follow particle through all the geometry boundaries
  vector<LMCstep*> Propagate(); ///< propagate particle through all the geometry nodes and simulate phys processes

  TGeoNode* GetNextBoundaryStep(Double_t&); ///< get step to reach next boundar
  LMCstep*  DoStep(Double_t);
  LMCstep*  CrossNextBoundary(); ///< cross next boundary and stop

  TGeoNode*       GetCurrentNode();
  Int_t           GetCurrentNodeId();
  const char*     GetCurrentNodeName();
  TGeoVolume*     GetCurrentVolume();
  TGeoMaterial*   GetCurrentMaterial();
  Double_t        GetCurrentDensity();
  const Double_t* GetCurrentPoint();
  const Double_t* GetCurrentDir();
  Bool_t          IsEntering();

  const Double_t* GetNormalDir(); ///< get normal direction to separation plane

  void            SetDebugLevel(int iDL);   // Setting Debug Level (0=no debug; 1=debug)

  /* user methods */

  virtual LMCstep* DoStepUser(Double_t d, Double_t E); ///< propagate particle of energy E in a step d
  virtual Int_t GetNPhotonsSci(LMCstep*);
  virtual Int_t GetNPhotonsCer(LMCstep*);
  Double_t GetdEdx(LMCstep*);
  Double_t GetdEdxCer(LMCstep*);


  vector<LMCstep*> PropOnWaterTank(Int_t);

  int Reflectivity(TVector3 Normal,TVector3& Direction,TVector3 Efield,double n1, double n2);
  vector<LMCstep*> PropOpticalPhoton();
  vector<LMCstep*> PropParticle();

  TVector3 Proj(TVector3 v1,TVector3 v2);


 protected:
  int         DebugLevel;
  TGeoManager *geom; ///< geometry manager
  TParticle   *part; ///< particle (contains the vertex where to start propagation)
  map < string, vector<string> > mPhys; ///< association between geom node and interactions ("SCI", "CER")  
  map < string, vector<string> >::iterator itmPhys;  
};

#endif
