#include <vector>
using namespace std;

class LMCstep;
class TParticle;

//////////////////////////////////////////////////////////////////////////////////////

class LMCtrack {

 public:
  LMCtrack(TParticle*);
  ~LMCtrack();
  void     Clear();
  void     AddParticle(TParticle*);
  TParticle* GetParticle();
  void     AddStep(LMCstep*);
  LMCstep* GetStep(Int_t n); ///< Get step pointer for step number n on stack
  Int_t    GetNSteps();

 private:
  TParticle *particle; ///< particle producing steps
  vector<LMCstep*> vs; ///< vector with track steps
};
