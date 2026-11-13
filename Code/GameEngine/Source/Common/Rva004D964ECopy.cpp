// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0Rva004D964E@@QAE@ABV0@@Z @0x004D964E (63B):
// Copy ctor: two Rva002390CB members via rowed copy ctor 0x2390CB plus four
// dwords plus byte. Evidence: push esi-edi plus two ??0 calls plus
// 0x10-0x1c dword copies plus 0x20 byte copy plus return-this ret-4;
// unblocks 0x004D9A44 0x004D971D; callers 0x004D9732 0x004D9A57.
#include "../../Include/Common/Rva002390CB.h"

#include "../../Include/Common/Rva004D964E.h"

Rva004D964E::Rva004D964E(const Rva004D964E &other) : m_00(other.m_00), m_08(other.m_08)
{
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
}
