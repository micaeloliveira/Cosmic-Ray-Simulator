//C++
#include <vector>

//ROOT
#include <TGeoMatrix.h>
#include <TGeoVolume.h>
#include <TGeoBBox.h>
#include <TGeoTube.h>
#include <TGeoTrd2.h>
#include <TGeoMaterial.h>


//MY
#include <LMCmaterials.h>
#include <LMCscintillatorN.h>

////////////////////////////////////////////////////////////////////////////////////

LMCscintillatorN::LMCscintillatorN(int index,LMCmaterials *m){

  //translation and rotation objects
  TGeoRotation *rot = new TGeoRotation();

  //Materials and media
  TGeoMixture *matSCI    = (TGeoMixture*)(m->GetMaterial("Scintillator"));
  TGeoMixture *matPMMA   = (TGeoMixture*)(m->GetMaterial("PMMA"));
  TGeoMedium  *medSCI    = new TGeoMedium("medScintillator",10,matSCI);
  TGeoMedium  *medLGtrap = new TGeoMedium("medLGtrap",11,matPMMA);  
  TGeoMedium  *medLGtube = new TGeoMedium("medLGtube",12,matPMMA);  

  //scintillator shape and volume 
  TGeoVolume *volSci    = new TGeoVolume("Scintillator",  new TGeoBBox("Scintillator",50.,25.,0.5), medSCI);
  TGeoVolume *volLGtrap = new TGeoVolume("LightGuideTrap",new TGeoTrd2("LGtrap",0.5,0.5,25.,2.,25.),medLGtrap);
  TGeoVolume *volLGtube = new TGeoVolume("LightGuideRod", new TGeoTube("LGrod",0.,2.,5.),           medLGtube);
  
  // Make the elementary assembly of the whole structure
  TelescopeSci = new TGeoVolumeAssembly("TelescopeSCI");

  //scintillator 
  TelescopeSci->AddNode(volSci,index,new TGeoCombiTrans(0.,0.,0., rot));

  //Trap Light Guide 
  rot->RotateY(90.);
  TelescopeSci->AddNode(volLGtrap,index,new TGeoCombiTrans(75.,0.,0., rot));

  //Rod Light Guide 
  TelescopeSci->AddNode(volLGtube,index,new TGeoCombiTrans(105.,0.,0., rot));

}

/////////////////////////////////////////////////////////////////////////////////////////////
LMCscintillatorN::~LMCscintillatorN(){
  delete TelescopeSci;
}

/////////////////////////////////////////////////////////////////////////////////////////////
TGeoVolume* LMCscintillatorN::GetAssemblyVolume() {return TelescopeSci;}

/////////////////////////////////////////////////////////////////////////////////////////////
void LMCscintillatorN::PrintOut() {
  TelescopeSci->Dump();
}
