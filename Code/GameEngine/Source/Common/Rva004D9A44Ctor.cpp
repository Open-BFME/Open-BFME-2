// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0Rva004D9A44@@QAE@ABVRva0036CA00Str@@ABVRva004D964E@@@Z @0x004D9A44 (30B):
// Two-member ctor: Rva0036CA00Str at +0 via rowed 0x000A8C7C then Rva004D964E
// at +4 via rowed 0x004D964E, return-this ret-8. Evidence: chain lane, calls
// 0x004D964E just landed, push-push-call-push-lea-call shape, caller 0x004DBC52.
#include "../../Include/Common/Rva0036CA00Str.h"

#include "../../Include/Common/Rva002390CB.h"

#include "../../Include/Common/Rva004D964E.h"

class Rva004D9A44
{
public:
	Rva004D9A44(const Rva0036CA00Str &a, const Rva004D964E &b);
private:
	Rva0036CA00Str m_str;
	Rva004D964E m_data;
};

Rva004D9A44::Rva004D9A44(const Rva0036CA00Str &a, const Rva004D964E &b) : m_str(a), m_data(b)
{
}
