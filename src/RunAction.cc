// RunAction.cc
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SDManager.hh"

RunAction::RunAction(){}
RunAction::~RunAction() {}
void RunAction::BeginOfRunAction(const G4Run*)
{
    // 可在此处初始化
}

void RunAction::EndOfRunAction(const G4Run* run)
{}

