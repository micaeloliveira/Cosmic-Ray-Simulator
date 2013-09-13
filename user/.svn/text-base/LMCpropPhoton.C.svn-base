#include "LMCpropPhoton.h"
#include "TRandom3.h"
#include <ctime>

//=====================================================================================
// Description : Constructor
//=====================================================================================
LMCpropPhoton::LMCpropPhoton(TGeoManager *g) : LMCpropagator(g) {

  RandomG = new TRandom3(time(NULL));

  PhotonAbsortionProb = new TF1("PhotonAbsortionProb","(3.36248e-11)*(x**3) - (1.59971e-08)*(x**2) - (2.63421e-06)*(x) + 1.54795e-03",200,700);

  Reflectividade.insert(pair<TString,Double_t>("BottomWALLtank_1",1));
  Reflectividade.insert(pair<TString,Double_t>("OUTERWALLtank_1" ,1));
  Reflectividade.insert(pair<TString,Double_t>("TopWALLtank_1"   ,1));
  
}

//=====================================================================================
// Description : Destructor
//=====================================================================================
LMCpropPhoton::~LMCpropPhoton(){

  delete PhotonAbsortionProb;

}

LMCstep* LMCpropPhoton::DoStepUser(Double_t d, Double_t E) {}

//=====================================================================================
// Description : Make the propagation of each single photon
//=====================================================================================
int LMCpropPhoton::Propagate(TParticle *photon){

  // Output variable
  int out = 10;
  
  // Resetting photon variables 
  outLambda      = 0;
  outDistLife    = 0;
  outDistDone    = 0;
  outNReflection = 0;

  geom->ResetState();

  // Setting Current Geometry Propagation point to Photon vertex 
  Double_t Vertex[3]    = {photon->Vx(),             photon->Vy(),             photon->Vz()};
  Double_t Direction[3] = {photon->Px()/photon->P(), photon->Py()/photon->P(), photon->Pz()/photon->P()};  
  geom->InitTrack(Vertex,Direction); 
  
  // CODIGO PARA FAZER DESENHAR TRACKS
  //Int_t track_index = geom->AddTrack(0,22,photon);
  //geom->SetCurrentTrack(track_index);
  //TVirtualGeoTrack *tphoton = geom->GetCurrentTrack();   
  //tphoton->SetLineColor(kGreen-1);
  //  
  //const Double_t* pos = geom->GetCurrentPoint();
  //tphoton->AddPoint(pos[0],pos[1],pos[2],0);
  
  //Calculate Lambda
  const    Double_t hbarc = 0.197326960277E-6; //GeV.nm 
  Double_t inLambda = 2.*TMath::Pi()*hbarc/photon->P(); 
     
  //Calculate Propagation distance
  double Prob = PhotonAbsortionProb->Eval(inLambda);  // Extracting prob of absortion in a dist of 1cm
    
  // Randomly calculating how many cm will the photon live
  bool Alive = true; 
  Double_t DistLife = 0;
  while(Alive){
  
    double value = RandomG->Rndm();
    if(value < Prob){Alive = false;}
    else            {DistLife++;}
  
  }
  outDistLife = DistLife;
  if(outDistLife == 0){out = 0;} // Photons that die in less then 1cm

  while(DistLife > 0){
  
    string   nCurrent     = geom->GetCurrentNode()->GetName();
    string   nBoundary    = geom->FindNextBoundaryAndStep()->GetName();
    if(nBoundary == "WATERvol_1"){nBoundary    = geom->FindNextBoundaryAndStep()->GetName();}
    Double_t DistBoundary = geom->GetStep();
    
    // CODIGO PARA FAZER DESENHAR TRACKS
    //pos = geom->GetCurrentPoint();
    //tphoton->AddPoint(pos[0],pos[1],pos[2],0);

    if(DistBoundary < DistLife){
     
      // Adding to distance done
      outDistDone += DistBoundary; 
     
      // Copying values for our   
      TVector3 Normal    = TVector3(geom->FindNormalFast());
      TVector3 Point     = TVector3(geom->GetCurrentPoint());
      TVector3 Direction = TVector3(geom->GetCurrentDirection());
      
      Normal[0] = -1*Normal[0];
      Normal[1] = -1*Normal[1];
      Normal[2] = -1*Normal[2];
       
      if(nBoundary == "BottomWALLtank_1"){

        bool Reflected;
        
        // Check if reflection index is diferent then 1 if so calculate possibility of reflection
        if(Reflectividade["BottomWALLtank_1"] != 1){
        
          double value = RandomG->Rndm();
          if(value > Reflectividade["BottomWALLtank_1"]){Reflected = false;}
          else                                          {Reflected = true;}
        
        }else{Reflected = true;}

        // If it is indeed reflected calculate new direction 
        if(Reflected){
          
          // Adding to Reflection Count
          outNReflection++;
          
          LMCReflection myRefector = LMCReflection(0);
          TVector3 result = myRefector.Calculate(Normal,Direction);

          DistLife = DistLife - DistBoundary;
          Double_t tPoint[3]; Point.GetXYZ(tPoint);
          Double_t tVec[3];   result.GetXYZ(tVec);
          geom->InitTrack(tPoint,tVec);
      
        }
        // If not reflected stop propagation and set photon dead
        else{
          out      = 0;
          DistLife = 0;
        }
      
      }
      else if(nBoundary == "OUTERWALLtank_1"){
     
        bool Reflected;
        
        // Check if reflection index is diferent then 1 if so calculate possibility of reflection
        if(Reflectividade["OUTERWALLtank_1"] != 1){
        
          double value = RandomG->Rndm();
          if(value > Reflectividade["OUTERWALLtank_1"]){Reflected = false;}
          else                                          {Reflected = true;}
        
        }else{Reflected = true;}

        // If it is indeed reflected calculate new direction 
        if(Reflected){

          // Adding to Reflection Count
          outNReflection++;

          LMCReflection myRefector = LMCReflection(0);
          TVector3 result = myRefector.Calculate(Normal,Direction);
     
          DistLife = DistLife - DistBoundary;
          Double_t tPoint[3]; Point.GetXYZ(tPoint);
          Double_t tVec[3];   result.GetXYZ(tVec);
          geom->InitTrack(tPoint,tVec);
        
        }
        // If not reflected stop propagation and set photon dead
        else{
          out      = 0;
          DistLife = 0;
        }
      
      }
      else if(nBoundary == "TopWALLtank_1"){
      
         bool Reflected;
        
        // Check if reflection index is diferent then 1 if so calculate possibility of reflection
        if(Reflectividade["TopWALLtank_1"] != 1){
        
          double value = RandomG->Rndm();
          if(value > Reflectividade["TopWALLtank_1"]){Reflected = false;}
          else                                          {Reflected = true;}
        
        }else{Reflected = true;}

        // If it is indeed reflected calculate new direction 
        if(Reflected){
      
          // Adding to Reflection Count
          outNReflection++;
      
          LMCReflection myRefector = LMCReflection(0);
          TVector3 result = myRefector.Calculate(Normal,Direction);

          DistLife = DistLife - DistBoundary;
          Double_t tPoint[3]; Point.GetXYZ(tPoint);
          Double_t tVec[3];   result.GetXYZ(tVec);
          geom->InitTrack(tPoint,tVec);
          
        }
        // If not reflected stop propagation and set photon dead
        else{
          out      = 0;
          DistLife = 0;
        }
      
      }
      else if(nBoundary == "PMTWindowTank_1" || nBoundary == "PMTWindowTank_2"
           || nBoundary == "PMTWindowTank_3" || nBoundary == "PMTWindowTank_4"){

        int tOut;
        
        if     (nBoundary == "PMTWindowTank_1"){tOut = 1;}
        else if(nBoundary == "PMTWindowTank_2"){tOut = 2;}
        else if(nBoundary == "PMTWindowTank_3"){tOut = 3;}
        else if(nBoundary == "PMTWindowTank_4"){tOut = 4;}
        
        LMCFresnel myFresnel = LMCFresnel(1.2,1.7,0);
        pair<bool,pair<TVector3,double> > result = myFresnel.Calculate(Normal,Direction,inLambda); 
        
        
        if(result.first){
      
          out = tOut;
          break;
      
        }else{
      
          // Adding to Reflection Count
          outNReflection++;
      
          Double_t tPoint[3]; Point.GetXYZ(tPoint);
          Double_t tVec[3];   result.second.first.GetXYZ(tVec);
          outLambda =result.second.second;
     
          DistLife = DistLife - DistBoundary;
          geom->InitTrack(tPoint,tVec);
      
        }

      }else{
      
        break;
        
      }
  
    }else{
      // Adding to distance done
      outDistDone += DistLife;
      
      // End propagation
      out      = 0;
      DistLife = 0;  
    }

  }

  if(out == 10){
    cout << "x=" << Vertex[0] << " y=" << Vertex[1] << " z=" << Vertex[2] << endl;
    cout << "Vx=" << Direction[0] << " Vy=" << Direction[1] << " Vz=" << Direction[2] << endl;
    cout << "erro!!!------------" << endl;
    cout << "Lambda   = " << outLambda << endl;
    cout << "DistLife = " << outDistLife << endl;
    cout << "DistDone = " << outDistDone << endl;
    cout << "NReflec  = "<< outNReflection << endl;
  }
  return out;
  
}

