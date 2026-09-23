// cl: /Og /Os /Ob1 /arch:SSE /GX- /G7 /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0BannerCarrierUpdateModuleData@@QAE@XZ, retail 0x00496FA5, 149 bytes.
// BannerCarrierUpdate data half: vtable 0x00C4F870 modelled as an explicit
// first member (DemoTrapUpdateModuleDataCtor precedent, so no vtable is
// emitted and no dtor row is owed), an uninitialised dword at +0x04 retail
// never stores, four LogicFramesPerSecond-scaled frame counts at
// +0x08/+0x0C/+0x10/+0x14 (x15/x10/x10/x10), two cleared pointer vectors at
// +0x18/+0x24, zeroed FX slots at +0x30/+0x34, two flags at +0x38/+0x39, a
// zeroed range at +0x3C and the required-upgrade slot at +0x40.
//
// Field identity is retail's own INI table at 0x00C4F9E8: IdleSpawnRate@+8,
// MeleeFreeUnitSpawnTime@+0xC, DiedRespawnTime@+0x10,
// MeleeFreeBannerReSpawnTime@+0x14, MorphCondition@+0x18, ExpLevelDraw@+0x24,
// BannerMorphFX@+0x30, UnitSpawnFX@+0x34, ReplenishNearbyHorde@+0x38,
// ReplenishAllNearbyHordes@+0x39, ScanHordeDistance@+0x3C,
// UpgradeRequired@+0x40. The +0x18/+0x24 members construct through the
// ICF-folded Vector_base at 0x211E58 and clear through the rowed void*
// erase at 0x31BD55, so their elements are 4 bytes; the element classes are
// otherwise unproven, hence TU-local forward-declared pointer stand-ins
// (BattlePlanUpdate precedent for fold-equivalent stand-ins). The FX and
// upgrade slots are 4-byte scalars retail only zeroes; their precise types
// are unproven, hence plain ints. Shape follows AutoPickUpUpdateModuleDataCtor
// (explicit vtable from the mem-init, LogicFramesPerSecond macro) with three
// load-bearing deviations, all probe-proven: /Og /Os /Ob1 instead of the /O1
// bundle (the bundle implies /Oy frame-pointer omission and this body keeps
// its ebp frame; the bare trio keeps size opts plus Ob1 inlining with no FPO),
// /G7 (Pentium-4 fast-imul selection: ecx-homed imul chains with the eax zero
// surviving for the +0x30/+0x34 stores below the +0x14 store; without it the
// x10s go lea/shl and everything re-homes), and m_upgradeRequired(0) in the
// mem-init (its store sits between the member constructions and the
// frame-count stores, the init-tail position). The two vectors build by
// implicit default construction: that inlines the vector() wrapper and
// exposes the declared-only Vector_base calls above (an explicit : m_vec()
// init would instead call the 18B vector-alloc thunk). Body order otherwise
// follows retail.

#include <vector>

struct BfmeMorphCondition;
struct BfmeExpLevelDraw;

namespace _STL {
// The two member vectors build through these ICF-folded base ctors pinned at
// 0x211E58 (same 29B as the matched BfmeE16 row). Declared here without a
// body so the calls stay outlined with no EH anywhere near the TU: with the
// visible STLport definition the /Ob1 build inlines the bases and the frame
// vanishes with them.
template<> _Vector_base<BfmeMorphCondition *, allocator<BfmeMorphCondition *> >::_Vector_base(const allocator<BfmeMorphCondition *> &);
template<> _Vector_base<BfmeExpLevelDraw *, allocator<BfmeExpLevelDraw *> >::_Vector_base(const allocator<BfmeExpLevelDraw *> &);
}

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class BannerCarrierUpdateModuleData
{
public:
	BannerCarrierUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	int m_idleSpawnRate; // +8
	int m_meleeFreeUnitSpawnTime; // +0xC
	int m_diedRespawnTime; // +0x10
	int m_meleeFreeBannerReSpawnTime; // +0x14
	_STL::vector<BfmeMorphCondition *> m_morphConditions; // +0x18
	_STL::vector<BfmeExpLevelDraw *> m_expLevelDraws; // +0x24
	int m_bannerMorphFX; // +0x30
	int m_unitSpawnFX; // +0x34
	bool m_replenishNearbyHorde; // +0x38
	bool m_replenishAllNearbyHordes; // +0x39
	float m_scanHordeDistance; // +0x3C
	int m_upgradeRequired; // +0x40
};

// ??0BannerCarrierUpdateModuleData@@QAE@XZ @0x496FA5
BannerCarrierUpdateModuleData::BannerCarrierUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4F870))
	, m_upgradeRequired(0)
{
	m_idleSpawnRate = LogicFramesPerSecond * 15;
	m_meleeFreeUnitSpawnTime = LogicFramesPerSecond * 10;
	m_diedRespawnTime = LogicFramesPerSecond * 10;
	m_meleeFreeBannerReSpawnTime = LogicFramesPerSecond * 10;
	m_bannerMorphFX = 0;
	m_unitSpawnFX = 0;
	m_morphConditions.clear();
	m_expLevelDraws.clear();
	m_replenishNearbyHorde = false;
	m_replenishAllNearbyHordes = false;
	m_scanHordeDistance = 0.0f;
}
