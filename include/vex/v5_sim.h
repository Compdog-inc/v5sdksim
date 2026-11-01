#ifndef V5_SIM_H_
#define V5_SIM_H_

#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"

/*-----------------------------------------------------------------------------*/
/** @file    v5_sim.h
 * @brief   Header for V5 Simulation API
 */
/*---------------------------------------------------------------------------*/

#include "v5_apitypes.h"
#include "v5_apiuser.h"
#include "v5_color.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Controller */

    void vexSimControllerSet(V5_ControllerId id, V5_ControllerIndex index, int32_t value);
    void vexSimControllerConnectionStatusSet(V5_ControllerId id, V5_ControllerStatus status);

    /* Competition */
    void vexSimCompetitionStatusSet(uint32_t status);

    /* Device */
    V5_DeviceT vexSimDeviceSetByIndex(uint32_t index, V5_DeviceType type, const char name[32]);
    void vexSimDeviceSet(V5_DeviceT device, V5_DeviceType type, const char name[32]);

    /* Motor */
    void vexSimDeviceMotorSupplyVoltageSet(V5_DeviceT device, int32_t voltage);
    void vexSimDeviceMotorRawRotorPositionSet(V5_DeviceT device, int32_t position);
    void vexSimDeviceMotorRotorVelocitySet(V5_DeviceT device, double velocity);
    void vexSimDeviceMotorRotorAccelerationSet(V5_DeviceT device, double acceleration);

    int32_t vexSimDeviceMotorUpdateAndGetMotorVoltage(V5_DeviceT device);

    void vexSimDeviceMotorSetType(V5_DeviceT device, int32_t type);

    // From perspective of looking at face of motor
    typedef enum _V5_MotorChassisOrientation
    {
        kMotorChassisOrientationCounterClockwisePositive = 0, // Motor is in CCW orientation
        kMotorChassisOrientationClockwisePositive = 1,        // Motor is in CW orientation
    } V5_MotorChassisOrientation;

    void vexSimDeviceMotorSetChassisOrientation(V5_DeviceT device, V5_MotorChassisOrientation orientation);

#ifdef __cplusplus
}
#endif
#endif /* V5_SIM_H_*/
