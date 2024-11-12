#include "G4Types.hh"

#include "G4RunManagerFactory.hh"
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"

#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4AnalysisManager.hh"
#include "G4TScoreNtupleWriter.hh"

#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc,char** argv)
{
  #ifdef G4MULTITHREADED
      	G4MTRunManager* runManager = new G4MTRunManager;
  #else
      	G4RunManager* runManager = new G4RunManager;
  #endif

  runManager->SetUserInitialization(new DetectorConstruction);
  runManager->SetUserInitialization(new PhysicsList);
  runManager->SetUserInitialization(new ActionInitialization());
  runManager->Initialize();

  G4UIExecutive* ui = nullptr;
  
  if ( argc == 1 ) { 
    ui = new G4UIExecutive(argc, argv);
  }

  auto visManager = new G4VisExecutive;
  visManager->Initialize();
  auto UImanager = G4UImanager::GetUIpointer();

  // Activate score ntuple writer
  //G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;
  //scoreNtupleWriter.SetVerboseLevel(1);
  //scoreNtupleWriter.SetNtupleMerging(true);

  if (ui) {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    UImanager->ApplyCommand("/control/execute beam.mac");
    ui->SessionStart();
    delete ui;
  }
  else {
    UImanager->ApplyCommand("/control/execute beam.mac");
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  delete visManager;
  delete runManager;
}