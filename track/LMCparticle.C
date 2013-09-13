//C++
#include <iostream>
using namespace std;

// ROOT
#include "TParticle.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"

// MY
#include "LMCparticle.h"

///////////////////////////////////////////////////////////////////////////////////////

LMCparticle::LMCparticle(Int_t PID, Double_t *mom, Double_t *vtx) 
  : TParticle(PID,0,0,0,0,0,mom[0],mom[1],mom[2],0.,vtx[0],vtx[1],vtx[2],0.) {

  //compute total energy
  fE = sqrt(P()*P() + pow(GetPDG()->Mass(),2.));

  //printout
  cout << "============== Particle =================" << endl;
  cout << "| PdgCode : " << GetPdgCode() << endl;
  cout << "| mass    : " << GetMass() << endl;
  cout << "| mom     : " << P() << " Px=" << Px() << " Py=" << Py() << " Pz=" << Pz() << endl;
  cout << "| energy  : " << fE << endl;
  cout << "| vertex  :  Vx=" << Vx() << " Vy=" << Vy() << " Vz=" << Vz() << endl;
  cout << "-----------------------------------------" << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////
LMCparticle::LMCparticle(const TParticle& p) : TParticle(p) {
  //printout
  if(GetPDG()) {
    cout << "============== Particle =================" << endl;
    cout << "| PdgCode = " << GetPdgCode() << endl;
    cout << "| mass = " << GetMass() << endl;
    cout << "| mom = " << P() << endl;
    cout << "| energy = " << fE << endl;
    cout << "-----------------------------------------" << endl;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
Int_t LMCparticle::PdgCode() { return GetPdgCode();}

/////////////////////////////////////////////////////////////////////////////////////////
Double_t LMCparticle::Mass() { return (Double_t)GetMass();}

/////////////////////////////////////////////////////////////////////////////////////////
Double_t* LMCparticle::GetMomentum() { 
  Double_t *mom = new Double_t[4];
  mom[0] = Px();
  mom[1] = Py();
  mom[2] = Pz();
  mom[3] = P();
  return mom;
}

/////////////////////////////////////////////////////////////////////////////////////////
Double_t* LMCparticle::GetDir() { 
  Double_t *dir = new Double_t[3];
  dir[0] = Px()/P();
  dir[1] = Py()/P();
  dir[2] = Pz()/P();
  return dir;
}

/////////////////////////////////////////////////////////////////////////////////////////
Double_t* LMCparticle::GetVertex() { 
  Double_t *vtx = new Double_t[3];
  vtx[0] = Vx();
  vtx[1] = Vy();
  vtx[2] = Vz();
  return vtx;
}


