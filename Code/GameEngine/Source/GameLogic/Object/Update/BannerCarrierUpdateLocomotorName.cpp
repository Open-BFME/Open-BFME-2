// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/iniexception /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// BFME1 BannerCarrierUpdateFindObjectName.cpp donor9cbfb551 supplies
// same module-data locomotor-name search. Native496E05 invokes496DA3
// with hidden string result then const-name pointer; RET8, copy/char
// StringBase constructors365F0/37BA0 prove the by-value string ABI.
// The old explicit void* result bank lost the return-object flag spill.
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include <vector>
struct BfmeMorphCondition {AsciiString name;unsigned at04;unsigned conditions[19];AsciiString locomotor;};

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

AsciiString BannerCarrierUpdateModuleData::rva00496DA3(const AsciiString &name) const {
 for(unsigned i=0;i<m_morphConditions.size();++i) {
  if(((const StringBase<char> &)m_morphConditions[i]->name).compareNoCase((const StringBase<char> &)name)==0) return m_morphConditions[i]->locomotor;
 }
 return "";
}
