//C
#include <iostream>
using namespace std;

//ROOT
#include "TH1F.h"

//MY
#include "LMCcerRadiator.h"

////////////////////////////////////////////////////////////////////////

LMCcerRadiator::LMCcerRadiator() {hrefindex = NULL;}

LMCcerRadiator::~LMCcerRadiator() {hrefindex = NULL;}

void LMCcerRadiator::SetRefIndex(TH1F *h) {hrefindex = h;}

Double_t LMCcerRadiator::GetRefIndex(Double_t wl) {
  Double_t value = 0.; 
  if (hrefindex) {
    Int_t bin = hrefindex->FindBin(wl);
    value = hrefindex->GetBinContent(bin);
  } 
  return value;
}

void LMCcerRadiator::Dump() {
  Int_t nbins = hrefindex->GetNbinsX();
  cout << "[LMCcerRadiator::Dump] " << flush;
  for (int i=1; i<nbins+1; i++) {
    cout << " wl=" << hrefindex->GetBinCenter(i) << " (" <<  hrefindex->GetBinContent(i) << ")" << flush;
  } 
  cout << endl;
}
