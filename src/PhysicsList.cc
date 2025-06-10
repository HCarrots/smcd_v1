#include "PhysicsList.hh"

#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
PhysicsList::PhysicsList()
{
    // 电磁
    RegisterPhysics(new G4EmStandardPhysics_option4());
    // 衰变
    RegisterPhysics(new G4DecayPhysics());
    // 放射性衰变
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList()
{
}