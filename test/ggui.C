//--------------------------------------------------------------------------------
//
// gui test - M.Oliveira and L.Batalha AUGUST!!!! 2012
//
//--------------------------------------------------------------------------------
#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TParticle.h>

#include "LMCsimGUI.h"
#include "LMCgeomN.h"
#include "LMCparticle.h"
#include "LMCpropagator.h"

//bool DisplayMode;

/////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

  //create root application
  //DisplayMode = false;
  TApplication theApp("App",&argc, argv);
    
  new LMCsimGUI(gClient->GetRoot(),200,200);
  //run application
  theApp.Run();

  return 0;

}

