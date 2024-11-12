#ifndef B3aEventAction_h
#define B3aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;

/// Event action class
/// In EndOfEventAction() there is collected information event per event
/// from Hits Collections, and accumulated statistic for
/// RunAction::EndOfRunAction().

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;

    void  BeginOfEventAction(const G4Event*) override;
    void  EndOfEventAction(const G4Event*) override;

  private:
    RunAction* fRunAction = nullptr;
};
#endif