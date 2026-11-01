#include "vex/v5.h"

#include <string.h>

static V5_Device devices[V5_MAX_DEVICE_PORTS] = {
    // Internal ADI
    [21] = {.type = kDeviceTypeAdiSensor, .timestamp = 0, .name = "Internal ADI"},
    // Battery
    [22] = {.type = kDeviceTypeRes2Sensor, .timestamp = 0, .name = "Built-in Battery"},
};

void initializeDevice(V5_DeviceT device)
{
    if (!device)
    {
        return;
    }

    switch (device->type)
    {
    case kDeviceTypeMotorSensor:
        V5_MotorData_init(&device->motor);
        break;
    }
}

uint32_t vexDevicesGetNumber(void)
{
    return 23; // 1-21 physical, 22 internal adi, 23 battery
}

uint32_t vexDevicesGetNumberByType(V5_DeviceType type)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < V5_MAX_DEVICE_PORTS; i++)
    {
        if (devices[i].type == type)
        {
            count++;
        }
    }
    return count;
}

V5_DeviceT vexDevicesGet(void)
{
    return devices;
}

V5_DeviceT vexDeviceGetByIndex(uint32_t index)
{
    if (index < V5_MAX_DEVICE_PORTS)
    {
        return &devices[index];
    }
    return NULL;
}

int32_t vexDeviceGetStatus(V5_DeviceType *buffer)
{
    if (buffer == NULL)
    {
        return -1;
    }

    for (uint32_t i = 0; i < V5_MAX_DEVICE_PORTS; i++)
    {
        buffer[i] = devices[i].type;
    }

    return V5_MAX_DEVICE_PORTS;
}

int32_t vexDeviceGetTimestamp(V5_DeviceT device)
{
    if (device)
    {
        return device->timestamp;
    }
    return 0;
}

int32_t vexDeviceGetTimestampByIndex(int32_t index)
{
    if (index >= 0 && index < V5_MAX_DEVICE_PORTS)
    {
        return devices[index].timestamp;
    }
    return 0;
}

uint32_t vexDeviceButtonStateGet(void)
{
    return 0;
}

V5_DeviceT vexSimDeviceSetByIndex(uint32_t index, V5_DeviceType type, const char name[32])
{
    if (index < V5_MAX_DEVICE_PORTS)
    {
        devices[index].type = type;
        strncpy(devices[index].name, name, sizeof(devices[index].name) - 1);
        devices[index].name[sizeof(devices[index].name) - 1] = '\0'; // Ensure null-termination
        initializeDevice(&devices[index]);
        return &devices[index];
    }
    return NULL;
}

void vexSimDeviceSet(V5_DeviceT device, V5_DeviceType type, const char name[32])
{
    if (device)
    {
        device->type = type;
        strncpy(device->name, name, sizeof(device->name) - 1);
        device->name[sizeof(device->name) - 1] = '\0'; // Ensure null-termination
        initializeDevice(device);
    }
}