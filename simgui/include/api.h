#pragma once

#include <stdint.h>
#include "vex/v5.h"

#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(AS_LIBRARY)
#define SIMGUI_API __declspec(dllexport)
#else
#define SIMGUI_API __declspec(dllimport)
#endif
#define SIMGUI_CALL __cdecl
#else
#if defined(AS_LIBRARY)
#define SIMGUI_API __attribute__((visibility("default")))
#else
#define SIMGUI_API
#endif
#define SIMGUI_CALL
#endif

#ifdef __cplusplus
#define SIMGUI_EXTERN_C extern "C"
#else
#define SIMGUI_EXTERN_C extern
#endif

struct SimFunctionTable
{
    void (*vexSimControllerSet)(V5_ControllerId, V5_ControllerIndex, int32_t);
    void (*vexSimControllerConnectionStatusSet)(V5_ControllerId, V5_ControllerStatus);
    void (*vexSimCompetitionStatusSet)(uint32_t);
    uint32_t (*vexCompetitionStatus)(void);
    V5_DeviceT (*vexDevicesGet)(void);
};

SIMGUI_EXTERN_C SIMGUI_API int SIMGUI_CALL loadFunctionTable(SimFunctionTable *functionTable);