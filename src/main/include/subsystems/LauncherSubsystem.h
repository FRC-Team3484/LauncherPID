#ifndef LAUNCHERSUBSYSTEM_H
#define LAUNCHERSUBSYSTEM_H

#include "Constants.h"
#include "FRC3484_Lib/utils/SC_Datatypes.h"

#include <frc2/command/SubsystemBase.h>

#include <rev/CANSparkMax.h>
#include <frc/DigitalInput.h>

#include <units/angle.h>
#include <units/angular_velocity.h>

class LauncherSubsystem : public frc2::SubsystemBase {
    public:
        LauncherSubsystem(
            int bottom_motor_can_id, 
            int top_motor_can_id,
            int launch_sensor_di_ch,
            SC::SC_PIDConstants _bottom_pidc,
            SC::SC_PIDConstants _top_pidc,
            double rpm_window
        );

        void Periodic() override;
        void SetLauncherSpeed(units::revolutions_per_minute_t speed);
        bool AtTargetRPM();
        void OpenLoopTestMotors(double power_bottom, double power_top);
        bool GetLaunchSensor();

    private:
        rev::CANSparkMax _bottom_motor;
        rev::CANSparkMax _top_motor;

        rev::SparkRelativeEncoder* _bottom_launcher_encoder;
        rev::SparkRelativeEncoder* _top_launcher_encoder;
        rev::SparkPIDController* _bottom_launcher_pid_controller;
        rev::SparkPIDController* _top_launcher_pid_controller;

        frc::DigitalInput _launch_sensor;

        bool _counter_not_null_top;
        bool _counter_not_null_bottom;

        units::revolutions_per_minute_t _target_speed;
        double _rpm_window;
};

#endif