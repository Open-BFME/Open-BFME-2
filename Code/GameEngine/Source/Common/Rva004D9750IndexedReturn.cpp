// cl: /O1 /G7 /arch:SSE /EHsc /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native 4D9750..4D977D RET8; caller supplies hidden 8-byte result and index.
// The return construction flag at EBP-4 proves a C++ value result rather than
// the prior bank's explicit output pointer. Copy/default providers are the
// same 2390CB/4CEE6E pair independently verified for native35B456 siblings.
#include "../../Include/Common/Rva002390CB.h"
class Rva004D9750 {
public:
    Rva002390CB rva004D9750(int index);
    Rva002390CB items[1];
};
Rva002390CB Rva004D9750::rva004D9750(int index)
{
    if (index == -1)
        return Rva002390CB();
    return items[index];
}
