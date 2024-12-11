#ifndef TELEOPLAUNCHERCOMMAND_H
#define TELEOPLAUNCHERCOMMAND_H

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
class TeleopLauncherCommand
        : public frc2::CommandHelper<frc2::Command, TeleopLauncherCommand> {
    public:
        TeleopLauncherCommand(LauncherSubsystem* launcher_subsystem, IntakeSubsystem* intake_subsystem, Operator_Interface* oi);

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