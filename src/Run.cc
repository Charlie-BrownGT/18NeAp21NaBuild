#include "Run.hh"
#include "DetectorConstruction.hh"

MyRunAction::MyRunAction()
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

	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(2);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->OpenFile("test.root");
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4double runID = run->GetRunID();
	G4cout << runID << G4endl;

    man->FillNtupleDColumn(1, 0, runID);
	man->AddNtupleRow(1);

    man->Write();
	man->CloseFile();
}