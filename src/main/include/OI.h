#ifndef OI_H
#define OI_H

#include "Constants.h"

#include <frc/XboxController.h>

class Operator_Interface{
    public:
        Operator_Interface();

        // Launcher
        bool IntakeThroughShooter();
        bool LaunchSpeaker();

        void SetRumble(double Rumble);

        int RawPOV();

    private:
        frc::XboxController _operator_controller{UserInterface::Operator::OPERATOR_CONTROLLER_PORT};
};
#endif