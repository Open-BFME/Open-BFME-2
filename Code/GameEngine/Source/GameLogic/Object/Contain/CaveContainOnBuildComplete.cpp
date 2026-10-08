// cl: /O1 /DNDEBUG /MD /EHsc
// CaveContain::onBuildComplete, target RVA 0x00466790, 65 bytes.
//
// Target evidence: CaveContainCtor.cpp stores vftable 0x00843A5C at object
// offset +0x34. Slot 0 is 0x00466780 (onCreate); slot 1 is 0x00466790
// (onBuildComplete); slot 3 is the rowed byte getter at 0x00466467. The
// 16-byte slot-0 body reads the ModuleData pointer at this -0x30 and its cave
// index at data +0x98, then writes the index to this +0xD0. The constructor
// and target body place that cave index at complete-object +0x104. The
// build-complete flag is at complete-object +0x100 (this +0xCC), and the owner
// Object* is at this -0x2C. The onBuildComplete body calls the CaveSystem
// helpers also used by nearby CaveContain methods.
//
// Donor provenance: Open-BFME-1 revision 6583b3c1ff21db4a561285717028fdafc780b7db,
// GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Contain/CaveContain.cpp,
// CaveContain::onBuildComplete. The target data access and Rva004F56FC callee
// use BFME2 evidence; donor naming and the relationship of that list-add helper
// to TunnelTracker::onTunnelCreated remain inferences.

class Object;

// Narrow target view: retail onCreate reads the module-data field at +0x98.
class CaveContainModuleDataView
{
public:
	unsigned char m_pad[0x98];
	int m_caveIndexData;
};

// Target helper is still recorded under its opaque row name. The donor calls
// TunnelTracker::onTunnelCreated(Object*) at this point in onBuildComplete.
class Rva004F56FC
{
public:
	void rva004F56FC(Object *obj);
};

class CaveSystem
{
public:
	void registerNewCave(int index);
	Rva004F56FC *getTunnelTrackerForCaveIndex(int index);
};

// Target data_xrefs.tsv records a read at RVA 0x00A031F4. TheCaveSystem is the
// donor label; the address-derived name keeps the target global movable.
extern CaveSystem *g_00A031F4;
#define TheCaveSystem g_00A031F4

// This TU-scoped view begins at the +0x34 secondary interface installed by
// CaveContainCtor.cpp. It is not a complete declaration of CaveContain.
class CaveContain
{
public:
	virtual void onCreate();
	virtual void onBuildComplete();
	virtual void rva004B3FD0();
	virtual bool shouldDoOnBuildComplete();

private:
	unsigned char m_pad[0xC8];
	unsigned char m_needToRunOnBuildComplete;
	int m_caveIndex;
};

// ?onCreate@CaveContain@@UAEXXZ
void CaveContain::onCreate()
{
	CaveContainModuleDataView *moduleData =
		*reinterpret_cast<CaveContainModuleDataView **>(
			reinterpret_cast<char *>(this) - 0x30);
	m_caveIndex = moduleData->m_caveIndexData;
}

void CaveContain::onBuildComplete()
{
	if (!shouldDoOnBuildComplete())
		return;

	m_needToRunOnBuildComplete = 0;
	TheCaveSystem->registerNewCave(m_caveIndex);
	Rva004F56FC *myTracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
	myTracker->rva004F56FC(*reinterpret_cast<Object **>((char *)this - 0x2C));
}

CaveSystem *g_00A031F4;
