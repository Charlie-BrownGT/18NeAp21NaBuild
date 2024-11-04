#ifndef B3PhysicsList_h
#define B3PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

namespace B3
{

/// Modular physics list
///
/// It includes the folowing physics builders
/// - G4DecayPhysics
/// - G4RadioactiveDecayPhysics
/// - G4EmStandardPhysics

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
  ~PhysicsList() override = default;

  void SetCuts() override;
};

}

#endif

