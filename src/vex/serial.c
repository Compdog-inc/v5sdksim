#include "vex/v5.h"

int32_t vexSerialWriteChar(uint32_t channel, uint8_t c)
{
    // TODO: implement
    return 0;
}

int32_t vexSerialWriteBuffer(uint32_t channel, uint8_t *data, uint32_t data_len)
{
    // TODO: implement
    return 0;
}

int32_t vexSerialReadChar(uint32_t channel)
{
    // TODO: implement
    return -1;
}

int32_t vexSerialPeekChar(uint32_t channel)
{
    // TODO: implement
    return -1;
}

int32_t vexSerialWriteFree(uint32_t channel)
{
    // TODO: implement
    return 2048;
}

void vexDeviceGenericSerialEnable(V5_DeviceT device, int32_t options)
{
    // TODO: implement
}

void vexDeviceGenericSerialBaudrate(V5_DeviceT device, int32_t baudrate)
{
    // TODO: implement
}

int32_t vexDeviceGenericSerialWriteChar(V5_DeviceT device, uint8_t c)
{
    // TODO: implement
    return 0;
}

int32_t vexDeviceGenericSerialWriteFree(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

int32_t vexDeviceGenericSerialTransmit(V5_DeviceT device, uint8_t *buffer, int32_t length)
{
    // TODO: implement
    return 0;
}

int32_t vexDeviceGenericSerialReadChar(V5_DeviceT device)
{
    // TODO: implement
    return -1;
}

int32_t vexDeviceGenericSerialPeekChar(V5_DeviceT device)
{
    // TODO: implement
    return -1;
}

int32_t vexDeviceGenericSerialReceiveAvail(V5_DeviceT device)
{
    // TODO: implement
    return 0;
}

int32_t vexDeviceGenericSerialReceive(V5_DeviceT device, uint8_t *buffer, int32_t length)
{
    // TODO: implement
    return 0;
}

void vexDeviceGenericSerialFlush(V5_DeviceT device)
{
    // TODO: implement
}