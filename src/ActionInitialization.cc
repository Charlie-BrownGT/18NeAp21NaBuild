#include "ActionInitialization.hh"

void ActionInitialization::BuildForMaster() const
{}

void ActionInitialization::Build() const
{
  auto runAction = new RunAction();
  SetUserAction(runAction);

  SetUserAction(new EventAction(runAction));
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new StackingAction);
}