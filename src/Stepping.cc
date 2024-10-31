#include "Stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	DDEventAction = eventAction;
	SDEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *DDScoringVolume = detectorConstruction->GetDDScoringVolume();
	G4LogicalVolume *SDScoringVolume = detectorConstruction->GetSDScoringVolume();
	
	if(volume != DDScoringVolume)
		return;
	
	G4double DDedep = step->GetTotalEnergyDeposit();
	DDEventAction->AddDDEdep(DDedep);

	//G4double SDedep = step->GetTotalEnergyDeposit();
	//SDEventAction->AddSDEdep(SDedep);
}