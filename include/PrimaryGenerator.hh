#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
 private:
  G4ParticleGun *particleGun;
  G4ParticleTable *particleTable;
  G4ParticleDefinition *particleDefinition;
  G4GeneralParticleSource *fGPS;

 public:
  PrimaryGenerator();
  ~PrimaryGenerator();


  void GeneratePrimaries(G4Event *) override;
};
#endif