#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Box.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "SensitiveDetector.hh"
#include "G4SubtractionSolid.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSNofSecondary.hh"
#include "G4SDParticleFilter.hh"

#include "TrackerHit.hh"
#include "TrackerSD.hh"
class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume *Construct() override;
private:
    G4LogicalVolume *logicDet;

    virtual void ConstructSDandField();
    G4MultiFunctionalDetector* bremsDetector1;  // 首字母小写
    G4MultiFunctionalDetector* bremsDetectorSiC;
    G4MultiFunctionalDetector* bremsDetector2;
    G4MultiFunctionalDetector* bremsDetector3;


};


#endif