#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace B3
{
  PrimaryGeneratorAction::PrimaryGeneratorAction()
  {
    
    //G4int n_particle = 1;
    //fParticleGun  = new G4ParticleGun(n_particle);

    // default particle kinematic
    /*
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("chargedgeantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    fParticleGun->SetParticleEnergy(124*MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    */
    particleGun = new G4GeneralParticleSource();
  }

  PrimaryGeneratorAction::~PrimaryGeneratorAction()
  {
    //delete fParticleGun;
    delete particleGun;
  }

  void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {
    /*
    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
    if (particle == G4ChargedGeantino::ChargedGeantino()) {
      G4int Z = 10, A = 18;
      G4double ionCharge   = 0.*eplus;
      G4double excitEnergy = 0.*keV;

      G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
      fParticleGun->SetParticleDefinition(ion);
      fParticleGun->SetParticleCharge(ionCharge);
    }

    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
    */
    particleGun -> GeneratePrimaryVertex(anEvent);
  }
}


