//GdScint Event Action

#ifdef G4UI_USE_ROOT
  #include "G4UIRoot.hh"
#endif

////////////////////////////
#include "GdScintSteppingAction.hh"
/////////////////////////////



#include "GdScintEventAction.hh"

#include "GdScintHit.hh"

#include "GdScintEventMessenger.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
//For outputting to ascii:
#include <iomanip>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
////OUTPUT                                                                 //
    G4int verboseLevel= 0;   //choose 0,1 or 2 for screen output detail    //
    G4int dataFiles = 3;     //choose 0,1,2,3 for ascii creation           //
    G4int Ntuples = 0;       //choose 1 for Ntuple creation                //
/////////////////////////////////////////////////////////////////////////////

GdScintEventAction::GdScintEventAction()
{
    GdScintCollID=-1;

    totEvents=0;
    fGdScintEvMess=new GdScintEventMessenger(this);
}

GdScintEventAction::~GdScintEventAction()
{
    delete fGdScintEvMess;
}

void GdScintEventAction::BeginOfEventAction(const G4Event* evt)
{
    G4int evtNb;
    evtNb = evt->GetEventID();

    if (GdScintCollID==-1)
    {
        G4SDManager * SDman = G4SDManager::GetSDMpointer();
        GdScintCollID = SDman->GetCollectionID("GdScintCollection");
    }
}

void GdScintEventAction::EndOfEventAction(const G4Event* evt)
{
    G4cout<<totEvents<<G4endl;
    totEvents++;

    G4RunManager *runMan = G4RunManager::GetRunManager();
    G4int runID = runMan->GetCurrentRun()->GetRunID();
    G4int evtNb = evt->GetEventID();

    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

    GdScintHitsCollection*          ScintHC    = NULL;

    G4int           n_hit = 0;

    G4double        ScintTotalEnergy = 0;
    G4ThreeVector   ScintPosition;
    G4String        ScintParticle;
//    G4double        ScintEnergy = 0;
//   G4double        ScintKE = 0;
    G4double        ScintEdep = 0;
    G4String        ScintParticleType;
//    G4double        ScintTrackLength = 0;
    G4ThreeVector   ScintMomentum;
    G4ThreeVector   ScintMomentumDir;
    G4String        ScintVertexVolumeName;
 //   G4double        ScintTrackID = 0;
 //  G4double        ScintParentID = 0;
    G4ThreeVector   ScintVertexPosition;
    G4ThreeVector   ScintVertexMomDir;
 //   G4double        ScintVertexKE = 0;
 //   G4double        ScintMass = 0;
    G4String        ScintNuclearProcess;

  ////////////////////////////////////////////////////////
  //  G4int         nucHits   = 0;
  //  G4int         InelasticNucHits = 0;

    if (HCE) ScintHC     = (GdScintHitsCollection*)     (HCE->GetHC(GdScintCollID));

//////////////////////////////////////////////////////////
//    SCINTILLATOR ANALYSIS     //
/////////////////////////////////////////////////////////

    //Analyse info from the scintillator
    if ( ScintHC )
    {
        n_hit = ScintHC->entries();
        if( verboseLevel > 1 ) {
        	G4cout<<"Total Number Of Step on this Hit "<<n_hit<<G4endl;
        }

        for (G4int i=0;i<n_hit;i++)
        {
            ScintEdep              = (*ScintHC)[i]-> GetScintEdep();

            ScintTotalEnergy += ScintEdep; // Keep it for later
        } // End of for loop
        G4cout<<"Edep in scintillator = "<<ScintTotalEnergy/MeV<<" MeV"<<G4endl;

		std::ofstream theFile6("scintillator.dat", std::ios::app);
		theFile6
		<<evtNb<<"\t"
		<<ScintTotalEnergy/MeV<<G4endl;

    } // End of if(ScintHC)

    //VisManager

    if ( G4VVisManager::GetConcreteInstance() )
    {
        G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
        G4int n_trajectories = 0;

        if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

        for (G4int i=0; i<n_trajectories; i++)
        { G4Trajectory* trj = (G4Trajectory*)
	                                ((*(evt->GetTrajectoryContainer()))[i]);
         trj->DrawTrajectory();
        }
    }

}//End of function

//Redundant functions...may use later...(good intentions!)

void GdScintEventAction::SetThreshold(G4int th){}

void GdScintEventAction::SetFileName(char const*){}
