
#include <iostream>
#include <cmath>
#include <string>
#include <map>
using namespace std;

//ROOT
#include "TROOT.h"
#include "TGeoManager.h"
#include <TGeoMatrix.h>
#include <TGeoVolume.h>

//MY
#include "LMCmaterials.h"
#include "LMCcerenkovTank.h"
#include "LMCscintillatorN.h"
#include "LMCgeomN.h"

////////////////////////////////////////////////////////////////////////////////////////////////

LMCgeomN::LMCgeomN(string s) {

  cout << "[LMCgeomN::LMCgeomN] building geometry for: " <<  s << endl;  

  //built geometry manager
  geom = new TGeoManager(s.c_str(),s.c_str());

  //get element table
  table = geom->GetElementTable();

  //load my materials
  materials = new LMCmaterials();

  //make mother volume
  TGeoMaterial *mat = materials->GetMaterial("Vacuum");

  //Telescope setup
  //components: are the setup components (Volumes) like scintillators and water tank
  //the components are composed by different Elements (light guides, scintillators,...) 
  //that need to be placed on the geometry

  mdet.clear();

  if (s == "Telescope") {

    //mother volume
    topVolume = geom->MakeBox("Top",new TGeoMedium("Vacuum",1,mat),100.,100.,150.);

    //create scintillators
    LMCscintillatorN *sc1 = new LMCscintillatorN(1,materials);     
    LMCscintillatorN *sc2 = new LMCscintillatorN(2,materials);     
    LMCscintillatorN *sc3 = new LMCscintillatorN(3,materials);     

    LMCcerenkovTank *tank = new LMCcerenkovTank(materials);

    mdet["SC1"] = sc1->GetAssemblyVolume();
    mdet["SC2"] = sc2->GetAssemblyVolume();
    mdet["SC3"] = sc3->GetAssemblyVolume();
    mdet["CER"] = tank->GetAssemblyVolume();

  } else if (s == "Tank") {

    //mother volume
    topVolume = geom->MakeBox("Top",new TGeoMedium("Vacuum",1,mat),30.,30.,30.);

    LMCcerenkovTank *tank = new LMCcerenkovTank(materials);
    mdet["CER"] = tank->GetAssemblyVolume();

  }

  if (s == "Telescope") {

    topVolume->AddNode(mdet["SC1"],  1, new TGeoTranslation(  0,  0, 50.));
    topVolume->AddNode(mdet["SC2"],  2, new TGeoTranslation(  0,  0,  0.));
    topVolume->AddNode(mdet["SC3"],  3, new TGeoTranslation(  0,  0,-50.));
    topVolume->AddNode(mdet["CER"], 1, new TGeoTranslation(  0,  0,-32.));

  } else if (s == "Tank" ) { 

    topVolume->AddNode(mdet["CER"], 1, new TGeoTranslation(0,0,-16.)); 

  }

  geom->SetTopVolume(topVolume);
  geom->CloseGeometry();

}

//===============================================================================
LMCgeomN::~LMCgeomN() {

  for ( itmdet = mdet.begin() ; itmdet != mdet.end(); itmdet++ ) delete itmdet->second;
  mdet.clear();
 
}


//===============================================================================
void LMCgeomN::Dump() {
}

//===============================================================================
TGeoManager* LMCgeomN::GetGeoManager() {return geom;}


//===============================================================================
void LMCgeomN::Raytrace() {

  //components: are the setup components like scintillators and water tank
  //the components are composed by different Elements (light guides, scintillators,...) 
  //that need to be placed on the geometry

  geom->SetVisLevel(4);
  geom->SetVisOption(1);
  topVolume->Raytrace();
}

//===============================================================================
void LMCgeomN::Draw() {

  //components: are the setup components like scintillators and water tank
  //the components are composed by different Elements (light guides, scintillators,...) 
  //that need to be placed on the geometry

  geom->SetVisLevel(4);
  geom->SetVisOption(1);
  topVolume->Draw(); 
}
