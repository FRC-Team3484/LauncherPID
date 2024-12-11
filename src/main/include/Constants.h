#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "FRC3484_Lib/utils/SC_ControllerMaps.h"
#include "FRC3484_Lib/utils/SC_Datatypes.h"

#include <units/time.h>
#include <units/angle.h>
#include <units/angular_velocity.h>

namespace IntakeConstants {
    // Ports
    constexpr int TRANSFER_MOTOR_CAN_ID = 42;
    constexpr int ROLLER_MOTOR_CAN_ID = 31;
    constexpr int PIECE_SENSOR_DI_CH = 0;

    // Intake roller power levels
    constexpr int ROLLER_STOP = 0;
    constexpr double ROLLER_EJECT = -1.0;
    constexpr double ROLLER_INTAKE = 0.4;

    // Transfer roller power levels
    constexpr int TRANSFER_STOP = 0;
    constexpr double TRANSFER_EJECT = -0.8;
    constexpr double TRANSFER_INTAKE = 0.4;

    constexpr bool TRANSFER_MOTOR_INVERTED = true;

    // Current limits
    constexpr uint ROLLER_STALL_LIMIT = 60;
    constexpr uint ROLLER_FREE_LIMIT = 40;
}

namespace LauncherConstants {
    // Ports
    constexpr int LEFT_MOTOR_CAN_ID = 40;
    constexpr int RIGHT_MOTOR_CAN_ID = 41;
    constexpr int LAUNCH_SENSOR_DI_CH = 2;

    // Launcher PID values
    constexpr SC::SC_PIDConstants LEFT_PID_CONSTANTS(5e-6, 1.5e-7, 0, 1.25e-4);
    constexpr SC::SC_PIDConstants RIGHT_PID_CONSTANTS(5e-6, 1.5e-7, 0, 1.25e-4);

    //Launch conditions
    constexpr double GEAR_RATIO = 1.0;
    constexpr double RPM_WINDOW_RANGE = 50;

    constexpr units::second_t WINDOW_TIME = .25_s;

    constexpr bool BOTTOM_MOTOR_INVERTED = true;
    constexpr bool TOP_MOTOR_INVERTED = true;
    
    // Launcher RPM
    constexpr units::revolutions_per_minute_t LAUNCH_STOP = 0_rpm;
    constexpr units::revolutions_per_minute_t LAUNCH_SPEAKER = 3000_rpm;
    constexpr units::revolutions_per_minute_t LAUNCH_INTAKE = -300_rpm;
}

namespace UserInterface {
    constexpr double RUMBLE_STOP = 0;

    namespace Operator {
        constexpr int OPERATOR_CONTROLLER_PORT = 1;

        //Launcher
        constexpr int INTAKE_LAUNCHER = XBOX_Y;
        constexpr int AIM_START = XBOX_X;

        constexpr double RUMBLE_HIGH = 0.5;
        constexpr double RUMBLE_LOW = 0.2;
    }
}

#endif