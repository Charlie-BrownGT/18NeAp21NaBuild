#include "Detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posIon = preStepPoint->GetPosition();
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, posIon[0]);
	man->FillNtupleDColumn(2, posIon[1]);
	man->FillNtupleDColumn(3, posIon[2]);
	man->AddNtupleRow(0);
	
	return true;
}