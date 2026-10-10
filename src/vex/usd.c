#include "vex/v5.h"

FRESULT vexFileMountSD(void)
{
    // TODO: create directory, fail if failed
    return FR_OK;
}

FRESULT vexFileDirectoryGet(const char *path, char *buffer, uint32_t len)
{
    // TODO: list filenames
    buffer[0] = 0;
    return FR_OK;
}

FIL *vexFileOpen(const char *filename, const char *mode)
{
    // TODO: implement
    return NULL;
}

FIL *vexFileOpenWrite(const char *filename)
{
    // TODO: implement
    return NULL;
}

FIL *vexFileOpenCreate(const char *filename)
{
    // TODO: implement
    return NULL;
}

void vexFileClose(FIL *fdp)
{
    // TODO: implement
}

int32_t vexFileRead(char *buf, uint32_t size, uint32_t nItems, FIL *fdp)
{
    // TODO: implement
    return 0;
}

int32_t vexFileWrite(char *buf, uint32_t size, uint32_t nItems, FIL *fdp)
{
    // TODO: implement
    return 0;
}

int32_t vexFileSize(FIL *fdp)
{
    // TODO: implement
    return 0;
}

FRESULT vexFileSeek(FIL *fdp, uint32_t offset, int32_t whence)
{
    // TODO: implement
    return FR_OK;
}

bool vexFileDriveStatus(uint32_t drive)
{
    // TODO: implement
    return false;
}

int32_t vexFileTell(FIL *fdp)
{
    // TODO: implement
    return 0;
}

void vexFileSync(FIL *fdp)
{
    // TODO: implement
}

uint32_t vexFileStatus(const char *filename)
{
    // TODO: implement
    return 0;
}
