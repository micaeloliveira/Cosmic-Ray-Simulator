#ifndef __LMCfunctor__
#define __LMCfunctor__

class TF1;
class TH1D;

class LMCfunctor {
 public:
  static LMCfunctor* Instance() {
    if (!pInstance) pInstance=new LMCfunctor(); 
    return pInstance;
  }
  TF1* GetBetheBloch() {return fBetheBloch;}
  TF1* GetCerenkovSpec() {return fCerenkovSpec;}
  TF1* GetNPhotonsCerenkov() {return fNPhotonsCerenkov;}
  TF1* GetPhotonAbsProb() {return fPhotonAbsProb;}
  TH1D* GetEmissionSpectrumSci() {return fEmissionSpectrumSci;}
  TH1D* GetQuantumEffR580() {return   fQuantumEffR580;}
  TH1D* GetQuantumEffXP2020() {return fQuantumEffXP2020;}
  TH1D* GetGeometricDistribution(double p);
  TF1* GetFresnelRefParCoef() {return fFresnelRefParCoef;} 
  TF1* GetFresnelRefPerpCoef() {return fFresnelRefPerpCoef;} 
  TF1* GetReflectance() {return fReflectance;} 
  TF1* GetExponentialDistribution() {return fExponentialDistribution;} 


 private:
  static LMCfunctor* pInstance;
  void Clear();
  TF1* fBetheBloch;
  TF1* fCerenkovSpec;
  TF1* fNPhotonsCerenkov;
  TF1* fPhotonAbsProb;
  TH1D* fEmissionSpectrumSci;
  TH1D* fQuantumEffR580;
  TH1D* fQuantumEffXP2020;
  TF1* fFresnelRefParCoef;
  TF1* fFresnelRefPerpCoef;
  TF1* fReflectance;
  TF1* fExponentialDistribution;

  
  LMCfunctor();
  ~LMCfunctor();
  double BetheBloch(double *x, double *p); ///< bethe-bloch energy lost
  double CerenkovSpec(double *x, double *p); ///< Cerenkov energy lost
  double NPhotonsCerenkov(double *x, double *p);///<Number of Cerenkov photons 
  TH1D* EmissionSpectrumSci();   ///<Photon Emission Spectrum Sci (BC-408)
  TH1D* QuantumEffR580();   ///<Quantum Efficiency Hamamatsu R580
  TH1D* QuantumEffXP2020();   ///<Quantum Efficiency Philips XP2020
  double FresnelRefParCoef(double* x, double* p); ///< fresnel coef: ref parallel
  double FresnelRefPerpCoef(double* x, double* p); ///< fresnel coef: ref perpendicular
  double Reflectance(double* x, double* p); ///< reflectance
  double ExponentialDistribution(double *x, double *p);///<Exponential Distribution


};


#endif
