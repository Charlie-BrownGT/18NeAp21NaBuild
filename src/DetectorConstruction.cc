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

	Li = new G4Element("Lithium","Li" , 3., 7.00*g/mole);
	LiTarget = new G4Material("LiTarget", 0.534*g/cm3, 1);
	LiTarget->AddElement(Li, 100.0*perCent);

	YAPCe = new G4Material("YAPCe", 5.37*g/cm3, 4);
	Y = nist->FindOrBuildElement("Y");
	Ce = nist->FindOrBuildElement("Ce");
	Al = nist->FindOrBuildElement("Al");
	O = nist->FindOrBuildElement("O");
	YAPCe->AddElement(Y, 14.75*perCent);
	YAPCe->AddElement(Ce, 0.25*perCent);
	YAPCe->AddElement(Al, 25.*perCent);
	YAPCe->AddElement(O, 60.*perCent);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{	
	G4double innerRadius = 0*cm, outerRadius = 5*cm, hz = 10*um, startAngle = 0.*deg, spanningAngle = 360.*deg;
	G4ThreeVector LiTargetPos(0, 0, 0.05*m);
	G4ThreeVector SDPos(0, 0, 1.49*m);
	G4ThreeVector DDPos(0., 0., 1.*m);

	solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 1.5*m);
	logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0, true);
	
	solidLi = new G4Tubs("solidLi", innerRadius, outerRadius, hz, startAngle, spanningAngle);
	logicLi = new G4LogicalVolume(solidLi, LiTarget, "logicLi");
	physLi = new G4PVPlacement(0, LiTargetPos, logicLi, "physLi", logicWorld, false, 0);

	solidSD = new G4Box("solidSD", 0.5*m, 0.5*m, 0.01*m);
	logicSD = new G4LogicalVolume(solidSD, vacuum, "logicSD");
	physSD = new G4PVPlacement(0, SDPos, logicSD, "physSD", logicWorld, false, 0);
	
	solidDD = new G4Box("solidDD", 5.00*mm, 5.00*mm, 0.25*mm);
	logicDD = new G4LogicalVolume(solidDD, YAPCe, "logicDD");
	physDD = new G4PVPlacement(0, DDPos, logicDD, "physDD", logicWorld, false, 0);
	
	//defining the scoring volumes used for the energy deposition
	DDEnergyScoringVol = logicDD;
	SDEnergyScoringVol = logicSD;

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensSD = new MySensitiveDetector("SD");
	logicSD->SetSensitiveDetector(sensSD);

	MySensitiveDetector *sensDD = new MySensitiveDetector("DD");
	logicDD->SetSensitiveDetector(sensDD);
}