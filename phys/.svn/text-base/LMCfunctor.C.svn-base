//============================================
//
//  Functions Repository
//  authors: LB & MO
//
//===========================================

//C++
#include <math.h>
#include <string>

// ROOT
#include "TF1.h"
#include <TMath.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TTree.h>
#include <TFile.h>

//OUR
#include "LMCfunctor.h"
//#include "LMCconstants.h"

using namespace std;
//using namespace LMCconstants;



LMCfunctor* LMCfunctor::pInstance = NULL;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
LMCfunctor::LMCfunctor() {
  fBetheBloch = new TF1("BetheBloch",this,&LMCfunctor::BetheBloch,.2,10.,5,"LMCfunctor","BetheBloch");
  fCerenkovSpec = new TF1("CerenkovSpec",this,&LMCfunctor::CerenkovSpec,250.,650.,3,"LMCfunctor","CerenkovSpec");
  fNPhotonsCerenkov = new TF1("NPhotonsCerenkov",this,&LMCfunctor::NPhotonsCerenkov,.2,10.,2,"LMCfunctor","NPhotonsCerenkov");
  fEmissionSpectrumSci = EmissionSpectrumSci();
  
  fQuantumEffR580      = QuantumEffR580();
  fQuantumEffXP2020    = QuantumEffXP2020();
  
  fPhotonAbsProb = new TF1("PhotonAbsortionProb","(3.36248e-11)*(x**3) - (1.59971e-08)*(x**2) - (2.63421e-06)*(x) + 1.54795e-03",200,700);
  fFresnelRefParCoef = new TF1("FresnelRefParCoef",this,&LMCfunctor::FresnelRefParCoef,0.,90.,2,"LMCfunctor","FresnelRefParCoef"); //var=thi (deg); pars=n1,n2
  fFresnelRefPerpCoef = new TF1("FresnelRefPerpCoef",this,&LMCfunctor::FresnelRefPerpCoef,0.,90.,2,"LMCfunctor","FresnelRefPerpCoef"); //var=thi (deg); pars=n1,n2
  fReflectance = new TF1("Reflectance",this,&LMCfunctor::Reflectance,0.,90.,2,"LMCfunctor","Reflectance"); //var=thi (deg); pars=n1,n2
  fExponentialDistribution = new TF1("ExponentialDistribution",this,&LMCfunctor::ExponentialDistribution,0.,1000.,1,"LMCfunctor","ExponentialDistribution");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LMCfunctor::Clear() {
  delete fBetheBloch;
  delete fCerenkovSpec;
  delete fNPhotonsCerenkov;
  delete fEmissionSpectrumSci;
  delete fQuantumEffR580;
  delete fQuantumEffXP2020;
  delete fPhotonAbsProb;
  delete fFresnelRefParCoef;
  delete fFresnelRefPerpCoef;
  delete fReflectance;
  delete fExponentialDistribution;
  
}

//////////////////////////////////////////////////////
////////////// functions a la ROOT ///////////////////
//////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::BetheBloch(double *x, double *p) {
  
  //material
  Double_t Zmat = 0.; 
  Double_t Amat = 1.;
  Double_t Dmat = 1.;//g/cm3
  Double_t X0   = 1.;
  //particle
  Double_t mass = 1.;//GeV
  if (p) {
    Zmat = p[0]; 
    Amat = p[1];
    Dmat = p[2];
    X0   = p[3];
    mass = p[4];
    int size = sizeof(p)/sizeof(p[0]);
  }
  Double_t ene = x[0];//step energy in GeV 



  // general comment:
  // we admit that all the variables are in GeV
  const Double_t c      = 299792458.0;                      // m/s
  const Double_t e_m_SI =  9.10938215*TMath::Power(10,-31); // electron mass in Kg
  const Double_t e_m    = 0.510998E-3;                      // GeV/c^2

  //particle velocity
  Double_t mom = TMath::Sqrt( TMath::Power(ene,2.) -TMath::Power(mass,2.) ); //step momentum 
  Double_t vel = c*mom/ene;
  Double_t gamma = ene/mass;
  Double_t beta = mom/ene;
  Double_t gammabeta = mom/mass;
  //compute ionization potential and density correction factor
  Double_t I, delta, X = TMath::Log(gamma*beta);
  //ioniz pot
  if (Zmat<13) I = 12*Zmat +7; // eV
  else I = 9.76*Zmat + 58.8*TMath::Power(Zmat,-0.19); // eV
  I *= 1.E-9;// conversion to GeV
  //density corr
  if (X<X0) delta = 0;
  else delta = 4.6052*X0; //this can be more precise if X1 is known
  //Compute Tmax (heavy particles approximation
  Double_t Tmax = (2.*e_m*gammabeta*gammabeta)/(1.+2.*e_m/mass*sqrt(1.+gammabeta*gammabeta)+pow(e_m,2.)/pow(mass,2.));

  //Compute dEdx
  Double_t dEdx = Dmat*Zmat/Amat*0.307075/pow(beta,2.)*(0.5*TMath::Log( (2.*e_m*pow(gammabeta,2.)*Tmax)/pow(I,2.) ) - pow(beta,2.) - delta/2.);
  dEdx *= 1.E-3; //convert to GeV
  

  return dEdx; //return GeV/cm
  
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::CerenkovSpec(double *x, double *p) {
  
  Double_t n=0, ene=0, mass=1;
  if (p) {
    n    = p[0]; 
    mass = p[1];
    ene  = p[2];
    int size = sizeof(p)/sizeof(p[0]);
  }
  const Double_t c      = 299792458.0;                      // m/s
  const Double_t alpha = 1/137.0359997; //fine structure constant
  Double_t mom = sqrt( pow(ene,2.) - pow(mass,2.) ); //step momentum (take care of units...???)
  Double_t vel = c*mom/ene;
  Double_t gamma = ene/mass;
  Double_t beta = mom/ene;
  Double_t costhetac = 1./beta/n; 
  
  //Cerenkov energy lost
  Double_t lambda = x[0];
  Double_t CerenkovSpec = (2*M_PI*alpha*(1.-pow(costhetac,2.)))/(pow(lambda,2.)); //in /nm^2
  
  
    
  return CerenkovSpec;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::NPhotonsCerenkov(double *x, double *p) {

  Double_t mass = 1.;
  Double_t n = 0;
  if (p) {
    n = p[0]; 
    mass = p[1];
    int size = sizeof(p)/sizeof(p[0]);
  }
  Double_t ene = x[0];//step energy in GeV 
  const Double_t c      = 299792458.0;                      // m/s
  const Double_t e_m = 0.510998E-3; //GeV/c^2
  const Double_t h_planck = 4.135667516E-15; //eV.s 
  const Double_t hc = h_planck*c*1.E-2;//eV*cm
  const Double_t alpha = 1/137.0359997; //fine structure constant
  const Double_t lmbdamin = 250; //nm
  const Double_t lmbdamax = 650; //nm
  //particle velocity
  //  Double_t mass = part->GetMass();
  //Double_t ene = Ostep->GetEnergy(); //step energy
  Double_t mom = sqrt( pow(ene,2.) - pow(mass,2.) ); //step momentum (take care of units...???)
  Double_t vel = c*mom/ene;
  Double_t gamma = ene/mass;
  Double_t beta = mom/ene;
 
  // calculate number of photons per unit lenght
  Double_t costhetac = 1./beta/n; 
  if(1./beta/n>1. || 1./beta/n!=1./beta/n)return 0;//No cerenkov cone emmited
  Double_t dNdx = 2 * M_PI * alpha * (1-pow(costhetac,2.)) * (1./lmbdamin - 1./lmbdamax); // per nm
  dNdx *= 1.E7; //per cm

  
  return dNdx;// number of photons per cm
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::ExponentialDistribution(double *x, double *p) {
  //x[0]- distance 
  //p[0]- Interaction probability per unit of distance

  Double_t lambda = 1.;

  if (p) {
    int size = sizeof(p)/sizeof(p[0]);
    lambda = p[0]; 
  }
 
  return lambda*exp(-lambda*x[0]);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::FresnelRefParCoef(double *x, double *p) {
  //x[0] = incident photon angle (deg)
  //p[0] = refractive index n1 (incident medium)
  //p[1] = refractive index n1 (refracted medium)

  Double_t n1 = 1.;
  Double_t n2 = 1.;
  if (p) {
    int size = sizeof(p)/sizeof(p[0]);
    n1 = p[0]; 
    n2 = p[1];
  }
  Double_t thi = TMath::DegToRad()*x[0]; //incident angle in deg
  Double_t tht = TMath::ASin(n1*TMath::Sin(thi)/n2);

  return (n2*TMath::Cos(thi)-n1*TMath::Cos(tht))/(n2*TMath::Cos(thi)+n1*TMath::Cos(tht));
  // return TMath::Tan(thi-tht)/TMath::Tan(thi+tht);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::FresnelRefPerpCoef(double *x, double *p) {
  //x[0] = incident photon angle (deg)
  //p[0] = refractive index n1 (incident medium)
  //p[1] = refractive index n1 (refracted medium)

  Double_t n1 = 1.;
  Double_t n2 = 1.;
  if (p) {
    int size = sizeof(p)/sizeof(p[0]);
    n1 = p[0]; 
    n2 = p[1];
  }
  Double_t thi = TMath::DegToRad()*x[0]; //incident angle in deg
  Double_t tht = TMath::ASin(n1*TMath::Sin(thi)/n2);
  
  return (n1*TMath::Cos(thi)-n2*TMath::Cos(tht))/(n1*TMath::Cos(thi)+n2*TMath::Cos(tht));
  //return TMath::Sin(thi-tht)/TMath::Sin(thi+tht);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double LMCfunctor::Reflectance(double *x, double *p) {
  //x[0] = incident photon angle (deg)
  //p[0] = refractive index n1 (incident medium)
  //p[1] = refractive index n1 (refracted medium)
  //p[2] = alpha angle (angle between the electric field of the incident photon and the normal to the incidence plane) in deg

  Double_t n1 = 1.;
  Double_t n2 = 1.;
  Double_t alpha = 0.;
  if (p) {
    int size = sizeof(p)/sizeof(p[0]);
    n1 = p[0]; 
    n2 = p[1];
    alpha = TMath::DegToRad()*p[2];
  }
  Double_t thid = x[0];
  Double_t thi = TMath::DegToRad()*x[0]; //incident angle in deg
  Double_t tht = TMath::ASin(n1*TMath::Sin(thi)/n2);
  fFresnelRefParCoef->SetParameters(n1,n2);
  fFresnelRefPerpCoef->SetParameters(n1,n2);

  return pow(fFresnelRefParCoef->Eval(thid),2.)*pow(sin(alpha),2.) + pow(fFresnelRefPerpCoef->Eval(thid),2.)*pow(cos(alpha),2.); 
}


/////////////////////////////////////////////////////////
/////////////// data values read to histograms //////////
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TH1D* LMCfunctor::EmissionSpectrumSci(){
  //======================================
  //
  //    Emission Spectrum for
  //    Bicron BC-480
  //    Source : Document BICRON
  //
  //======================================
    
  Double_t lambda=0, lightout=0;
  
    
  TTree *Lambda = new TTree("Lambda", "");
  Lambda->ReadFile("phys/lambda.dat","lambda/D:lightout/D");
  Lambda->SetBranchAddress("lambda",&lambda);
  Lambda->SetBranchAddress("lightout",&lightout);
  
  Int_t ent = Lambda->GetEntries();
  
  const int max = ent;
  Double_t LAMBDA[max], LIGHT[max];
  
  TH1D *hlambda = new TH1D ("hlambda","",160, 360., 520.);
  
  for(int i=0; i<ent; i++){
    Lambda->GetEntry(i);    
    LAMBDA[i] = lambda;
    LIGHT[i]  = lightout;
  }
  
  TGraph *glambda = new TGraph (max, LAMBDA, LIGHT);
  
  Double_t light=0;
  for (int i=360; i<520; i++){
      light = glambda->Eval(i);
      hlambda->Fill((i+0.5),light);
  }
  
  return hlambda;
  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TH1D* LMCfunctor::QuantumEffR580(){
  //======================================
  //
  //    Quantum Efficiency for
  //    Hamamatsu R580
  //    Source : Document Hamamatsu
  //
  //======================================
  
  Double_t lambda=0, eff=0;
  
  TTree *Lambda = new TTree("Lambda", "");
  Lambda->ReadFile("phys/QeffR580.dat","lambda/D:eff/D");
  Lambda->SetBranchAddress("lambda",&lambda);
  Lambda->SetBranchAddress("eff",&eff);
  
  Int_t ent = Lambda->GetEntries();
  
  const int max = ent;
  Double_t LAMBDA[max], LIGHT[max];
    
  TH1D *hQeff1 = new TH1D ("hQeff1","", 400, 290., 690.);
  
  for(int i=0; i<ent; i++){
    Lambda->GetEntry(i);    
    LAMBDA[i] = lambda;
    LIGHT[i]  = eff;
  }
  
  TGraph *gQeff = new TGraph (max, LAMBDA, LIGHT);
  
  Double_t qeff=0;
  for (int i=290; i<690; i++){
      qeff = gQeff->Eval(i);
      hQeff1->Fill((i+0.5),qeff);
  }
  
  return hQeff1;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
TH1D* LMCfunctor::QuantumEffXP2020(){
  //======================================
  //
  //    Quantum Efficiency for
  //    Philips XP2020
  //    Source : Document Philips
  //
  //======================================
  const Int_t M = 61;
  Double_t lambda[M] = { 300,  310,  320,  330,  340,  350,  360,  370,  380,  390,  
			 400,  410,  420,  430,  440,  450,  460,  470,  480,  490,  
			 500,  510,  520,  530,  540,  550,  560,  570,  580,  590,  
			 600,  610,  620,  630,  640,  650,  660,  670,  680,  690,  
			 700,  710,  720,  730,  740,  750,  760,  770,  780,  790,  
			 800,  820,  840,  860,  880,  900,  920,  940,  960,  980,  
			 1000 };
  Double_t eff[M] = { 0.1364,0.1600,0.1938,0.2255,0.2553,0.2657,0.2687,0.2681,0.2741,0.2703,
		      0.2666,0.2601,0.2510,0.2393,0.2255,0.2149,0.2049,0.1952,0.1757,0.1645,
		      0.1538,0.1435,0.1312,0.1170,0.1033,0.0879,0.0775,0.0653,0.0470,0.0378,
		      0.0269,0.0224,0.0180,0.0118,0.0078,0.0055,0.0038,0.0024,0.0013,0.0009,
		      0.0005,0.0003,0.0002,0.0001, 0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
		      0.0 ,  0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
		      0.0};
  

  TGraph *gQeff = new TGraph (M, lambda, eff);
  TH1D *hQeff   = new TH1D   ("hQeff","", 700, 300., 1000.);

  Double_t qeff=0;
  for (int i=300; i<1000; i++)
    {
      qeff = gQeff->Eval(i);
      hQeff->Fill((i+0.5),qeff);
    }
  
  return hQeff;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//===================================================================================
//Will be used to calculate the distance covered by a photon inside a certain volume
//INPUT PARAMS: 
//p -> prob of photon absorption in 1 cm 
//N -> Number of steps (each one = 1cm) before being absorbed
//OUTPUT:
//The function returns the prob that a photon walks N steps before being absorbed
//====================================================================================
TH1D* LMCfunctor::GetGeometricDistribution(double p){

  TH1D *GeomD   = new TH1D   ("","", 100, 0., 100.);

  for (int i=0; i<100; i++)
    {
      GeomD->Fill((i+0.5),(p)*pow(1-p,i));
    }
  
  return GeomD;

}
