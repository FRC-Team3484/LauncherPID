// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Constants.h"
#include "commands/TeleopLauncherCommand.h"

using namespace IntakeConstants;
using namespace LauncherConstants;
using namespace UserInterface;

TeleopLauncherCommand::TeleopLauncherCommand(LauncherSubsystem* launcher_subsystem, IntakeSubsystem* intake_subsystem, Operator_Interface* oi) 
        : _launcher{launcher_subsystem}, _intake{intake_subsystem}, _oi{oi} {
    AddRequirements(_launcher);
    AddRequirements(_intake);
}

// Called when the command is initially scheduled.
void TeleopLauncherCommand::Initialize() {
    _state = base;
}

// Called repeatedly when this Command is scheduled to run
void TeleopLauncherCommand::Execute() {
    switch (_state) {
        case base:
            _intake->SetRollerPower(ROLLER_STOP);
            _intake->SetTransferPower(TRANSFER_STOP);
            _launcher->SetLauncherSpeed(LAUNCH_STOP);
            _oi->SetRumble(RUMBLE_STOP);

            if (_oi->IntakeThroughShooter()) _state = intake;
            if (_oi->LaunchSpeaker()) _state = launch_1;
            break;

        case intake:
            if (_intake->HasPiece()) {
                _oi->SetRumble(Operator::RUMBLE_LOW);
                _intake->SetRollerPower(ROLLER_STOP);
                _intake->SetTransferPower(TRANSFER_STOP);
                _launcher->SetLauncherSpeed(LAUNCH_STOP);
            } else {
                _oi->SetRumble(RUMBLE_STOP);
                _intake->SetRollerPower(ROLLER_INTAKE);
                _intake->SetTransferPower(TRANSFER_INTAKE);
                _launcher->SetLauncherSpeed(LAUNCH_INTAKE);
            }
            
            if (!_oi->IntakeThroughShooter()) _state = base;
            break;
        
        case launch_1:
            _intake->SetRollerPower(ROLLER_STOP);
            _intake->SetTransferPower(TRANSFER_STOP);
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);

            if (_launcher->AtTargetRPM()) _state = launch_2;
            if (!_oi->LaunchSpeaker()) _state = base;
            break;

        case launch_2:
            _intake->SetRollerPower(ROLLER_EJECT);
            _intake->SetTransferPower(TRANSFER_EJECT);
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);

            if (_launcher->GetLaunchSensor()) _state = launch_3;
            if (!_oi->LaunchSpeaker()) _state = base;
            break;

        case launch_3:
            _intake->SetRollerPower(ROLLER_EJECT);
            _intake->SetTransferPower(TRANSFER_EJECT);
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);

            if (!_launcher->GetLaunchSensor()) _state = launch_4;
            if (!_oi->LaunchSpeaker()) _state = base;
            break;

        case launch_4:
            _intake->SetRollerPower(ROLLER_EJECT);
            _intake->SetTransferPower(TRANSFER_EJECT);
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);

            _oi->SetRumble(Operator::RUMBLE_HIGH);

            if (!_oi->LaunchSpeaker()) _state = base;
            break;

        default:
            _state = base;
    }
}

// Called once the command ends or is interrupted.
void TeleopLauncherCommand::End(bool interrupted) {
    _intake->SetRollerPower(ROLLER_STOP);
    _intake->SetTransferPower(TRANSFER_STOP);
    _launcher->SetLauncherSpeed(LAUNCH_STOP);
    _oi->SetRumble(RUMBLE_STOP);
}

// Returns true when the command should end.
bool TeleopLauncherCommand::IsFinished() {
  return false;
}
