#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("Position", "Position");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleDColumn("X");
  man->CreateNtupleDColumn("Y");
  man->CreateNtupleDColumn("Z");
  man->FinishNtuple(0);

  man->CreateNtuple("RunID", "RunID");
  man->CreateNtupleDColumn("RunID");
  man->FinishNtuple(1);

  man->CreateNtuple("TotalEnergy", "TotalEnergy");
  man->CreateNtupleDColumn("TotalEnergy");
  man->FinishNtuple(2);

  man->CreateNtuple("CrystalEnergy", "CrystalEnergy");
  man->CreateNtupleDColumn("Energy");
  man->FinishNtuple(3);

  man->CreateNtuple("IDEnergy", "IDEnergy");
  man->CreateNtupleDColumn("Energy");
  man->FinishNtuple(4);
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->OpenFile("test.root");
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4double runID = run->GetRunID();
  man->FillNtupleDColumn(1, 0, runID);
  man->AddNtupleRow(1);

  man->Write();
  man->CloseFile();
}


