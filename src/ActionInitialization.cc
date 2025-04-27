#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{
};

ActionInitialization::~ActionInitialization()
{
};

void ActionInitialization::BuildForMaster() const
{

};

void ActionInitialization::Build() const
{
    PrimaryGenerator *primaryGenerator = new PrimaryGenerator();
    SetUserAction(primaryGenerator);
    SetUserAction(new RunAction());
    SetUserAction(new EventAction());};