#ifndef TrackerSD_HH
#define TrackerSD_HH

#include <vector>

#include "G4VSensitiveDetector.hh"
#include "TrackerHit.hh"

class G4Step;
class G4HCofThisEvent;


class TrackerSD : public G4VSensitiveDetector {
 public:
  TrackerSD(const G4String& name, const G4String& hitsCollectionName);
  ~TrackerSD() override = default;

  
  void Initialize(G4HCofThisEvent* hitCollection) override;
  G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  void EndOfEvent(G4HCofThisEvent* hitCollection) override;

 private:
  TrackerHitsCollection* fHitsCollection = nullptr;
};



#endif