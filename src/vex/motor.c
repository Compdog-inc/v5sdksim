#include "vex/v5.h"

double getGearRatio(V5MotorGearset gearset)
{
    switch (gearset)
    {
    case kMotorGearSet_36:
        return 36.0 / 1.0;
    case kMotorGearSet_18:
        return 18.0 / 1.0;
    case kMotorGearSet_06:
        return 6.0 / 1.0;
    default:
        return 1.0;
    }
}

void vexDeviceMotorVelocitySet(V5_DeviceT device, int32_t velocity)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.controlMode = kMotorControlModeVELOCITY;
    device->motor.velocityTarget = velocity;
}

void vexDeviceMotorVelocityUpdate(V5_DeviceT device, int32_t velocity)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.controlMode = kMotorControlModeVELOCITY;
    device->motor.velocityTarget = velocity;
}

void vexDeviceMotorVoltageSet(V5_DeviceT device, int32_t value)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.controlMode =
        device->motor.brakeMode == kV5MotorBrakeModeHold ? kMotorControlModeHOLD : device->motor.brakeMode == kV5MotorBrakeModeBrake ? kMotorControlModeBRAKE
                                                                                                                                     : kMotorControlModeOFF;
    device->motor.voltageTarget = value;
}

int32_t vexDeviceMotorVelocityGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    if (device->motor.controlMode == kMotorControlModeVELOCITY)
    {
        return device->motor.velocityTarget;
    }
    else
    {
        return 0;
    }
}

double vexDeviceMotorActualVelocityGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    if (device->motor.orientation == kMotorChassisOrientationClockwisePositive)
    {
        return -device->motor.rotorVelocity / getGearRatio(device->motor.gearing);
    }
    else
    {
        return device->motor.rotorVelocity / getGearRatio(device->motor.gearing);
    }
}

int32_t vexDeviceMotorDirectionGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    // TODO: implement
    return 0;
}

void vexDeviceMotorModeSet(V5_DeviceT device, V5MotorControlMode mode)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
    device->motor.controlMode = mode;
}

V5MotorControlMode vexDeviceMotorModeGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return kMotorControlModeOFF;
    }

    return device->motor.controlMode;
}

void vexDeviceMotorPwmSet(V5_DeviceT device, int32_t value)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

int32_t vexDeviceMotorPwmGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    // TODO: implement
    return 0;
}

void vexDeviceMotorCurrentLimitSet(V5_DeviceT device, int32_t value)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.currentLimit = value < 0 ? 0 : (value > 2500 ? 2500 : value);
}

int32_t vexDeviceMotorCurrentLimitGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.currentLimit;
}

void vexDeviceMotorVoltageLimitSet(V5_DeviceT device, int32_t value)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.voltageLimit = value < 0 ? 0 : (value > 12000 ? 12000 : value);
}

int32_t vexDeviceMotorVoltageLimitGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.voltageLimit;
}

void vexDeviceMotorPositionPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

void vexDeviceMotorVelocityPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

int32_t vexDeviceMotorCurrentGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.motorCurrent;
}

int32_t vexDeviceMotorVoltageGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.motorVoltage;
}

double vexDeviceMotorPowerGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    return (device->motor.motorVoltage / 1000.0) * (device->motor.motorCurrent / 1000.0);
}

double vexDeviceMotorTorqueGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    // TODO: implement
    return 0.0;
}

double vexDeviceMotorEfficiencyGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    // TODO: implement
    return 0.0;
}

double vexDeviceMotorTemperatureGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    // TODO: implement
    return 0.0;
}

bool vexDeviceMotorOverTempFlagGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return false;
    }

    // TODO: implement
    return false;
}

bool vexDeviceMotorCurrentLimitFlagGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return false;
    }

    // TODO: implement
    return false;
}

uint32_t vexDeviceMotorFaultsGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.faults;
}

bool vexDeviceMotorZeroVelocityFlagGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return false;
    }

    // TODO: implement
    return false;
}

bool vexDeviceMotorZeroPositionFlagGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return false;
    }

    // TODO: implement
    return false;
}

uint32_t vexDeviceMotorFlagsGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.flags;
}

void vexDeviceMotorReverseFlagSet(V5_DeviceT device, bool value)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

bool vexDeviceMotorReverseFlagGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return false;
    }

    // TODO: implement
    return false;
}

void vexDeviceMotorEncoderUnitsSet(V5_DeviceT device, V5MotorEncoderUnits units)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.encoderUnits = units;
}

V5MotorEncoderUnits vexDeviceMotorEncoderUnitsGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return kMotorEncoderDegrees;
    }

    return device->motor.encoderUnits;
}

void vexDeviceMotorBrakeModeSet(V5_DeviceT device, V5MotorBrakeMode mode)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.brakeMode = mode;
}

V5MotorBrakeMode vexDeviceMotorBrakeModeGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return kV5MotorBrakeModeCoast;
    }

    return device->motor.brakeMode;
}

