#ifndef __LMCcerRadiator__
#define __LMCcerRadiator__

//ROOT
#include "TObject.h"

class TH1F;

//////////////////////////////////////////////////////////////////////////////////////////

class LMCcerRadiator : public TObject {
 public:
  LMCcerRadiator();
  ~LMCcerRadiator();

  void     SetRefIndex(TH1F*);
  Double_t GetRefIndex(Double_t);

  void Dump();

 private:
  TH1F *hrefindex; ///histo with refractive index as function of wave length (nm)
};

#endif
