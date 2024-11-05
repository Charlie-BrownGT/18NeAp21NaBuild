#include "DetectorConstruction.hh"



namespace B3
{

DetectorConstruction::DetectorConstruction()
{
  DefineMaterials();
}

void DetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();

  G4bool isotopes = false;

  O = man->FindOrBuildElement("O" , isotopes);
  G4Element* Si = man->FindOrBuildElement("Si", isotopes);
  G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);

  auto LSO = new G4Material("Lu2SiO5", 7.4 * g / cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);

  G4double z, a;
	G4double density = 1.e-25*g/cm3, pressure = 1.e-5*pascal, temperature = 2.73 * kelvin;
	vacuum = new G4Material("Vacuum", z=1., a=1.008 * g/mole, density, kStateGas, temperature, pressure);

  Li = new G4Element("Lithium","Li" , 3., 7.00*g/mole);
	LiTarget = new G4Material("LiTarget", 0.534*g/cm3, 1);
	LiTarget->AddElement(Li, 100.0*perCent);

  YAPCe = new G4Material("YAPCe", 5.37*g/cm3, 4);
	Y = man->FindOrBuildElement("Y");
	Ce = man->FindOrBuildElement("Ce");
	Al = man->FindOrBuildElement("Al");
	//O = man->FindOrBuildElement("O");
	YAPCe->AddElement(Y, 14.75*perCent);
	YAPCe->AddElement(Ce, 0.25*perCent);
	YAPCe->AddElement(Al, 25.*perCent);
	YAPCe->AddElement(O, 60.*perCent);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4double innerRadius = 0*cm, outerRadius = 15*cm, hz = 10*um, startAngle = 0.*deg, spanningAngle = 360.*deg;
  G4double IDinnerRadius = 0*cm, IDouterRadius = 30*cm, IDhz = 20*cm, IDstartAngle = 0.*deg, IDspanningAngle = 360.*deg;

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");

  auto solidWorld = new G4Box("World", 1.*m, 1.*m, 2.*m);
  auto logicWorld = new G4LogicalVolume(solidWorld, default_mat, "World");
  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, fCheckOverlaps);                          

  // define crystal, used as a detector later
  G4ThreeVector crystPos(0, 0, 0.5*m);
  auto solidCryst = new G4Box("crystal", 10.*cm, 10.*cm, 0.5*mm);
  auto logicCryst = new G4LogicalVolume(solidCryst, cryst_mat, "CrystalLV");
  new G4PVPlacement(nullptr, crystPos, logicCryst, "crystal", logicWorld, false, 0, fCheckOverlaps);

  // patient, used as a detector later
  G4ThreeVector patientPos(0, 0, 0.75*m);
  G4Material* patient_mat = nist->FindOrBuildMaterial("G4_BRAIN_ICRP");
  auto solidPatient = new G4Tubs("Patient", IDinnerRadius, IDouterRadius, IDhz, IDstartAngle, IDspanningAngle);
  auto logicPatient = new G4LogicalVolume(solidPatient, patient_mat, "PatientLV");                                        
  new G4PVPlacement(nullptr, patientPos, logicPatient, "Patient", logicWorld, false, 0, fCheckOverlaps);          

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // declare crystal as a MultiFunctionalDetector scorer
  auto cryst = new G4MultiFunctionalDetector("crystal");
  G4SDManager::GetSDMpointer()->AddNewDetector(cryst);
  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
  cryst->RegisterPrimitive(primitiv1);
  SetSensitiveDetector("CrystalLV",cryst);

  // declare patient as a MultiFunctionalDetector scorer
  auto patient = new G4MultiFunctionalDetector("patient");
  G4SDManager::GetSDMpointer()->AddNewDetector(patient);
  G4VPrimitiveScorer* primitiv2 = new G4PSDoseDeposit("dose");
  patient->RegisterPrimitive(primitiv2);
  SetSensitiveDetector("PatientLV",patient);
}
}

