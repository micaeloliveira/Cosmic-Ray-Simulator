#include "LMCgeomN.h"
#include "LMCpropagator.h"
#include <vector>
#include "TParticle.h"
using namespace std;

int main() {
  double vtx[3] = {0.,0.,60.};
  double mom[3] = {0.,0.,-10.};
  int PID = 13;

  //define geometry
  LMCgeomN *g = new LMCgeomN("Telescope");

  //create propagator and 
  LMCpropagator *prop = new LMCpropagator(g->GetGeoManager());

  //set particle in propagator
  TParticle *particle = new TParticle(PID,0,0,0,0,0,mom[0],mom[1],mom[2],0.,vtx[0],vtx[1],vtx[2],0.);
  prop->SetParticle(particle);

  //activate phys processes (node, phys proc)
  vector<string> vint (1,"SCI");  
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
  prop->SetPhysProcesses("WATERvol_1",vint);  
  prop->SetPhysProcesses("PMTWindowTank_1",vint);
  prop->SetPhysProcesses("PMTWindowTank_2",vint);  
  prop->SetPhysProcesses("PMTWindowTank_3",vint);
  prop->DumpPhysProcesses();  

  vector<LMCstep*> v = prop->Follow();

  return 0;
}

