#ifndef __LMCuserData__
#define __LMCuserData__

class TH1F;
class TRandom3;

///////////////////////////////////////////////////////////////////////////////

class LMCuserData {
 public:
  LMCuserData();
  ~LMCuserData();
  
  Double_t SetWaterRefIndex(Double_t wl); ///< wavelength in nanometers (nm)
  TH1F* GetWaterRefIndex();

  Double_t SetXP2020DetEff(Double_t wl); ///< wavelength in nanometers (nm)
  TH1F* GetXP2020DetEff();

  Double_t SetCerDetEffMean(Double_t lmin, Double_t lmax);

  Double_t GetCerDetEffMean();

 private:
  TF1 *CerSpectrum; ///< cerenkov spectrum
  TRandom3 *rand; ///< random 
  TH1F *XP2020eff; ///< xp2020 quantum eff
  TH1F *WaterRefIndex;
  Double_t EffMean; ///< detection efficiency mean for cer spectrum (200.,700. nm)
};

#endif
