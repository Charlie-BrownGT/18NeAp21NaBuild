#include "Event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
	DDEdep = 0.;
	SDEdep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	DDEdep = 0.;
	SDEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->FillNtupleDColumn(2, 0, DDEdep);
	man->AddNtupleRow(2);

	man->FillNtupleDColumn(3, 0, SDEdep);
	man->AddNtupleRow(3);
}

void MyEventAction::AddDDEdep(G4double DDedep){
	DDEdep += DDedep;
}

void MyEventAction::AddSDEdep(G4double SDedep){
	SDEdep += SDedep;
}