Double_t LMCpropPhoton::GetLambda()     {return outLambda;}
Double_t LMCpropPhoton::GetDistLife()   {return outDistLife;}
Double_t LMCpropPhoton::GetDistDone()   {return outDistDone;}
Double_t LMCpropPhoton::GetNReflection(){return outNReflection;}  
  
void LMCpropPhoton::SetRandGen(TRandom3* iRand){RandomG = iRand;}

/////////////////////////////////////////////////////////////////////////////////////// USER
Int_t LMCpropPhoton::GetNPhotonsSci(LMCstep *s) {return -1;}

/////////////////////////////////////////////////////////////////////////////////////// USER
Int_t LMCpropPhoton::GetNPhotonsCer(LMCstep *s) {return -1;}

LMCReflection::LMCReflection(int iDebug){

  debug   = iDebug;

}

LMCReflection::~LMCReflection(){}

TVector3 LMCReflection::Calculate(TVector3 newNormal,TVector3 newIncidente){

  TVector3 out;

  // Variable declaration
  TVector3 crossProduct = newIncidente.Cross(newNormal);
  double thetai = newNormal.Angle(newIncidente);

  // Just in case there's an error with the normal and incident vector
  if (thetai <= TMath::Pi()/2) {
    cout << endl << "thetai: " <<  TMath::Pi()-thetai << endl;
    cout << "Impossible frontier configuration (possible miscalculation of the normal)!" << endl << endl;
    return out;
  }

  thetai= TMath::Pi()-thetai; // Correction to the angle

    if(debug>0) {
      cout << endl << "thetai: " << thetai << endl;
      cout << "newNormal: (" << newNormal[0]    << "," << newNormal[1]    << "," << newNormal[2]    << ") " << endl;
      cout << "Incidente: (" << newIncidente[0] << "," << newIncidente[1] << "," << newIncidente[2] << ") " << endl;
    }

    // Rotation of the reflected vector
    newIncidente.Rotate(TMath::Pi(),crossProduct); 
    newIncidente.Rotate(TMath::Pi(),newNormal); 

    if(debug>0) {
      cout << "Reflected Vector: (" << newIncidente[0] << "," << newIncidente[1] << "," << newIncidente[2] << ") " << endl;
    }

    // new angle -> should remain the same!
    double thetar = newNormal.Angle(newIncidente);
 
    if(debug>0) {
      cout << "thetar (after the rotation): " << thetar << endl << endl;
    }

    out = newIncidente;

  return out;


}


