//
/// \file GdScintDetectorConstruction.cc
/// \brief Implementation of the GdScintDetectorConstruction class

#include "GdScintDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"

#include "G4SDManager.hh"
#include "GdScintSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GdScintDetectorConstruction::GdScintDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ 

   SDman   = G4SDManager::GetSDMpointer();
   myGdScintSD = NULL;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GdScintDetectorConstruction::~GdScintDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GdScintDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //////////////////////////////////////////////////////////////
  //UNIT                                                     //
  /////////////////////////////////////////////////////////////

  G4double inch = 0.0254*m;
  G4double foot = 0.3048*m;
//  G4double pi = 4*std::atan(1.);

  ////************************************************************************
  //// MATERIALS: Data taken from http://www.webelements.com/

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density, fractionmass;
  G4double pressure, temperature;
  G4String name, symbol;
  G4int ncomponents, natoms;

  //// Define all elements used

  a = 1.00794*g/mole;
  G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1, a);

  a = 12.0107*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6, a);

//  a = 14.0*g/mole;
//  G4Element* elC14 = new G4Element(name="Carbon14", symbol="C14", z=6, a);

//  a = 14.0067*g/mole;
//  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", z=7, a);

  a = 15.9994*g/mole;
  G4Element* elO = new G4Element(name="Oxygen", symbol="O", z=8, a);

//  a=18.998*g/mole;
//  G4Element* elF = new G4Element(name="Flourine"  ,symbol="F" , z= 9., a);

//  a = 22.9897*g/mole;
//  G4Element* elNa = new G4Element(name="Sodium", symbol="Na", z=11, a);

//  a = 24.305*g/mole;
//  G4Element* elMg = new G4Element(name="Magnesium", symbol="Mg", z=12, a);

  a=26.98*g/mole;
  G4Element* elAl = new G4Element(name="Aluminium"  ,symbol="Al" , z= 13., a);

  a = 28.0855*g/mole;
  G4Element* elSi = new G4Element(name="Silicon", symbol="Si", z=14, a);

  a = 30.9738*g/mole;
  G4Element* elP = new G4Element(name="Phosphorus", symbol="P", z=15, a);

  a = 32.066*g/mole;
  G4Element* elS = new G4Element(name="Sulphur", symbol="S", z=16, a);

//  a = 35.453*g/mole;
//  G4Element* elCl = new G4Element(name="Chlorine", symbol="Cl", z=17, a);

  a = 39.95*g/mole;
  G4Element* elAr = new G4Element(name="Argon", symbol="Ar", z=18, a);

//  a=39.964*g/mole;
//  G4Element* elK = new G4Element(name="Potassium"  ,symbol="K" , z= 19, a);

//  a=40.078*g/mole;
//  G4Element* elCa = new G4Element(name="Calcium",symbol="Ca" , z= 20., a);

  a = 51.9961*g/mole;
  G4Element* elCr = new G4Element(name="Chromium", symbol="Cr", z=24, a);

  a = 54.938*g/mole;
  G4Element* elMn = new G4Element(name="Manganese", symbol="Mn", z=25, a);

  a = 55.845*g/mole;
  G4Element* elFe = new G4Element(name="Iron", symbol="Fe", z=26, a);

  a = 58.6934*g/mole;
  G4Element* elNi = new G4Element(name="Nickel", symbol="Ni", z=28, a);

//  a = 63.546*g/mole;
//  G4Element* elCu = new G4Element(name="Copper", symbol="Cu", z=29, a);

  a = 92.9064*g/mole;
  G4Element* elNb = new G4Element(name="Niobium", symbol="Nb", z=41, a);

//  a = 126.9*g/mole;
//  G4Element* elI = new G4Element(name="Iodine", symbol="I", z=53, a);

//  a=157.25*g/mole;
//  G4Element* elGd = new G4Element(name="Gadolinium"  ,symbol="Gd" , z= 64, a);

