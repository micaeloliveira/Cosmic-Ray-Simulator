void ROOT_LCos(){

	gSystem->Load("libGeom");

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

  top->SetLineColor(kMagenta);
  gGeoManager->SetTopVisible(); // the TOP is generally invisible
  top->Draw();

  gGeoManager->InitTrack(0,0,90,0,0,-1);
  cout << "intersect 1= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;
  cout << "intersect 2= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;
  cout << "intersect 3= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;
  cout << "intersect 4= " << gGeoManager->FindNextBoundaryAndStep()->GetName() << endl;

  if  (gGeoManager->IsOutside()) {cout << "fora" << endl;}
  else                           {cout << "dentro" << endl;}


/*

  Double_t theta = 0;
  Double_t phi   = -3.14159/2;
 
  Double_t xp  = TMath::Sin(theta)*TMath::Cos(phi);
  Double_t yp  = TMath::Sin(theta)*TMath::Sin(phi);
  Double_t zp  = TMath::Cos(theta);

  const Double_t *cdir = gGeoManager->GetCurrentDirection();
  gGeoManager->SetCurrentDirection(xp,yp,zp);
*/

  
}
   
