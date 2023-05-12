#ifndef GdScintHit_h
#define GdScintHit_h 1

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


#include <G4VProcess.hh>

class GdScintHit : public G4VHit
{
  public:

      GdScintHit();
     ~GdScintHit();

      GdScintHit(const GdScintHit&);
      const GdScintHit& operator=(const GdScintHit&);
      int operator==(const GdScintHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

private:
    
    G4ThreeVector   positionScint;
    G4ThreeVector   momentumScint;
    G4ThreeVector   momDirScint;
    G4double        timeScint;
    G4double        stimeScint;
    G4double        trackIDScint;
    G4double        parentIDScint;
    G4String        particleScint;
    G4String        volNameScint;
    G4double        energyScint;
    G4double        massScint;
    G4double        velocityScint;
    G4double        trackLengthScint;
    G4double        edepScint;
    G4String        partTypeScint;
    G4double        stepNumScint;
    G4ThreeVector   vPosScint;
    G4ThreeVector   vMomDirScint;
    G4double        vKEScint;
    G4double        KEScint;
    G4String        cProcessScint;
    
    
    G4bool           rec;
    G4bool           InelasticRec;
    
    G4bool           NuclearProcess;
    
    
public:
    
    inline void SetScintPosition(G4ThreeVector position)         {positionScint = position;};
    inline G4ThreeVector GetScintPosition()                      const {return positionScint;};
    
    inline void SetScintMomentum(G4ThreeVector mom)              {momentumScint = mom;};
    inline G4ThreeVector GetScintmom()                           const {return momentumScint;};
    
    inline void SetScintMomentumDir(G4ThreeVector momDir)        {momDirScint = momDir;};
    inline G4ThreeVector GetScintmomDir()                        const {return momDirScint;};
    
    inline void SetScintTime(G4double time)                      {timeScint = time;};
    inline G4double GetScintTime()                               const {return timeScint;};
    
    inline void SetScintsTime(G4double stime)                    {stimeScint = stime;};
    inline G4double GetScintsTime()                              const {return stimeScint;};
    
    inline void SetScintTrackID(G4double trackID)                {trackIDScint = trackID;};
    inline G4double GetScintTrackID()                            const {return trackIDScint;};
    
    inline void SetScintParentID(G4double parentID)              {parentIDScint = parentID;};
    inline G4double GetScintParentID()                           const {return parentIDScint;};
    
    inline void SetScintParticle(G4String particle)               {particleScint = particle;};
    inline G4String GetScintParticle()                            const {return particleScint;};
    
    inline void SetScintVertexVolName(G4String volName)           {volNameScint = volName;};
    inline G4String GetScintVertexVolName()                       const {return volNameScint;};
    
    inline void SetScintEnergy(G4double energy)                  {energyScint = energy;};
    inline G4double GetScintEnergy()                             const {return energyScint;};
    
    inline void SetScintMass(G4double mass)                      {massScint = mass;};
    inline G4double GetScintMass()                               const {return massScint;};
    
    inline void SetScintVelocity(G4double velocity)              {velocityScint = velocity;};
    inline G4double GetScintVelocity()                           const {return velocityScint;};
    
    inline void SetScintTrackLength(G4double trackLength)        {trackLengthScint = trackLength;};
    inline G4double GetScintTrackLength()                        const {return trackLengthScint;};
    
    inline void SetScintEdep(G4double edep)                      {edepScint = edep;};
    inline G4double GetScintEdep()                               const {return edepScint;};
    
    inline void SetScintParticleType(G4String partType)          {partTypeScint = partType;};
    inline G4String GetScintParticleType()                       const {return partTypeScint;};
    
    inline void SetScintCurrentStepNumber(G4double stepNum)      {stepNumScint= stepNum;};
    inline G4double GetScintCurrentStepNumber()                  const {return stepNumScint;};
    
    inline void SetScintVertexPosition(G4ThreeVector vPos)       {vPosScint = vPos;};
    inline G4ThreeVector GetScintVertexPosition()                const {return vPosScint;};
    
    inline void SetScintVertexMomentumDirection(G4ThreeVector vMomDir)        {vMomDirScint = vMomDir;};
    inline G4ThreeVector GetScintVertexMomentumDirection()                    const {return vMomDirScint;};
    
    inline void SetScintVertexKineticEnergy(G4double vKE)        {vKEScint = vKE;};
    inline G4double GetScintVertexKineticEnergy()                const {return vKEScint;};
    
    inline void SetScintKineticEnergy(G4double KE)               {KEScint = KE;};
    inline G4double GetScintKineticEnergy()                      const{return KEScint;};
    
    inline void SetScintNuclearProcess (G4String cProcess)       {cProcessScint = cProcess;};
    inline G4String GetScintNuclearProcess()                     {return cProcessScint;};
    
    
    void SetRecoil                  (void)     { rec = true;};
    G4bool GetRecoil()                         { return rec; };
    
    void SetInelasticRecoil         (void)     { InelasticRec = true;};
    G4bool GetInelasticRecoil()                { return InelasticRec; };
    
    void NoProcess                  (void)      { NuclearProcess = false;};
    G4bool GetProcess()                         { return NuclearProcess; };


};

// vector collection of one type of hits
typedef G4THitsCollection<GdScintHit> GdScintHitsCollection;

extern G4Allocator<GdScintHit> GdScintHitsAllocator;

inline void* GdScintHit::operator new(size_t) {
  void* aScintHit;
  aScintHit = (void*) GdScintHitsAllocator.MallocSingle();
  return aScintHit;
}

inline void GdScintHit::operator delete(void* aScintHit) {
  GdScintHitsAllocator.FreeSingle((GdScintHit*) aScintHit);
}

#endif
