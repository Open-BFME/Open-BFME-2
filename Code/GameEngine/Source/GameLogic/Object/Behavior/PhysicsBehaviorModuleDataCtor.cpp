// cl: /GX /DNDEBUG /MD

// PhysicsBehaviorModuleData default constructor @0x390119 (176B). Identity:
// the factory 0x24E774 (landed PhysicsBehaviorModuleDataFriendNew.cpp) news
// 0x5C and calls this ctor as its sole raw caller; the INI table at 0x00C19DE8
// (landed buildFieldParse row) names every member and offset below. Vtable
// 0x0084ED70 pinned as ??_7PhysicsBehaviorModuleData@@6B@.
//
// Every constant default sits in the member initializer list, which MSVC
// emits in declaration order; that interleaving is what keeps 1.3, 0.33, 0.66
// and 5.0 live together from the entry (xmm0-xmm3) and lets the vtable store
// sink below the zeroing. The three shock times are body assignments from the
// int global at 0x009BA4E4 (BFME 2's logic frame rate, 5): one second, two
// seconds, one second. Earlier attempts wrote every store in the body in retail
// order and pinned it with volatile members, which left 0.33 on demand in xmm0.
// The +0x28 slot has no INI field and keeps an address-derived name.

extern const int g_009BA4E4;

extern "C" const void *const vtbl_0084ED70[];  // ??_7PhysicsBehaviorModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_0084ED70=??_7PhysicsBehaviorModuleData@@6B@")

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class PhysicsBehaviorModuleData : public UpdateModuleData
{
public:
	PhysicsBehaviorModuleData();

private:
	const void *m_vtable; // +0x00, retail vtable 0x0084ED70
	unsigned int m_unused04;
	float m_firstHeight;
	float m_secondHeight;
	float m_firstPercentIndent;
	float m_secondPercentIndent;
	int m_shockStunnedTimeLow;
	int m_shockStunnedTimeHigh;
	int m_shockStandingTime;
	int m_bounceCount;
	float m_unk28;
	float m_bounceFirstHeight;
	float m_bounceSecondHeight;
	float m_bounceFirstPercentIndent;
	float m_bounceSecondPercentIndent;
	float m_curveFlattenMinDist;
	bool m_tumbleRandomly;
	bool m_orientToFlightPath;
	bool m_ignoreTerrainHeight;
	float m_firstPercentHeight;
	float m_secondPercentHeight;
	float m_gravityMult;
	void *m_groundHitFX;
	void *m_groundBounceFX;
	bool m_allowBouncing;
	bool m_killWhenRestingOnGround;
};

// ??0PhysicsBehaviorModuleData@@QAE@XZ @0x00390119
PhysicsBehaviorModuleData::PhysicsBehaviorModuleData() :
	m_vtable(reinterpret_cast<const void *>(((unsigned int)vtbl_0084ED70))),
	m_firstHeight(1.3f),
	m_secondHeight(1.3f),
	m_firstPercentIndent(0.33f),
	m_secondPercentIndent(0.66f),
	m_bounceCount(2),
	m_unk28(5.0f),
	m_bounceFirstHeight(1.3f),
	m_bounceSecondHeight(1.3f),
	m_bounceFirstPercentIndent(0.33f),
	m_bounceSecondPercentIndent(0.66f),
	m_curveFlattenMinDist(0.0f),
	m_tumbleRandomly(false),
	m_orientToFlightPath(false),
	m_ignoreTerrainHeight(false),
	m_firstPercentHeight(0.33f),
	m_secondPercentHeight(0.66f),
	m_gravityMult(1.0f),
	m_groundHitFX(0),
	m_groundBounceFX(0),
	m_allowBouncing(false),
	m_killWhenRestingOnGround(false)
{
	m_shockStunnedTimeLow = g_009BA4E4;
	m_shockStunnedTimeHigh = 2 * g_009BA4E4;
	m_shockStandingTime = g_009BA4E4;
}
// ?g_009BA4E4@@3HB: the global at VA 0xdba4e4 is ?g_Va00DBA4E4@@3HA.
#pragma comment(linker, "/alternatename:?g_009BA4E4@@3HB=?g_Va00DBA4E4@@3HA")
