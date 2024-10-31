#include "Stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	DDEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetDDScoringVolume();
	
	if(volume != fScoringVolume)
		return;
	
	G4double DDedep = step->GetTotalEnergyDeposit();
	DDEventAction->AddEdep(DDedep);
}