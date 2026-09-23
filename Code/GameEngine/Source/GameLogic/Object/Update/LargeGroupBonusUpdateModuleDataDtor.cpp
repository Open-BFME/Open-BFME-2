// cl: /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??1LargeGroupBonusUpdateModuleData@@UAE@XZ, retail 0x0049048E, 75 bytes.
//
// LargeGroupBonusUpdateModuleData destructor: destroys the AttributeModifier
// string at +0x2C through the folded 0x36410 and the flag-name vector at
// +0x20 through the rowed 0x2CC70 and the HordeMemberFilter at +0x0C through
// the pinned 0x360D26, then restores the Snapshot base vtable 0xBBB554. The
// member declaration order (filter plus vector plus string) drives states
// 0 plus 1 plus 2 so the teardown reads 2 plus 1 plus 0 exactly as retail.
// Shape follows GeometryInfoDtor (TU-local Snapshot with inline dtor doing
// the explicit BBB554 restore after the members fall; novtable suppresses
// the entry derived-vtable store retail lacks). The companion constructor
// TU keeps dtor-less member declarations for its single-state frame; this TU
// keeps the dtor-ful ones. Identity is the ctor TU plus the own table at
// 0x00C4D1A8 plus the factory at 0x24D43F which news 0x30.

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

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class __declspec(novtable) LargeGroupBonusUpdateModuleData : public Snapshot
{
public:
	virtual ~LargeGroupBonusUpdateModuleData();

private:
	int m_unused04; // +4
	int m_updateRate; // +8
	Rva00360D26Member m_hordeMemberFilter; // +0xC
	int m_count; // +0x10
	float m_radius; // +0x14
	bool m_alliesOnly; // +0x18
	float m_rubOffRadius; // +0x1C
	_STL::vector<AsciiString> m_flagSubObjectNames; // +0x20
	AsciiString m_attributeModifier; // +0x2C
};

// ??1LargeGroupBonusUpdateModuleData@@UAE@XZ @0x49048E
LargeGroupBonusUpdateModuleData::~LargeGroupBonusUpdateModuleData()
{
}
