// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1
//
// BFME1 GameLogic.cpp setFPMode donor, constants folded: retail keeps one
// and/or pair (RC_NEAR plus PC_24 under a PC|RC mask) where BFME1 spells the
// two field updates separately. The imports resolve by slot with no pins.

extern "C" {
#include <float.h>
}

// ?setFPMode@@YAXXZ
void setFPMode(void)
{
    _fpreset();
    unsigned int val = _statusfp();
    val = (val & ~0x10300) | 0x20000;
    _controlfp(val, 0x30300);
}
