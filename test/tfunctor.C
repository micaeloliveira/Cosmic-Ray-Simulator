#include <iostream>
using namespace std;

#include <TApplication.h>
#include <TCanvas.h>
#include <TParticle.h>
#include <TF1.h>

#include "LMCfunctor.h"

bool DisplayMode;

/////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

  cout << " Running tfunctor; #args = " << argc << " | " << flush;
  for (int i=0; i<argc; i++) { cout << argv[i] << " " << flush;}
  cout << endl;

  //create root application to display graphics
  DisplayMode = false;
  TApplication theApp("App",&argc, argv);

  //canvas
  TCanvas *c = new TCanvas("LRCsim","LRCsim",700,700);
  c->cd();

  //functions
  TF1* fExpD = LMCfunctor::Instance()->GetExponentialDistribution();
  fExpD->SetParameter(0,0.005); 
  fExpD->Draw();

  //generate random
  cout << "random values: " << flush;
  for (int i=0; i<10; i++) { 
    cout << fExpD->GetRandom() << " " << flush;
  }
  cout << endl;

  
  //run application
  theApp.Run();

  return 0;

}

