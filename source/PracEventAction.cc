#include "PracEventAction.hh"
#include "PracRunAction.hh"

#include "G4Event.hh"
//#include "G4RunManager.hh" 
#include "g4root.hh"

#include "G4SystemOfUnits.hh"

PracEventAction::PracEventAction(PracRunAction* runAction) : G4UserEventAction(), fEnergyDeposit(0), fStepLength(0), fRunAction(runAction)
{
	// pass
}


PracEventAction::~PracEventAction() {}


void PracEventAction::BeginOfEventAction(const G4Event*)
{
    fEnergyDeposit = 0.;
    fStepLength = 0.;
}


void PracEventAction::EndOfEventAction(const G4Event* event)
{
    G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
    G4cout << "Event ID                 : " << event->GetEventID() << G4endl;
    G4cout << "Total Energy Deposit     : " << fEnergyDeposit << G4endl;
    G4cout << "Total Step Length        : " << fStepLength << G4endl;
    G4cout << "====================  End of Event Information (Manual)  ====================" << G4endl;
    G4cout << G4endl;

    if (fEnergyDeposit > 99)
    {
        fRunAction->PutStepLengthData(fStepLength);
    }

    G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
    anaMan -> FillNtupleDColumn(0, fEnergyDeposit);
    anaMan -> FillNtupleDColumn(1, fStepLength);
    anaMan -> AddNtupleRow();
}
