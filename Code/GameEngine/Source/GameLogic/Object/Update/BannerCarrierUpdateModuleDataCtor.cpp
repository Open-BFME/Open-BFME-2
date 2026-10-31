// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/iniexception /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0BannerCarrierUpdateModuleData@@QAE@XZ, retail 0x00496FA5, 149 bytes.
// BannerCarrierUpdate data half: vtable 0x00C4F870, an uninitialised dword at
// +0x04 retail never stores, four LogicFramesPerSecond-scaled frame counts at
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
// (BattlePlanUpdate precedent for fold-equivalent stand-ins).

#include "ascii_string.h"
#include "Common/Snapshot.h"
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>

extern int BfmeLogicFramesPerSecond;

#define LogicFramesPerSecond BfmeLogicFramesPerSecond

struct BfmeMorphCondition;

struct BfmeExpLevelDraw;

class FXList;

// Field identity is retail's own INI table at 0x00C4F9E8; the +0x18/+0x24 element
// classes keep the names the ledger's vector destructor rows carry.
class BannerCarrierUpdateModuleData : public Snapshot
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();
	AsciiString rva00496DA3(const AsciiString &name) const;
	const FXList *getFX() const { return m_bannerMorphFX; }
	int m_unused04; // +0x04
	unsigned m_idleSpawnRate; // +0x08
	unsigned m_meleeFreeUnitSpawnTime; // +0x0C
	int m_diedRespawnTime; // +0x10
	int m_meleeFreeBannerReSpawnTime; // +0x14
	_STL::vector<BfmeMorphCondition *> m_morphConditions; // +0x18
	_STL::vector<BfmeExpLevelDraw *> m_expLevelDraws; // +0x24
	const FXList *m_bannerMorphFX; // +0x30
	const FXList *m_unitSpawnFX; // +0x34
	bool m_replenishNearbyHorde; // +0x38
	bool m_replenishAllNearbyHordes; // +0x39
	unsigned char m_pad3A[2]; // +0x3A
	float m_scanHordeDistance; // +0x3C
	AsciiString m_upgradeRequired; // +0x40
};

// ??0BannerCarrierUpdateModuleData@@QAE@XZ @0x496FA5
BannerCarrierUpdateModuleData::BannerCarrierUpdateModuleData()
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
