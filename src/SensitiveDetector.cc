#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name){
    fTotalEnergyDeposited = 0;
};

SensitiveDetector::~SensitiveDetector(){};

void SensitiveDetector::Initialize(G4HCofThisEvent *){
    fTotalEnergyDeposited = 0;
};  //  This method is invoked at the begining of each event.

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *){
    G4cout << "Total energy deposited: " << G4BestUnit(fTotalEnergyDeposited, "Energy") << G4endl;
};  //  This method is invoked at the end of each event.

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *){
    G4double edep = aStep->GetTotalEnergyDeposit();
    fTotalEnergyDeposited += edep;
    return true;
};  //  This method is invoked by G4SteppingManager for generating hit(s).
