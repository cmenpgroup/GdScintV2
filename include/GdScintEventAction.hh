//
/// \file GdScintEventAction.hh
/// \brief Definition of the GdScintEventAction class
#ifndef GdScintEventAction_H
#define GdScintEventAction_H 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//2017: follwing have been changed:
#ifdef ANALYSIS_USE
 #include "TROOT.h"
 #include "TFile.h"
 #include "TNtuple.h"
 #include "TTree.h"
 #include "TH1D.h"
#endif

class GdScintEventMessenger;

class GdScintEventAction : public G4UserEventAction
{
  public:
    GdScintEventAction();
    virtual ~GdScintEventAction();

  public:
    virtual void   BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);

    void WriteRecoilToFile(G4int);
    void SetThreshold(G4int);
    void SetFileName(const char*);

  public:
         G4double      particleke;

  private:
  G4int                       GdScintCollID;

  G4int totEvents; //total number of events processed
  G4int fThreshold;

  GdScintEventMessenger* fGdScintEvMess;

};

#endif








