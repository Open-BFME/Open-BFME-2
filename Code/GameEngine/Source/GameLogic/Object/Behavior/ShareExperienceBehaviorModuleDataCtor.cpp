// cl: /O1 /GX /arch:SSE /MD /DNDEBUG
//
// ??0ShareExperienceBehaviorModuleData@@QAE@XZ, retail 0x0047FE90, 76 bytes.
// Framed single-state EH ctor: zero floats at +8/+0xC, pool float 1.0f at
// +0x10, folded vtable 0x00C486B0, filter member at +0x14 through the
// pinned nullary filter (0x3623E5, Rva003623E5Filter spelling), unknown
// dword at +4 kept as explicit pad. Own table 0x00C48740 holds Radius/
// DropOff/Percentage/ObjectFilter; the ShareExperienceBehavior pool key at
// 0x47FE4B ends near the rowed proc; the factory at 0x24BFE5 news 0x18
// and calls this ctor as sole caller; the rowed proc at 0x47FEDC starts
// where this ctor ends. Recipe: GeometryUpgrade (virtual mid-init vtable
// placement) over Topple (empty base with declared-only dtor arms the
// single EH state with zero code). The EBO base keeps the implicit base
// position this-direct (no this-adjust). Row supersedes the pinned ctor.

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();

private:
	unsigned char m_data[4];
};

class ShareExperienceBehaviorModuleDataBase
{
public:
	~ShareExperienceBehaviorModuleDataBase();
};

class ShareExperienceBehaviorModuleData : public ShareExperienceBehaviorModuleDataBase
{
public:
	ShareExperienceBehaviorModuleData();
	virtual ~ShareExperienceBehaviorModuleData();

private:
	unsigned char m_unk04[4]; // +4
	float m_r8; // +8
	float m_rC; // +0xC
	float m_r10; // +0x10
	Rva003623E5Filter m_filter; // +0x14
};

// ??0ShareExperienceBehaviorModuleData@@QAE@XZ @0x47FE90
ShareExperienceBehaviorModuleData::ShareExperienceBehaviorModuleData()
	: m_r8(0.0f)
	, m_rC(0.0f)
	, m_r10(1.0f)
{
}
