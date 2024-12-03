// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef ROBOT_H
#define ROBOT_H

#include "OI.h"
#include "Constants.h"
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/LauncherSubsystem.h"
#include "commands/TeleopLaunchCommand.h"

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <frc/PowerDistribution.h>

class Robot : public frc::TimedRobot {
    public:
        void RobotInit() override;
        void RobotPeriodic() override;
        void DisabledInit() override;
        void DisabledPeriodic() override;
        void DisabledExit() override;
        void AutonomousInit() override;
        void AutonomousPeriodic() override;
        void AutonomousExit() override;
        void TeleopInit() override;
        void TeleopPeriodic() override;
        void TeleopExit() override;
        void TestInit() override;
        void TestPeriodic() override;
        void TestExit() override;

    private:
        enum State {shoot};
        State _robot_state = shoot;

        // Power Stuff
        frc::PowerDistribution _pdp{1, frc::PowerDistribution::ModuleType::kRev};
        
        // Interface OI
        Operator_Interface _oi_operator{};

        // Subsystems
        IntakeSubsystem _intake_subsystem{IntakeConstants::ROLLER_MOTOR_CAN_ID, IntakeConstants::PIECE_SENSOR_DI_CH, IntakeConstants::TRANSFER_MOTOR_CAN_ID};
        LauncherSubsystem _launcher_subsystem{LauncherConstants::LEFT_MOTOR_CAN_ID, LauncherConstants::RIGHT_MOTOR_CAN_ID, LauncherConstants::LAUNCH_SENSOR_DI_CH, LauncherConstants::LEFT_PID_CONSTANTS, LauncherConstants::RIGHT_PID_CONSTANTS, LauncherConstants::RPM_WINDOW_RANGE};

        //Commands
        TeleopLaunchCommand _launch_command{&_launcher_subsystem, &_intake_subsystem, &_oi_operator};
};

#endif