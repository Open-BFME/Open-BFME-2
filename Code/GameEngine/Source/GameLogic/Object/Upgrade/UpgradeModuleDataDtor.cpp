// cl: /DNDEBUG /MD /EHsc /O1
//
// ??1UpgradeModuleData@@UAE@XZ, retail 0x00255A42 (48 bytes).
// BFME1 donor: Code/GameEngine/Source/GameLogic/Object/Upgrade/
// UpgradeModuleDataDestructorThunk.cpp (86 bytes, two strings at +0x18/+0x1C).
// BFME2 keeps a single string member at +0x4C (releaseBuffer call via the
// pre-existing 0x36410 pins, no new pin) and installs the base vtable after
// the member teardown with the trivial base dtor inlined away (no base call).
// Identity proof: ??_GUpgradeModuleData @0x4BC7E2 (matched, ModuleFactory.cpp)
// calls 0x255A42, and ??1GrantScienceUpgradeModuleData @0x25637D (matched)
// calls it as its base dtor after destroying its own +0x60 string.

#include <new.h>

#include "../../../../Include/Common/AsciiStringMember.h"

class ModuleDataBase
{
public:
	virtual ~ModuleDataBase() {}
};

class UpgradeModuleData : public ModuleDataBase
{
public:
	UpgradeModuleData();
	char m_pad[0x4C - 4];
	AsciiStringMember m_name;
};

// ??0UpgradeModuleData@@QAE@XZ present-unmatched
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline UpgradeModuleData::UpgradeModuleData()
{
}

// ?bfmeAnchorUpgradeModuleDataCtor absent-from-retail
void *bfmeAnchorUpgradeModuleDataCtor(void *where)
{
	return ::new (where) UpgradeModuleData();
}

void deleteUpgradeModuleData(UpgradeModuleData *upgradeModuleData)
{
	delete upgradeModuleData;
}
