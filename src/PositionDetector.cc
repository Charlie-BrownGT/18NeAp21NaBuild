#include "PositionDetector.hh"

PositionDetector::PositionDetector(G4String name) : G4VSensitiveDetector(name)
{}

PositionDetector::~PositionDetector()
{}

G4bool PositionDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	
	G4ThreeVector posIon = preStepPoint->GetPosition();
	G4cout << "Ion position: " << posIon << G4endl;
	
	return true;
}
