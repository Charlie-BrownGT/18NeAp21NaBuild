#ifndef B3PhysicsList_h
#define B3PhysicsList_h 1

#include "G4VModularPhysicsList.hh"


#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"

namespace B3
{
  class PhysicsList: public G4VModularPhysicsList
  {
  public:
    PhysicsList();
    ~PhysicsList() override = default;

    void SetCuts() override;
  };
}
#endif