//  a = 207.2*g/mole;
//  G4Element* elPb = new G4Element(name="Lead", symbol="Pb", z=82, a);

  // Temperature of DRIFT lab
  temperature = 293.15*kelvin;

  // Create Argon gas for the Oxy GEM detector
  density =  0.001784*g/cm3; // at STP
  pressure = 1.0*atmosphere;
  G4Material* Ar_gas = new G4Material(name="Argon_gas", density, ncomponents=1,
                          kStateGas, temperature, pressure);
  Ar_gas->AddElement(elAr, natoms=1);

  // Create CO2 gas at STP
  density = 0.001964*g/cm3; // at STP
  pressure = 1.0*atmosphere;
  G4Material* CO2 = new G4Material(name="CO2_gas", density, ncomponents=2,
                                             kStateGas, temperature);
  CO2->AddElement(elC, natoms=1);
  CO2->AddElement(elO, natoms=2);

  // 1 atm Ar-CO2 mixture
  density = 0.5*(0.001784 + 0.001964)*g/cm3; //
  pressure= 1.0*atmosphere; //
  G4Material*gem_gas = new G4Material(name="gas_GEM", density, ncomponents=2, kStateGas, temperature);
  gem_gas->AddMaterial(Ar_gas, fractionmass=50.0*perCent);
  gem_gas->AddMaterial(CO2, fractionmass=50.0*perCent);

  // Create stainless steel
  density = 8.027*g/cm3;
  G4Material* SS = new G4Material(name="Stainless_steel", density, ncomponents=9);
  SS->AddElement(elFe, fractionmass=67.445*perCent);
  SS->AddElement(elCr, fractionmass=18*perCent);
  SS->AddElement(elNi, fractionmass=11*perCent);
  SS->AddElement(elMn, fractionmass=2*perCent);
  SS->AddElement(elSi, fractionmass=1*perCent);
  SS->AddElement(elNb, fractionmass=0.4*perCent);
  SS->AddElement(elS, fractionmass=0.08*perCent);
  SS->AddElement(elP, fractionmass=0.045*perCent);
  SS->AddElement(elS, fractionmass= 0.03*perCent);

  //  Mylar
  G4Material* Mylar = new G4Material("Mylar", density = 1.39*g/cm3, ncomponents = 3);
  Mylar->AddElement(elC, natoms = 10);
  Mylar->AddElement(elH, natoms = 8);
  Mylar->AddElement(elO, natoms =4);

  G4Material* Aluminium = new G4Material("Aluminium", density =2.70*g/cm3 , ncomponents=1);
  Aluminium->AddElement(elAl, natoms=1);

  // Create BC-521 Scintillator
  density = 0.89*g/cm3;
  G4Material* BC521 = new G4Material(name="BC-521", density, ncomponents=2);
  BC521->AddElement(elH, natoms = 153);
  BC521->AddElement(elC, natoms = 117);

  // Vacuum
