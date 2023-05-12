#include "GdScintSD.hh"
#include "GdScintDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4HEVector.hh"


GdScintSD::GdScintSD(G4String name, GdScintDetectorConstruction* GdSD) 
  :G4VSensitiveDetector(name),GdDetector(GdSD)
{
  G4String HCname="GdScintCollection";
  collectionName.insert(HCname);
}

GdScintSD::~GdScintSD()
{;}

void GdScintSD::Initialize(G4HCofThisEvent* HCE)
{
  GdScintCollection = new GdScintHitsCollection( SensitiveDetectorName, collectionName[0] ); 

  HitID = -1;
  verboseLevel=0;
}


G4bool GdScintSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
////Get the Scint hit
    G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
    G4VPhysicalVolume* physVol = theTouchable->GetVolume();
    G4int ScintNumber = 0;
    ScintNumber= physVol->GetCopyNo();
	
	G4double edep = aStep->GetTotalEnergyDeposit();
       	
	if (edep==0) return false;
	
	
    GdScintHit* aScintHit = new GdScintHit();

    aScintHit->SetScintPosition(aStep->GetPostStepPoint()->GetPosition());
    aScintHit->SetScintTime(aStep->GetPostStepPoint()->GetGlobalTime());
    aScintHit->SetScintsTime(aStep->GetPreStepPoint()->GetGlobalTime());
    aScintHit->SetScintParticle(aStep->GetTrack()->GetDefinition()->GetParticleName());
    aScintHit->SetScintEnergy(aStep->GetTrack()->GetKineticEnergy());
    aScintHit->SetScintEdep(aStep->GetTotalEnergyDeposit());
    aScintHit->SetScintParticleType(aStep->GetTrack()->GetDefinition()->GetParticleType());
    aScintHit->SetScintTrackLength(aStep->GetStepLength());
    aScintHit->SetScintMomentum(aStep->GetTrack()->GetMomentum());
    aScintHit->SetScintMomentumDir(aStep->GetTrack()->GetMomentumDirection());
    aScintHit->SetScintVertexVolName(aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName());
    aScintHit->SetScintTrackID(aStep->GetTrack()->GetTrackID());
    aScintHit->SetScintParentID(aStep->GetTrack()->GetParentID());
    aScintHit->SetScintKineticEnergy(aStep->GetTrack()->GetKineticEnergy());
    aScintHit->SetScintCurrentStepNumber(aStep->GetTrack()->GetCurrentStepNumber());
    aScintHit->SetScintVertexPosition(aStep->GetTrack()->GetVertexPosition());
    aScintHit->SetScintVelocity(aStep->GetTrack()->GetVelocity());
    aScintHit->SetScintVertexMomentumDirection(aStep->GetTrack()->GetVertexMomentumDirection());
    aScintHit->SetScintVertexKineticEnergy(aStep->GetTrack()->GetVertexKineticEnergy());
    aScintHit->SetScintMass(aStep->GetTrack()->GetDynamicParticle()->GetMass());
    
    if (aStep->GetTrack()->GetCreatorProcess()) {
        aScintHit->SetScintNuclearProcess(aStep->GetTrack()->GetCreatorProcess()->GetProcessName());
    } else {
        aScintHit->NoProcess();
    }

    // hit is nuclear recoil
    if ( aStep->GetTrack()->GetCreatorProcess() ) {
        G4String part = aStep->GetTrack()->GetDefinition()->GetParticleType();
        G4String proc = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
        
        if ( proc ) {
            if ( part == "nucleus" ){
                if ( (proc == "pi+Elastic") || (proc == "pi-Elastic") || (proc == "k+Elastic") || (proc == "k-Elastic") || (proc == "k0LElastic") ||(proc == "k0SElastic") || (proc == "protonElastic") || (proc == "neutronElastic") ) {
                    aScintHit->SetRecoil();
                }
            }
        }        
    }

    // hit is inelastic nuclear recoil
    if( aStep->GetTrack()->GetCreatorProcess() ) {
        G4String part = aStep->GetTrack()->GetDefinition()->GetParticleType();
        G4String proc = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
        
        if( part != "gamma" ) {
            if( (proc == "pi+Inelastic") || (proc == "pi-Inelastic") || (proc == "k+Inelastic") || (proc == "k-Inelastic") || (proc == "k0LInelastic") ||(proc == "k0SInelastic") || (proc == "protonInelastic") || (proc == "neutronInelastic")){
                aScintHit->SetInelasticRecoil();
            }
        }
    }

 
HitID = GdScintCollection->insert(aScintHit);
 
   return true;
}

void GdScintSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    G4String HCname = collectionName[0];
    static G4int HCID = -1;
    if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(HCname);

    HCE->AddHitsCollection(HCID,GdScintCollection);
  
    G4int nHits = GdScintCollection->entries();
    if (verboseLevel>=1) {
        G4cout << "     Number of Scint hits: " << nHits << G4endl;
//    if (verboseLevel>=1)
//        GdScintCollection->PrintScintHits();

  }
}

void GdScintSD::clear()
{;}

void GdScintSD::DrawScint()
{;}

void GdScintSD::PrintScint()
{;}
