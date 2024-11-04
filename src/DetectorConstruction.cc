#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

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

  G4Element*  O = man->FindOrBuildElement("O" , isotopes);
  G4Element* Si = man->FindOrBuildElement("Si", isotopes);
  G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);

  auto LSO = new G4Material("Lu2SiO5", 7.4 * g / cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4double innerRadius = 0*cm, outerRadius = 15*cm, hz = 10*um, startAngle = 0.*deg, spanningAngle = 360.*deg;
  
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");

  auto solidWorld = new G4Box("World", 1.*m, 1.*m, 2.*m);
  auto logicWorld = new G4LogicalVolume(solidWorld, default_mat, "World");
  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, fCheckOverlaps);                          

  // ring
  G4ThreeVector ringPos(0, 0, 1.*m);
  auto solidRing = new G4Tubs("Ring", innerRadius, outerRadius*2, hz*2, startAngle, spanningAngle);
  auto logicRing = new G4LogicalVolume(solidRing, default_mat, "Ring");                                       
  new G4PVPlacement(nullptr, ringPos, logicRing, "ring", logicWorld, false, 0, fCheckOverlaps);  

  // define crystal
  G4ThreeVector crystPos(0, 0, 0.5*m);
  auto solidCryst = new G4Box("crystal", 10*cm, 10*cm, 10*cm);
  auto logicCryst = new G4LogicalVolume(solidCryst, cryst_mat, "CrystalLV");
  new G4PVPlacement(nullptr, crystPos, logicCryst, "crystal", logicWorld, false, 0, fCheckOverlaps);

  G4ThreeVector detectorPos(0, 0, 1.*m);
  auto solidDetector = new G4Tubs("Detector", innerRadius, outerRadius, hz, startAngle, spanningAngle);
  auto logicDetector = new G4LogicalVolume(solidDetector, default_mat, "Detector");
  new G4PVPlacement(nullptr, detectorPos, logicDetector, "Detector", logicWorld, false, 0, fCheckOverlaps);  

  // patient
  G4ThreeVector patientPos(0, 0, -0.5*m);
  G4Material* patient_mat = nist->FindOrBuildMaterial("G4_BRAIN_ICRP");
  auto solidPatient = new G4Tubs("Patient", innerRadius, outerRadius, hz, startAngle, spanningAngle);
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

