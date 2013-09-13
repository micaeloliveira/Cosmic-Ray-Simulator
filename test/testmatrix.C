#include "TGeoMatrix"

void main() {

  TGeoRotation rot; rot.SetAngles(0.,0.,0.);
  TGeoTranslation trans(0.,0.,50.);
  TGeoCombiTrans mshift(trans, rot);

  return 0;

}
