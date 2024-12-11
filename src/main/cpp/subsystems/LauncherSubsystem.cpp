// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/LauncherSubsystem.h"

#include <numbers>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace frc;
using namespace rev;
using namespace units;
using namespace LauncherConstants;

LauncherSubsystem::LauncherSubsystem(
        int bottom_motor_can_id,
        int top_motor_can_id,
        int launch_sensor_di_ch,
        SC::SC_PIDConstants bottom_pidc,
        SC::SC_PIDConstants top_pidc,
        double rpm_window
) :
    _bottom_motor{bottom_motor_can_id, CANSparkMax::MotorType::kBrushless},
    _top_motor{top_motor_can_id, CANSparkMax::MotorType::kBrushless},
    _launch_sensor{launch_sensor_di_ch}
{
    _rpm_window = rpm_window;

    _bottom_launcher_encoder = new SparkRelativeEncoder(_bottom_motor.GetEncoder());
    _top_launcher_encoder = new SparkRelativeEncoder(_top_motor.GetEncoder());
    _bottom_launcher_pid_controller = new SparkPIDController(_bottom_motor.GetPIDController());
    _top_launcher_pid_controller = new SparkPIDController(_top_motor.GetPIDController());

    if (_bottom_launcher_pid_controller != NULL) {
        _bottom_launcher_pid_controller->SetFeedbackDevice(*_top_launcher_encoder);
    }

    if (_top_launcher_pid_controller != NULL) {
        _top_launcher_pid_controller->SetFeedbackDevice(*_top_launcher_encoder);
    }

    _bottom_motor.RestoreFactoryDefaults();
    _top_motor.RestoreFactoryDefaults();

    _bottom_motor.SetInverted(BOTTOM_MOTOR_INVERTED);
    _top_motor.SetInverted(TOP_MOTOR_INVERTED);
    _bottom_motor.SetIdleMode(CANSparkBase::IdleMode::kCoast);
    _top_motor.SetIdleMode(CANSparkBase::IdleMode::kCoast);

    if (_bottom_launcher_pid_controller != NULL) {
        _bottom_launcher_pid_controller->SetP(bottom_pidc.Kp);
        _bottom_launcher_pid_controller->SetI(bottom_pidc.Ki);
        _bottom_launcher_pid_controller->SetD(bottom_pidc.Kd);
        _bottom_launcher_pid_controller->SetIZone(0);
        _bottom_launcher_pid_controller->SetFF(bottom_pidc.Kf);
        _bottom_launcher_pid_controller->SetOutputRange(-1, 1);
    }

    if (_top_launcher_pid_controller != NULL) {
        _top_launcher_pid_controller->SetP(top_pidc.Kp);
        _top_launcher_pid_controller->SetI(top_pidc.Ki);
        _top_launcher_pid_controller->SetD(top_pidc.Kd);
        _top_launcher_pid_controller->SetIZone(0);
        _top_launcher_pid_controller->SetFF(top_pidc.Kf);
        _top_launcher_pid_controller->SetOutputRange(-1, 1);
    }
}

// This method will be called once per scheduler run
void LauncherSubsystem::Periodic() {

    _counter_not_null_top = false;
    _counter_not_null_bottom = false;

    if (_bottom_launcher_pid_controller != NULL) {
        _counter_not_null_bottom = true;
        if (_target_speed == 0_rpm) {
            _bottom_launcher_pid_controller->SetReference(0, CANSparkMax::ControlType::kDutyCycle);
            _bottom_launcher_pid_controller->SetIAccum(0);
        } else {
            _bottom_launcher_pid_controller->SetReference(_target_speed.value(), CANSparkMax::ControlType::kVelocity);
        }
    }

    if (_top_launcher_pid_controller != NULL) {
        _counter_not_null_top = true;
        if (_target_speed == 0_rpm) {
            _top_launcher_pid_controller->SetReference(0, CANSparkMax::ControlType::kDutyCycle);
            _top_launcher_pid_controller->SetIAccum(0);
        } else {
            _top_launcher_pid_controller->SetReference(_target_speed.value(), CANSparkMax::ControlType::kVelocity);
        }
    }
}

void LauncherSubsystem::SetLauncherSpeed(revolutions_per_minute_t speed) {
    _target_speed = speed;
}

bool LauncherSubsystem::GetLaunchSensor() {
    return !_launch_sensor.Get();
}

bool LauncherSubsystem::AtTargetRPM() {
    bool bottom_at_speed = false;
    bool top_at_speed = false;

    if (_counter_not_null_bottom) {
        if (_target_speed != 0_rpm) {
            bottom_at_speed = std::abs(_bottom_launcher_encoder->GetVelocity()-_target_speed.value()) < _rpm_window;
        } else {
            bottom_at_speed = true;
        }
    } else {
        bottom_at_speed = true;
    }

    if (_counter_not_null_top) {
        if (_target_speed != 0_rpm) {
            top_at_speed = std::abs(_top_launcher_encoder->GetVelocity()-_target_speed.value()) < _rpm_window;
        } else {
            top_at_speed = true;
        }
    } else {
        top_at_speed = true;
    }

    return bottom_at_speed && top_at_speed;
}