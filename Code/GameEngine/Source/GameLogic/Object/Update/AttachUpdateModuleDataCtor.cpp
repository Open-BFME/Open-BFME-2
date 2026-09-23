// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0AttachUpdateModuleData@@QAE@XZ, retail 0x00491968, 167 bytes.
// Attach behavior data: ObjectFilter at +8 builds through the opaque
// 0x3623E5 pin, ParentStatus at +0xC is a 128-bit KindOf mask reset
// through the rowed bitset<128>::reset at 0x0024CA24, ScanRange at +0x1C
// defaults to 10.0, AlwaysTeleport at +0x20 is true, AnchorToTopOfGeometry
// at +0x21 is false, the six EvaEvent ints at +0x24/+0x28/+0x2C/+0x34/
// +0x38/+0x3C default to -1, AttachFX at +0x30 nulls, and two 28B
// FixedStorage temps from the prototype at 0x00DFEFA4 feed the filter
// through the 0x362087 pin. Own table 0x00C4DC48 proves every field; the
// ModuleData factory at 0x0024D8D2 news 0x40 and calls this ctor as sole
// caller. Shape follows GrantUpgradeCreateModuleDataCtor (bitset reset
// plus empty base for EH) over AutoPickUpUpdateModuleDataCtor (filter
// plus temps plus explicit vtable).

#include <bitset>
#include <cstring>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

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

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	Rva003623E5Member m_objectFilter; // +8, ObjectFilter
	unsigned long m_parentStatus[4]; // +0xC, ParentStatus bitset<128>
	float m_scanRange; // +0x1C, ScanRange
	bool m_alwaysTeleport; // +0x20, AlwaysTeleport
	bool m_anchorToTopOfGeometry; // +0x21, AnchorToTopOfGeometry
	unsigned char m_pad22[2]; // +0x22
	int m_parentOwnerAttachmentEvaEvent; // +0x24
	int m_parentAllyAttachmentEvaEvent; // +0x28
	int m_parentEnemyAttachmentEvaEvent; // +0x2C
	void *m_attachFX; // +0x30, AttachFX
	int m_parentOwnerDiedEvaEvent; // +0x34
	int m_parentAllyDiedEvaEvent; // +0x38
	int m_parentEnemyDiedEvaEvent; // +0x3C
};

// ??0AttachUpdateModuleData@@QAE@XZ @0x491968
AttachUpdateModuleData::AttachUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4DD18))
{
	((_STL::bitset<128> *)m_parentStatus)->reset();
	m_scanRange = 10.0f;
	m_attachFX = 0;
	m_alwaysTeleport = true;
	m_anchorToTopOfGeometry = false;
	m_parentOwnerAttachmentEvaEvent = -1;
	m_parentAllyAttachmentEvaEvent = -1;
	m_parentEnemyAttachmentEvaEvent = -1;
	m_parentOwnerDiedEvaEvent = -1;
	m_parentAllyDiedEvaEvent = -1;
	m_parentEnemyDiedEvaEvent = -1;
	memset(m_parentStatus, 0, sizeof(m_parentStatus));
	m_objectFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
