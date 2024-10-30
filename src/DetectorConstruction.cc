#include "DetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();

	G4double z, a;
	G4double density = 1.e-25*g/cm3, pressure = 1.e-5*pascal, temperature = 2.73 * kelvin;
	vacuum = new G4Material("Vacuum", z=1., a=1.008 * g/mole, density, kStateGas, temperature, pressure);

	worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexWorld[2] = {1.0, 1.0};
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);

	Li = new G4Element("Lithium","Li" , 3., 7.00*g/mole);
	LiTarget = new G4Material("LiTarget", 0.534*g/cm3, 1);
	LiTarget->AddElement(Li, 100.0*perCent);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{	
	G4double innerRadius = 0*cm, outerRadius = 5*cm, hz = 10*um, startAngle = 0.*deg, spanningAngle = 360.*deg;
	G4ThreeVector LiTargetPos(0, 0, 0.5*m);

	solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 1.*m);
	logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0, true);
	
	solidLi = new G4Tubs("solidLi", innerRadius, outerRadius, hz, startAngle, spanningAngle);
	logicLi = new G4LogicalVolume(solidLi, LiTarget, "logicLi");
	physLi = new G4PVPlacement(0, LiTargetPos, logicLi, "physLi", logicWorld, false, 0);

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{}
