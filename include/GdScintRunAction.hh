//
/// \file GdScintRunAction.hh
/// \brief Definition of the GdScintRunAction class
#ifndef GdScintRunAction_h
#define GdScintRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

class G4Run;

class GdScintRunAction : public G4UserRunAction
{
  public:
    GdScintRunAction();
  ~GdScintRunAction();  // is virtual in B4

  public:
    void BeginOfRunAction(const G4Run*);   // is virtual in B4
    void EndOfRunAction(const G4Run*);    // is virtual in B4
};

#endif
