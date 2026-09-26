// ??0PhysicsBehaviorModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-26
// cl: /O1 /arch:SSE /GX /DNDEBUG /MD
// BANKED PARTIAL 2026-09-26 (score 0.98): 176/178B, 38/38 insns.
// SOLE WALL: retail hoists the four float-pool loads (1.3/.33/.66/5.0) to the
// top into xmm0-xmm3 plus xor-ecx before the first store; every probed shape
// emits them on demand in one register (xmm0 reused per group).
// PROVEN by probe matrix (build/probe/pb_*.cpp, all 176B/38ins): /O1 base,
// /O2 (worse: edx for late G loads), /Ot, /Ob2, /Og, /Oy, /Oi, /G5, /G6,
// /G7, /GB, /arch:SSE2, /Op, /Os, /Ob0, semantic body order (stores go
// semantic, loads hoist: proves stores do NOT move), init-list, float
// locals (const-prop kills them: identical output to literals),
// multi-declarator single statement (same).
// DIAGNOSIS: retail's 4-simultaneous-live float ranges need overlapping
// source lifetimes, but stores are provably grouped (scheduler never groups
// them: semantic probe) while grouped literals never overlap lifetimes
// (single-reg chaining). Locals would overlap but /O1 forward-propagates
// them away. Missing lever: a construct that materializes 4 constants into
// 4 registers early without optimizer folding (volatile/address-taken cost
// stack traffic; calls forbidden: retail has none).
// LAYOUT (retail-proven, all 25 stores exact incl. frame/epilogue/G-triple
// with 3x reload + add-ecx-ecx and gate-filled pool/G/vtable addresses):
// INI table 0x00C19DE8 gives every member name/offset; factory 0x24E774
// news 0x5C; float bits read from image (1.3f/0.33f/0.66f/5.0f/1.0f exact);
// G = extern const int at VA 0xDBA4E4 (=5); +0x28 unnamed (5.0, no INI
// field); +0x04 untouched gap (Topple/Tornado precedent).
// NEXT IDEAS (untried): statement shapes that force 4 live regs (computed
// values e.g. division chains are overkill); check whether another landed
// frameless multi-constant ctor TU shows the hoist idiom.
// t=50 model=muse-spark score=0.98 stash=reverse/attempts/0x00390119.cpp

//
// ??0PhysicsBehaviorModuleData@@QAE@XZ, retail 0x00390119, 178 bytes.
// Bounce/tumble behavior ModuleData: the own INI table at 0x00C19DE8
// (landed buildFieldParse row) proves every member below -- FirstHeight at
// +0x08, SecondHeight at +0x0C, First/SecondPercentIndent at +0x10/+0x14,
// ShockStunnedTimeLow/High/StandingTime at +0x18/+0x1C/+0x20, BounceCount
// at +0x24, BounceFirst/SecondHeight at +0x2C/+0x30,
// BounceFirst/SecondPercentIndent at +0x34/+0x38, CurveFlattenMinDist at
// +0x3C, TumbleRandomly at +0x40, OrientToFlightPath at +0x41,
// IgnoreTerrainHeight at +0x42, First/SecondPercentHeight at +0x44/+0x48,
// GravityMult at +0x4C, GroundHitFX/GroundBounceFX at +0x50/+0x54,
// AllowBouncing at +0x58 and KillWhenRestingOnGround at +0x59. The factory
// at 0x0024E774 (landed PhysicsBehaviorModuleDataFriendNew.cpp) news 0x5C
// and calls this ctor as its sole raw caller, fixing the class size.
// BFME2 deltas vs the ZH PhysicsUpdate donor: all height defaults are 1.3,
// all percent defaults are 0.33/0.66, shock times come from the 0x00DBA4E4
// pool (5/10/5) and the +0x28 slot (5.0, no INI field) is left unnamed.
// Body order follows retail (grouped by constant); the vtable store sits in
// its observed position between the zero stores and the percent stores.

