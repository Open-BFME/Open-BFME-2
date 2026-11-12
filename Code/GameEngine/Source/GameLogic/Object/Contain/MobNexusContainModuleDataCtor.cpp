// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0InvisibilitySpecialPowerModuleData@@QAE@XZ, retail 0x004C244D, 118 bytes.
// Mob-nexus contain data: the own table at 0x00C5C468 carries
// InvisibilityNugget at +0x7C, BroadcastRadius at +0x134, ObjectFilter at
// +0x138 and Duration at +0x13C, matching every store below; the ModuleData
// factory at 0x2518CB pushes this ctor's proc VA and the proc at 0x4C2389
// is rowed. Shape follows RousingSpeechUpdateModuleDataCtor (opaque
// virtual base through the 0x4930A0 pin, derived virtuals, mid-init vtable
// through the ??_7 pin) with the single-temp applyFilter tail through the
// 0x362120 pin: the InvisibilityNugget member builds through the fresh
// 0x2542F3 pin (119B frameless body, identity unproven) and the
// BroadcastRadius/Duration stores are init-listed so they bracket the
// filter construction exactly as retail.

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

class Rva002542F3Member
{
public:
	Rva002542F3Member();

private:
	unsigned char m_data[0x9C];
};

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

#include "../../../../Include/GameLogic/Module/Rva003623E5Filter.h"

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

class InvisibilitySpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	InvisibilitySpecialPowerModuleData();
	virtual ~InvisibilitySpecialPowerModuleData();

private:
	Rva002542F3Member m_invisibilityNugget; // +0x7C
	unsigned char m_pad118[0x134 - 0x118]; // +0x118
	float m_broadcastRadius; // +0x134
	Rva003623E5Member m_objectFilter; // +0x138
	int m_duration; // +0x13C
};

// ??0InvisibilitySpecialPowerModuleData@@QAE@XZ @0x4C244D
InvisibilitySpecialPowerModuleData::InvisibilitySpecialPowerModuleData()
	: SpecialPowerModuleData()
	, m_broadcastRadius(0.0f)
	, m_duration(0)
{
	reinterpret_cast<Rva003623E5Filter *>(&m_objectFilter)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)));
}
