// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ
// partial score=0.93 date=2026-09-21
// ??0ReplenishUnitsBehaviorModuleData@@QAE@XZ R1: V4-pattern locals for radius+delay
// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

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
	float radius = g_replenishRadiusDefault;
	m_startsActive = false;
	int delay = g_replenishDelayDefault;
	m_replenishRadius = radius;
	m_replenishFXList = 0;
	m_replenishHordeMembersOnly = false;
	m_replenishDelay = delay;
	m_noReplenishIfEnemyWithinRadius = 0.0f;
}
