//
/// \file GdScintSteppingAction.cc
/// \brief Implementation of the GdScintSteppingAction class

#include "GdScintSteppingAction.hh"
#include "G4SteppingManager.hh"
#include "globals.hh"
#include "G4StepPoint.hh"
#include "G4ReactionProduct.hh"


//For outputting to ascii:
#include <iomanip>
#include <fstream>

GdScintSteppingAction::GdScintSteppingAction()
{}

GdScintSteppingAction::~GdScintSteppingAction()
{}

G4VProcess* GdScintSteppingAction::GetCurrentProcess()
{
  return fpSteppingManager->GetfCurrentProcess();
}
 void GdScintSteppingAction::UserSteppingAction(const G4Step* aStep)
{

}
