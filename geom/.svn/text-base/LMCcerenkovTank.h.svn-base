#ifndef _LMCcerenkovTank_
#define _LMCcerenkovTank_

#include <vector>
#include <map>

class TGeoVolume;
class TGeoMatrix;
class LMCmaterials;

using namespace std;

////////////////////////////////////////////////////////////////////////////////////

class LMCcerenkovTank  {

 public:
  LMCcerenkovTank(LMCmaterials*);
  ~LMCcerenkovTank();
 
  void SetElement(TGeoVolume*){;}

  TGeoVolume* GetAssemblyVolume();

  void PrintOut();

 private:
  TGeoVolume *WaterTank; //water tank assembly volume

};

#endif
