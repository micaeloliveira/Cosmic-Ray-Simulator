//==============================================
//
//  June 2012, Improvements to LMCstep 
//  authors: L. Batalha & M. Oliveira
//
//==============================================

#include <math.h>
#include <iostream>

//ROOT
#include "TROOT.h"
#include "TGeoManager.h"
#include <TGeoMatrix.h>
#include <TGeoVolume.h>
#include <TVector3.h>
#include <TParticle.h>
#include <TRandom.h>
#include <TMath.h>
#include <TParticle.h>
#include <TTree.h>
#include <TH1D.h>
#include <TGraph.h>
#include "TF1.h"


//MY
#include "LMCstep.h"
#include "LMCconstants.h"
#include "LMCfunctor.h"


using namespace std;
//using namespace LMCconstants;

///////////////////////////////////////////////////////////////////////////////////////
LMCstep::LMCstep() {
  Energy_i = 0.;
  Energy_lost = 0.;
  dE_ioniz = 0.;
  dE_cerenk = 0.;
  CurrentNode = NULL;
  CurrentMedium = NULL;
  CurrentMaterial = NULL;
  NPhotonsSci = 0;
  NPhotonsCer = 0;
  vparticles.clear();
}

///////////////////////////////////////////////////////////////////////////////////////
LMCstep::~LMCstep() {;}

///////////////////////////////////////////////////////////////////////////////////////
void LMCstep::SetEnergy(Double_t E) { Energy_i = E;}
void LMCstep::SetEnergyLost(Double_t E) { Energy_lost = E;}
void LMCstep::SetEnergyLostIoniz(Double_t E) { dE_ioniz = E;}
void LMCstep::SetEnergyLostCerenk(Double_t E) { dE_cerenk = E;}
void LMCstep::SetCurrentNode(TGeoNode *n) { CurrentNode = n;}		
void LMCstep::SetCurrentMedium(TGeoMedium *n) { CurrentMedium = n;}	
void LMCstep::SetCurrentMaterial(TGeoMaterial *n) { CurrentMaterial = n;}	
void LMCstep::SetInitPoint(TVector3 v) { InitPoint = v;}		
void LMCstep::SetEndPoint(TVector3 v) { EndPoint = v;}			
void LMCstep::SetNPhotonsSci(Int_t n) { NPhotonsSci = n;}		
void LMCstep::SetNPhotonsCer(Int_t n) { NPhotonsCer = n;}               
void LMCstep::SetCerAngle(Double_t t) { thetaCer = t;}               

void LMCstep::SetNewParticles() {
  
  //getchar();
 
  //Sets Sci Photons
  for(int j=0; j<NPhotonsSci ;j++ ){   
    int PID = LMCconstants::id("photon");//particle ID
    TVector3 posistep = GetInitPoint();//initial step point
    TVector3 posfstep = GetEndPoint();//final step point
    double posParticle[3];//particle position
    Double_t k = gRandom->Uniform(0.,1.);//generates a random num for particle position defenition
    //Calculates particle creation position
    posParticle[0]=posistep.X()+k*(posfstep.X()-posistep.X());
    posParticle[1]=posistep.Y()+k*(posfstep.Y()-posistep.Y());
    posParticle[2]=posistep.Z()+k*(posfstep.Z()-posistep.Z());
    
    //Random Direction
    Double_t costheta = gRandom->Uniform(-1.,1.);
    Double_t phi = gRandom->Uniform(0.,2*TMath::Pi());
    //Calculates Momentum
    //from emission spectrum distribution for Scintillator
    Double_t lambda = LMCfunctor::Instance()->GetEmissionSpectrumSci()->GetRandom();//nm
    Double_t p = ((LMCconstants::hc()*1.E+2)/(lambda*1.E-9))*1.E-9;//photon momentum GeV
    double mom[3]; 
    mom[0]= p*sin(acos(costheta));
    mom[1]= p*costheta*cos(phi);
    mom[2]= p*costheta*sin(phi);
   

    //Sets new particle
    TParticle *particle = new TParticle(PID,0,0,0,0,0,mom[0],mom[1],mom[2],0.,posParticle[0],posParticle[1],posParticle[2],0.);
    
    //Electric Field
    TVector3 vaux ;//vaux is just the vector corresponding to the photon
    vaux.SetXYZ(mom[0],mom[1],mom[2]);
    TVector3 Efield =vaux.Orthogonal(); 
    Efield = Efield.Unit();
    particle->SetPolarisation(Efield);
    
    //adds particle to list of particles
    vparticles.push_back(particle);

  }

  //Sets Cer  Photons
  for(int j=0; j<NPhotonsCer ;j++ ){   
    int PID = LMCconstants::id("photon");//particle ID
    TVector3 posistep = GetInitPoint();//initial step point
    TVector3 posfstep = GetEndPoint();//final step point
    double posParticle[3];//particle position
    Double_t k = gRandom->Uniform(0.,1.);//generates a random num for particle position defenition
    //Calculates particle creation position
    posParticle[0]=posistep.X()+k*(posfstep.X()-posistep.X());
    posParticle[1]=posistep.Y()+k*(posfstep.Y()-posistep.Y());
    posParticle[2]=posistep.Z()+k*(posfstep.Z()-posistep.Z());
    //Random Direction
    Double_t phi   = gRandom->Uniform(0,TMath::TwoPi());
    //Creates a vector belonging to the Cerenkov cone
    TVector3 vpart, vperp, vphoton;
    vpart = posfstep - posistep;
    vperp = vpart.Orthogonal();
    vphoton = vpart;
    vphoton.Rotate(thetaCer,vperp);  
    vphoton.Rotate(phi,vpart);
    
    Double_t lambdacer = LMCfunctor::Instance()->GetCerenkovSpec()->GetRandom();//nm
    // Energy for the Cerenkov Photons
    Double_t p = LMCconstants::hc()/(lambdacer*1.E-11)*(1.E-9);// GeV
    double mom[3];
    mom[0] = p*vphoton.Unit().X();
    mom[1] = p*vphoton.Unit().Y();
    mom[2] = p*vphoton.Unit().Z();
    

    TParticle *particle = new TParticle(PID,0,0,0,0,0,mom[0],mom[1],mom[2],0.,posParticle[0],posParticle[1],posParticle[2],0.);

    
    //Electric Field
     TVector3 vaux,vaux2;//vaux is just the vector corresponding to the photon and vaux2 is the cross product vaux*vpart
    vaux.SetXYZ(mom[0],mom[1],mom[2]);
    vaux2 = vaux.Cross(vpart);
    TVector3 Efield =vaux.Cross(vaux2); 
    Efield = Efield.Unit();
    particle->SetPolarisation(Efield);
    
    /*
    cout << "vaux=" << vaux.X() << " | " <<  vaux.Y() << " | " << vaux.Z() << endl;
    cout << "vpart=" << vpart.X() << " | " <<  vpart.Y() << " | " << vpart.Z() << endl;
    cout << "vaux2=" << vaux2.X() << " | " <<  vaux2.Y() << " | " << vaux2.Z() << endl;
    cout << "v=" << Efield.X() << " | " <<  Efield.Y() << " | " << Efield.Z() << endl;   
    getchar();
    */
    
    vparticles.push_back(particle);
    
  }

} 


