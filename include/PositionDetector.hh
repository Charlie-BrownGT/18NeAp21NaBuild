#ifndef POSITIONDETECTOR_HH
#define POSITIONDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UserRunAction.hh"

class PositionDetector : public G4VSensitiveDetector
{
public:
	PositionDetector(G4String);
	~PositionDetector();
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};
#endif