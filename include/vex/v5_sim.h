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

    void vexSimControllerSet(V5_ControllerId id, V5_ControllerIndex index, int32_t value);
    void vexSimControllerConnectionStatusSet(V5_ControllerId id, V5_ControllerStatus status);

#ifdef __cplusplus
}
#endif
#endif /* V5_SIM_H_*/
