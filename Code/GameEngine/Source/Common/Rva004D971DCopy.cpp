// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0Rva004D971D@@QAE@ABV0@@Z @0x004D971D (33B):
// Copy ctor: Rva0036CA00Str at +0 via rowed 0x000A8C7C then Rva004D964E at +4
// via rowed 0x004D964E, edi holds src across calls, return-this ret-4.
// Evidence: chain lane, push-esi-edi plus add-edi-4 shape, caller 0x004D9ADA.
#include "../../Include/Common/Rva0036CA00Str.h"

#include "../../Include/Common/Rva002390CB.h"

#include "../../Include/Common/Rva004D964E.h"

class Rva004D971D
{
public:
	Rva004D971D(const Rva004D971D &other);
private:
	Rva0036CA00Str m_str;
	Rva004D964E m_data;
};

Rva004D971D::Rva004D971D(const Rva004D971D &other) : m_str(other.m_str), m_data(other.m_data)
{
}
