// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ
// partial score=0.85 date=2026-09-21
// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ, retail 0x004841CC,
// 90 bytes. Frameless ctor over table 0xC4A150 (ReplenishRadius@118,
// NoReplenishIfEnemyWithinRadius@11C, ReplenishFXList@120,
// ReplenishStatii@124, ReplenishDelay@134, StartsActive@138,
// ReplenishHordeMembersOnly@139). Identity is the rowed poolkey 0x4841AD
// (ReplenishUnitsBehavior), which ends exactly where this ctor begins,
// plus factory 0x24C5D1 (news 0x13C, sole caller) plus proc 0x484598
// (same table, double-add on the rowed 0x4CE29D getter). Shape follows the
// Chinook/OpenContain precedent: ropes member at +8 constructed through
// the rowed 0x25342C construct body, statii bitset at +0x124 reset through
// the rowed 0x24CA24 body (GrantUpgradeCreate bitset<128> idiom), vtable
// 0x00C4ED70 folded. All callees rowed.

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

extern float g_replenishRadiusDefault;
extern int g_replenishDelayDefault;

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x108];
};

class ReplenishUnitsBehaviorModuleData
{
public:
	ReplenishUnitsBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	Rva0025342CMember m_ropes; // +8..+0x10F
	unsigned char m_pad110[8]; // +0x110..+0x117
	float m_replenishRadius; // +0x118
	float m_noReplenishIfEnemyWithinRadius; // +0x11C
	int m_replenishFXList; // +0x120
	unsigned long m_replenishStatii[4]; // +0x124
	int m_replenishDelay; // +0x134
	bool m_startsActive; // +0x138
	bool m_replenishHordeMembersOnly; // +0x139
};

// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ @0x4841CC
ReplenishUnitsBehaviorModuleData::ReplenishUnitsBehaviorModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_ropes.construct();
	((_STL::bitset<128> *)m_replenishStatii)->reset();
	m_startsActive = false;
	m_replenishRadius = g_replenishRadiusDefault;
	m_replenishFXList = 0;
	m_replenishHordeMembersOnly = false;
	m_replenishDelay = g_replenishDelayDefault;
	m_noReplenishIfEnemyWithinRadius = 0.0f;
}
