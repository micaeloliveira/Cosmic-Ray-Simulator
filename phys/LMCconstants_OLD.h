//=======================================================
//
//   Class to store Fundamental constants
//   
//
//   Authors:  LB & MO
//   Date: June 2012
//
//========================================================


#ifndef __LMCconstants__
#define __LMCconstants__


namespace LMCconstants {
 
  // velocity of light (m/s)
  inline Double_t c()
    { return 2.99792458*1.E8; }      
  
  //electron mass (GeV/)
  inline Double_t e_m()
    {return 0.510998*1.E-3;}                    //   (GeV/c^2)
  
  //Planck Constant
  inline Double_t h_planck()  //(eV*s) 
    {return 4.135667516*1.E-15;}                
  
  inline Double_t hc()  //(eV*cm)
    {return h_planck()*c()*1.E-2;}
  
  //Bohr Radius  (m)
  inline Double_t Bohr()
    {return 5.2917721*1.E-11;}  
  
  //Classical electron radius  (m) 
  inline Double_t r_e()
    {return 2.8179402894*1.E-15;}  
  
  //Particle PDGcodes
  inline Int_t id(string s)
  {
    if (s == "photon")        return   22;
    if (s == "mu-")           return   13;
    if (s == "mu+")           return  -13;
    if (s == "e-")            return   11;
    if (s == "e+")            return  -11;
    if (s == "nu_e")          return   12;
    if (s == "antinu_e")      return  -12;
    if (s == "nu_mu")         return   14;
    if (s == "antinu_mu")     return  -14;
  }


};

#endif
