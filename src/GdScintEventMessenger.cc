//Mostly relic from Scint Sim.  Easily changed for interactive commands for Gd Sim if reqd.

#include "GdScintEventMessenger.hh"
#include "GdScintEventAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"

GdScintEventMessenger::GdScintEventMessenger(GdScintEventAction * GdEA)
:GdEvAct(GdEA)
{ 
  GdEADir = new G4UIdirectory("/GdEA/");
  GdEADir->SetGuidance("Gd event action control.");

  SetThresholdCmd = new G4UIcmdWithAnInteger("/GdEA/setThreshold",this);
  SetThresholdCmd->SetGuidance("Set the threshold of the pmts");
  SetThresholdCmd->SetParameterName("Threshold",false);
  SetThresholdCmd->AvailableForStates(G4State_Idle);

  //output to a root file, set its filename  
  SetFileCmd = new G4UIcmdWithAString("/GdEA/setFile",this);
  SetFileCmd->SetGuidance("Set the output root filename");
  SetFileCmd->SetParameterName("filename",false);
  SetFileCmd->AvailableForStates(G4State_Idle);
}

GdScintEventMessenger::~GdScintEventMessenger()
{
  delete SetThresholdCmd;
  delete SetFileCmd;
  delete GdEADir;
}

void GdScintEventMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
//Set the threshold of pmts
  if( command == SetThresholdCmd )
    {
    G4int th;
    if(SetThresholdCmd->GetNewIntValue(newValue)) th=(SetThresholdCmd->GetNewIntValue(newValue));
      GdEvAct->SetThreshold(th);
   }
  
  //Set filename for root output
  else if (command == SetFileCmd) {
     GdEvAct->SetFileName(newValue.data());
     }
  }
