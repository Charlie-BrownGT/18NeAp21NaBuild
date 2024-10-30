#include <iostream>

#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "Action.hh"

int main(int argc, char** argv)
{
	#ifdef G4MULTITHREADED
      	G4MTRunManager* runManager = new G4MTRunManager;
    #else
      	G4RunManager* runManager = new G4RunManager;
    #endif
	
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	runManager->Initialize();
	
	G4UIExecutive* ui = 0;

	if (argc == 1){
        ui = new G4UIExecutive(argc, argv);
    }

	//G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui){
		UImanager->ApplyCommand("/control/execute vis.mac");
		UImanager->ApplyCommand("/control/execute beam.mac");
		ui->SessionStart();
	}
	else{
       	UImanager->ApplyCommand("/control/execute beam.mac");
       	G4String command = "/control/execute ";
       	G4String fileName = argv[1];
       	UImanager->ApplyCommand(command+fileName);
    }
	delete visManager;
  	delete runManager;
}