//  G4double atomicNumber = 1.;
//  G4double massOfMole = 1.008*g/mole;
//  density = 1.e-25*g/cm3;
//  temperature = 2.73*kelvin;
//  pressure = 3.e-18*pascal;
//  G4Material* Vacuum = new G4Material("interGalactic", atomicNumber,
//                     massOfMole, density, kStateGas,
//                     temperature, pressure);

  //*************************************************************************
  // VOLUMES

    // World volume
    G4double world_sizeZ = 1.2*m;
    G4double world_sizeXY = 1.2*m;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    //----------------------------
    // Creation of the volumes
    //----------------------------

      /////////////////////////////////////////////////////////
      //World volume
      ////////////////////////////////////////////////////////

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Vacuum Vessel - cylinder
  //
  G4double vesselOut_sizeZ = 0.5*3.0*foot;      //  1/2 z length
  G4double vesselOut_sizeRmin = 0.0*foot;   // inner radius
  G4double vesselOut_sizeRmax = 1.0*foot;   // outer radius
  G4double vesselOut_sizeSPhi = 0.0;        // starting angle phi in radians
  G4double vesselOut_sizeDPhi = 2.0*pi;     // ending angle phi in radians

  G4double vesselIn_sizeZ = vesselOut_sizeZ - 0.375*inch; // outer vessel length minus wall thickness
  G4double vesselIn_sizeRmin = vesselOut_sizeRmin;   // inner radius
  G4double vesselIn_sizeRmax = vesselOut_sizeRmax - 0.375*inch;   // outer radius minus wall thickness
  G4double vesselIn_sizeSPhi = vesselOut_sizeSPhi;     // starting angle phi in radians
  G4double vesselIn_sizeDPhi = vesselOut_sizeDPhi;     // ending angle phi in radians

  G4double vessel_posX = 0.*cm;         // x position with respect to world origin
  G4double vessel_posY = 0.*cm;         // y position with respect to world origin
  G4double vessel_posZ = 0.*cm;         // z position with respect to world origin
  G4Material* vessel_mat = SS;          // stainless steel material

  G4Tubs* vesselOut = new G4Tubs("VesselOut",
                                vesselOut_sizeRmin,
                                vesselOut_sizeRmax,
                                vesselOut_sizeZ,
                                vesselOut_sizeSPhi,
                                vesselOut_sizeDPhi);

  G4Tubs* vesselIn = new G4Tubs("VesselIn",
                                vesselIn_sizeRmin,
                                vesselIn_sizeRmax,
                                vesselIn_sizeZ,
                                vesselIn_sizeSPhi,
                                vesselIn_sizeDPhi);

  G4SubtractionSolid* solidVessel = new G4SubtractionSolid("Vessel", vesselOut, vesselIn);

  G4LogicalVolume* logicVessel =
    new G4LogicalVolume(solidVessel,            //its solid
                        vessel_mat,             //its material
                        "Vessel");       //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(vessel_posX,vessel_posY,vessel_posZ), //position in the world volume
                    logicVessel,             //its logical volume
                    "Vessel",                //its name
                    logicWorld,              //its world  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  // Scintillator - cylinder
  //
  G4double scint_sizeZ = 3.0*inch;        // full z length
  G4double scint_sizeRmin = 0.0*inch;     // inner radius
  G4double scint_sizeRmax = 1.5*inch;     // outer radius
  G4double scint_sizeSPhi = 0.0;          // starting angle phi in radians
  G4double scint_sizeDPhi = 2.0*pi;       // ending angle phi in radians
  G4double scint_posX = 0.*cm;            // x position with respect to world origin
  G4double scint_posY = 0.*cm;            // y position with respect to world origin
  G4double scint_posZ = 1.0*cm + 0.5*scint_sizeZ; // z position with respect to world origin
  G4Material* scint_mat = BC521;          // Plastic scintillator material (BC521 is a placeholder)

  G4Tubs* solidScint =
    new G4Tubs("Scintillator",                    //its name
        scint_sizeRmin, scint_sizeRmax, 0.5*scint_sizeZ, scint_sizeSPhi, scint_sizeDPhi); //its dimensions

  G4LogicalVolume* logicScint =
    new G4LogicalVolume(solidScint,            //its solid
                        scint_mat,             //its material
                        "Scintillator");       //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(scint_posX,scint_posY,scint_posZ), //position in the world volume
                    logicScint,              //its logical volume
                    "Scintillator",          //its name
                    logicWorld,              //its world  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  // OXY CERN Triple GEM
  //
  G4double oxy_gem_sizeZ = 1.5*cm;   // full z length
  G4double oxy_gem_sizeXY = 10.*cm;  // full x and y lengths
  G4double oxy_gem_posX = 0.*cm;     // x position with respect to world origin
  G4double oxy_gem_posY = 0.*cm;     // y position with respect to world origin
  G4double oxy_gem_posZ = -1.0*cm - 0.5*oxy_gem_sizeZ;   // z position with respect to world origin
  G4Material* oxy_gem_mat = gem_gas; // GEM material

  G4Box* solidGEM = new G4Box("GEM",0.5*oxy_gem_sizeXY, 0.5*oxy_gem_sizeXY, 0.5*oxy_gem_sizeZ);
  G4LogicalVolume* logicGEM = new G4LogicalVolume(solidGEM,oxy_gem_mat,"GEM");
  new G4PVPlacement(0,
                    G4ThreeVector(oxy_gem_posX,oxy_gem_posY,oxy_gem_posZ),
                    logicGEM,
                    "GEM",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

    /////////////////////////
    //SENSITIVE DETECTORS  //
    /////////////////////////

//    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    
    if(!myGdScintSD)
    {
        myGdScintSD = new GdScintSD( "GdScintSD", this );
        SDman -> AddNewDetector( myGdScintSD );
    }
    logicScint -> SetSensitiveDetector ( myGdScintSD );

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
