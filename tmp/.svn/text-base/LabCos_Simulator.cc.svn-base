//#include <interface/LabGeometry.h>

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoMatrix.h>
#include <TGeoVolume.h>
#include <TApplication.h>

#include <TString.h>
#include <TH1D.h>

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  TApplication* rootapp = new TApplication("example",&argc, argv);

  string ProgMode = argv[1];

	if(argc >= 1){
	
		if(ProgMode == "ShowGeo"){

			TH1D * teste = new TH1D("hist","hist",10,1,10);

			TGeoManager *geom = new TGeoManager("simple1", "Simple geometry");

			TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0,0,0);
			TGeoMaterial *matAl     = new TGeoMaterial("Al", 26.98,13,2.7);

			//--- define some media
			TGeoMedium *Vacuum = new TGeoMedium("Vacuum",1, matVacuum);
		  TGeoMedium *Al     = new TGeoMedium("Root Material",2, matAl);

		  TGeoTranslation *tr1 = new TGeoTranslation(0., 0.,  0.);
		  TGeoTranslation *tr2 = new TGeoTranslation(0., 0.,-80.);
			TGeoTranslation *tr3 = new TGeoTranslation(0., 0., 80.);
			TGeoTranslation *tr4 = new TGeoTranslation(0., 0.,-50.);

			TGeoVolume *top = geom->MakeBox("Top",Vacuum,500.,500.,200.);

			TGeoVolume *Cintilador01 = geom->MakeBox("Cintilador01",Vacuum, 100., 50., 2.);
									Cintilador01 ->SetLineColor(kBlack);             
              
  		TGeoVolume *Panela = geom-> MakeTube("Panela", Vacuum,50 ,51, 20);
             
			top->AddNode(Cintilador01, 1, tr1);
			top->AddNode(Cintilador01, 2, tr2);
			top->AddNode(Cintilador01, 3, tr3);
			top->AddNode(Panela      , 1, tr4);
  
			gGeoManager->SetTopVolume(top);	
			gGeoManager->CloseGeometry();

			top->SetLineColor(kRed);
			gGeoManager->SetTopVisible(); // the TOP is generally invisible
			top->Draw();

			gGeoManager->InitTrack(0,0,90,0,0,-1);
			cout << "intersect 1= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;
			cout << "intersect 2= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;
			cout << "intersect 3= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;
			cout << "intersect 4= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;

			if  (gGeoManager->IsOutside()) {cout << "fora" << endl;}
			else                           {cout << "dentro" << endl;}

		}
	
	}

 rootapp->Run();
 return 0;

}
