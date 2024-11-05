#include "EventAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B3a
{

  EventAction::EventAction(RunAction* runAction)
  : fRunAction(runAction)
  {}

  void EventAction::BeginOfEventAction(const G4Event* /*evt*/)
  {}

  void EventAction::EndOfEventAction(const G4Event* evt )
  {
    //Hits collections
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    if(!HCE) return;

    // Get hits collections IDs
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    fCollID_cryst   = SDMan->GetCollectionID("crystal/edep");
    fCollID_IonDet = SDMan->GetCollectionID("IonDet/dose");
  }
}