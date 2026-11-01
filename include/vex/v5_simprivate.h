#ifndef V5_SIM_PRIVATE_H_
#define V5_SIM_PRIVATE_H_

#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"
#include "memory.h"

/*-----------------------------------------------------------------------------*/
/** @file    v5_simprivate.h
 * @brief   Private Header for V5 Simulation API
 */
/*---------------------------------------------------------------------------*/

#include "v5_apitypes.h"
#include "v5_apiuser.h"
#include "v5_color.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void loadSimExtensions();

    typedef struct _V5_MotorData
    {
        int32_t motorType;
        V5MotorControlMode controlMode;
        V5MotorBrakeMode brakeMode;
        V5MotorEncoderUnits encoderUnits;
        V5MotorGearset gearing;
        V5_MotorChassisOrientation orientation;

        uint32_t flags;
        uint32_t faults;

        int32_t currentLimit;
        int32_t voltageLimit;

        int32_t supplyVoltage;
        int32_t rawRotorPosition;
        int32_t rotorPositionOffset;
        double rotorVelocity;
        double rotorAcceleration;

        int32_t motorVoltage;
        int32_t motorCurrent;

        union
        {
            int32_t voltageTarget;
            int32_t velocityTarget;
        };
    } V5_MotorData;

    static inline void V5_MotorData_init(V5_MotorData *motorData)
    {
        memset(motorData, 0, sizeof(V5_MotorData));

        motorData->motorType = 0;
        motorData->controlMode = kMotorControlModeOFF;
        motorData->brakeMode = kV5MotorBrakeModeCoast;
        motorData->encoderUnits = kMotorEncoderDegrees;
        motorData->gearing = kMotorGearSet_36;
        motorData->orientation = kMotorChassisOrientationCounterClockwisePositive;

        motorData->flags = 0;
        motorData->faults = 0;

        motorData->currentLimit = 2500;
        motorData->voltageLimit = 12000;

        motorData->supplyVoltage = 0;
        motorData->rawRotorPosition = 0;
        motorData->rotorPositionOffset = 0;
        motorData->rotorVelocity = 0.0;
        motorData->rotorAcceleration = 0.0;

        motorData->motorVoltage = 0;
        motorData->motorCurrent = 0;
    }

    typedef struct _V5_Device
    {
        V5_DeviceType type;
        int32_t timestamp;
        char name[32];

        union
        {
            V5_MotorData motor;
        };
    } V5_Device;

#ifdef __cplusplus
}
#endif
#endif /* V5_SIM_PRIVATE_H_*/
