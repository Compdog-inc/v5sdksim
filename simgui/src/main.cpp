#include "simgui.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

static DWORD WINAPI guiThread(void *pvParameters)
{
    runGui();

    return 0;
}

int main(int, char **)
{
    HANDLE thread = CreateThread(NULL, 0, guiThread, NULL, 0, NULL);
    WaitForSingleObject(thread, INFINITE);
    return 0;
}