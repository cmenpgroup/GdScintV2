//
/// \file GdScintRunAction.cc
/// \brief Implementation of the GdScintRunAction class

#include "GdScintAnalysis.hh"

#include "GdScintRunAction.hh"
#include "GdScintDetectorConstruction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//For outputting to ascii:
#include <iomanip>
#include <fstream>


GdScintRunAction::GdScintRunAction()
{}

GdScintRunAction::~GdScintRunAction()
{}

void GdScintRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    G4int nbEventInRun;
    nbEventInRun = aRun->GetNumberOfEventToBeProcessed();

    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/tracking/storeTrajectory 1");

   if (G4VVisManager::GetConcreteInstance())
    { G4cout << "run visualisation" << G4endl;
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    }

    std::ofstream theFile3("NumOfEvent.dat", std::ios::app);
    theFile3 <<nbEventInRun<<"\n";

    // save Rndm status
    G4RunManager::GetRunManager()->SetRandomNumberStore(true);
    G4Random::showEngineStatus();
}

void GdScintRunAction::EndOfRunAction(const G4Run* aRun)
{
  if (G4VVisManager::GetConcreteInstance())
 {
     G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
 }
}
