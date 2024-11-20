#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{
  DefineMaterials();
}

void DetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();

  G4double z, a;
  G4double density = 1.e-25*g/cm3, pressure = 1.e-5*pascal, temperature = 2.73 * kelvin;
  vacuum = new G4Material("Vacuum", z=1., a=1.008 * g/mole, density, kStateGas, temperature, pressure);

  C = new G4Element("Carbon","C" , 6., 12.00*g/mole);
  F = new G4Element("Flourine","F" , 9., 38.00*g/mole);
  CF4 = new G4Material("CF4", 88*g/mole, 2);
  CF4->AddElement(C, 13.65*perCent);
  CF4->AddElement(F, 86.35*perCent);

  Li = new G4Element("Lithium","Li" , 3., 7.00*g/mole);
  LiTarget = new G4Material("LiTarget", 0.534*g/cm3, 1);
  LiTarget->AddElement(Li, 100.0*perCent);

  YAPCe = new G4Material("YAPCe", 5.37*g/cm3, 4);
  Y = man->FindOrBuildElement("Y");
  Ce = man->FindOrBuildElement("Ce");
  Al = man->FindOrBuildElement("Al");
  O = man->FindOrBuildElement("O");
  YAPCe->AddElement(Y, 14.75*perCent);
  YAPCe->AddElement(Ce, 0.25*perCent);
  YAPCe->AddElement(Al, 25.*perCent);
  YAPCe->AddElement(O, 60.*perCent);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  solidWorld = new G4Box("World", 1.*m, 1.*m, 3.*m);
  logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
  physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, fCheckOverlaps);                          

  // define lithium target
  G4double TinnerRadius = 0*cm, TouterRadius = 5*cm, Thz = 25.*um, TstartAngle = 0.*deg, TspanningAngle = 360.*deg;
  G4ThreeVector targetPos(0, 0, 0);

  solidTarget = new G4Tubs("ID", TinnerRadius, TouterRadius, Thz, TstartAngle, TspanningAngle);
  logicTarget = new G4LogicalVolume(solidTarget, LiTarget, "LiTarget");
  physTarget = new G4PVPlacement(nullptr, targetPos, logicTarget, "target", logicWorld, false, 0, fCheckOverlaps);

  // define crystal, used as a detector later
  G4ThreeVector crystPos(0, 0, 1.*m);
  solidCryst = new G4Box("crystal", 1.*cm, 1.*cm, 0.005*mm);
  logicCryst = new G4LogicalVolume(solidCryst, YAPCe, "CrystalLV");
  physCryst = new G4PVPlacement(nullptr, crystPos, logicCryst, "crystal", logicWorld, false, 0, fCheckOverlaps);

  // Definitions for ID geometry 
	G4double dx = 5.0 * cm;  // Half-length along X-axis
	G4double dy = 20.0 * cm;  // Half-length along Y-axis
	G4double dz = 20.0 * cm;  // Half-length along Z-axis
	G4double alpha = 30. * deg;  // Angle between Y-axis and the Z-side
	G4double theta = 0. * deg;  // Tilt of Z-axis relative to global Z
	G4double phi = 0. * deg;    // Azimuthal angle of Z-axis relative to global X
	G4RotationMatrix* rotation = new G4RotationMatrix();
	rotation->rotateY(90*deg);
	G4ThreeVector IDposition = G4ThreeVector(0, 0, 130*cm);

  solidID = new G4Para("MyPara", dx, dy, dz, alpha, theta, phi);
	logicID = new G4LogicalVolume(solidID, CF4, "logicID");
	physID = new G4PVPlacement(rotation, IDposition, logicID, "physID", logicWorld, false, 0, true);

  // Print materials
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
  Detector *Cryst = new Detector("Cryst");
  logicCryst->SetSensitiveDetector(Cryst);

  Detector *ID = new Detector("ID");
  logicID->SetSensitiveDetector(ID);
}


