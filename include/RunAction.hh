#ifndef B2RunAction_HH
#define B2RunAction_HH
 
#include "G4UserRunAction.hh"
 
class G4Run;

/// Run action class
 
class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override = default;
 
    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run* run) override;
};

 
#endif