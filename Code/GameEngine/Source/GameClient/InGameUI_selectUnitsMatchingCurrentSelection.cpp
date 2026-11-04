// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?selectUnitsMatchingCurrentSelection@InGameUI@@UAEHXZ, RVA 0x0029AF1C, 35 bytes.
// Identity: InGameUI class is established by the adjacent table entries for its virtual methods.
// Structural evidence: retail dispatches through vtable slots 98 and 99.

#include "../../Include/GameClient/InGameUI.h"

int InGameUI::selectUnitsMatchingCurrentSelection()
{
    int result = selectMatchingAcrossScreen();
    if (result == -1)
        return result;
    if (result != 0)
        return result;
    return selectMatchingAcrossMap();
}
