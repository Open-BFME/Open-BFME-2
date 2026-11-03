// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0GenBase009EB7D0@@QAE@XZ @ 0x0061ED40 (51B): prototype base constructor.
// Ported from Open-BFME-1
// Code/GameEngine/Source/Common/MidVptrOnlyDerivedCtors.cpp
// (GenBase009EB7D0 at 0x9EB7D0, same 51B). Keeps the halfword clear and the
// bitfield updates in retail order; the late vptr write is the base's own
// vftable store. Dedicated TU so Create_Rva00972880_Prototype keeps its
// pin-call shape (same-TU definition would let MSVC see the body).
extern "C" char GenBase009EB7D0_vtbl;

#include "../WWLib/GenBase009EB7D0.h"

GenBase009EB7D0::GenBase009EB7D0()
{
	unsigned char *base = reinterpret_cast<unsigned char *>(this);
	unsigned int value;

	*reinterpret_cast<unsigned short volatile *>(base + 4) = 0;
	value = *reinterpret_cast<unsigned int volatile *>(base + 4);
	value &= 0xff07ffffu;
	value |= 0x00070000u;
	*reinterpret_cast<unsigned int volatile *>(base + 4) = value;
	value &= 0xf8ffffffu;
	*reinterpret_cast<char *volatile *>(base) = &GenBase009EB7D0_vtbl;
	*reinterpret_cast<unsigned int volatile *>(base + 4) = value;
	*reinterpret_cast<unsigned int volatile *>(base + 8) = 0;
	*reinterpret_cast<unsigned int volatile *>(base + 0xc) = 0;
	*reinterpret_cast<unsigned int volatile *>(base + 0x10) = 0;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_GenBase009EB7D0_vtbl=??_7ShdDefFactoryClass@@6B@")
