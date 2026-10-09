// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Native50FA0..50FC4 constructs a144-byte event wrapper: copy the136-byte
// prefix through thiscall2D99E3, then initialize float88 and flag8C.
// WB77AE00 and queue caller5933D establish constructor use; owner name unknown.
#include "Common/BfmeAudioEventPrefix136.h"
struct Rva00050FA0 {
 Rva00050FA0(const BfmeAudioEventPrefix136&);
 BfmeAudioEventPrefix136 prefix;
 float zero88;unsigned char zero8C;char pad8D[3];
};
Rva00050FA0::Rva00050FA0(const BfmeAudioEventPrefix136&source):prefix(source),zero88(0.0f),zero8C(0){}
