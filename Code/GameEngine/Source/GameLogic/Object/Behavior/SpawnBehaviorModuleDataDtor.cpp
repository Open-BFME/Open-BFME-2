// cl: /Ireference/shims/bfme2_ascii /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1SpawnBehaviorModuleData@@UAE@XZ, retail 0x0025766F, 48 bytes. Virtual
// dtor over vtable 0x007F4128 (slot 0 deleting dtor at 0x00257653 calls
// this body). Destroys the spawn-template vector at +0x20 through the
// rowed vector dtor at 0x0002CC70 then restores the Snapshot base vtable
// 0x00BBB554. Layout from the rowed ctor TU at 0x002575C2 (news 0x174
// vtable 0xBF4128 vector +0x20 DieMux +0x2C via init slave block +0x5C
// via construct). Shape follows Passive/LargeGroup ModuleData dtors
// (TU-local Snapshot with inline BBB554 restore novtable suppressing the
// entry derived store retail lacks). BFME1 donor
// SpawnBehaviorModuleDataDestructorThunk.cpp proves the single-vector
// teardown.
extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

#include <vector>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}

#include "ascii_string.h"

class __declspec(novtable) SpawnBehaviorModuleData : public Snapshot
{
public:
	virtual ~SpawnBehaviorModuleData();

private:
	int m_unused04; // +0x04
	int m_spawnNumber; // +0x08
	int m_spawnReplaceDelay; // +0x0C
	int m_initialBurst; // +0x10
	bool m_isOneShot; // +0x14
	bool m_canReclaimOrphans; // +0x15
	bool m_aggregateHealth; // +0x16
	bool m_exitByBudding; // +0x17
	bool m_spawnedRequireSpawner; // +0x18
	bool m_respectCommandLimit; // +0x19
	unsigned char m_pad1A[2]; // +0x1A
	int m_damageTypes; // +0x1C
	_STL::vector<AsciiString> m_spawnTemplateNames; // +0x20
	unsigned char m_pad2C[0x174 - 0x2C]; // +0x2C tail to 0x174 (DieMux plus slave block plus fade tail)
};

SpawnBehaviorModuleData::~SpawnBehaviorModuleData()
{
}
