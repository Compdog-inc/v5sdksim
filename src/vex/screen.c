#include "vex/v5.h"

void vexDisplayForegroundColor(uint32_t col)
{
    // TODO: implement
}

void vexDisplayBackgroundColor(uint32_t col)
{
    // TODO: implement
}

uint32_t vexDisplayForegroundColorGet(void)
{
    // TODO: implement
    return 0;
}

uint32_t vexDisplayBackgroundColorGet(void)
{
    // TODO: implement
    return 0;
}

void vexDisplayErase(void)
{
    // TODO: implement
}

void vexDisplayScroll(int32_t nStartLine, int32_t nLines)
{
    // TODO: implement
}

void vexDisplayScrollRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t nLines)
{
    // TODO: implement
}

void vexDisplayCopyRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t *pSrc, int32_t srcStride)
{
    // TODO: implement
}

void vexDisplayPixelSet(uint32_t x, uint32_t y)
{
    // TODO: implement
}

void vexDisplayPixelClear(uint32_t x, uint32_t y)
{
    // TODO: implement
}

void vexDisplayLineDraw(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO: implement
}

void vexDisplayLineClear(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO: implement
}

void vexDisplayRectDraw(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO: implement
}

void vexDisplayRectClear(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO: implement
}

void vexDisplayRectFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO: implement
}

void vexDisplayCircleDraw(int32_t xc, int32_t yc, int32_t radius)
{
    // TODO: implement
}

void vexDisplayCircleClear(int32_t xc, int32_t yc, int32_t radius)
{
    // TODO: implement
}

void vexDisplayCircleFill(int32_t xc, int32_t yc, int32_t radius)
{
    // TODO: implement
}

void vexDisplayPrintf(int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, ...)
{
    // TODO: implement
}

void vexDisplayString(const int32_t nLineNumber, const char *format, ...)
{
    // TODO: implement
}

void vexDisplayStringAt(int32_t xpos, int32_t ypos, const char *format, ...)
{
    // TODO: implement
}

void vexDisplayBigString(const int32_t nLineNumber, const char *format, ...)
{
    // TODO: implement
}

void vexDisplayBigStringAt(int32_t xpos, int32_t ypos, const char *format, ...)
{
    // TODO: implement
}

void vexDisplaySmallStringAt(int32_t xpos, int32_t ypos, const char *format, ...)
{
    // TODO: implement
}

void vexDisplayCenteredString(const int32_t nLineNumber, const char *format, ...)
{
    // TODO: implement
}

void vexDisplayBigCenteredString(const int32_t nLineNumber, const char *format, ...)
{
    // TODO: implement
}

// Not really for user code but we need these for some wrapper functions
void vexDisplayVPrintf(int32_t xpos, int32_t ypos, uint32_t bOpaque, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVString(const int32_t nLineNumber, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVStringAt(int32_t xpos, int32_t ypos, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVBigString(const int32_t nLineNumber, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVBigStringAt(int32_t xpos, int32_t ypos, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVSmallStringAt(int32_t xpos, int32_t ypos, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVCenteredString(const int32_t nLineNumber, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayVBigCenteredString(const int32_t nLineNumber, const char *format, va_list args)
{
    // TODO: implement
}

void vexDisplayTextSize(uint32_t n, uint32_t d)
{
    // TODO: implement
}

void vexDisplayFontNamedSet(const char *pFontName)
{
    // TODO: implement
}

int32_t vexDisplayStringWidthGet(const char *pString)
{
    // TODO: implement
    return 0;
}

int32_t vexDisplayStringHeightGet(const char *pString)
{
    // TODO: implement
    return 0;
}

bool vexDisplayRender(bool bVsyncWait, bool bRunScheduler)
{
    // TODO: implement
    return false;
}

void vexDisplayDoubleBufferDisable(void)
{
    // TODO: implement
}

void vexDisplayClipRegionSet(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO: implement
}

void vexDisplayClipRegionClear()
{
    // TODO: implement
}

uint32_t vexImageBmpRead(const uint8_t *ibuf, v5_image *oBuf, uint32_t maxw, uint32_t maxh)
{
    // TODO: implement
    return 0;
}

uint32_t vexImagePngRead(const uint8_t *ibuf, v5_image *oBuf, uint32_t maxw, uint32_t maxh, uint32_t ibuflen)
{
    // TODO: implement
    return 0;
}

// special use only ! Talk to James.
int32_t vexScratchMemoryPtr(void **ptr)
{
    // TODO: implement
    return 0;
}

bool vexScratchMemoryLock(void)
{
    // TODO: implement
    return false;
}

void vexScratchMemoryUnlock(void)
{
    // TODO: implement
}

void vexTouchUserCallbackSet(void (*callback)(V5_TouchEvent, int32_t, int32_t))
{
    // TODO: implement
}

bool vexTouchDataGet(V5_TouchStatus *status)
{
    // TODO: implement
    return false;
}