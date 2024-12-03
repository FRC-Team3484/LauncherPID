// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef TELEOPLAUNCHCOMMAND_H
#define TELEOPLAUNCHCOMMAND_H

#include "OI.h"
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/LauncherSubsystem.h"

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TeleopLaunchCommand
        : public frc2::CommandHelper<frc2::Command, TeleopLaunchCommand> {
    public:
        TeleopLaunchCommand(LauncherSubsystem* launcher_Subsystem, IntakeSubsystem* intake_subsystem, Operator_Interface* oi );
    
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        enum State {base, intake, launch_1, launch_2, launch_3, launch_4};
        State _state = base;

        LauncherSubsystem* _launcher;
        IntakeSubsystem* _intake;
        Operator_Interface* _oi;
};

#endif