#include "OI.h"

using namespace UserInterface::Operator;

// ----------
// Operator
// ----------

//     Intake
Operator_Interface::Operator_Interface(){};
bool Operator_Interface::IntakeThroughShooter() {return _operator_controller.GetRawButton(INTAKE_LAUNCHER);}

//     Launcher
//     -> Starts launch and aim
bool Operator_Interface::LaunchSpeaker() {return _operator_controller.GetRawButton(AIM_START);}

void Operator_Interface::SetRumble(double Rumble) {
    _operator_controller.SetRumble(frc::GenericHID::kBothRumble, Rumble);
}

int Operator_Interface::RawPOV() {
    return _operator_controller.GetPOV();
}