//C
#include "math.h"
#include <iostream>
using namespace std;

//ROOT
#include "TH1.h"
#include "TF1.h"
#include "TRandom3.h"

#include "LMCuserData.h"

/////////////////////////////////////////////////////////////////////////////////////
LMCuserData::LMCuserData() {
  //lambda limits
  Double_t xlow = 200.;
  Double_t xup = 700.;
  Int_t nbins = 500; 

  //random
  rand = new TRandom3(0);
  cout << "[LMCuserData::LMCuserData] random initialized..." << endl;

  //cerenkov spectrum
  CerSpectrum = new TF1("f1","1/(x*x)",100.,800.); //cerenkov spectrum
  cout << "[LMCuserData::LMCuserData] cerenkov spectrum made..." << endl;

  //xp2020 quantum eff
  XP2020eff = new TH1F("hXP2020DetEff","hXP2020DetEff", nbins, xlow, xup);
  Double_t w = xlow;
  Double_t sl = (xup-xlow)/nbins;
  for (Int_t i=0; i<nbins; i++) {
    Float_t eff = (float)SetXP2020DetEff(w);
    if ( w > 250. && w < 640. && eff > 0.) {
      XP2020eff->Fill(w,eff);
    } else {
      XP2020eff->Fill(w,0.);
    }
    w+=sl;
  }
  cout << "[LMCuserData::LMCuserData] XP2020 quantum eff init..." << endl;

  //water ref index
  WaterRefIndex = new TH1F("hWaterRefIndex","hWaterRefIndex", nbins, xlow, xup);
  w = xlow;
  sl = (xup-xlow)/nbins;
  for (Int_t i=0; i<nbins; i++) {
    Float_t n = (float)SetWaterRefIndex(w);
    WaterRefIndex->Fill(w,n);
    w+=sl;
  }
  cout << "[LMCuserData::LMCuserData] water ref index init ..." << endl;

  //get mean det eff for cerenkov spectrum
  EffMean = SetCerDetEffMean(200.,700.);
  cout << "[LMCuserData::LMCuserData] mean detection eff with cerenkov spectrum = " << EffMean << endl;
}

LMCuserData::~LMCuserData() {
  delete CerSpectrum;
  delete rand;
  delete XP2020eff;
  delete WaterRefIndex;
}

Double_t LMCuserData::SetWaterRefIndex(Double_t wl) {
  wl *= 1.E3; //convert from [nm] to [mum]
  const Double_t B[] = {0.5684027565, 0.1726177391, 0.02086189578, 0.1130748688};
  const Double_t C[] = {5.101829712E-3, 1.821153936E-2, 2.620722293E-2, 1.069792721E1};
  Double_t n2 =0.;
  n2 += 1.;
  for (int i=0; i<4; i++) {
    n2 += B[i]*pow(wl,2.)/(pow(wl,2.)-C[i]);
  }
  return sqrt(n2);
}

TH1F* LMCuserData::GetWaterRefIndex() {return WaterRefIndex;}


Double_t LMCuserData::SetXP2020DetEff(Double_t wl) {
  //cathode sensitivity (mA/W)
  const Double_t A[] = {2916.00764, -36.79515, 0.17202, -3.71802E-4, 3.75999E-7, -1.43791E-10};
  Double_t sen  = 0.;
  for (int i=0; i<6; i++) {
    sen += A[i]*pow(wl,i);
  }
  Double_t eff = sen * 1.24 / wl; 
  return eff; //because it is a percent value
}

TH1F* LMCuserData::GetXP2020DetEff() {return XP2020eff;}

Double_t LMCuserData::SetCerDetEffMean(Double_t lmin, Double_t lmax) {
  Double_t effmean = 0.;

  Int_t N = 10000; //number of photons to
  Int_t Ndet = 0;
  Int_t ic = 0;
  do {
    Double_t rw = CerSpectrum->GetRandom();
    if (rw <lmax && rw >lmin) {
      ic++;
      if (rand->Rndm() < SetXP2020DetEff(rw)) {Ndet++;}
    }
  } while (ic<N);
  effmean = (Double_t)Ndet/N;
  cout << "[LMCuserData::GetCerDetEffMean] effmean = " << effmean << " lambda=[" << lmin << "," << lmax << "]" << endl;
  return effmean;
}

Double_t LMCuserData::GetCerDetEffMean() {return EffMean;}
