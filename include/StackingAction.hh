#ifndef B3StackingAction_h
#define B3StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

namespace B3
{

/// Stacking action class : manage the newly generated particles
///
/// One wishes do not track secondary neutrino.Therefore one kills it
/// immediately, before created particles will  put in a stack.

class StackingAction : public G4UserStackingAction
{
  public:
    StackingAction() = default;
    ~StackingAction() override = default;

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
};

}
#endif
