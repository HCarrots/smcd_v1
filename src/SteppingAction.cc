#include "SteppingAction.hh"


SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction) {}



void SteppingAction::UserSteppingAction(const G4Step* step)
{
  /*if (!fScoringVolume) {
    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume =
    step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  //fEventAction->AddEdep(edepStep);
  std::cout<<"edepStep:"<<edepStep<<std::endl;*/
}