void vexDeviceMotorPositionSet(V5_DeviceT device, double position)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    if (device->motor.orientation == kMotorChassisOrientationClockwisePositive)
    {
        position = -position;
    }

    int32_t rawPosition;
    switch (device->motor.encoderUnits)
    {
    case kMotorEncoderDegrees:
        rawPosition = (int32_t)(position * 50.0 * getGearRatio(device->motor.gearing) / 360.0);
        break;
    case kMotorEncoderRotations:
        rawPosition = (int32_t)(position * 50.0 * getGearRatio(device->motor.gearing));
        break;
    case kMotorEncoderCounts:
        rawPosition = (int32_t)(position);
        break;
    default:
        rawPosition = 0;
    }

    device->motor.rotorPositionOffset = device->motor.rawRotorPosition - rawPosition;
}

double vexDeviceMotorPositionGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    double position;
    switch (device->motor.encoderUnits)
    {
    case kMotorEncoderDegrees:
        position = (device->motor.rawRotorPosition - device->motor.rotorPositionOffset) / 50.0 / getGearRatio(device->motor.gearing) * 360.0;
        break;
    case kMotorEncoderRotations:
        position = (device->motor.rawRotorPosition - device->motor.rotorPositionOffset) / 50.0 / getGearRatio(device->motor.gearing);
        break;
    case kMotorEncoderCounts:
        position = (device->motor.rawRotorPosition - device->motor.rotorPositionOffset);
        break;
    default:
        position = 0.0;
        break;
    }

    if (device->motor.orientation == kMotorChassisOrientationClockwisePositive)
    {
        return -position;
    }
    else
    {
        return position;
    }
}

int32_t vexDeviceMotorPositionRawGet(V5_DeviceT device, uint32_t *timestamp)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        if (timestamp)
        {
            *timestamp = 0;
        }
        return 0;
    }

    if (timestamp)
    {
        *timestamp = device->timestamp;
    }

    int32_t position = device->motor.rawRotorPosition - device->motor.rotorPositionOffset;
    if (device->motor.orientation == kMotorChassisOrientationClockwisePositive)
    {
        return -position;
    }
    else
    {
        return position;
    }
}

void vexDeviceMotorPositionReset(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.rotorPositionOffset = device->motor.rawRotorPosition;
}

double vexDeviceMotorTargetGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0.0;
    }

    // TODO: implement
    return 0.0;
}

void vexDeviceMotorServoTargetSet(V5_DeviceT device, double position)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

void vexDeviceMotorAbsoluteTargetSet(V5_DeviceT device, double position, int32_t velocity)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

void vexDeviceMotorRelativeTargetSet(V5_DeviceT device, double position, int32_t velocity)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

void vexDeviceMotorGearingSet(V5_DeviceT device, V5MotorGearset value)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.gearing = value;
}

V5MotorGearset vexDeviceMotorGearingGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return kMotorGearSet_36;
    }

    return device->motor.gearing;
}

void vexDeviceMotorExternalProfileSet(V5_DeviceT device, double position, int32_t velocity)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    // TODO: implement
}

int32_t vexDeviceMotorTypeGet(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    return device->motor.motorType;
}

void vexSimDeviceMotorSupplyVoltageSet(V5_DeviceT device, int32_t voltage)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.supplyVoltage = voltage;
}

void vexSimDeviceMotorRawRotorPositionSet(V5_DeviceT device, int32_t position)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.rawRotorPosition = position;
}

void vexSimDeviceMotorRotorVelocitySet(V5_DeviceT device, double velocity)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.rotorVelocity = velocity;
}

void vexSimDeviceMotorRotorAccelerationSet(V5_DeviceT device, double acceleration)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.rotorAcceleration = acceleration;
}

int32_t vexSimDeviceMotorUpdateAndGetMotorVoltage(V5_DeviceT device)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return 0;
    }

    device->timestamp = (int32_t)vexSystemTimeGet();

    int32_t voltageLimit = device->motor.supplyVoltage < device->motor.voltageLimit ? device->motor.supplyVoltage : device->motor.voltageLimit;

    int32_t voltage = 0;
    switch (device->motor.controlMode)
    {
    case kMotorControlModeOFF:
    case kMotorControlModeBRAKE:
    case kMotorControlModeHOLD:
        voltage = device->motor.voltageTarget < -voltageLimit ? -voltageLimit : device->motor.voltageTarget > voltageLimit ? voltageLimit
                                                                                                                           : device->motor.voltageTarget;
        break;
    }

    device->motor.motorVoltage = voltage;

    if (device->motor.orientation == kMotorChassisOrientationClockwisePositive)
    {
        return -voltage;
    }
    else
    {
        return voltage;
    }
}

void vexSimDeviceMotorSetType(V5_DeviceT device, int32_t type)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.motorType = type;
}

void vexSimDeviceMotorSetChassisOrientation(V5_DeviceT device, V5_MotorChassisOrientation orientation)
{
    if (!device || device->type != kDeviceTypeMotorSensor)
    {
        return;
    }

    device->motor.orientation = orientation;
}