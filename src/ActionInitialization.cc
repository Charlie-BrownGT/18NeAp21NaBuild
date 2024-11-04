#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "StackingAction.hh"

using namespace B3;

namespace B3a
{

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
  auto runAction = new RunAction();
  SetUserAction(runAction);

  SetUserAction(new EventAction(runAction));
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new StackingAction);
}
}

