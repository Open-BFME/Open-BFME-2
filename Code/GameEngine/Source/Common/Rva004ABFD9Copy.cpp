// cl: /EHsc /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include/Common
#include "Common/Snapshot.h"
#include "BfmeModuleData.h"
// Native table has the shared 31-slot ModuleData interface, ending at 0xC54A74.
// Native teardown then restores Snapshot table 0xBBB554; original intermediate
// inheritance and the meaning of the word at +4 remain unrecovered.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
// Class identity recovered from factory 0x24F362 and ctor 0x4ABED8 sharing
// vtable 0xC549F8; the address-derived owner is now LargeGroupAudioUpdateModuleData.
//
// ??0LargeGroupAudioUpdateModuleData@@QAE@ABV0@@Z @0x004ABF47 102B: copy constructor of the class
// whose destructor is the rowed ??1LargeGroupAudioUpdateModuleData (0x004ABFD9, vtable 0x00C549F8
// slot 0 via ??_GLargeGroupAudioUpdateModuleData 0x004AC021). It copies the polymorphic base
// through the rowed address-derived base copy constructor 0x004ABCE6
// (the original base identity is still unknown), installs vtable
// 0x00C549F8, copies the member at +8 (rowed Rva003ED658 copy 0x003ED658) and
// three plain fields, then inserts itself into the global registry 0x00E03CE0
// (rowed Rva00E03CE0::Rva004ABEAE 0x004ABEAE). Identities are address-derived.

struct __declspec(novtable) Rva001408C0Target : public ModuleData
{
	Rva001408C0Target(const Rva001408C0Target &other);
	virtual ~Rva001408C0Target();

	int m_04;
};

#include "../../Include/Common/Rva00E03CE0.h"

// Existing data-ledger owner; use typed views of the one registry datum.
#include "../../Include/Common/ModuleKeyRegistryStorage.h"

#include "../../Include/GameLogic/Rva003ED658.h"

class LargeGroupAudioUpdateModuleData : public Rva001408C0Target
{
public:
	LargeGroupAudioUpdateModuleData(const LargeGroupAudioUpdateModuleData &other);
	virtual __declspec(noinline) ~LargeGroupAudioUpdateModuleData();

private:
	Rva003ED658 m_key;
	int m_timeBetweenUpdatesMin;
	int m_timeBetweenUpdatesVariation;
	short m_unitWeight;
};

LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData(const LargeGroupAudioUpdateModuleData &other) :
	Rva001408C0Target(other),
	m_key(other.m_key),
	m_timeBetweenUpdatesMin(other.m_timeBetweenUpdatesMin),
	m_timeBetweenUpdatesVariation(other.m_timeBetweenUpdatesVariation),
	m_unitWeight(other.m_unitWeight)
{
	reinterpret_cast<Rva00E03CE0 *>(&BfmeLargeGroupAudioRegistry)->Rva004ABEAE(this);
}

inline Rva001408C0Target::~Rva001408C0Target() {}
