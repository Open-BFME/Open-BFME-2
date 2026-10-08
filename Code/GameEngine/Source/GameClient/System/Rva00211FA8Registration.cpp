// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 0x00210DB6..0x00210DC9 (19B), entered by the callback address
// stored at 0x00211FDC in the 0x00211FA8 registration routine.
// All instructions through RET are measured; the next entry at 0x00210DC9
// is independently rowed. No incoming stack argument is read or popped.
// The target calls GameLogic on the named singleton with (true, false)
// and returns 3. Keep the unknown callback's original identity unresolved.
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

int rva00210DB6()
{
    TheGameLogic->rva00376E92(true, false);
    return 3;
}
