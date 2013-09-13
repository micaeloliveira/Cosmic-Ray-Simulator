//====================================
//
//  May 2012, Great Improvements 
//  L. Batalha & M. Oliveira
//  (FB: Presuncao e agua benta cada um toma a que quer...)
//====================================

//C++
#include <iostream>
#include <math.h>
#include <string>

// ROOT
#include <TMath.h>
#include <TParticle.h>
#include <TVector3.h>
#include <TF1.h>
#include <TGeoManager.h>
#include <TRandom.h>
#include <TH1D.h>



// MY
#include "LMCgeomN.h"
#include "LMCparticle.h"
#include "LMCpropagator.h"
//#include "LMCpropMuon.h"
#include "LMCstep.h"
#include "LMCcerRadiator.h"
#include "LMCfunctor.h"
#include "LMCconstants.h"
using namespace std;
//using namespace LMCconstants;

///////////////////////////////////////////////////////////////////////////////////////
LMCpropagator::LMCpropagator(TGeoManager *g) {
  geom       = g;
  part       = NULL;
  DebugLevel = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
LMCpropagator::~LMCpropagator() {}

///////////////////////////////////////////////////////////////////////////////////////xo
void LMCpropagator::SetParticle(TParticle *p) {
  //reset geom manager
  geom->ResetState();
  //particle pointer
  part = p;
  //set init point on geometry
  Double_t vtx[3] = {part->Vx(), part->Vy(), part->Vz()};
  geom->SetCurrentPoint(vtx);
 
  //set direction
  Double_t D[3] = {part->Px()/part->P(), part->Py()/part->P(), part->Pz()/part->P()};  
  geom->SetCurrentDirection(D);  
  
  if(DebugLevel > 0){ 
    //printout  
    const Double_t *a = geom->GetCurrentPoint();
    cout << "[LMCpropagator::Setparticle] particle direction = ( " << D[0] << " , " <<  D[1] << " , " <<  D[2] << " )"<< endl;
    cout << "[LMCpropagator::Setparticle] particle Vtx = ( " << vtx[0] << "," << vtx[1] << "," << vtx[2] << " )" << endl;
    cout << "Current point = ( " << a[0] << "," << a[1] << "," << a[2] << " )" << endl;
  }

}

///////////////////////////////////////////////////////////////////////////////////////
TParticle* LMCpropagator::GetParticle() {return part;}

///////////////////////////////////////////////////////////////////////////////////////
vector<LMCstep*> LMCpropagator::Follow() {
  //this method follows particle from boundary to boundary; a list of steps is made 

  //follow particle
  if(DebugLevel > 0){cout << "[LMCpropagator::Follow] tracking new particle..." << endl;}

  //create vector of steps
  vector<LMCstep*> vs;

  //next boundary and step in
  Double_t snext;
  TGeoNode *node;
  TGeoMaterial *mat;
  TGeoVolume *vol;

  //1st point
  LMCstep *Jstep = new LMCstep();
  const Double_t *pos = geom->GetCurrentPoint();
  Jstep->SetInitPoint(TVector3(pos));

  while ( geom->FindNextBoundaryAndStep() ) {
    //get current point after step
    snext = geom->GetStep(); //get which step distance was done
    //current node
    node = geom->GetCurrentNode();
    Jstep->SetCurrentNode(node);
    //material
    mat = geom->GetCurrentVolume()->GetMaterial();
    Jstep->SetCurrentMaterial(mat);
    //store end point on step object
    pos = geom->GetCurrentPoint();
    Jstep->SetEndPoint(TVector3(pos));
    //output
    Jstep->Dump();
    //add step to vector
    vs.push_back(Jstep);
    //next step object and init point
    Jstep = new LMCstep();
    Jstep->SetInitPoint(TVector3(pos));
}

  return vs;
}

///////////////////////////////////////////////////////////////////////////////////////xo
TGeoNode*       LMCpropagator::GetCurrentNode()    {return geom->GetCurrentNode();}
Int_t           LMCpropagator::GetCurrentNodeId()  {return geom->GetCurrentNodeId();}
const char*     LMCpropagator::GetCurrentNodeName(){return geom->GetCurrentNode()->GetName();}
TGeoVolume*     LMCpropagator::GetCurrentVolume()  {return geom->GetCurrentVolume();}
TGeoMaterial*   LMCpropagator::GetCurrentMaterial(){return geom->GetCurrentVolume()->GetMaterial();}
const Double_t* LMCpropagator::GetCurrentPoint()   {return geom->GetCurrentPoint();}
const Double_t* LMCpropagator::GetCurrentDir()     {return geom->GetCurrentDirection();}
Double_t        LMCpropagator::GetCurrentDensity() {return geom->GetCurrentNode()->GetMedium()->GetMaterial()->GetDensity();}
Bool_t          LMCpropagator::IsEntering()        {return geom->IsEntering();}


///////////////////////////////////////////////////////////////////////////////////////
TGeoNode* LMCpropagator::GetNextBoundaryStep(Double_t& snext) {
  TGeoNode *node = geom->FindNextBoundary();
  snext          = geom->GetStep();
  return node;
}

///////////////////////////////////////////////////////////////////////////////////////
LMCstep* LMCpropagator::DoStep(Double_t s) {

  //create step object
  LMCstep *Jstep = new LMCstep();

  //store init point
  const Double_t *pos;
  pos = geom->GetCurrentPoint();
  Jstep->SetInitPoint(TVector3(pos));

  //do step
  geom->SetStep(s);
  geom->Step(kTRUE, kTRUE);

  //store end point
  pos = geom->GetCurrentPoint();
  Jstep->SetEndPoint(TVector3(pos));

  //return step
  return Jstep;
}

///////////////////////////////////////////////////////////////////////////////////////
LMCstep* LMCpropagator::CrossNextBoundary() {

  //create step object
  LMCstep *Jstep = new LMCstep();
  //store init point
  const Double_t *pos;
  pos = geom->GetCurrentPoint();
  Jstep->SetInitPoint(TVector3(pos));

  //do step and cross
  TGeoNode *no = geom->FindNextBoundaryAndStep(); 

  //store end point
  pos = geom->GetCurrentPoint();
  Jstep->SetEndPoint(TVector3(pos));

  //return step
  return Jstep;
}

///////////////////////////////////////////////////////////////////////////////////////
const Double_t* LMCpropagator::GetNormalDir() {
  return geom->FindNormal();
}

//=====================================================================================
// Description: Setting Output Debug Level for this class
// Variables  : iDL = 0 -> No Debug info
//              iDL = 1 -> Some debug info
//=====================================================================================
void LMCpropagator::SetDebugLevel(int iDL){DebugLevel = iDL;}  

////////////////////////////////////////////////////////////////////////////////////////
void LMCpropagator::SetPhysProcesses(string snode, vector<string> vint) {mPhys[snode] = vint;}

////////////////////////////////////////////////////////////////////////////////////////
void LMCpropagator::DumpPhysProcesses() {
  for ( itmPhys=mPhys.begin() ; itmPhys != mPhys.end() ; itmPhys++ ) {
    cout << itmPhys->first << " => " << flush;
    for ( uint i=0 ; i<itmPhys->second.size(); i++) {
      cout << " " << itmPhys->second[i] << flush;
    }
    cout << endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
// propagate particle along detector
vector<LMCstep*> LMCpropagator::Propagate() {

  vector<LMCstep*> vstep = vector<LMCstep*>();
 
  ///////////////////////////////////////////// propagate particle

  //print
  cout << "[LMCpropagator::Propagate] ========================================================= " << endl;
  cout << "particle to propagate: pdgcode=" << part->GetPdgCode() 
       << " | mass=" << part->GetMass() 
       << " | mom=" << part->Pt() << " , " << part->Px() << " , " << part->Pz() << endl; 
  const Double_t *a = geom->GetCurrentPoint();
  cout << "Current point = ( " << a[0] << "," << a[1] << "," << a[2] << " )" << endl;
  cout << "Current Material=" << geom->SearchNode()->GetMedium()->GetMaterial()->GetName() << endl;

  //check if particle is outside detector
  if(geom->IsOutside()){
    cout << "---> PARTICLE is OUSIDE DETECTOR!!!" << endl;
    return vstep;
  } 

  /////////////////// optical photon
  if( part->GetPdgCode() == 22){
    vstep= PropOpticalPhoton();
  } else {
  //////////////////// all other particles
    vstep=PropParticle();
  }

  return vstep;

}

/////////////////////////////////////////////////////////////////////////////////////// USER
LMCstep* LMCpropagator::DoStepUser(Double_t s, Double_t E) {

  /*
    TParticle* p = GetParticle();
    cout << p->GetPdgCode() << endl;
    string st;
    st = p->GetName();
    cout << st  << endl;
    getchar();
  */


  //create step
  LMCstep *Ostep = new LMCstep();
  Ostep->SetEnergy(E); //set particle energy at beginning  of step
  //store init point
  const Double_t *pos;
  pos = geom->GetCurrentPoint();
  Ostep->SetInitPoint(TVector3(pos));
  //set current  node, medium and material
  Ostep->SetCurrentNode(geom->GetCurrentNode());
  Ostep->SetCurrentMedium(geom->GetCurrentVolume()->GetMedium());
  Ostep->SetCurrentMaterial(geom->GetCurrentVolume()->GetMaterial());
  
  //  string str ("Vacuum");
  // if(!str.compare(geom->GetCurrentVolume()->GetMedium()))return 





  //Checks which physical processes are active
  string nodename;
  TGeoNode *currentnode;
  currentnode = geom->GetCurrentNode();
  nodename = currentnode->GetName(); //get current node
  itmPhys = mPhys.find(nodename);                    
  vector<string> vi = itmPhys->second;
  bool sci=0;
  bool cer=0;
  bool dEdx=0;
  for (uint i=0;i<vi.size(); i++) {
    if(vi[i]== "SCI")sci=true; 
    if(vi[i]== "CER")cer=true;
    if(vi[i]== "dEdx")dEdx=true;
  }



  //do step
  geom->SetStep(s);
  geom->Step(kTRUE, kTRUE);
  //store end point
  pos = geom->GetCurrentPoint();
  Ostep->SetEndPoint(TVector3(pos));
  Double_t Elost_ioniz=0.,Elost_cer=0.;
  Int_t Npho_cer=0,Npho_sci=0;
  
  //If dEdx is activated calculate energy losses
  if(dEdx){
    Elost_ioniz = GetdEdx(Ostep);
    // cout << E << "           "  << Elost_ioniz << "    " << endl;
    //getchar();

    //cout << E << "           "  << Elost_ioniz << "    " << endl;
    //getchar();
    //in case the energy losses are greater than ene
    if (Elost_ioniz!=Elost_ioniz || E<Elost_ioniz) {
      //cout << "AAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
     
      //cout << Elost_ioniz << endl;
      Elost_ioniz = E;
      // cout << Elost_ioniz << endl;
      //getchar();
      Ostep->SetEnergyLostIoniz(Elost_ioniz);
      if(sci){
	Npho_sci  = GetNPhotonsSci(Ostep);
	Ostep->SetNPhotonsSci(Npho_sci); 
      }
      Ostep->SetEnergyLostCerenk(0);
      Ostep->SetNPhotonsCer(0);
      
      Ostep->SetEnergyLost(Elost_ioniz);

      Ostep->SetNewParticles();

      return Ostep;
    }
    
    Ostep->SetEnergyLostIoniz(Elost_ioniz);
    
    //If SCI is activated calculate energy losses and number of photons
    if(sci){
      Npho_sci  = GetNPhotonsSci(Ostep);
      Ostep->SetNPhotonsSci(Npho_sci); 
    }
    
  }
  
  //If CER is activated calculate energy losses and number of photons
  if(cer){
    Elost_cer = GetdEdxCer(Ostep);
   

    if (Elost_cer!=Elost_cer || E<Elost_cer) {
      Elost_cer = E;
    }
    
    Ostep->SetEnergyLostCerenk(Elost_cer);
    Npho_cer  = GetNPhotonsCer(Ostep);     
    Ostep->SetNPhotonsCer(Npho_cer);
    
    //comput cerenkov angle and particle velocity
    Double_t mass = part->GetMass();
    Double_t ene = Ostep->GetEnergy(); //step energy
    Double_t mom = sqrt( pow(ene,2.) - pow(mass,2.) ); //step momentum (take care of units...???)
    Double_t beta = mom/ene;
    Double_t n = 0;
    if(Ostep->GetCurrentMaterial()->GetCerenkovProperties()){
      LMCcerRadiator *cerrad = (LMCcerRadiator*)(Ostep->GetCurrentMaterial()->GetCerenkovProperties());
      n = cerrad->GetRefIndex(370.); //for wavelength of maximum det eff
    }

    Double_t costhetac = 1./beta/n; 
    Ostep->SetCerAngle(acos(costhetac));
  }
  
  //After all physical processes the parameters are assigned
  Ostep->SetEnergyLost(Elost_ioniz+Elost_cer);

  Ostep->SetNewParticles();


  return Ostep;
}

/////////////////////////////////////////////////////////////////////////////////////// USER
Double_t LMCpropagator::GetdEdx(LMCstep *Ostep) {
 
  TF1* fBB = LMCfunctor::Instance()->GetBetheBloch();
 
  //material 
  Double_t Zmat = Ostep->GetCurrentMaterial()->GetZ();
  Double_t Amat = Ostep->GetCurrentMaterial()->GetA();
  Double_t Dmat = Ostep->GetCurrentMaterial()->GetDensity();
  Double_t X0 = Ostep->GetCurrentMaterial()->GetRadLen();
 
  //if(DebugLevel > 0){cout << "[LMCpropagator::GetdEdx] Zmat=" << Zmat << " Amat=" << Amat << " Dmat=" << Dmat << endl;}
  //particle velocity
  Double_t mass = part->GetMass();
  Double_t ene = Ostep->GetEnergy(); //step energy
  
  fBB->SetParameter(0,Zmat);
  fBB->SetParameter(1,Amat);
  fBB->SetParameter(2,Dmat);
  fBB->SetParameter(3,X0);
  fBB->SetParameter(4,mass);
  
  Double_t dEdx =  fBB->Eval(ene);
  
  return dEdx*Ostep->GetStepLength(); //return GeV
}

/////////////////////////////////////////////////////////////////////////////////////// USER
Int_t LMCpropagator::GetNPhotonsSci(LMCstep *Ostep) {
  
  /*
    Double_t Zmat = Ostep->GetCurrentMaterial()->GetZ();
    // Double_t I= 16.*pow(Zmat,0.9)*1.E-9; // in Gev
    Double_t I;
    if (Zmat<13) I = 12*Zmat +7; // eV
    else I = 9.76*Zmat + 58.8*TMath::Power(Zmat,-0.19); // eV
    I *= 1.E-9;// conversion to GeV
  */
  Double_t dEdxIoniz = Ostep->GetEnergyLostIoniz();
  
  Double_t I = 100*1.E-09;//GeV
  Double_t Nmean = dEdxIoniz/I; //average number of Sci photons 
  Int_t Nphotons =0;
  
  //fluctuation of the Number of Photons
  //Poisson - low number of photons
  if(Nmean < 10.){
    Nphotons = gRandom->Poisson(Nmean);
  }
  //Gaussian
  else {
    Nphotons = static_cast<int>(gRandom->Gaus(Nmean,sqrt(Nmean)));
  }

  return Nphotons;
}
/////////////////////////////////////////////////////////////////////////////////////// USER
Double_t LMCpropagator::GetdEdxCer(LMCstep *Ostep) {
  
  TF1* fC =LMCfunctor::Instance()->GetCerenkovSpec();
  
  //material 
  Double_t n = 0;
  
  if(Ostep->GetCurrentMaterial()->GetCerenkovProperties()){
    LMCcerRadiator *cerrad = (LMCcerRadiator*)(Ostep->GetCurrentMaterial()->GetCerenkovProperties());
    n = cerrad->GetRefIndex(370.); //for wavelength of maximum det eff
  }
  
  //particle
  Double_t mass = part->GetMass();
  Double_t ene  = Ostep->GetEnergy(); //step energy
  Double_t mom = sqrt( pow(ene,2.) - pow(mass,2.) ); //step momentum (take care of units...???)
  Double_t beta = mom/ene;
   
  if(1./beta/n>1. || 1./beta/n!=1./beta/n) return 0;//No cerenkov cone emmited; no Cerenkov Properties
  
  fC->SetParameter(0,n);
  fC->SetParameter(1,mass);
  fC->SetParameter(2,ene);
  
  Double_t lambdamin = 250.;
  Double_t lambdamax = 650.;
  Double_t averagelambda =  fC->Mean(lambdamin,lambdamax);
  
  
  return GetNPhotonsCer(Ostep)*LMCconstants::hc()/(averagelambda*1.E-11)*(1.E-9);//energy lostby Cerenkov radiation in GeV

    
}
/////////////////////////////////////////////////////////////////////////////////////// USER
Int_t LMCpropagator::GetNPhotonsCer(LMCstep *Ostep) {
 
  TF1* fC =LMCfunctor::Instance()->GetNPhotonsCerenkov();
 
  
  //material 
  Double_t n = 0;
  
  if(Ostep->GetCurrentMaterial()->GetCerenkovProperties()){
    LMCcerRadiator *cerrad = (LMCcerRadiator*)(Ostep->GetCurrentMaterial()->GetCerenkovProperties());
    n = cerrad->GetRefIndex(370.); //for wavelength of maximum det eff
  }
  if(n==0)return 0;//if refractive index equals to zero (trouble returning the refractive index of PMT window, returns 0 !) 

  //particle
  Double_t mass = part->GetMass();
  Double_t ene = Ostep->GetEnergy(); //step energy
  
  fC->SetParameter(0,n);
  fC->SetParameter(1,mass);
  
  Double_t dNdx = fC->Eval(ene);//Number of cer photons per cm
  
  Double_t Nmean = dNdx*Ostep->GetStepLength(); //average number of Cer photons 
  Int_t Nphotons =0;
  
  //fluctuation of the Number of Photons
  //Poisson - low number of photons
  if(Nmean < 10.){
    Nphotons = gRandom->Poisson(Nmean);
  }
  //Gaussian
  else {
    Nphotons = static_cast<int>(gRandom->Gaus(Nmean,sqrt(Nmean)));
  }

  return Nphotons;
}

/////////////////////////////////////////////////////////////////////////////////////// USER
vector<LMCstep*> LMCpropagator::PropOnWaterTank(Int_t flag) {
  // propagate particle inside water tank
  // flag = 0 : bring particle to water tank entrance and do not take into account energy lost before tank
  // flag = 1 : bring particle to water tank entrance and take into account energy lost before tank
  if(DebugLevel > 0){ cout << "[LMCpropagator::PropOnWaterTank] On option (0) implemented..." << endl;}

  //propagate particle till finding water tank
  //stop loop when entering water
 
  vector<LMCstep*> TankSTEPS;   
  for (unsigned int i=0; i< TankSTEPS.size(); i++) {delete TankSTEPS[i];}
  TankSTEPS.clear();

  const Double_t *pos; 
  Double_t        dist=0;
  TGeoNode       *node = geom->GetCurrentNode();
  LMCstep        *step; 
  //............................................................find water material
  /* while(strcmp(GetCurrentMaterial()->GetName(),"Water")){

  node = GetNextBoundaryStep(dist); //get distance to next boundary
  cout << "Next boundary at = " << dist << "cm |" << flush;
  if (node) {
  cout << "   Node=" << node->GetName() 
  << "   Med=" << node->GetMedium()->GetName()
  << "   Mat=" << node->GetMedium()->GetMaterial()->GetName() << flush;
  }

  step = DoStepAndCrossBoundary(); //step in and cross boundary
  pos  = geom->GetCurrentPoint();
  cout << " [after step = " << pos[0] << "," << pos[1] << "," << pos[2] << " ]" << endl;
  AllSTEPS.push_back(step);

  }
  */

  //............................................................Some dummy prints and infos

  pos  = geom->GetCurrentPoint();   //we shall be at the beginning of the tank water
  node = GetNextBoundaryStep(dist); //get distance on water (until exiting tank)
  
  //Get the water material refractive index (example)
  //LMCcerRadiator *cerwater = (LMCcerRadiator*)(GetCurrentMaterial()->GetCerenkovProperties());

  if(DebugLevel > 0){
    cout << " We are suposed to be on beginning of water tank: " << pos[0] << ","  << pos[1] << "," << pos[2] << endl;
    cout << " Distance to tank exit=" << dist << "cm" << endl;
    //if (cerwater) cerwater->Dump();
  }
  

  //............................................................propagate particle on water tank

  if(DebugLevel > 0){cout << "[LMCpropagator::PropOnWaterTank] Propagating muon on water..." << endl;}

  //get particle energy at the tank entrance
  Double_t ene = 0.;
  if (flag==0){ene = sqrt( pow(part->P(),2.) + pow(part->GetMass(),2.) );}

  do {
    //step 1mm on water and store step object
    step = DoStepUser(0.1, ene);
    TankSTEPS.push_back(step);    

    if(DebugLevel > 0){
      cout << "Energy (GeV) = " << ene << endl;
      step->Dump();
    }
    
    //update particle energy
    ene -= step->GetEnergyLost();

    //get new distance to boundary
    node = GetNextBoundaryStep(dist);
    
    if(DebugLevel > 0){cout << " [DISTANCE to next boundary (cm) = " << dist << "]" << endl;}
        
  } while (dist>0.1 && ene>0. );

  return TankSTEPS;

}
/////////////////////////////////////////////////////////////////////////////////////
vector<LMCstep*> LMCpropagator::PropParticle() {
 
  vector<LMCstep*> vstep = vector<LMCstep*>();

  //propagating charged  particle 
  string nodename;
  TGeoNode *currentnode;
  bool PartStop=false;
 

  bool sci=false;
  bool cer=false;

  Double_t ene = sqrt(pow(part->P(),2.)+pow(part->GetMass(),2.)); //get particle energy at the tank entrance in GeV
  Double_t enelost=0.;

  while(geom->FindNextBoundaryAndStep() && !(geom->IsOutside())){
    
    currentnode = geom->GetCurrentNode();
    nodename = currentnode->GetName(); //get current node
    cout << "node [" << nodename << "] " << endl; 
    itmPhys = mPhys.find(nodename);                    
    if (itmPhys == mPhys.end() ) continue; //node not found

    //node found and list phys processes
    vector<string> vi = itmPhys->second;
    cout << "node [" << nodename << "] found on list of detectors! " 
	 << " | Interation processes activated=" << flush;
    for (uint i=0;i<vi.size(); i++) {cout << vi[i] << " " << flush;}
    cout << endl;   

    //get distance to next boundary
    //    const Double_t *pos  = geom->GetCurrentPoint();
    //    cout << " [after step at point= " << pos[0] << "," << pos[1] << "," << pos[2] << " ]" << endl;
    Double_t  dist=0;
    TGeoNode *innode = GetNextBoundaryStep(dist); 
    cout << "NEXT BOUNDARY: distance=" << dist << "cm | nodename=" << innode->GetName() << " | IsEntering? " << geom->IsEntering() << endl; 

  
    //step inside detector
    LMCstep *step =  new LMCstep();
   
   
    do {
      // cout << ene << endl;
      //getchar();
      //step 1mm and store step object
      step = DoStepUser(0.1, ene);
     
      //update particle energy
      enelost = step->GetEnergyLost(); 
      
      ene -= enelost;
      //cout << ene <<"          "  << enelost<< endl;
      //getchar();
      
      if(ene==0){
	cout<<"*** PARTICLE STOPPED  in "<<innode->GetName()<<" ***"<<endl;
	PartStop =true;
      }

      vstep.push_back(step);
      //get new distance to boundary
      innode = GetNextBoundaryStep(dist);


      if(DebugLevel > 0){cout << " [DISTANCE to next boundary (cm) = " << dist << "]" << endl;}
     
    } while (dist>0.1 && ene>0. );
    
  
    if (PartStop) break;
  }
  
  if (!PartStop){
    cout << "---> PARTICLE is OUSIDE DETECTOR!!!" << endl;
  }
  return vstep;

  
}
/////////////////////////////////////////////////////////////////////////////////////
vector<LMCstep*> LMCpropagator::PropOpticalPhoton() {
 
  vector<LMCstep*> vstep = vector<LMCstep*>();

  
  
  const Double_t *a = geom->GetCurrentPoint();
  Double_t lambda =  LMCconstants::hc()/(part->P()*1.E-9)*(1.E-7);//photon lambda in nm
  Double_t AbsProb =   LMCfunctor::Instance()->GetPhotonAbsProb()->Eval(lambda);//photon absorption probability per cm
  //having calculated the probability that a photon is absorbed in 1 cm we need to compute the distance that the photon will cross before being absorbed
  


  TF1* fExpD = LMCfunctor::Instance()->GetExponentialDistribution();
  fExpD->SetParameter(0,AbsProb);
  Double_t Photondist =  fExpD->GetRandom();

  Photondist =1000;
  cout << Photondist << endl;
  //getchar();


  TGeoNode *innode;
  double dist=0;
  
  while(Photondist >0){
    
    
    LMCstep *step =  new LMCstep();
    a = geom->GetCurrentPoint();
    step->SetInitPoint(TVector3(a));
    step->SetCurrentNode(geom->GetCurrentNode());
    step->SetCurrentMedium(geom->GetCurrentVolume()->GetMedium());
    step->SetCurrentMaterial(geom->GetCurrentVolume()->GetMaterial());
    
    //string   nCurrent  = geom->SearchNode()->GetName();
    string   nCurrent  = geom->GetCurrentNode()->GetName();
    cout<<"  - "<<geom->GetCurrentNode()->GetName()<<"   "<<nCurrent<<endl;
   
    //Gets the refractive index of medium 1
    double n1 = -1;
    
    if (step->GetCurrentMaterial()->GetCerenkovProperties()){
      LMCcerRadiator *cerrad1 = (LMCcerRadiator*)(step->GetCurrentMaterial()->GetCerenkovProperties());
      n1 = cerrad1->GetRefIndex(370.); //for wavelength of maximum det eff
    }
    cout<<"n1 = "<<n1<<endl;
    
  
            
  
    //For optical photons we are interested only on the initial position and final position, which are stored in LMCstep element
    
    cout << "Current point [1] = ( " << a[0] << "," << a[1] << "," << a[2] << " )" << endl;
    cout << "Current Material [1]=" << GetCurrentMaterial()->GetName() << endl;
    cout << "Current Node [1]=" << geom->GetCurrentNode()->GetName() << endl;
    
    string s = GetCurrentMaterial()->GetName();
 
    //getchar();
  
    //dist is the distance to the next boundary
    innode = geom->GetCurrentNode();
    innode = GetNextBoundaryStep(dist);
    cout<<"DIST:  "<<dist<<endl;

    geom->FindNextBoundaryAndStep();

    cout << "STEP DONE... "<<endl;

    a = geom->GetCurrentPoint();
    cout << "Current point [2] = ( " << a[0] << "," << a[1] << "," << a[2] << " )" << endl;
    cout << "Current Material [2]=" << GetCurrentMaterial()->GetName() << endl;
    cout << "Current Node [2]=" << geom->GetCurrentNode()->GetName() << endl;
    cout << "......................"<<endl;


    //Gets the refractive index of medium 2
    double n2 = -1;
    
    if (GetCurrentMaterial()->GetCerenkovProperties()){
      LMCcerRadiator *cerrad2 = (LMCcerRadiator*)(GetCurrentMaterial()->GetCerenkovProperties());
      n2 = cerrad2->GetRefIndex(370.); //for wavelength of maximum det eff
    }
    cout<<"N2-------------->"<<n2<<endl;
   

    
    step->SetEndPoint(TVector3(a));
    
    //The step is stocked in the LMCstep vector
    vstep.push_back(step);
    
    if(dist < Photondist){
      
      if(s !="Vacuum"){Photondist = Photondist - dist;}
      cout << "Distance Left:" << Photondist <<endl;
      //after the boundary is found we find the current point direction and the normal vector to the boundary
      TVector3 Normal    = TVector3(geom->FindNormal());
      TVector3 NormalF   = TVector3(geom->FindNormalFast());
      TVector3 Point     = TVector3(geom->GetCurrentPoint());
      TVector3 Direction = TVector3(geom->GetCurrentDirection());
      
      cout <<"Normal:" << Normal.Z()<< endl;
      cout <<"NormalF:" << NormalF.Z()<< endl;
      cout <<"Direction:"<< Direction.Z()<< endl;
    
      //Everytime a step is done the particle goes to the next boundary stepping inside the volume. Then the transmission and diffision coefficients are computed and if the particle is reflected it returns to the previous medium, otherwise it will stay in the same medium.
      
      //retrieve the Efield vector
      TVector3 Efield;
      part->GetPolarisation(Efield);

      cout << "Normal=" << Normal.X() << " | " <<  Normal.Y() << " | " << Normal.Z() << endl;
      cout << "Efield=" << Efield.X() << " | " <<  Efield.Y() << " | " << Efield.Z() << endl;

      int RT = Reflectivity(Normal,Direction,Efield,n1,n2);
      //RT is 0 if the particle is reflected and 1 if the particle is transmited
      //In case RT is 1 and the transmission occurs between two medium with different refractive indices the photon dies
      if(RT==1 && (n1!=n2)){
	//cout <<"PHOTON DIED IN " << nCurrent << endl;
	//return vstep;

      }
    
      cout <<"NormalA:"<< Normal.Z()<< endl;
      cout <<"NormalFA:"<< NormalF.Z()<< endl;
      cout <<"DirectionA:"<< Direction.Z()<< endl;
      
    }
    else{
      cout <<"PHOTON DIED IN " << nCurrent << endl;
      break;
    }
  }
  
  cout << "SAIU" << endl;
  //getchar();
  return vstep;

  
}
/////////////////////////////////////////////////////////////////////////////////////
int LMCpropagator::Reflectivity(TVector3 Normal,TVector3& Direction,TVector3 Efield, double n1, double n2) {
  
  bool Reflection=false;
  
  //according to fresnel laws one of the previous booleans will be true
  //depends on the n's of the two mediums and the angle of incidence of the photon


  /*
  double theta_i =  Normal.Angle(Direction);
  cout <<"ANGULO=" << theta_i << endl;

  //if(Transmission){
  
  TVector3 DirectionT(0,1,0);
  TVector3 NormalT(0,0,1);
  
  //Snell-Decartes law
  double theta_1 =  NormalT.Angle(DirectionT);
  cout << "Angle1=" << theta_1 << endl;
  n1=1.2;
  n2=1.;
  //double theta_2 = TMath::ASin(TMath::Sin(theta_1)*n1/n2);
  double theta_2 = TMath::ASin(TMath::Sin(theta_1)*0.1);
  cout << "Angle2=" << theta_2 << endl;
  TVector3 CrossVector = NormalT.Cross(DirectionT);
  DirectionT.Rotate(theta_2-theta_1, NormalT);
  cout << "DirectionT(" << Direction.X() << " ; " << Direction.Y() << " ; " << Direction.Z() << endl;
  cout << "Angle3=" << NormalT.Angle(DirectionT) << endl;
  //}
  */
  
  Double_t thi = Normal.Angle(Direction);
 
  //Calculation of the Perp and Parallel components of the Efield
  TVector3 Eperp,Epar, vperp_inc_plane;
  vperp_inc_plane = Normal.Cross(Direction);
  if(thi==0.){
    vperp_inc_plane = Direction.Orthogonal();
  }
  Eperp = Proj(Efield, vperp_inc_plane);
  Epar = Efield-Eperp;
  Double_t alpha = Efield.Angle(vperp_inc_plane);//angle between Efield and the vector perpendicular to the incidence plane  

  cout << "====================" << endl;
  cout << "Direction=" << Direction.X() << " | " <<  Direction.Y() << " | " << Direction.Z() << endl;
  cout << "Efield=" << Efield.X() << " | " <<  Efield.Y() << " | " << Efield.Z() << endl;
  cout << "Normal=" << Normal.X() << " | " <<  Normal.Y() << " | " << Normal.Z() << endl;
  cout << "Perp=" << Eperp.X() << " | " <<  Eperp.Y() << " | " << Eperp.Z() << endl;
  cout << TMath::RadToDeg()*thi << " | " << TMath::RadToDeg()*alpha << endl;
  cout << "====================" << endl;

  
  TF1* R =LMCfunctor::Instance()->GetReflectance();
  cout << n1 << "********" << n2 << endl;
  R->SetParameter(0,n1);
  R->SetParameter(1,n2);
  R->SetParameter(2,TMath::RadToDeg()*alpha);
  Double_t Reflectance =  R->Eval(TMath::RadToDeg()*thi);
  cout << "R=" << Reflectance << endl;
 
  
  if(gRandom->Uniform(0.,1.)<Reflectance){
    cout << "[Particle was reflected...]" << endl;
    Reflection=true;
  }
  
  
  //TVector3 t1(0.,1.,2.);
  //TVector3 t2(0.,0.,1.);
  //cout << "(" << Proj(t1,t2).X() << "," << Proj(t1,t2).Y() << "," << Proj(t1,t2).Z() << ")" << endl;
  //getchar();
  

  if(Reflection){
   
    //Change the Efield vector according to fresnel coefficients
    TF1* rpar =LMCfunctor::Instance()->GetFresnelRefParCoef();
    rpar->SetParameter(0,n1);
    rpar->SetParameter(1,n2);
    
    TF1* rperp =LMCfunctor::Instance()->GetFresnelRefPerpCoef();
    rperp->SetParameter(0,n1);
    rperp->SetParameter(1,n2);
    
    //The new components of the Efield are simply the components before the reflection times the corresponding fresnel coefficients
    Eperp=rperp->Eval(thi)*Eperp;
    Epar=rpar->Eval(thi)*Epar;

    //The new polarisation is set
    part->SetPolarisation(Epar+Eperp);

    //Invert propagation direction
    Direction.Rotate(TMath::Pi(),Normal);
    Direction[0] = -1*Direction[0];
    Direction[1] = -1*Direction[1];
    Direction[2] = -1*Direction[2];
    
    Double_t D[3];
    D[0]=Direction.X();
    D[1]=Direction.Y();
    D[2]=Direction.Z();
    geom->SetCurrentDirection(D);
    geom->FindNextBoundaryAndStep();
   
    return 0;
    
  }
  else{
    //If the particle is transmited
    return 1;
  }
    
}

//Projecting v1 onto v2
TVector3  LMCpropagator::Proj(TVector3 v1,TVector3 v2) {
  
  Double_t s = v1.Dot(v2.Unit()); 
  return s*v2;

}
