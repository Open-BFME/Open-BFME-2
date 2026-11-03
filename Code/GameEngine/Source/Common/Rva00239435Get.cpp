// cl: /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva00239435@Rva00239435@@QAE?AVRva002390CB@@H@Z, retail 0x00239435, 34 bytes.
// Copy of 8-byte element at this+0x124 indexed by second arg into hidden return.
// Evidence: callee ??0Rva002390CB@@QAE@ABV0@@Z rowed in Rva002390CBCopy.cpp; callers 0x0023B44D 0x002767CB 0x0030DF99 0x004338E4; prev FreelistPoolPop next Rva00239AF4 same flags.
#include "../../Include/Common/Rva0036CA00Str.h"
#include "../../Include/Common/Rva002390CB.h"
class Rva00239435 {
    char m_pad[0x124];
    Rva002390CB m_arr[1];
public:
    Rva002390CB rva00239435(int index);
};
Rva002390CB Rva00239435::rva00239435(int index)
{
    return m_arr[index];
}
