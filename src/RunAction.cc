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
  {
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Position", "Position");
    man->CreateNtupleIColumn("Event");
    man->CreateNtupleDColumn("X");
    man->CreateNtupleDColumn("Y");
    man->CreateNtupleDColumn("Z");
    man->FinishNtuple(0);
  }

  void RunAction::BeginOfRunAction(const G4Run* run)
  {
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->OpenFile("test.root");
  }

  void RunAction::EndOfRunAction(const G4Run* run)
  {
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
	  man->CloseFile();
  }
}

