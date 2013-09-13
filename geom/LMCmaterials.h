#ifndef _LMCmaterials_
#define _LMCmaterials_

#include <string>
#include <map>

using namespace std;

class TGeoMaterial;

//---------------------------------------------------------------

class LMCmaterials {

 public:
  LMCmaterials();
  ~LMCmaterials();

  /** Add material */
  void AddMaterial(string,TGeoMaterial*); 

  /** Get material */
  TGeoMaterial* GetMaterial(string);

  /** Print class contents */
  void PrintOut();

 private:
  map<string,TGeoMaterial*> mMaterials;
  map<string,TGeoMaterial*>::iterator itMaterials;

};

#endif
