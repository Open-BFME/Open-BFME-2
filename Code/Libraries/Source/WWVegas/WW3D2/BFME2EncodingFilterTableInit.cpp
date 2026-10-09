// cl: /O1 /Ob2 /Oy- /G7 /arch:SSE /Oi /MD /DNDEBUG /EHs-c- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Clean ZH motchan.cpp adaptive-delta table generation is the semantic guide;
// target 001B20E5..001B2138 independently proves the stream table at DB6C28,
// range16..255, 0.375f * degrees-to-radians and 1-sin(angle). The existing
// data ledger supplies filtertable's actual decorated name, not a new pin.
// /O1 /Oy- restores two stack slots, memory constant MULSS, and LEAVE.
// WWMath::Sin is the donor's existing x87 helper (FLD/FSIN/FSTP). Plain CRT
// sin lets MSVC keep all arithmetic in x87 and does not reproduce retail's
// float rounding boundary; the helper preserves the target's SSE/x87 shape.
#include "wwmath.h"
// Retail DB6C28 has the same sixteen power-of-ten seed values as ZH;
// DB6C68..DB7028 is zero-filled before this dynamic initialization runs.
float filtertable[256] = {
 1e-8f, 1e-7f, 1e-6f, 1e-5f, 1e-4f, 1e-3f, 1e-2f, 1e-1f,
 1.0f, 10.0f, 100.0f, 1000.0f, 10000.0f, 100000.0f, 1000000.0f, 10000000.0f
};
bool Rva001B20E5Init() {
 float n=0;
 for(int i=16;i<256;++i,n+=1.0f) {
 float radians=n*0.375f;
 radians*=0.017453292f;
 filtertable[i]=1.0f-WWMath::Sin(radians);
 }
 return true;
}
