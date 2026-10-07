// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/Libraries/Source/WWVegas/WW3D2/dllist.h (EA Zero Hour source).
// Native calls at 0x001303E9 and 0x00130A16 use this insertion method.
// Retail stores prove succ/pred/list at +0/+4/+8 and list head at +4.
// Instantiate only this existing shared-header body so unrelated sorting
// renderer definitions and dependencies do not accompany the provider.
#include "always.h"
#include "dllist.h"

class SortingNodeStruct;
template void DLNodeClass<SortingNodeStruct>::Insert_Before(DLNodeClass<SortingNodeStruct>*);
