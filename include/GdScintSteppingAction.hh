//
/// \file GdScintSteppingAction.hh
/// \brief Definition of the GdScintSteppingAction class

#ifndef GdScintSteppingAction_H
#define GdScintSteppingAction_H 1

#include "G4UserSteppingAction.hh"
#include "G4VProcess.hh"

#include "G4Track.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

class GdScintSteppingAction : public G4UserSteppingAction
{
  public:

   GdScintSteppingAction();
  ~GdScintSteppingAction();

  public:

   virtual void UserSteppingAction(const G4Step* aStep);
   G4VProcess* GetCurrentProcess();


  private:

};

#endif
