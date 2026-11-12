// cl: /O1 /arch:SSE /G7 /MD /Oy-
// platformsdk
// BFME 1 donor 1399ad37d42ea52a63829e417c46a1ba9ed2cd20:
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp,
// W3DDisplay::takeScreenShot. Target 0x00049B3A..0x00049BE8 (174B)
// has the same client-corner conversions and three-byte RGB buffer lifecycle.
// BFME 2 adds an optional filename: 0x00047BC0 copies it when nonnull,
// otherwise generates a filename, flips the RGB rows and writes the bitmap.
// The two member callees retain address names until their identities are rowed.
// Their retail ECX receivers and ret 8/16 establish the declarations below.

#include <new>
#include <windows.h>

extern void *ApplicationHWnd;

#include "../../../Include/W3DDevice/GameClient/W3DDisplayClass.h"

void W3DDisplay::takeScreenShot(const char *filename)
{
    RECT bounds;
    POINT point;
    GetClientRect((HWND)ApplicationHWnd, &bounds);
    point.x = bounds.left;
    point.y = bounds.top;
    ClientToScreen((HWND)ApplicationHWnd, &point);
    bounds.left = point.x;
    bounds.top = point.y;
    point.x = bounds.right;
    point.y = bounds.bottom;
    ClientToScreen((HWND)ApplicationHWnd, &point);
    bounds.right = point.x;
    bounds.bottom = point.y;

    unsigned int width = bounds.right - bounds.left;
    unsigned int height = bounds.bottom - bounds.top;
    char *image = new char[3 * width * height];
    rva00045213(image, 3 * width);
    rva00047BC0(image, width, height, filename);
    delete [] image;
}
