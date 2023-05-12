//
/// \file GdScintPrimaryGeneratorAction.cc
/// \brief Implementation of the GdScintPrimaryGeneratorAction class

#include "GdScintPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GdScintPrimaryGeneratorAction::GdScintPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fGEMDetector(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(10.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GdScintPrimaryGeneratorAction::~GdScintPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GdScintPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
  //

  G4double gemSizeXY = 0;
  G4double gemSizeZ = 0;

  if (!fGEMDetector)
  {
    G4LogicalVolume* gemLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("GEM");
    if ( gemLV ) fGEMDetector = dynamic_cast<G4Box*>(gemLV->GetSolid());
  }

  if ( fGEMDetector ) {
    gemSizeXY = fGEMDetector->GetXHalfLength()*2.;
    gemSizeZ = fGEMDetector->GetZHalfLength()*2.;
  }
  else  {
    G4ExceptionDescription msg;
    msg << "GEM detector volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("GdgemPrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }

  G4double size = 0.5;
  G4double x0 = size * gemSizeXY * (G4UniformRand()-0.5);
  G4double y0 = size * gemSizeXY * (G4UniformRand()-0.5);
  G4double z0 = -2.0 * gemSizeZ;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
