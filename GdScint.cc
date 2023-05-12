//
/// \file GdScint.cc
/// \brief Main program of the Gd Neutron Scintillator
//
// Author: Michael Wood, Canisius College

#include "GdScintDetectorConstruction.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "time.h"

#ifdef G4UI_USE_ROOT
#include "G4UIRoot.hh"
#endif

#include "G4VModularPhysicsList.hh"

#include "GdScintDetectorConstruction.hh"
#include "GdScintPrimaryGeneratorAction.hh"
//#include "GdScintPhysicsList.hh"
#include "GdScintRunAction.hh"
#include "GdScintEventAction.hh"
#include "GdScintSteppingAction.hh"

#include "G4PhysListFactory.hh"

#include "G4ScoringManager.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // Use this for the Chilean cluster
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
      //Set random seed with system time
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(seed); // set seed(G4long)
  G4long seed2 = CLHEP::HepRandom::getTheSeed();     // get current seed
  G4cout << "Current random seed = " << seed << G4endl;
  G4cout << "Current random seed = " << seed2 << G4endl;
  // Construct the default run manager
  //
  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new GdScintDetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserAction(new GdScintPrimaryGeneratorAction());
  runManager->SetUserAction(new GdScintRunAction());
  runManager->SetUserAction(new GdScintEventAction());
  runManager->SetUserAction(new GdScintSteppingAction());

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Initialize G4 kernel
  runManager->Initialize();

  //Cause the run manager to generate a single event using the
  //primary generator action registered above.
  runManager->BeamOn(0);

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
