#include "StackingAction.hh"

#include "G4Track.hh"
#include "G4NeutrinoE.hh"



G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{
  //keep primary particle
  if (track->GetParentID() == 0) return fUrgent;

  //kill secondary neutrino
  if (track->GetDefinition() == G4NeutrinoE::NeutrinoE()) return fKill;
  else return fUrgent;
}