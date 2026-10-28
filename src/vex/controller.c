#include "vex/v5.h"

static int32_t controller_values[2][21] = {0};

int32_t vexControllerGet(V5_ControllerId id, V5_ControllerIndex index)
{
    if (id >= 0 && id < 2)
    {
        if (index >= 0 && index < 20)
        {
            return controller_values[id][index];
        }
        else if (index == BatteryCapacity)
        {
            /* skip ButtonAll and Flags enum indices, go straight to BatteryCapacity at 20 */
            return controller_values[id][20];
        }
    }

    return 0;
}

void vexSimControllerSet(V5_ControllerId id, V5_ControllerIndex index, int32_t value)
{
    if (id >= 0 && id < 2)
    {
        if (index >= 0 && index < 20)
        {
            controller_values[id][index] = value;
        }
        else if (index == BatteryCapacity)
        {
            /* skip ButtonAll and Flags enum indices, go straight to BatteryCapacity at 20 */
            controller_values[id][20] = value;
        }
    }
}

static V5_ControllerStatus controller_status[2] = {kV5ControllerOffline, kV5ControllerOffline};

V5_ControllerStatus vexControllerConnectionStatusGet(V5_ControllerId id)
{
    if (id >= 0 && id < 2)
    {
        return controller_status[id];
    }

    return kV5ControllerOffline;
}

void vexSimControllerConnectionStatusSet(V5_ControllerId id, V5_ControllerStatus status)
{
    if (id >= 0 && id < 2)
    {
        controller_status[id] = status;
    }
}

bool vexControllerTextSet(V5_ControllerId id, uint32_t line, uint32_t col, const char *str)
{
    // TODO: implement
    return false;
}