///////////////////////////////////////////////////////////////////////////////////////
Double_t LMCstep::GetEnergy() { return Energy_i;}
Double_t LMCstep::GetEnergyLost() { return Energy_lost;}
Double_t LMCstep::GetEnergyLostIoniz() { return dE_ioniz;}
Double_t LMCstep::GetEnergyLostCerenk() { return dE_cerenk;}
TGeoNode* LMCstep::GetCurrentNode() { return CurrentNode;}		
TGeoMedium* LMCstep::GetCurrentMedium() { return CurrentMedium;}	
TGeoMaterial* LMCstep::GetCurrentMaterial() { return CurrentMaterial;}	
const TVector3 LMCstep::GetInitPoint() { return InitPoint;}		
const TVector3 LMCstep::GetEndPoint() { return EndPoint;}			
Int_t LMCstep::GetNPhotonsSci() { return NPhotonsSci;}		
Int_t LMCstep::GetNPhotonsCer() { return NPhotonsCer;}               
Double_t LMCstep::GetCerAngle() { return thetaCer;}               

Double_t LMCstep::GetStepLength() { 
  Double_t L2 = pow(InitPoint.X()-EndPoint.X(),2.) + pow(InitPoint.Y()-EndPoint.Y(),2.) + pow(InitPoint.Z()-EndPoint.Z(),2.);
  return sqrt(L2);
}

void LMCstep::Dump() { 
  cout << "[LMCstep::Dump] "
       << "STEP from : " << InitPoint.X() << ", " << InitPoint.Y() << ", " << InitPoint.Z() 
       << " ->>> TO ->>>> " 
       << EndPoint.X() << ", " << EndPoint.Y() << ", " << EndPoint.Z() << endl;
  if (CurrentNode)     cout << "               NODE = " << CurrentNode->GetName() << flush;
  if (CurrentMaterial) cout << "  | MATERIAL = " << CurrentMaterial->GetName() << endl;
  cout << "               Energy initial=" << Energy_i << " | Energy lost=" << Energy_lost << endl;  
  cout << "               StepLength (cm)= " << GetStepLength() << " | NPhotonsCer = " << NPhotonsCer 
       << " | NPhotonsSci = " << NPhotonsSci << endl;

  if(NPhotonsSci>0 || NPhotonsCer>0){
    cout << "Particles in each step..." << endl;
  
    cout.width(6); cout<<"Pdg";
    cout.width(10); cout<<"Energy";
    cout.width(15); cout<<"P()";
    cout.width(10); cout<<"x";
    cout.width(10); cout<<"y";
    cout.width(10); cout<<"z";
    cout.width(15); cout<<"px";
    cout.width(15); cout<<"py";
    cout.width(15); cout<<"pz";  
    cout<<endl;
    int flag=0;
    for(int j=0;j<vparticles.size();j++){
      if(flag>=5) continue;
    
      cout.width(6); cout<<vparticles[j]->GetPdgCode();
      cout.width(10); cout<<vparticles[j]->Energy();
      cout.width(15); cout<<vparticles[j]->P();
      cout.width(10); cout<<vparticles[j]->Vx();
      cout.width(10); cout<<vparticles[j]->Vy();
      cout.width(10); cout<<vparticles[j]->Vz();
      cout.width(15); cout<<vparticles[j]->Px();
      cout.width(15); cout<<vparticles[j]->Py();
      cout.width(15); cout<<vparticles[j]->Pz();    
      cout<<endl;
      flag++;
  
      //getchar();
    }
  }


}               
