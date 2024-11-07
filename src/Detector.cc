#include "Detector.hh"

Detector::Detector(G4String name) : G4VSensitiveDetector(name)
{}

Detector::~Detector()
{}

G4bool Detector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	
	G4ThreeVector posIon = preStepPoint->GetPosition();
	//G4cout << "Ion position: " << posIon << G4endl;

	G4double kineticEnergy = track->GetKineticEnergy();
	G4double totalEnergy = track->GetTotalEnergy();
	//G4cout << "Ion totalEnergy: " << totalEnergy << G4endl;

	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, 0, evt);
	man->FillNtupleDColumn(0, 1, posIon[0]);
	man->FillNtupleDColumn(0, 2, posIon[1]);
	man->FillNtupleDColumn(0, 3, posIon[2]);
	man->AddNtupleRow(0);

	man->FillNtupleDColumn(2, 0, totalEnergy);
	man->AddNtupleRow(2);

	
	if(posIon[2] < 1.05*m){
		man->FillNtupleDColumn(3, 0, totalEnergy);
		man->AddNtupleRow(3);
	}

	if(posIon[2] > 1.05*m){
		man->FillNtupleDColumn(4, 0, totalEnergy);
		man->AddNtupleRow(4);
	}
	

	return true;
}
