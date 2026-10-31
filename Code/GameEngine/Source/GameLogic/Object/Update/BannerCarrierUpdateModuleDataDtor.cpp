// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
// ??1BannerCarrierUpdateModuleData@@UAE@XZ retail 0x00497056 249B
// Evidence: pin BannerCarrierUpdateModuleData dtor at 0x00497056; donor open-bfme-1 BannerCarrierUpdateModuleDataDestructors.cpp:97; ctor layout BannerCarrierUpdateModuleDataCtor.cpp size 0x44 vectors +0x18 +0x24 FX +0x30 +0x34 flags +0x38 +0x39 range +0x3C upgrade string +0x40; callees rowed element dtors 0x00496A63 0x00496F30 plus typed erase twins 0x0031BD55 plus releaseBuffer 0x00036410 plus free 0x00030830 plus operator delete 0x0002FD60
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include <vector>

struct BfmeMorphCondition;
struct BfmeExpLevelDraw;

class FXList;

class Rva00496A63
{
public:
	~Rva00496A63();

private:
	AsciiString m_first; // +0
	unsigned char m_pad04[0x54 - 4];
	AsciiString m_second; // +0x54
};

class Rva00496F30
{
public:
	~Rva00496F30();
private:
	int m_00; // +0x00
	_STL::vector<StringBase<char> *> m_vec; // +0x04
};

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

// The +0x40 string's teardown is an out-of-line call to the rowed releaseBuffer
// (0x00036410 narrow, 0x00036E70 wide).
BannerCarrierUpdateModuleData::~BannerCarrierUpdateModuleData()
{
	for (_STL::size_t i = 0; i < m_morphConditions.size(); ++i)
		delete (Rva00496A63 *)m_morphConditions[i];
	m_morphConditions.clear();
	for (_STL::size_t i = 0; i < m_expLevelDraws.size(); ++i)
		delete (Rva00496F30 *)m_expLevelDraws[i];
	m_expLevelDraws.clear();
}
