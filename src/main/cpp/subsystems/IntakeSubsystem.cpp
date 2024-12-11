// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Constants.h"
#include "subsystems/IntakeSubsystem.h"

#include <frc/smartdashboard/SmartDashboard.h>

using namespace IntakeConstants;
using namespace frc;
using namespace ctre::phoenix;

IntakeSubsystem::IntakeSubsystem(
    int roller_motor_can_id,
    int piece_sensor_di_ch,
    int transfer_motor_id
) :
    _roller_motor{roller_motor_can_id, rev::CANSparkMax::MotorType::kBrushless},
    _transfer_motor{transfer_motor_id},
    _piece_sensor{piece_sensor_di_ch}
{
    _transfer_motor.ConfigFactoryDefault();
    _transfer_motor.SetNeutralMode(motorcontrol::Brake);
    _transfer_motor.SetInverted(TRANSFER_MOTOR_INVERTED);

    _roller_motor.RestoreFactoryDefaults();
    _roller_motor.SetSmartCurrentLimit(ROLLER_STALL_LIMIT, ROLLER_FREE_LIMIT);
}

// This method will be called once per scheduler run
void IntakeSubsystem::Periodic() {}

void IntakeSubsystem::SetRollerPower(double power) {
    _roller_motor.Set(power);
}

void IntakeSubsystem::SetTransferPower(double power) {
    _transfer_motor.Set(motorcontrol::VictorSPXControlMode::PercentOutput, power);
}

bool IntakeSubsystem::HasPiece() {
    return !_piece_sensor.Get();
}