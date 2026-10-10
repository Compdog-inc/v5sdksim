#include "vex/v5.h"

void vexDeviceMotorVelocitySet(V5_DeviceT device, int32_t velocity)
{
    // TODO: implement
}

void vexDeviceMotorVelocityUpdate(V5_DeviceT device, int32_t velocity)
{
    // TODO: implement
}

void vexDeviceMotorVoltageSet(V5_DeviceT device, int32_t value)
{
    // TODO: implement
}

int32_t vexDeviceMotorVelocityGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

double vexDeviceMotorActualVelocityGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

int32_t vexDeviceMotorDirectionGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

void vexDeviceMotorModeSet(V5_DeviceT device, V5MotorControlMode mode)
{
    // TODO: implement
}

V5MotorControlMode vexDeviceMotorModeGet(V5_DeviceT device)
{
    // TODO: implement
    return kMotorControlModeOFF;
}

void vexDeviceMotorPwmSet(V5_DeviceT device, int32_t value)
{
    // TODO: implement
}

int32_t vexDeviceMotorPwmGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

void vexDeviceMotorCurrentLimitSet(V5_DeviceT device, int32_t value)
{
    // TODO: implement
}

int32_t vexDeviceMotorCurrentLimitGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

void vexDeviceMotorVoltageLimitSet(V5_DeviceT device, int32_t value)
{
    // TODO: implement
}

int32_t vexDeviceMotorVoltageLimitGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

void vexDeviceMotorPositionPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid)
{
    // TODO: implement
}

void vexDeviceMotorVelocityPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid)
{
    // TODO: implement
}

int32_t vexDeviceMotorCurrentGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

int32_t vexDeviceMotorVoltageGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

double vexDeviceMotorPowerGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

double vexDeviceMotorTorqueGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

double vexDeviceMotorEfficiencyGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

double vexDeviceMotorTemperatureGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

bool vexDeviceMotorOverTempFlagGet(V5_DeviceT device)
{
    // TODO: implement
    return false;
}

bool vexDeviceMotorCurrentLimitFlagGet(V5_DeviceT device)
{
    // TODO: implement
    return false;
}

uint32_t vexDeviceMotorFaultsGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

bool vexDeviceMotorZeroVelocityFlagGet(V5_DeviceT device)
{
    // TODO: implement
    return false;
}

bool vexDeviceMotorZeroPositionFlagGet(V5_DeviceT device)
{
    // TODO: implement
    return false;
}

uint32_t vexDeviceMotorFlagsGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

void vexDeviceMotorReverseFlagSet(V5_DeviceT device, bool value)
{
    // TODO: implement
}

bool vexDeviceMotorReverseFlagGet(V5_DeviceT device)
{
    // TODO: implement
    return false;
}

void vexDeviceMotorEncoderUnitsSet(V5_DeviceT device, V5MotorEncoderUnits units)
{
    // TODO: implement
}

V5MotorEncoderUnits vexDeviceMotorEncoderUnitsGet(V5_DeviceT device)
{
    // TODO: implement
    return kMotorEncoderDegrees;
}

void vexDeviceMotorBrakeModeSet(V5_DeviceT device, V5MotorBrakeMode mode)
{
    // TODO: implement
}

V5MotorBrakeMode vexDeviceMotorBrakeModeGet(V5_DeviceT device)
{
    // TODO: implement
    return kV5MotorBrakeModeCoast;
}

void vexDeviceMotorPositionSet(V5_DeviceT device, double position)
{
    // TODO: implement
}

double vexDeviceMotorPositionGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

int32_t vexDeviceMotorPositionRawGet(V5_DeviceT device, uint32_t *timestamp)
{
    // TODO: implement
    return 0;
}

void vexDeviceMotorPositionReset(V5_DeviceT device)
{
    // TODO: implement
}

double vexDeviceMotorTargetGet(V5_DeviceT device)
{
    // TODO: implement
    return 0.0;
}

void vexDeviceMotorServoTargetSet(V5_DeviceT device, double position)
{
    // TODO: implement
}

void vexDeviceMotorAbsoluteTargetSet(V5_DeviceT device, double position, int32_t velocity)
{
    // TODO: implement
}

void vexDeviceMotorRelativeTargetSet(V5_DeviceT device, double position, int32_t velocity)
{
    // TODO: implement
}

void vexDeviceMotorGearingSet(V5_DeviceT device, V5MotorGearset value)
{
    // TODO: implement
}

V5MotorGearset vexDeviceMotorGearingGet(V5_DeviceT device)
{
    // TODO: implement
    return kMotorGearSet_36;
}

void vexDeviceMotorExternalProfileSet(V5_DeviceT device, double position, int32_t velocity)
{
    // TODO: implement
}

int32_t vexDeviceMotorTypeGet(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}
