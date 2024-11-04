#include "G4Types.hh"

#include "G4RunManagerFactory.hh"
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
  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv);}

  //use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  // Construct the default run manager
  //
  auto runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Set mandatory initialization classes
  //
  runManager->SetUserInitialization(new B3::DetectorConstruction);
  //
  runManager->SetUserInitialization(new B3::PhysicsList);

  // Set user action initialization
  //
  runManager->SetUserInitialization(new B3a::ActionInitialization());

  // Initialize visualization
  //
  auto visManager = new G4VisExecutive;
  
  // auto visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();

  // Activate score ntuple writer
  // The verbose level can be also set via UI commands
  // /score/ntuple/writerVerbose level
  // The default file type ("root") can be changed in xml, csv, hdf5
  // scoreNtupleWriter.SetDefaultFileType("xml");
  G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;
  scoreNtupleWriter.SetVerboseLevel(1);
  scoreNtupleWriter.SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output
    // (the default in G4TScoreNtupleWriter)

  if ( ! ui ) {
    // batch mode
    //UImanager->ApplyCommand("/control/execute beam.mac");
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    //UImanager->ApplyCommand("/control/execute beam.mac");
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}