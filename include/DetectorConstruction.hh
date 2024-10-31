#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4GenericMessenger.hh"
#include "globals.hh"

#include "Detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetDDScoringVolume() const { return DDEnergyScoringVol; }

	virtual G4VPhysicalVolume *Construct();
	virtual void ConstructSDandField();
	
private:
	G4Material *vacuum, *LiTarget, *YAPCe;
	G4Element *Li, *Y, *Ce, *Al, *O;

	G4Box *solidWorld, *solidSD, *solidDD;
	G4Tubs *solidLi;
	G4VPhysicalVolume *physWorld, *physLi,*physSD, *physDD;
	G4LogicalVolume *logicWorld, *logicLi, *logicSD, *logicDD;

	G4LogicalVolume *DDEnergyScoringVol;
	
	void DefineMaterials();
};
#endif
