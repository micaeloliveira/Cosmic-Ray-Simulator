//ROOT
#include "TROOT.h"
#include "TGeoManager.h"
#include <TGeoMatrix.h>
#include <TGeoVolume.h>
#include <TVector3.h>
#include <TGeoMaterial.h>
#include <TF1.h>
#include <TCanvas.h>

#include "LMCgeomN.h"
#include "LMCpropagator.h"
//#include "LMCpropMuon.h"
#include "LMCmaterials.h"
#include <vector>
#include "TParticle.h"
#include "LMCstep.h"
#include "LMCfunctor.h"
#include <TApplication.h>

#include "LMCconstants.h"
#include "LMCstack.h"

using namespace std;

 
int main(int argc, char** argv) {
  
  cout<<"Ids  "<<LMCconstants::id("mu-")<<endl;
  cout<<"Electron Radius   "<<LMCconstants::r_e()<<"  and mass "<<LMCconstants::e_m()<<endl;
  cout<<"hc   "<<LMCconstants::hc()<<endl;
  
  double vtx[3] = {0.,0.,60.};
  double mom[3] = {0.,0.,-2.};
  int PID = 13;
   
  //define geometry
  LMCgeomN *g = new LMCgeomN("Telescope");
  
  //create propagator and 
  LMCpropagator *prop = new LMCpropagator(g->GetGeoManager());
  // LMCpropMuon *prop = new LMCpropMuon (g->GetGeoManager());
  

  //stack
  LMCstack *stack = LMCstack::GetInstance();
  
  //set particle in propagator
  TParticle *particle = new TParticle(PID,0,0,0,0,0,mom[0],mom[1],mom[2],0.,vtx[0],vtx[1],vtx[2],0.);
  stack->AddParticle(particle);
  
  //activate phys processes (node, phys proc)
  vector<string> vint;
  vint.assign  (1,"SCI");
  prop->SetPhysProcesses("Scintillator_1",vint);
  prop->SetPhysProcesses("Scintillator_2",vint);
  prop->SetPhysProcesses("Scintillator_3",vint);
  
  vint.push_back("dEdx");
  prop->SetPhysProcesses("Scintillator_1",vint);
  prop->SetPhysProcesses("Scintillator_2",vint);
  prop->SetPhysProcesses("Scintillator_3",vint);
  
  
  vint.assign (1,"CER");
  prop->SetPhysProcesses("LightGuideTrap_1",vint);
  prop->SetPhysProcesses("LightGuideTrap_2",vint);
  prop->SetPhysProcesses("LightGuideTrap_3",vint);
  prop->SetPhysProcesses("LightGuideRod_1",vint);
  prop->SetPhysProcesses("LightGuideRod_2",vint);
  prop->SetPhysProcesses("LightGuideRod_3",vint);
  prop->SetPhysProcesses("PMTWindowTank_1",vint);
  prop->SetPhysProcesses("PMTWindowTank_2",vint);  
  prop->SetPhysProcesses("PMTWindowTank_3",vint);
  prop->SetPhysProcesses("WATERvol_1",vint); 
  
  vint.push_back("dEdx");
  prop->SetPhysProcesses("LightGuideTrap_1",vint);
  prop->SetPhysProcesses("LightGuideTrap_2",vint);
  prop->SetPhysProcesses("LightGuideTrap_3",vint);
  prop->SetPhysProcesses("LightGuideRod_1",vint);
  prop->SetPhysProcesses("LightGuideRod_2",vint);
  prop->SetPhysProcesses("LightGuideRod_3",vint);
  prop->SetPhysProcesses("PMTWindowTank_1",vint);
  prop->SetPhysProcesses("PMTWindowTank_2",vint);  
  prop->SetPhysProcesses("PMTWindowTank_3",vint);
  prop->SetPhysProcesses("WATERvol_1",vint);
  
  
  prop->DumpPhysProcesses();  
  
  //propagate stack particles
  for (int i=0; i<stack->Size(); i++) {
    TParticle *p = stack->NextParticle();
    cout << "propagating particle id= " << p->GetPdgCode() << endl;
    
    prop->SetParticle(p);
    stack->Dump();
    vector<LMCstep*> vstep = prop->Propagate();
    
    for(uint j=0; j<vstep.size();j++) {
      vector<TParticle*> vpart = vstep[j]->GetParticles();
      cout << "[tstack] Nb of new particles generated: " << vpart.size() << endl;
      
      for(uint i=0; i<vpart.size();i++) {
	stack->AddParticle(vpart[i]);
      }  
    }
    cout << " stack size = " <<stack->Size() <<  endl;
    
    getchar();
  }
   

  return 0;
}

