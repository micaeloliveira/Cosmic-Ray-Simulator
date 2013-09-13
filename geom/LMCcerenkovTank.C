
#include <vector>
using namespace std;

//ROOT
#include <TMath.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoMatrix.h>
#include <TGeoTube.h>
#include <TGeoVolume.h>
#include <TGeoMatrix.h>

//MY
#include "LMCmaterials.h"
#include "LMCcerenkovTank.h"

////////////////////////////////////////////////////////////////////////////////////
LMCcerenkovTank::LMCcerenkovTank(LMCmaterials *m){

  //Materials and media
  TGeoMixture *matALU    = (TGeoMixture*)(m->GetMaterial("Aluminium"));
  TGeoMixture *matPMMA   = (TGeoMixture*)(m->GetMaterial("PMMA"));
  TGeoMixture *matWATER  = (TGeoMixture*)(m->GetMaterial("Water"));
  TGeoMixture *matPMT    = (TGeoMixture*)(m->GetMaterial("Quartz"));
  TGeoMedium  *medWATER  = new TGeoMedium("medWATER",20,matWATER);
  TGeoMedium  *medALU    = new TGeoMedium("medALU",21,matALU);
  TGeoMedium  *medWINDOW = new TGeoMedium("medWINDOW",22,matPMMA);  
  TGeoMedium  *medPMT    = new TGeoMedium("medPMT",23,matPMT);  

  //translation and rotation objects
  TGeoRotation *rot = new TGeoRotation();

  //tank volume
  TGeoVolume *vWaterTank      = new TGeoVolume("WATERvol"      ,new TGeoTube("WATERvol"      , 0. ,22.5,15.0),medWATER);
  TGeoVolume *vWallTubeTank   = new TGeoVolume("OUTERWALLtank" ,new TGeoTube("OUTERWALLtank" ,22.5,22.8,15.0),medALU);
  TGeoVolume *vWallBottomTank = new TGeoVolume("BottomWALLtank",new TGeoTube("BottomWALLtank", 0. ,22.8, 0.15),medALU);

  //...top cover
  TGeoVolume *vWallTopTank = new TGeoVolume("TopWALLtank"  ,new TGeoTube("TopWALLtank",0.,22.8, 0.75),medALU);  
  TGeoVolume *vPmtWindow   = new TGeoVolume("PMTWindowTank",new TGeoTube("PMTWindowTank",0.,3.075,0.75),medWINDOW); //just one approx.
  vPmtWindow->SetLineColor(kRed);
  TGeoVolume *vPmt          = new TGeoVolume("PMTtank",new TGeoTube("PMTtank",0.,2.2,5.),medPMT);
  vPmt->SetLineColor(kBlue);

  //PMT center locations
  Double_t phi = 60.; //other pmt windows and pmts
  Double_t x[4], y[4];
  x[0] = 0.0;
  y[0] = 0.0;
  for (int i=0; i<3; i++) {
    phi += 120.;
    x[i+1] = 14.*TMath::Cos(phi*TMath::Pi()/180.);
    y[i+1] = 14.*TMath::Sin(phi*TMath::Pi()/180.); 
  } 


 // Make the elementary assembly of the whole structure
  WaterTank = new TGeoVolumeAssembly("WATERtank");
  WaterTank->AddNode(vWallTubeTank  ,1,new TGeoCombiTrans(0.,0.,0., rot)); //tube side wall
  WaterTank->AddNode(vWaterTank     ,1,new TGeoCombiTrans(0.,0.,0., rot)); //water
  WaterTank->AddNode(vWallBottomTank,1,new TGeoCombiTrans(0.,0.,-(15.+0.15), rot)); //bottom wall
  WaterTank->AddNode(vWallTopTank   ,1,new TGeoCombiTrans(0.,0.,(15.+0.75), rot)); //top wall
  //...pmt windows
  for (int i=0; i<4; i++) { 
    vWallTopTank->AddNodeOverlap(vPmtWindow,i+1,new TGeoCombiTrans(x[i],y[i],0., rot)); 
  }
  //...pmts
  for (int i=0; i<4; i++) { 
    WaterTank->AddNode(vPmt,i+1,new TGeoCombiTrans(x[i],y[i],(15.0+1.5+5.0), rot)); 
  }

  // WaterTank->AddNode(vPmt,1,new TGeoCombiTrans(0.,0.,(15.0+1.5+5.0), rot)); //central pmt
  // phi = 60.; //other pmt windows and pmts
  // index = 1;
  // for (int i=0; i<3; i++) {
  //   index++;
  //   phi += 120.;
  //   x = 14.*TMath::Cos(phi*TMath::Pi()/180.);
  //   y = 14.*TMath::Sin(phi*TMath::Pi()/180.); 
  //   WaterTank->AddNode(vPmt,index,new TGeoCombiTrans(x,y,(15.0+1.5+5.0), rot));
  //  } 

}

//////////////////////////////////////////////////////////////////////////////////////
LMCcerenkovTank::~LMCcerenkovTank(){
  delete WaterTank;
}


/////////////////////////////////////////////////////////////////////////////////////////////
TGeoVolume* LMCcerenkovTank::GetAssemblyVolume() {return WaterTank;}

/////////////////////////////////////////////////////////////////////////////////////////////
void LMCcerenkovTank::PrintOut() {
  WaterTank->Dump();
}
