// RunAction.hh
#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH
#include "G4UserRunAction.hh"
class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
private:
    G4double fPrimaryEnergy;
   
};
#endif