extern const int g_Va00DBA4E4;

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class PhysicsBehaviorModuleData : public UpdateModuleData
{
public:
	PhysicsBehaviorModuleData();

private:
	// +0x00 vtable (body store in the retail-observed position).
	const void *m_vtable;
	// +0x04 unstored gap.
	unsigned int m_unused04;
	// +0x08 FirstHeight (table offset).
	float m_firstHeight;
	// +0x0C SecondHeight (table offset).
	float m_secondHeight;
	// +0x10 FirstPercentIndent (table offset).
	float m_firstPercentIndent;
	// +0x14 SecondPercentIndent (table offset).
	float m_secondPercentIndent;
	// +0x18 ShockStunnedTimeLow (table offset).
	int m_shockStunnedTimeLow;
	// +0x1C ShockStunnedTimeHigh (table offset).
	int m_shockStunnedTimeHigh;
	// +0x20 ShockStandingTime (table offset).
	int m_shockStandingTime;
	// +0x24 BounceCount (table offset).
	int m_bounceCount;
	// +0x28 unnamed slot (no INI field, retail default 5.0).
	float m_unk28;
	// +0x2C BounceFirstHeight (table offset).
	float m_bounceFirstHeight;
	// +0x30 BounceSecondHeight (table offset).
	float m_bounceSecondHeight;
	// +0x34 BounceFirstPercentIndent (table offset).
	float m_bounceFirstPercentIndent;
	// +0x38 BounceSecondPercentIndent (table offset).
	float m_bounceSecondPercentIndent;
	// +0x3C CurveFlattenMinDist (table offset).
	float m_curveFlattenMinDist;
	// +0x40 TumbleRandomly (table offset).
	bool m_tumbleRandomly;
	// +0x41 OrientToFlightPath (table offset).
	bool m_orientToFlightPath;
	// +0x42 IgnoreTerrainHeight (table offset).
	bool m_ignoreTerrainHeight;
	// +0x44 FirstPercentHeight (table offset).
	float m_firstPercentHeight;
	// +0x48 SecondPercentHeight (table offset).
	float m_secondPercentHeight;
	// +0x4C GravityMult (table offset).
	float m_gravityMult;
	// +0x50 GroundHitFX (table offset).
	void *m_groundHitFX;
	// +0x54 GroundBounceFX (table offset).
	void *m_groundBounceFX;
	// +0x58 AllowBouncing (table offset).
	bool m_allowBouncing;
	// +0x59 KillWhenRestingOnGround (table offset).
	bool m_killWhenRestingOnGround;
};

// ??0PhysicsBehaviorModuleData@@QAE@XZ @0x00390119
PhysicsBehaviorModuleData::PhysicsBehaviorModuleData()
{
	m_firstHeight = 1.3f;
	m_secondHeight = 1.3f;
	m_bounceFirstHeight = 1.3f;
	m_bounceSecondHeight = 1.3f;
	m_curveFlattenMinDist = 0.0f;
	m_tumbleRandomly = false;
	m_orientToFlightPath = false;
	m_ignoreTerrainHeight = false;
	m_groundHitFX = 0;
	m_groundBounceFX = 0;
	m_allowBouncing = false;
	m_killWhenRestingOnGround = false;
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_firstPercentIndent = 0.33f;
	m_bounceFirstPercentIndent = 0.33f;
	m_firstPercentHeight = 0.33f;
	m_secondPercentIndent = 0.66f;
	m_bounceSecondPercentIndent = 0.66f;
	m_secondPercentHeight = 0.66f;
	m_bounceCount = 2;
	m_unk28 = 5.0f;
	m_gravityMult = 1.0f;
	m_shockStunnedTimeLow = g_Va00DBA4E4;
	m_shockStunnedTimeHigh = g_Va00DBA4E4 + g_Va00DBA4E4;
	m_shockStandingTime = g_Va00DBA4E4;
}
