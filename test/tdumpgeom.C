#include "LMCgeomN.h"
#include "LMCpropagator.h"
#include <vector>
#include "TParticle.h"
#include "TObjArray.h"

#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
int main() {

  TGeoNode *node =  NULL;
  TGeoVolume *vol = NULL;
  
  LMCgeomN *g = new LMCgeomN("Telescope");
  TObjArray *oa = g->GetGeoManager()->GetListOfNodes();
  for (int i=0; i<oa->GetEntries(); i++) {
    node =  (TGeoNode*)oa->At(i);
    vol = node->GetVolume();
    cout << "= " << node->GetName() << "  " << vol->GetName()  <<endl;
    TObjArray *vnodes = vol->GetNodes();
    cout << vnodes->GetEntries() << endl;
    for (int j=0; j<vnodes->GetEntries(); j++) {
      node = (TGeoNode*)vnodes->At(j);
      cout << "== " << node->GetName() << endl;
      vol = node->GetVolume();
      TObjArray *vnodes1 = vol->GetNodes();
      for (int k=0; k<vnodes1->GetEntries(); k++) {
	node = (TGeoNode*)vnodes1->At(k);
	cout << "=== " << node->GetName() << endl;
	vol = node->GetVolume();
	TObjArray *vnodes2 = vol->GetNodes();
	if(!vnodes2) continue;
	for (int q=0; q<vnodes2->GetEntries(); q++) {
	   node = (TGeoNode*)vnodes2->At(q);
	   cout << "==== " << node->GetName() << endl;
	 }
	
      }
    }
  }

  return 0;
}

