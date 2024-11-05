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

  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  runManager->SetUserInitialization(new B3::DetectorConstruction);
  runManager->SetUserInitialization(new B3::PhysicsList);

  runManager->SetUserInitialization(new B3a::ActionInitialization());

  auto visManager = new G4VisExecutive;
  
  visManager->Initialize();
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

  if (ui) {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    //UImanager->ApplyCommand("/control/execute beam.mac");
    ui->SessionStart();
    delete ui;
  }
  else {
    //UImanager->ApplyCommand("/control/execute beam.mac");
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  delete visManager;
  delete runManager;
}