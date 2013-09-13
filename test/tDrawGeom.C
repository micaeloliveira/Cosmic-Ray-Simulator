//--------------------------------------------------------------------------------
//
//  LabRC simulator
//
//--------------------------------------------------------------------------------

#include <TApplication.h>
#include <TCanvas.h>
#include <TParticle.h>

#include "LMCgeomN.h"
#include "LMCparticle.h"
#include "LMCpropagator.h"

bool DisplayMode;

/////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

  cout << " Running DrawGeom: #args = " << argc << " | " << flush;
  for (int i=0; i<argc; i++) { cout << argv[i] << " " << flush;}
  cout << endl;
  if (argc == 0) {
    cout << " usage: DrawGeom [geom] (Telescope, Tank)" << endl;
    exit(0);
  }

  //create Lab geom
  string GeomToBuild = "Telescope"; //default geometry
  if (argc>0) {
    GeomToBuild = argv[1];
  } 
  cout << "[DrawGeom] geometry to build: " << GeomToBuild << endl; 
  LMCgeomN *g = new LMCgeomN(GeomToBuild);

  //create root application
  DisplayMode = false;
  TApplication theApp("App",&argc, argv);
  TCanvas *c = new TCanvas("LRCsim","LRCsim",700,700);
  c->cd();
  g->Draw();
  
  //run application
  theApp.Run();

  return 0;

}

