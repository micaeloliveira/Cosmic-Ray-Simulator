//C++
#include <TQObject.h>
#include <RQ_OBJECT.h>
#include <string>

//#include "LMCgeomN.h"
//#include "LMCparticle.h"
//#include "LMCpropagator.h"
//using namespace std;



//////////////////////////////////////////////////////////////////////////////////////////

class TGWindow;
class TGHSlider;
class TGMainFrame;
class TRootEmbeddedCanvas;
class TGLabel;
class TGClient;

class LMCsimGUI {
  RQ_OBJECT("LMCsimGUI")
    
 private:
  TGMainFrame         *fMain;
  TRootEmbeddedCanvas *fEcanvas;
  TGHSlider    *fSlider1;
  TGLabel      *lSlider1;
   // LMCgeomN *g; ///< geometry
  
 public:
  //LMCsimGUI();
  LMCsimGUI(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~LMCsimGUI();
  
  void DrawTelescope(); ///< draw geometry
  void DrawTank(); ///< draw geometry
  void Rotate(); ///< draw geometry
  void View1(); ///< draw geometry
  void View2(); ///< draw geometry
  void View3(); ///< draw geometry
  void SlideView(); ///< draw geometry
  void ZoomIn(); ///< draw geometry
  void ZoomOut(); ///< draw geometry
  void Run(); ///< draw geometry
  //void DrawEvent(); ///< draw event
  //void Run(int); ///< run over n events
  //ClassDef(LMCsimGUI,0)


};
