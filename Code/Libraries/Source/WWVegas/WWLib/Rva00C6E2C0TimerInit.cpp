// cl: /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// Libraries/Source/WWVegas/WWLib/Rva00C6E2C0TimerInit.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// bfmeRva00C6E2C0InitializeTimerResolution 0x007B5510 (20B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/mmsys.h"

// Cleanup at 0x00C71590 calls timeEndPeriod(1); its row is rva007B9AC0.
void rva007B9AC0();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6E2C0InitializeTimerResolution()
{
    timeBeginPeriod(1);
    atexit(rva007B9AC0);
}
