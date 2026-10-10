#include "vex/v5.h"

int32_t vexControllerGet(V5_ControllerId id, V5_ControllerIndex index)
{
    // TODO: implement
    return 0;
}

V5_ControllerStatus vexControllerConnectionStatusGet(V5_ControllerId id)
{
    // TODO: implement
    return kV5ControllerVexnet;
}

bool vexControllerTextSet(V5_ControllerId id, uint32_t line, uint32_t col, const char *str)
{
    // TODO: implement
    return false;
}