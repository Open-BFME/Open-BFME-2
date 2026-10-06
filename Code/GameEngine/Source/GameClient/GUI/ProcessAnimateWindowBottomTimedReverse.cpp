// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Source: GeneralsMD ProcessAnimateWindow.cpp at BFME1 revision
// 10af19f44a89ab7ecc23195bb9a842ceafbc02c9; return virtual update unchanged.
// Target identity: matched BottomTimed ctor RVA 0x005C4FEF installs vptr
// VA 0x00C7481C; slot 4 targets this 5-byte body at RVA 0x005CB265.
// Slot 3 targets the independently matched BottomTimed update at 0x005C5AF7.
// Only the process interface is needed for this frameless virtual dispatch.
#include "GameClient/ProcessAnimateWindow.h"

Bool ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow(AnimateWindow *animWin)
{
    return updateAnimateWindow(animWin);
}
