// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1ReplaceSelfUpgradeModuleData@@UAE@XZ, retail 0x004B797A, 51 bytes.
// ReplaceSelfUpgrade ModuleData dtor: destroys the AsciiString vector at
// +0x118 through the rowed 0x2CC70 body (state 0), then restores the Snapshot
// base vtable 0x00BBB554. Layout from the rowed ctor 0x004B790B (base 0x118
// via OpenContain 0x253487, vector at +0x118, size 0x124 via factory
// 0x002506CE) and table 0x00C58A88 via rowed buildFieldParse 0x004B7023.
// Own vtable 0x00858B40; caller is the slot-0 ??_G at 0x004B795E. Shape follows
// CreateObjectDieModuleDataDtor/CivilianSpawnUpdateModuleDataDtor (TU-local
// Snapshot with inline BBB554-restoring dtor plus novtable derived suppressing
// the entry store retail lacks plus single vector member).
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
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) ReplaceSelfUpgradeModuleData : public Snapshot
{
public:
	virtual ~ReplaceSelfUpgradeModuleData();

private:
	unsigned char m_pad04[0x118 - 4];
	_STL::vector<AsciiString> m_replaceWith; // +0x118
};

ReplaceSelfUpgradeModuleData::~ReplaceSelfUpgradeModuleData()
{
}
