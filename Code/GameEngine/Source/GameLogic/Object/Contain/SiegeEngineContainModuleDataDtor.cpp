// cl: /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS
//
// ??1SiegeEngineContainModuleData@@UAE@XZ, retail 0x0047C9CB, 74 bytes.
// Target evidence: vtable 0x00C47180 (installed by the matched ctor
// 0x0047C927) has slot 0 = scalar deleting dtor 0x0047C9AF which calls this
// body; RiderChangeContainModuleData dtor 0x0047EB36 calls here as base.
// Teardown order +0x194 string via pinned ??1?$StringBase@D@@QAE@XZ at
// 0x00036410 then +0x18C filter via rowed ??1Rva00360D26Member at 0x00360D26
// then base ??1TransportContainModuleData at 0x004684F1. Layout from the
// matched ctor (size 0x1B8 with pair at +0x194 and mask at +0x1A4).
// No derived vptr store in retail so derived class is novtable.

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class TransportContainModuleData
{
public:
	TransportContainModuleData();
	virtual ~TransportContainModuleData();

private:
	unsigned char m_opaque[0x18C - 4];
};

class __declspec(novtable) SiegeEngineContainModuleData : public TransportContainModuleData
{
public:
	virtual ~SiegeEngineContainModuleData();

private:
	Rva00360D26Member m_member18C; // +0x18C
	int m_int190; // +0x190
	StringBase<char> m_str194; // +0x194
	int m_int198; // +0x198
	float m_float19C; // +0x19C
	bool m_flag1A0; // +0x1A0
	unsigned char m_pad1A1[3];
	unsigned char m_mask1A4[16]; // +0x1A4 trivial mask
	bool m_flag1B4; // +0x1B4
	unsigned char m_pad1B5[3];
};

SiegeEngineContainModuleData::~SiegeEngineContainModuleData()
{
}
