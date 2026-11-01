#include "api.h"
#include "vex/v5.h"

#include "simgui.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

static SimFunctionTable *functionTable = nullptr;

static DWORD WINAPI guiThread(void *pvParameters)
{
    runGui();
    // force exit when the GUI thread exits to simplify exiting the simulation
    ExitProcess(0);
    return 0;
}

SIMGUI_EXTERN_C SIMGUI_API int SIMGUI_CALL loadFunctionTable(SimFunctionTable *table)
{
    functionTable = table;
    CreateThread(NULL, 0, guiThread, NULL, 0, NULL);
    return 0;
}

// redirect function calls to function table
SIMGUI_EXTERN_C void vexSimControllerSet(V5_ControllerId id, V5_ControllerIndex index, int32_t value)
{
    if (functionTable && functionTable->vexSimControllerSet)
    {
        functionTable->vexSimControllerSet(id, index, value);
    }
}

SIMGUI_EXTERN_C void vexSimControllerConnectionStatusSet(V5_ControllerId id, V5_ControllerStatus status)
{
    if (functionTable && functionTable->vexSimControllerConnectionStatusSet)
    {
        functionTable->vexSimControllerConnectionStatusSet(id, status);
    }
}

SIMGUI_EXTERN_C void vexSimCompetitionStatusSet(uint32_t status)
{
    if (functionTable && functionTable->vexSimCompetitionStatusSet)
    {
        functionTable->vexSimCompetitionStatusSet(status);
    }
}

SIMGUI_EXTERN_C uint32_t vexCompetitionStatus(void)
{
    if (functionTable && functionTable->vexCompetitionStatus)
    {
        return functionTable->vexCompetitionStatus();
    }
    return 0;
}

SIMGUI_EXTERN_C V5_DeviceT vexDevicesGet(void)
{
    if (functionTable && functionTable->vexDevicesGet)
    {
        return functionTable->vexDevicesGet();
    }
    return NULL;
}