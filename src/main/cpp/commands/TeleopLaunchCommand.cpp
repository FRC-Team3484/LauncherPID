// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TeleopLaunchCommand.h"

using namespace IntakeConstants;
using namespace LauncherConstants;
using namespace UserInterface;
TeleopLaunchCommand::TeleopLaunchCommand(LauncherSubsystem* launcher_subsystem, IntakeSubsystem* intake_subsystem, Operator_Interface* oi)
        : _launcher{launcher_subsystem},_intake{intake_subsystem}, _oi{oi} { 
    AddRequirements(_launcher), AddRequirements(_intake);
}

void TeleopLaunchCommand::Initialize() {
    _state = base;
}

void TeleopLaunchCommand::Execute() {
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

            if (_intake->HasPiece() || !_oi->IntakeThroughShooter()) _state = base;
            break;

        case launch_1:
            _intake->SetRollerPower(ROLLER_STOP);
            _intake->SetTransferPower(TRANSFER_STOP);
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);
            
            if (_launcher->AtTargetRPM()) _state = launch_2;
            if (!_oi->LaunchSpeaker()) _state = base;
            break;
        
        case launch_2:
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);
            _intake->SetRollerPower(ROLLER_EJECT);
            _intake->SetTransferPower(TRANSFER_EJECT);

            if (_launcher->GetLaunchSensor()) _state = launch_3;
            if (!_oi->LaunchSpeaker()) _state = base;
            break;
        
        case launch_3:
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);
            _intake->SetRollerPower(ROLLER_EJECT);
            _intake->SetTransferPower(TRANSFER_EJECT);

            if (!_launcher->GetLaunchSensor()) _state = launch_4;
            if (!_oi->LaunchSpeaker()) _state = base;
            break;

        case launch_4:
            _launcher->SetLauncherSpeed(LAUNCH_SPEAKER);
            _intake->SetRollerPower(ROLLER_EJECT);
            _intake->SetTransferPower(TRANSFER_EJECT);

            _oi->SetRumble(Operator::RUMBLE_HIGH);

            if (!_oi->LaunchSpeaker()) _state = base;
            break;
        
        default:
            _state = base;
    }
}

void TeleopLaunchCommand::End(bool interrupted) {
    _intake->SetRollerPower(ROLLER_STOP);
    _intake->SetTransferPower(TRANSFER_STOP);
    _launcher->SetLauncherSpeed(LAUNCH_STOP);
    _oi->SetRumble(RUMBLE_STOP);
}

bool TeleopLaunchCommand::IsFinished() {
    return false;
}
