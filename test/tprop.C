//C++
#include <vector>
#include <iostream>
using namespace std;

//ROOT
#include "TROOT.h"
#include "TGeoManager.h"
#include <TGeoMatrix.h>
#include <TGeoVolume.h>
#include <TVector3.h>
#include <TGeoMaterial.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include "TParticle.h"

//LMC
#include "LMCgeomN.h"
#include "LMCpropagator.h"
//#include "LMCpropMuon.h"
#include "LMCmaterials.h"
#include "LMCstep.h"
#include "LMCfunctor.h"
#include "LMCconstants.h"
#include "LMCstack.h"



 //////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

  cout<<"Ids  "<< LMCconstants::id("mu-")<<endl;
  cout<<"Electron Radius   "<<LMCconstants::r_e()<<"  and mass "<<LMCconstants::e_m()<<endl;
  cout<<"hc   "<<LMCconstants::hc()<<endl;
  TApplication theApp("App",&argc,argv);
  
   
  //define geometry
  LMCgeomN *g = new LMCgeomN("Telescope");
  //LMCgeomN *g = new LMCgeomN("Tank");
  LMCmaterials *mat = g->GetLMCmaterials();
  
  //create propagator and 
  LMCpropagator *prop = new LMCpropagator(g->GetGeoManager());
  //LMCpropMuon *prop = new LMCpropMuon (g->GetGeoManager());
  
  //set particle in stack
  LMCstack *stack = LMCstack::GetInstance();
  double vtx[3] = {0.,0.,50};
  double mom[3] = {1.,0.,0.};
  int PID = 22;
  TParticle *particle = new TParticle(PID,0,0,0,0,0,mom[0],mom[1],mom[2],0.,vtx[0],vtx[1],vtx[2],0.);
  TVector3 vaux(mom[0],mom[1],mom[2]);
  if(PID==22) particle->SetPolarisation(vaux.Orthogonal()); //photon
  stack->AddParticle(particle);
  
  //activate phys processes (node, phys proc)
  vector<string> vint;

  //............. sci, dedx
  vint.assign  (1,"SCI");
  vint.push_back("dEdx");
  prop->SetPhysProcesses("Scintillator_1",vint);
  prop->SetPhysProcesses("Scintillator_2",vint);
  prop->SetPhysProcesses("Scintillator_3",vint);
  
  //............. cer, dedx
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
  
  prop->DumpPhysProcesses();  

  //example of retrieving function
  TF1 *f = LMCfunctor::Instance()->GetBetheBloch(); 
  f->SetParameter(0,mat->GetMaterial("Scintillator")->GetZ());
  f->SetParameter(1,mat->GetMaterial("Scintillator")->GetA());
  f->SetParameter(2,mat->GetMaterial("Scintillator")->GetDensity());
  f->SetParameter(3,mat->GetMaterial("Scintillator")->GetRadLen());
  f->SetParameter(4,0.136);
  TCanvas *c = new TCanvas ("c", "Bethe Bloch", 1000,1000);
  c->cd();
  f->Draw();

  //evaluate function for different values
  double x=0.1;
  cout << "function evaluation: " << flush;
  for (int i=0; i<10; i++) {
    cout << f->Eval(x) << "(" << x << ") " << flush;
  }
  cout << endl;


  //propagate particles in stack
  for (int i=0; i<stack->Size(); i++) {
    TParticle *p = stack->NextParticle();
    cout << "propagating particle id= " << p->GetPdgCode() << endl;
    prop->SetParticle(p);
    vector<LMCstep*> vstep = prop->Propagate();
    for(uint j=0; j<vstep.size();j++) {
      vector<TParticle*> vpart = vstep[j]->GetParticles();
      for(uint i=0; i<vpart.size();i++) {
	stack->AddParticle(vpart[i]);
      }  
    }
    cout << " stack size = " <<stack->Size() <<  endl;
    for (int n=0; n<stack->Size(); n++) {
      cout << stack->GetEntry(n) << endl;
    }    
    getchar();
  }
  
  theApp.Run(1);
  
  return 0;
}

