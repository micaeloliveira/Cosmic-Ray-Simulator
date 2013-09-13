//
// g++ -o testgeo.exe testgeo.C `root-config --cflags` `root-config --libs --glibs` -lGeom
//

#include <TGeoMatrix.h>

int main() {

  TGeoTranslation t(0,0,0);
  TGeoRotation r("ROT",0,0,0);
  TGeoCombiTrans *M = new TGeoCombiTrans(t,r);
  
  Double_t tr[3];
  tr = M->GetTranslation();

  //  t.SetTranslation(100,0,0);

  //  TGeoHMatrix *nM = M

  return 0;

}
