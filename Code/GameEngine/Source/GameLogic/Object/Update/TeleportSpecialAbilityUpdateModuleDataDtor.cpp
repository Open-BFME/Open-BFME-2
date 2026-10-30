// cl: /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Rva0044ECCE is an address-derived base stand-in; its target class name is unproven.
//
// ??1TeleportSpecialAbilityUpdateModuleData@@UAE@XZ retail 0x00492F19 74B.
// Dtor over ctor TU layout TeleportSpecialAbilityUpdateModuleDataCtor.cpp
// vtable 0x00C4E208 strings at +0xCC/+0xD0 plus trivial Busy at +0xC8
// plus MaxDistance at +0xD4 size 0xD8 via factory 0x24DC00.
// Destroys +0xD0 then +0xCC through pinned StringBase 0x36410 states 1/0
// then base Rva0044ECCE through pinned 0x44ECCE state -1.
// Shape follows GiveOrRestoreUpgradeSpecialPowerModuleDataDtor 0x4CD2E8
// 74B precedent novtable derived plus virtual base.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) TeleportSpecialAbilityUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~TeleportSpecialAbilityUpdateModuleData();

private:
	int m_busyForDuration;
	StringBase<char> m_destinationWeaponName;
	StringBase<char> m_sourceWeaponName;
	float m_maxDistance;
};

// ??1TeleportSpecialAbilityUpdateModuleData@@UAE@XZ @0x00492F19
TeleportSpecialAbilityUpdateModuleData::~TeleportSpecialAbilityUpdateModuleData()
{
}
