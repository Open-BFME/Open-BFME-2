// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1BannerCarrierUpdateModuleData@@UAE@XZ retail 0x00497056 249B
// Evidence: pin BannerCarrierUpdateModuleData dtor at 0x00497056; donor open-bfme-1 BannerCarrierUpdateModuleDataDestructors.cpp:97; ctor layout BannerCarrierUpdateModuleDataCtor.cpp size 0x44 vectors +0x18 +0x24 FX +0x30 +0x34 flags +0x38 +0x39 range +0x3C upgrade string +0x40; callees rowed element dtors 0x00496A63 0x00496F30 plus typed erase twins 0x0031BD55 plus releaseBuffer 0x00036410 plus free 0x00030830 plus operator delete 0x0002FD60
#include <vector>
#include "Common/Snapshot.h"

struct BfmeMorphCondition;
struct BfmeExpLevelDraw;

class Rva00496A63
{
public:
	~Rva00496A63();
};

class Rva00496F30
{
public:
	~Rva00496F30();
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class BannerCarrierUpdateModuleData : public Snapshot
{
public:
	virtual ~BannerCarrierUpdateModuleData();
private:
	int m_unused04; // +0x04
	int m_field08; // +0x08
	int m_field0C; // +0x0C
	int m_field10; // +0x10
	int m_field14; // +0x14
	_STL::vector<BfmeMorphCondition *> m_objectNames; // +0x18
	_STL::vector<BfmeExpLevelDraw *> m_upgrades; // +0x24
	int m_bannerMorphFX; // +0x30
	int m_unitSpawnFX; // +0x34
	bool m_replenishNearbyHorde; // +0x38
	bool m_replenishAllNearbyHordes; // +0x39
	unsigned char m_pad3A[2]; // +0x3A
	float m_scanHordeDistance; // +0x3C
	StringBase<char> m_upgradeRequired; // +0x40
};

BannerCarrierUpdateModuleData::~BannerCarrierUpdateModuleData()
{
	for (_STL::size_t i = 0; i < m_objectNames.size(); ++i)
		delete (Rva00496A63 *)m_objectNames[i];
	m_objectNames.clear();
	for (_STL::size_t i = 0; i < m_upgrades.size(); ++i)
		delete (Rva00496F30 *)m_upgrades[i];
	m_upgrades.clear();
}
