#include "LMCphysGen.h"

LMCphysGen::LMCphysGen(){

  // Default values for shape functions
  FuncTheta = "Cos2";
  FuncPhi   = "Const";
  FuncP     = "Measured1";
   
  fH.insert(pair<TString,TH1D*>("GenTheta",    new TH1D("GenTheta","GenTheta",100,   0,TMath::Pi())));
  fH.insert(pair<TString,TH1D*>("GenPhi",      new TH1D("GenPhi"  ,"GenPhi"      ,100,-TMath::Pi(),TMath::Pi())));
  fH.insert(pair<TString,TH1D*>("GenP",        new TH1D("GenP"    ,"GenP"        ,100,0,1000)));

}

LMCphysGen::~LMCphysGen(){}

//=====================================================================================
// Description: Get a Muon from pre-defined distributions for its caracteristics
//=====================================================================================
TParticle* LMCphysGen::GenRandomMuon() {

  TF1 *fTheta;
  TF1 *fPhi;
  TF1 *fP;

  // Initializing shape functions
  if     (FuncTheta == "Const")    {fTheta = new TF1("fTheta","1"               , 0,TMath::Pi()/2);}
  else if(FuncTheta == "Cos")      {fTheta = new TF1("fTheta","TMath::Cos(x)"   , 0,TMath::Pi()/2);}
  else if(FuncTheta == "Cos2")     {fTheta = new TF1("fTheta","TMath::Cos(x)**2", 0,TMath::Pi()/2);}

  if     (FuncPhi   == "Const")    {fPhi   = new TF1("fPhi"  , "1",-1*TMath::Pi(),TMath::Pi());}
  
  if     (FuncP     == "Measured1"){fP     = new TF1("fP"    , "1/(x**1.8)",0.1,200);}

  // Assuming spacial diagonal of 100*100*150
  Double_t SpaDiag = 206.155;
  
  // Using defined shape functions to generate to get new random values
  Double_t Theta = fTheta       ->GetRandom(); 
  Double_t Phi   = fPhi         ->GetRandom();
  Double_t P     = fP           ->GetRandom();

  // Filling some debug histograms
  fH["GenTheta"]->Fill(Theta);
  fH["GenPhi"]  ->Fill(Phi);
  fH["GenP"]    ->Fill(P);

  // Calculating P components
  Double_t px =  P*TMath::Sin(Theta)*TMath::Cos(Phi);
  Double_t py =  P*TMath::Sin(Theta)*TMath::Sin(Phi);
  Double_t pz = -P*TMath::Cos(Theta);

  Double_t X     = (RandGen->Rndm()*1000)-500;
  Double_t Y     = (RandGen->Rndm()*1000)-500;

  //Double_t X     = -2*SpaDiag*px+fX->GetRandom();
  //Double_t Y     = -2*SpaDiag*py+fY->GetRandom();
  //Double_t Z     = -2*SpaDiag*pz+fZ->GetRandom();

  Double_t pmom[3] = {px,py,pz};
  Double_t pos[3]  = { X, Y,200};

  TParticle *particle =  new TParticle(13,0,0,0,0,0,pmom[0],pmom[1],pmom[2],0.,pos[0],pos[1],pos[2],0.);

  delete fTheta;
  delete fPhi;
  delete fP;
  //delete fX;
  //delete fY;
  //delete fZ;

  return particle;
  
  
}

///////////////////////////////////////////////////////////////////////////////////////
TParticle* LMCphysGen::GenSingleMuon(Double_t mom, Double_t the, Double_t phi, Double_t x, Double_t y, Double_t z) {
  Double_t px = mom*TMath::Sin(the*TMath::Pi()/180.)*TMath::Cos(phi*TMath::Pi()/180.);
  Double_t py = mom*TMath::Sin(the*TMath::Pi()/180.)*TMath::Sin(phi*TMath::Pi()/180.);
  Double_t pz = mom*TMath::Cos(the*TMath::Pi()/180.);

  Double_t pmom[3] = {px,py,pz};
  Double_t pos[3]  = {x,y,z};

  TParticle *particle =  new TParticle(13,0,0,0,0,0,pmom[0],pmom[1],pmom[2],0.,pos[0],pos[1],pos[2],0.);
  return particle;
}

///////////////////////////////////////////////////////////////////////////////////////
vector<TParticle*> LMCphysGen::GenCerPhotons(TParticle *part, LMCstep *step, Int_t N) {

  const Double_t hbarc = 0.197326960277E-6; //GeV.nm 
  vector <TParticle*> v;
  //rotation matrix to transform vectors from geom -> part
  TRotation rm;
  TVector3 vt(part->Px(), part->Py(), part->Pz());
  rm.RotateX(vt.Theta()); //rotate on X
  rm.RotateZ(vt.Phi()); //rotate on Z
  TVector3 pdir = vt.Unit();
  // rotation matrix from part->geom
  TRotation im = rm.Inverse();
  //generate photons
  Double_t Emin = 2.*TMath::Pi()* hbarc / 200.; //GeV
  Double_t Emax = 2.*TMath::Pi()* hbarc / 700.; //GeV

  TVector3 InitPoint = step->GetInitPoint(); 
  Double_t stepLength = step->GetStepLength();
  for (int i=0; i< N; i++) {
    Double_t thetaCer = step->GetCerAngle();
    Double_t phi = (RandGen->Rndm())*2.*TMath::Pi();  
    TVector3 photonDir(sin(thetaCer)*cos(phi), sin(thetaCer)*sin(phi), cos(thetaCer));
    TVector3 photonDirDet = im*photonDir;                         //transform photon direction from particle to detector frame
    Double_t photonE      = Emin + (RandGen->Rndm())*(Emax-Emin); //cerenkov photon flat on energy (GeV)
    TVector3 photonMomDet = photonE*photonDirDet;                 //on detector frame
    TVector3 GenPoint     = InitPoint + stepLength*(RandGen->Rndm())*pdir;
    v.push_back(new TParticle(22,0,0,0,0,0,photonMomDet.X(),photonMomDet.Y(),photonMomDet.Z(),photonE,GenPoint.X(),GenPoint.Y(),GenPoint.Z(),0));
  }

  return v;

}

void LMCphysGen::setRandGen(TRandom* iRand){RandGen = iRand;}

map<TString,TH1D*> LMCphysGen::GetPlots(){return fH;}
