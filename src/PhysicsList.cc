#include "PhysicsList.hh"

PhysicsList::PhysicsList()
{
  SetVerboseLevel(1);

  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  RegisterPhysics (new G4HadronElasticPhysicsXS());
  RegisterPhysics (new G4HadronPhysicsQGSP_BIC_HP());
  RegisterPhysics (new G4IonElasticPhysics());
  RegisterPhysics (new G4IonPhysicsXS());
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}

