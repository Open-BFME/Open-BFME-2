// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0TunnelContainModuleData@@QAE@XZ, retail 0x0025797E, 107 bytes
// (pinned). Over the rowed HordeGarrisonContainModuleData ctor 0x0047A251
// (its dtor 0x00257A05 is state 0 of retail's unwind map): set the float at
// +0xD4 to 1.0, then reset the inherited +0x40 filter through 0x00362192
// with BitSet(0, 8) and a copy of the default storage at 0x00DFEFA4, as in
// GarrisonContainModuleData's constructor in GarrisonContain.cpp.
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

class Rva00045411BitSet
{
public:
	Rva00045411BitSet(int a, int b);
	Rva00045411BitSet(const Rva00045411BitSet &other);
private:
	unsigned char m_bytes[0x1C];
};

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../Include/GameLogic/Module/OpenContainModuleData.h"
#include "../../../../Include/GameLogic/Module/HordeGarrisonContainModuleData.h"

class TunnelContainModuleData : public HordeGarrisonContainModuleData
{
public:
	TunnelContainModuleData();
private:
	float m_D4;
};

TunnelContainModuleData::TunnelContainModuleData()
{
	m_D4 = 1.0f;
	m_passengerFilter.rva00362192(Rva00045411BitSet(0, 8), *reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
}
