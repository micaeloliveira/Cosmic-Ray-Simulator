#include "LMCuserMuon.h" 
#include "LMCgeomN.h"
#include "LMCparticle.h"
#include "LMCpropagator.h"

#include <string>
using namespace std;

int main() {

  //create geometry
  LMCgeomN *g = new LMCgeomN("Telescope");

  //create muon propagator
  LMCuserMuon *pmuon = new LMCuserMuon(g);

  //create muon particle
  LMCparticle *part = pmuon->GenerateSingle(1.,180.,0.,0.,0.,51.);
  pmuon->Follow(part);

  return 0;

}
