#include "DetectorConstruction.hh"


DetectorConstruction::DetectorConstruction(){
    
};

DetectorConstruction::~DetectorConstruction(){
    
};


G4VPhysicalVolume *DetectorConstruction::Construct(){
    
    G4bool checkOverlaps = true;
    //Al2O3
    G4Element* elAl = new G4Element("Aluminium", "Al", 13, 26.98*g/mole);
    G4Element* elO  = new G4Element("Oxygen",    "O",  8, 16.00*g/mole);
    G4Material* Al2O3 = new G4Material("Alumina", 3.97*g/cm3, 2);
    Al2O3->AddElement(elAl, 2); 
    Al2O3->AddElement(elO,  3); 
    //SiC
    G4Element* elSi = new G4Element("Silicon", "Si", 14, 28.09*g/mole);
    G4Element* elC  = new G4Element("Carbon",  "C",  6, 12.01*g/mole);
    G4Material* SiC = new G4Material("SiliconCarbide", 3.21*g/cm3, 2);
    SiC->AddElement(elSi, 1); 
    SiC->AddElement(elC,  1); 

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldmat = nist->FindOrBuildMaterial("G4_Galactic");

    G4double worldX = 5.*cm,worldY = 5.*cm,worldZ = 5.*cm;
    G4Box *solidWorld = new G4Box("SoildWorld",worldX,worldY,worldZ);    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldmat,"LogicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"PhysWorld",0,false,0,checkOverlaps);
    G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.1));
    worldVisAtt->SetVisibility(true);
    logicWorld->SetVisAttributes(worldVisAtt);

    G4double sicX = 3.*cm,sicY = 3.*cm,sicZ = 3.*cm;
    G4Box *solidsic = new G4Box("SoildSic",sicX,sicY,sicZ);
    G4LogicalVolume *logicsic = new G4LogicalVolume(solidsic,SiC,"Logicsic");
    G4VPhysicalVolume *physsic = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicsic,"Physsic",logicWorld,false,0,checkOverlaps);
    G4VisAttributes *sicVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.1));
    sicVisAtt->SetVisibility(true);
    logicsic->SetVisAttributes(sicVisAtt);

   
    
    return physWorld;
    
}

