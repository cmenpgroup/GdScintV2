#include "GdScintHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <iomanip>

G4Allocator<GdScintHit> GdScintHitsAllocator;

GdScintHit::GdScintHit()
{
    positionScint = G4ThreeVector(0., 0., 0.);
    
    timeScint = 0.;

	rec = false;
	InelasticRec = false;
}

GdScintHit::~GdScintHit() {;}

GdScintHit::GdScintHit(const GdScintHit & right)
{

  positionScint  = right.positionScint;
  rec = right.rec;
  InelasticRec = right.InelasticRec;
  timeScint = right.timeScint;

}

const GdScintHit & GdScintHit::operator=(const GdScintHit & right)
{
  positionScint  = right.positionScint;
  rec = right.rec;
  InelasticRec = right.InelasticRec;  
  timeScint = right.timeScint;
  
  return *this;
}

int GdScintHit::operator==(const GdScintHit & right) const
{
  return 0;
}

void GdScintHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

  if(pVVisManager) {
    G4Circle circle(positionScint);
    circle.SetScreenSize(0.002);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,1.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void GdScintHit::Print()
{
  //       G4cout << "      Scint hit: " << std::setw(5) << G4BestUnit(time,"Time")
  //          <<" at " << G4BestUnit(pos,"Length") << G4endl;
}
