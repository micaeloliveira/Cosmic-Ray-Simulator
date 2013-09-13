#include <iostream>
#include <string>
#include <map>

//ROOT
#include <TGeoMaterial.h>
#include <TH1F.h>

//MY
#include "LMCmaterials.h"
#include "LMCcerRadiator.h"
#include "LMCuserData.h"

using namespace std;

class TGeoMaterial;

/////////////////////////////////////////////////////////////////////////////////////////////////

LMCmaterials::LMCmaterials() {

  //lambda limits
  Double_t xlow = 200.;
  Double_t xup = 700.;
  Int_t nbins = 500; 

  mMaterials["Hydrogen"]     = new TGeoMaterial("Hydrogen",1.008,1,0.7080000E-01);

  mMaterials["Deuterium"]    = new TGeoMaterial("Deuterium",2.01,1,0.162);

  mMaterials["Helium"]       = new TGeoMaterial("Helium",4,2,0.125);

  mMaterials["Lithium"]      = new TGeoMaterial("Lithium",6.94,3,0.534);

  mMaterials["Beryllium"]    = new TGeoMaterial("Beryllium",9.01,4,1.848);

  mMaterials["Carbon"]       = new TGeoMaterial("Carbon",12.01,6,2.265);

  mMaterials["Nitrogen_liq"] = new TGeoMaterial("Nitrogen_liq",14.01,7,0.808);

  mMaterials["Neon_liq"]     = new TGeoMaterial("Neon_liq",20.18,10,1.207);

  mMaterials["Aluminium"]    = new TGeoMaterial("Aluminium",26.98,13,2.7);

  mMaterials["Iron"]         = new TGeoMaterial("Iron",55.85,26,7.87); 

  mMaterials["Copper"]       = new TGeoMaterial("Copper",63.54,29,8.96);

  mMaterials["Tungsten"]     = new TGeoMaterial("Tungsten",183.85,74,19.3);

  mMaterials["Lead"]         = new TGeoMaterial("Lead",207.19,82,11.35);

  mMaterials["Uranium"]      = new TGeoMaterial("Uranium",238.03,92,18.95);

  mMaterials["Air"]          = new TGeoMaterial("Air",14.61,7,0.1205000E-02);

  mMaterials["Vacuum"]       = new TGeoMaterial("Vacuum",0,0,0);
  itMaterials = mMaterials.find("Vacuum");
  (itMaterials->second)->SetUniqueID(60);
  //Set Ref Index
  TH1F *Vacuumh = new TH1F("hVacuum","hVacuum", nbins, xlow, xup);
  Double_t w = xlow;
  Double_t sl = (xup-xlow)/nbins;
  for (Int_t i=0; i<nbins; i++) {
    Float_t n = 1. ;//The value of the plexiglass ref index
    Vacuumh->Fill(w,n);
    w+=sl;
  }
  //add refractive index to material
  LMCcerRadiator *VacuumRad = new LMCcerRadiator();
  VacuumRad->SetRefIndex(Vacuumh);
  itMaterials->second->SetCerenkovProperties(VacuumRad);
  



  mMaterials["Oxygen_liq"]   = new TGeoMaterial("Oxygen_liq",16,8,1.141);

  mMaterials["Argon"]        = new TGeoMaterial("Argon",39.95,18,0.1620000E-02);        

  mMaterials["Alu_honeycomb"] = new TGeoMaterial("Alu_honeycomb",26.98,13,0.616);       

  mMaterials["Nitrogen_gas"] = new TGeoMaterial("Nitrogen_gas",14.01,7,0.1205000E-02);    

  mMaterials["Scintillator"] = new TGeoMixture("Scintillator",2, 1.03000 );        
  itMaterials = mMaterials.find("Scintillator");
  (itMaterials->second)->SetUniqueID(23);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,12.01,6,0.9154801);
   ((TGeoMixture*)(itMaterials->second))->DefineElement(1,1.008,1,0.8451993E-01);
   //Set Ref Index
   TH1F *Scintillatorh = new TH1F("hScintillator","hScintillator", nbins, xlow, xup);
   w = xlow;
   sl = (xup-xlow)/nbins;
   for (Int_t i=0; i<nbins; i++) {
     Float_t n = 1.49 ;//The value of the plexiglass ref index
     Scintillatorh->Fill(w,n);
     w+=sl;
   }
   //add refractive index to material
   LMCcerRadiator *ScintillatorRad = new LMCcerRadiator();
   ScintillatorRad->SetRefIndex(Scintillatorh);
   itMaterials->second->SetCerenkovProperties(ScintillatorRad);


  mMaterials["Silicon"]  = new TGeoMaterial("Silicon",28.09,14,2.33);    

  mMaterials["Boron"] = new TGeoMaterial("Boron",10.811,5,2.34);          

  mMaterials["Sodium"] = new TGeoMaterial("Sodium",22.99,11,0.971);

  mMaterials["Mylar"] = new TGeoMixture("Mylar",3,   1.39000    );
  itMaterials = mMaterials.find("Mylar");
  (itMaterials->second)->SetUniqueID(27);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,12.01,6,0.624987);	    
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,1.008,1,0.4196415E-01);  
  ((TGeoMixture*)(itMaterials->second))->DefineElement(2,16,8,0.3330489);       

  mMaterials["Neon_Alum"] = new TGeoMaterial("Neon_Alum",20.18,10,2.7);

  mMaterials["Beamline_air"] = new TGeoMaterial("Beamline_air",14.61,7.3,0.1000000E-05); 

  mMaterials["Gold"] = new TGeoMaterial("Gold",197,79,19.5);

  mMaterials["Niobium"] = new TGeoMaterial("Niobium",93,41,8.55);

  mMaterials["Lanthanum"] = new TGeoMaterial("Lanthanum",139,57,6.17);

  mMaterials["Calcium"] = new TGeoMaterial("Calcium",40.08,20,1.55);

  mMaterials["Rohacell"] = new TGeoMixture("Rohacell",4,  0.500000E-01); 
  itMaterials = mMaterials.find("Rohacell");
  (itMaterials->second)->SetUniqueID(39);			   
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,12.01,6,0.7055886);	   
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,1.008,1,0.7402512E-01); 
  ((TGeoMixture*)(itMaterials->second))->DefineElement(2,16,8,0.1175002);	   
  ((TGeoMixture*)(itMaterials->second))->DefineElement(3,14.01,7,0.1028861);     

  mMaterials["Water"] = new TGeoMixture("Water",2,1.00000);
  itMaterials = mMaterials.find("Water");
  (itMaterials->second)->SetUniqueID(40);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,1.00794,1,0.1118984);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,15.9994,8,0.8881017);
  //get water refractive index
  LMCuserData *u = new LMCuserData();
  TH1F *h = u->GetWaterRefIndex();
  //add refractive index to material
  LMCcerRadiator *WaterRad = new LMCcerRadiator();
  WaterRad->SetRefIndex(h);
  itMaterials->second->SetCerenkovProperties(WaterRad);

  mMaterials["Polyethylene"] = new TGeoMixture("Polyethylene",2,  0.935000    );
  itMaterials = mMaterials.find("Polyethylene");
  (itMaterials->second)->SetUniqueID(  42);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,12.01,6,0.856267);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,1.008,1,0.1437331);

  mMaterials["Quartz"] = new TGeoMixture("Quartz",2,   2.65000    );
  itMaterials = mMaterials.find("Quartz");
  (itMaterials->second)->SetUniqueID(50);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,28.09,14,0.467);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,16,8,0.533);    

  mMaterials["Glass"] = new TGeoMixture("Glass",2,   2.32000    );
  itMaterials = mMaterials.find("Glass");
  (itMaterials->second)->SetUniqueID(  51);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,28.09,14,0.4674655);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,16,8,0.5325345);

  mMaterials["PMMA"] = new TGeoMixture("PMMA",3,   1.18000    );
  itMaterials = mMaterials.find("PMMA");
  (itMaterials->second)->SetUniqueID( 52);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(0,12,6,0.6);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(1,1,1,0.8000000E-01);
  ((TGeoMixture*)(itMaterials->second))->DefineElement(2,16,8,0.32);
  //Set Ref Index
  TH1F *PMMAh = new TH1F("hPMMA","hPMMA", nbins, xlow, xup);
  w = xlow;
  sl = (xup-xlow)/nbins;
  for (Int_t i=0; i<nbins; i++) {
    Float_t n = 1.49 ;//The value of the plexiglass ref index
    PMMAh->Fill(w,n);
    w+=sl;
  }
  //add refractive index to material
  LMCcerRadiator *PMMARad = new LMCcerRadiator();
  PMMARad->SetRefIndex(PMMAh);
  itMaterials->second->SetCerenkovProperties(PMMARad);

}

/////////////////////////////////////////////////////////////////////////////////////////////////
LMCmaterials::~LMCmaterials() {
  for ( itMaterials=mMaterials.begin() ; itMaterials != mMaterials.end(); itMaterials++ ) {
    delete (*itMaterials).second;
  }
  mMaterials.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void LMCmaterials::AddMaterial(string s, TGeoMaterial *p) {mMaterials[s] = p;}

/////////////////////////////////////////////////////////////////////////////////////////////////
TGeoMaterial* LMCmaterials::GetMaterial(string s) {
  itMaterials = mMaterials.find(s);
  return itMaterials->second;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void LMCmaterials::PrintOut() {
  for ( itMaterials=mMaterials.begin() ; itMaterials != mMaterials.end(); itMaterials++ ) {
    cout << (*itMaterials).first << " => " << (*itMaterials).second << endl;
  }
}


