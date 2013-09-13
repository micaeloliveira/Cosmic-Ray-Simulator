#ifndef _LMCscintillatorN_
#define _LMCscintillatorN_

#include <vector>
using namespace std;

class TGeoMatrix;
class TGeoVolume;
class LMCmaterials;

////////////////////////////////////////////////////////////////////////////////////

class LMCscintillatorN  {

 public:
  LMCscintillatorN(int index,LMCmaterials*);
  ~LMCscintillatorN();
 
  TGeoVolume* GetAssemblyVolume();

  void PrintOut();

 private:
  TGeoVolume *TelescopeSci; //scintillator assembly volume
  
};

#endif
