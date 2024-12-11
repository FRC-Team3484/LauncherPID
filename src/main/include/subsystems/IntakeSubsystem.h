#ifndef INTAKESUBSYSTEM_H
#define INTAKESUBSYSTEM_H

#include <frc2/command/SubsystemBase.h>

#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>

#include <frc/DigitalInput.h>

class IntakeSubsystem : public frc2::SubsystemBase {
    public:
        IntakeSubsystem(
            int roller_motor_can_id,
            int piece_sensor_di_ch,
            int transfer_motor_id
        );

        void Periodic() override;

        void SetRollerPower(double power);
        void SetTransferPower(double power);

        bool HasPiece();

    private:
        rev::CANSparkMax _roller_motor;
        ctre::phoenix::motorcontrol::can::VictorSPX _transfer_motor;

        frc::DigitalInput _piece_sensor;
};

#endif