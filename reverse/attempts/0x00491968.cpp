// ??0AttachUpdateModuleData@@QAE@XZ
// partial score=0.6 date=2026-09-23
// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// stlport
//
// ??0AttachUpdateModuleData@@QAE@XZ, retail 0x00491968, 166 bytes.
// Attach behavior's module data: the rowed 17B proc 0x00491957 carries
// ObjectFilter at +0x8 plus ParentStatus at +0xC plus ScanRange at +0x1C
// plus AlwaysTeleport at +0x20 plus AnchorToTopOfGeometry at +0x21 plus
// six EvaEvent ints at +0x24 through +0x3C plus AttachFX at +0x30 on table
// 0x00C4DC48, the rowed factory 0x0024D8D2 news 0x40 with this ctor as
// sole caller, and the rowed pool key 0x00491912 ends where the proc
// begins. Shape follows RespawnBodyModuleDataCtor: the empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor) arms
// state 0 with no code, the compiler installs the derived vtable
// 0x00C4DD18 after the base (slot0 is the scalar-deleting dtor 0x00491A84,
// slot1 is the shared ret stub 0x004B3FD0; resolves through the ??_7 pin),
// the ObjectFilter member builds through the opaque 0x3623E5 pin and its
// completion advances state 1, the ParentStatus bitset resets through the
// rowed 0x24CA24 body then zeroes through the _memset import thunk, the
// ScanRange float loads from the absolute global at 0x00BC2428, the
// EvaEvent ints default to -1 with AttachFX kept 0, and the filter
// consumes two FixedStorage temps built from 0x00DFEFA4 through the
// 0x362087 pin (ret 0x38 pops both temps). Row supersedes the ctor pin.

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

extern "C" void *memset(void *, int, unsigned int);

#define AttachStoragePrototype (*(const struct BfmeFixedStorage0004543D *)0x00DFEFA4)

extern float g_attachScanRangeDefault;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class AttachUpdateModuleData : public UpdateModuleData
{
public:
	AttachUpdateModuleData();
	virtual ~AttachUpdateModuleData();

private:
	unsigned char m_unk04[4]; // +0x04
	Rva003623E5Member m_objectFilter; // +0x08
	unsigned long m_parentStatus[4]; // +0x0C, ParentStatus bitset: reset
		// through the ledger-known bitset<128>::reset body (rowed at
		// 0x24CA24, GiveOrRestoreUpgrade precedent) then zeroed with
		// memset; a real bitset<128> member would emit a _Base_bitset
		// ctor call retail never has (V1-proven)
	float m_scanRange; // +0x1C
	bool m_alwaysTeleport; // +0x20
	bool m_anchorToTopOfGeometry; // +0x21
	int m_parentOwnerAttachmentEvaEvent; // +0x24
	int m_parentAllyAttachmentEvaEvent; // +0x28
	int m_parentEnemyAttachmentEvaEvent; // +0x2C
	int m_attachFX; // +0x30
	int m_parentOwnerDiedEvaEvent; // +0x34
	int m_parentAllyDiedEvaEvent; // +0x38
	int m_parentEnemyDiedtEvaEvent; // +0x3C
};

// ??0AttachUpdateModuleData@@QAE@XZ @0x00491968
AttachUpdateModuleData::AttachUpdateModuleData()
{
	((_STL::bitset<128> *)m_parentStatus)->reset();
	float scanRange = g_attachScanRangeDefault;
	m_attachFX = 0;
	int noEvaEvent = -1;
	memset(m_parentStatus, 0, sizeof(m_parentStatus));
	m_scanRange = scanRange;
	m_alwaysTeleport = true;
	m_anchorToTopOfGeometry = false;
	m_parentOwnerAttachmentEvaEvent = noEvaEvent;
	m_parentAllyAttachmentEvaEvent = noEvaEvent;
	m_parentEnemyAttachmentEvaEvent = noEvaEvent;
	m_parentOwnerDiedEvaEvent = noEvaEvent;
	m_parentAllyDiedEvaEvent = noEvaEvent;
	m_parentEnemyDiedtEvaEvent = noEvaEvent;
	m_objectFilter.initFromStorages(
		BfmeFixedStorage0004543D(AttachStoragePrototype),
		BfmeFixedStorage0004543D(AttachStoragePrototype));
}
