#include "PrimaryGenerator.hh"

/*PrimaryGenerator::PrimaryGenerator(){
    particleGun = new G4ParticleGun(1);
    particleTable = G4ParticleTable::GetParticleTable();

    G4String partical_name = "gamma";

    particleDefinition = particleTable->FindParticle(partical_name);
    particleGun->SetParticleDefinition(particleDefinition);

    G4double partical_E = 1.*MeV;
    particleGun->SetParticleEnergy(partical_E);

    G4double GunposX = 0.,GunposY = 0.,GunposZ = 0.;
    G4ThreeVector Gunpos(GunposX,GunposY,GunposZ);
    particleGun->SetParticlePosition(Gunpos);

    G4double GunpX = 0.,GunpY = 0.,GunpZ = 1.;
    G4ThreeVector Gunp(GunpX,GunpY,GunpZ);
    particleGun->SetParticleMomentumDirection(Gunp);
}

void PrimaryGenerator::GeneratePrimaries(G4Event *event){
    particleGun->GeneratePrimaryVertex(event);
}
*/

PrimaryGenerator::PrimaryGenerator() : G4VUserPrimaryGeneratorAction()
{
    /*particleGun = new G4ParticleGun(1);
    
    G4String partical_name = "e-";
    particleDefinition = particleTable->FindParticle(partical_name);
    particleGun->SetParticleDefinition(particleDefinition);
    G4double partical_E = 1.*MeV;
    particleGun->SetParticleEnergy(partical_E);
    G4double GunposX = 3*cm,GunposY = 0.,GunposZ = 0.;
    G4ThreeVector Gunpos(GunposX,GunposY,GunposZ);
    particleGun->SetParticlePosition(Gunpos);

    G4double GunpX = -1.,GunpY = 0.,GunpZ = 0.;
    G4ThreeVector Gunp(GunpX,GunpY,GunpZ);
    particleGun->SetParticleMomentumDirection(Gunp);*/

    fGPS = new G4GeneralParticleSource;

}


void PrimaryGenerator::GeneratePrimaries(G4Event *evt)
{

    //particleGun->GeneratePrimaryVertex(evt);
    fGPS->GeneratePrimaryVertex(evt);
}

PrimaryGenerator::~PrimaryGenerator()
{
    //delete particleGun;
    delete fGPS;
}