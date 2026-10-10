#include "vex/v5.h"

// rtos hooks
void vexSystemTimerStop()
{
    // TODO: implement
}

void vexSystemTimerClearInterrupt()
{
    // TODO: implement
}

int32_t vexSystemTimerReinitForRtos(uint32_t priority, void (*handler)(void *data))
{
    // TODO: implement
    return 0;
}

void vexSystemApplicationIRQHandler(uint32_t ulICCIAR)
{
    // TODO: implement
}

int32_t vexSystemWatchdogReinitRtos(void)
{
    // TODO: implement
    return 0;
}

uint32_t vexSystemWatchdogGet(void)
{
    // TODO: implement
    return 0;
}

void vexSystemBoot(void)
{
    // TODO: implement
}

void vexSystemUndefinedException(void)
{
    // TODO: implement
}

void vexSystemFIQInterrupt(void)
{
    // TODO: implement
}

void vexSystemIQRQnterrupt(void)
{
    // TODO: implement
}

void vexSystemSWInterrupt(void)
{
    // TODO: implement
}

void vexSystemDataAbortInterrupt(void)
{
    // TODO: implement
}

void vexSystemPrefetchAbortInterrupt(void)
{
    // TODO: implement
}

void vexSystemMemoryDump(void)
{
    // TODO: implement
}

void vexSystemDigitalIO(uint32_t pin, uint32_t value)
{
    // TODO: implement
}

uint32_t vexSystemStartupOptions(void)
{
    // TODO: implement
    return 0;
}

void vexSystemExitRequest(void)
{
    // TODO: implement
}

uint32_t vexSystemLinkAddrGet(void)
{
    // TODO: implement
    return 0;
}

uint32_t vexSystemUsbStatus(void)
{
    // TODO: implement
    return 0;
}

void vexBackgroundProcessing(void)
{
    // TODO: implement
}

uint32_t vexSystemVersion(void)
{
    // 1.1.5 (b255) - sim
    return 1 << 24 | 1 << 16 | 5 << 8 | 255;
}

uint32_t vexStdlibVersion(void)
{
    // TODO: implement
    return 0;
}

// get SDK version
uint32_t vexSdkVersion(void)
{
    // 1.1.5.2
    return 1 << 24 | 1 << 16 | 5 << 8 | 2;
}