LMCFresnel::LMCFresnel(double n1,double n2,int iDebug){

  IndexN1 = n1;
  IndexN2 = n2;
  debug   = iDebug;

}

LMCFresnel::~LMCFresnel(){}

pair<bool,pair<TVector3,double> > LMCFresnel::Calculate(TVector3 newNormal,TVector3 newIncidente,double lambda){

  pair<bool,pair<TVector3,double> > out;

  srand(time(NULL));                        // Create seed based on current time
  double RandNumber= (random() % 100)/100.; // Random Number between 0 and 1 

  // Variable declaration
  double thetai,thetat;
  double ReflectProb=0.;

  TVector3 crossProduct = newIncidente.Cross(newNormal);

  thetai = newNormal.Angle(newIncidente);

  // Just in case there's an error with the normal and incident vector
  if (thetai <= TMath::Pi()/2) {
    cout << endl << "thetai: " <<  TMath::Pi()-thetai << endl;
    cout << "Impossible frontier configuration (possible miscalculation of the normal)!" << endl << endl;
    return out;
  }

  thetai= TMath::Pi()-thetai; // Correction to the angle

  thetat=asin(IndexN1*sin(thetai)/IndexN2); // Snell's Law for Transmission Angle
   
  // The probability of reflection is:
  ReflectProb= 0.5*( (sin(thetai-thetat))*(sin(thetai-thetat))/((sin(thetai+thetat))*(sin(thetai+thetat))) + 
               (tan(thetai-thetat))*(tan(thetai-thetat))/((tan(thetai+thetat))*(tan(thetai+thetat))) );

  if(debug>0) {
    cout << endl << "thetai: " << thetai << endl;
    cout << "thetat (by Snell's Law): " << thetat << endl;
    cout << "Reflection Probability: " << ReflectProb << endl;
    cout << "RandNumber: " << RandNumber << endl << endl;
  }

  // transmission/reflection - true/false
  if ( RandNumber <= ReflectProb ){
    out.first  = false;
    double angle = newNormal.Angle(newIncidente);

    if(debug>0) {
      cout << "newNormal: (" << newNormal[0]    << "," << newNormal[1]    << "," << newNormal[2]    << ") " << endl;
      cout << "Incidente: (" << newIncidente[0] << "," << newIncidente[1] << "," << newIncidente[2] << ") " << endl;
    }

    // Rotation of the reflected vector
    newIncidente.Rotate(TMath::Pi(),crossProduct); 
    newIncidente.Rotate(TMath::Pi(),newNormal); 

    if(debug>0) {
      cout << "Reflected Vector: (" << newIncidente[0] << "," << newIncidente[1] << "," << newIncidente[2] << ") " << endl;
    }

    // new angle -> should remain the same!
    double thetar = newNormal.Angle(newIncidente);
 
    if(debug>0) {
      cout << "thetar (after the rotation): " << thetar << endl << endl;
    }

    out.second.first  = newIncidente;
    out.second.second = lambda;          

  }else{ // And now, the Refraction case

    out.first = true;
    double angle = newNormal.Angle(newIncidente);

    if(debug>0) {  
      cout << "newNormal: (" << newNormal[0] << "," << newNormal[1] << "," << newNormal[2] << ") " << endl;
      cout << "Incidente: ("  << newIncidente[0] << "," << newIncidente[1] << "," << newIncidente[2] << ") " << endl;
    }

    // Rotation of the vector, acording to Snell's Law
    newIncidente.Rotate(-(thetai-thetat),crossProduct); 

    if(debug>0) {
      cout << "Transmited Vector: (" << newIncidente[0] << "," << newIncidente[1] << "," << newIncidente[2] << ") " << endl << endl;
    }

    // new angle -> Just to cross-check with the one calculated with SL
    double newthetat = newNormal.Angle(newIncidente);

    if(debug>0){cout << "New Thetat(after the rotation): " << TMath::Pi()-newthetat << endl << endl;}

    out.second.first = newIncidente;
    out.second.second = lambda * (IndexN2/IndexN1);

  }          

  return out;

}
