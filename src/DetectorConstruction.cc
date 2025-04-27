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

    //first floor
    G4double detX = 1.75*cm,detY = 1.75*cm;
    G4double solid1Z = 0.03*cm;
    G4Box *solid1 = new G4Box("Solid1",detX/2,detY/2,solid1Z/2);
    G4double SourceX = 0.875*cm,SourceY = 0.875*cm;
    G4Box *Source = new G4Box("Source",SourceX/2,SourceY/2,solid1Z/2);
    G4ThreeVector offset(0, 0, 0);  
    G4SubtractionSolid* ceramics_1 = new G4SubtractionSolid(
        "ceramics_1", // 新几何体名称
        solid1,            // 被减体
        Source,            // 减去体
        0,                 // 无旋转
        offset             // 减去体的位置偏移
    );
    G4LogicalVolume *ceramics_1_logic = new G4LogicalVolume(ceramics_1,Al2O3,"ceramics_1_logic");
    G4LogicalVolume *logicSource = new G4LogicalVolume(Source,worldmat,"LogicSource");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),ceramics_1_logic,"Phys_ceramics_1",logicWorld,false,0,checkOverlaps);
    G4VisAttributes *C1VisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.5));
    C1VisAtt->SetVisibility(true);
    ceramics_1_logic->SetVisAttributes(C1VisAtt);
    new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicSource,"Phys_Source",logicWorld,false,0,checkOverlaps);
    G4VisAttributes *SrcVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
    SrcVisAtt->SetVisibility(true);
    logicSource->SetVisAttributes(SrcVisAtt);

    //second floor
    G4double solid2Z = 0.035*cm;
    G4Box *solid2 = new G4Box("Solid2",detX/2,detY/2,solid2Z/2);
    G4double SiCX = 1.*cm,SiCY = 1.*cm;
    G4Box *soild_SiC = new G4Box("SiC",SiCX/2,SiCY/2,solid2Z/2);
    G4ThreeVector offset2(0, 0, 0);
    G4SubtractionSolid* ceramics_2 = new G4SubtractionSolid(
        "ceramics_2", // 新几何体名称
        solid2,            // 被减体
        soild_SiC,            // 减去体
        0,                 // 无旋转
        offset2             // 减去体的位置偏移
    );
    G4LogicalVolume *ceramics_2_logic = new G4LogicalVolume(ceramics_2,Al2O3,"ceramics_2_logic");
    G4LogicalVolume *logicSiC = new G4LogicalVolume(soild_SiC,SiC,"LogicSiC");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,solid1Z),ceramics_2_logic,"Phys_ceramics_2_up",logicWorld,false,0,checkOverlaps);
    new G4PVPlacement(0,G4ThreeVector(0.,0.,-solid1Z),ceramics_2_logic,"Phys_ceramics_2_down",logicWorld,false,0,checkOverlaps);
    G4VisAttributes *C2VisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.5));
    C2VisAtt->SetVisibility(true);
    ceramics_2_logic->SetVisAttributes(C2VisAtt);

    new G4PVPlacement(0,G4ThreeVector(0.,0.,solid1Z),logicSiC,"Phys_SiC_up",logicWorld,false,0,checkOverlaps);
    new G4PVPlacement(0,G4ThreeVector(0.,0.,-solid1Z),logicSiC,"Phys_SiC_down",logicWorld,false,0,checkOverlaps);
    G4VisAttributes *SiCVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));
    SiCVisAtt->SetVisibility(true);
    logicSiC->SetVisAttributes(SiCVisAtt);

    //third floor
    G4double solid3Z = 0.03*cm;
    G4Box *solid3 = new G4Box("Solid3",detX/2,detY/2,solid3Z/2);
    G4LogicalVolume *ceramics_3_logic = new G4LogicalVolume(solid3,Al2O3,"ceramics_3_logic");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,solid1Z+solid2Z),ceramics_3_logic,"Phys_ceramics_3_up",logicWorld,false,0,checkOverlaps);
    new G4PVPlacement(0,G4ThreeVector(0.,0.,-solid1Z-solid2Z),ceramics_3_logic,"Phys_ceramics_3_down",logicWorld,false,0,checkOverlaps);
    G4VisAttributes *C3VisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.5));
    C3VisAtt->SetVisibility(true);
    ceramics_3_logic->SetVisAttributes(C3VisAtt);
    
    return physWorld;
    
}

void DetectorConstruction::ConstructSDandField(){
    G4String trackerChamberSDname = "/TrackerChamberSD";
    auto trackerSD = new TrackerSD(trackerChamberSDname, "TrackerHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(trackerSD);
    // Setting trackerSD to all logical volumes with the same name
    // of "Chamber_LV".
    SetSensitiveDetector("LogicSiC", trackerSD, true);
}