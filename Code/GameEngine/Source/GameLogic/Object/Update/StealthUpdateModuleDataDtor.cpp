// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1StealthUpdateModuleData@@UAE@XZ, retail 0x003759F5, 119 bytes.
// Virtual dtor over vtable 0x008184D8 (slot 0 deleting dtor at 0x003759D9).
// Layout from ctor 0x0037588B (news 0xC8, table 0x00C18210). Destruction
// reverse: +0xBC/+0xB0 vectors via rowed 0x0002CC70 (states 4/3), +0x8C/+0x84
// holders via rowed Release_Ref 0x00050ED3 (states 2/1), +0x74 vector via
// rowed 0x0002CC70 (state 0), then Snapshot base restores 0x00BBB554.
// +0x80/+0x88 pairs are int plus nullable holder (ctor Upgrades fold at
// 0x004CEE6E sets -1 plus 0). No entry vtable store, so novtable.
// CivilianSpawn/LargeGroupBonus precedent.
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

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct ThingRefHolder
{
	~ThingRefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

struct UpgradesPair
{
	int m_minusOne;
	ThingRefHolder m_holder;
};

class __declspec(novtable) StealthUpdateModuleData : public Snapshot
{
public:
	virtual ~StealthUpdateModuleData();

private:
	unsigned int m_unused04;
	int m_flags08;
	int m_zero0C;
	unsigned long m_bits10[4];
	float m_speed20;
	float m_half24;
	float m_one28;
	int m_count2C;
	unsigned char m_byte30;
	float m_zero34;
	unsigned char m_byte38;
	int m_zero3C;
	int m_zero40;
	int m_zero44;
	int m_zero48;
	int m_zero4C;
	int m_zero50;
	unsigned char m_one54;
	unsigned char m_one55;
	unsigned char m_zero56;
	unsigned int m_zero58;
	unsigned int m_zero5C;
	float m_zero60;
	unsigned long m_bits64[4];
	_STL::vector<AsciiString> m_strings74;
	UpgradesPair m_pair80;
	UpgradesPair m_pair88;
	int m_ten90;
	int m_ten94;
	int m_zero98;
	int m_zero9C;
	int m_zeroA0;
	int m_minusOneA4;
	int m_minusOneA8;
	int m_minusOneAC;
	_STL::vector<AsciiString> m_stringsB0;
	_STL::vector<AsciiString> m_stringsBC;
};

StealthUpdateModuleData::~StealthUpdateModuleData()
{
}
