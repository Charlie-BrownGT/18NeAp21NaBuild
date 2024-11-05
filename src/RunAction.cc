#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

using namespace B3;

namespace B3a
{
  RunAction::RunAction()
  {}

  void RunAction::BeginOfRunAction(const G4Run* run)
  {}

  void RunAction::EndOfRunAction(const G4Run* run)
  {}
}

