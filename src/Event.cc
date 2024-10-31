#include "Event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
	DDEdep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	DDEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->FillNtupleDColumn(2, 0, DDEdep);
	
	man->AddNtupleRow(2);
}

void MyEventAction::AddEdep(G4double DDedep){
	DDEdep += DDedep;
}