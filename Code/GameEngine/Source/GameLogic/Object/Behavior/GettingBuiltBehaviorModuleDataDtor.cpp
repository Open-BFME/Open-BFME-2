// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1GettingBuiltBehaviorModuleData@@UAE@XZ, retail 0x00453315, 129 bytes.
// Virtual dtor over vtable 0x00C40090 (slot 0 deleting dtor at 0x004534D9).
// Donor BFME1 GettingBuiltBehaviorModuleDataDestructorThunk.cpp (five members
// in reverse order). BFME2 adds +0x40 pool member plus float/flag tail (ctor
// 0x0045324E news 0x4C, INI table 0x00C402A0 via buildFieldParse 0x00453396).
// Destruction reverse of declaration: +0x40 via pinned 0x00360D26 (state 5),
// +0x18/+0x14 AsciiString via folded 0x00036410 (states 4/3), +0x10/+0x0C/+0x08
// holders via rowed Release_Ref 0x00050ED3 (states 2/1/0), then Snapshot base
// restores 0x00BBB554. Flammable/Production precedent.

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
	char *m_data;
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

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class GettingBuiltBehaviorModuleData : public Snapshot
{
public:
	virtual ~GettingBuiltBehaviorModuleData();

private:
	int m_unused04;
	ThingRefHolder m_ref08;
	ThingRefHolder m_ref0C;
	ThingRefHolder m_ref10;
	AsciiString m_str14;
	AsciiString m_str18;
	unsigned char m_flag1C;
	float m_width20;
	float m_width24;
	int m_count28;
	unsigned char m_flag2C;
	float m_f30;
	float m_f34;
	float m_f38;
	float m_f3C;
	Rva00360D26Member m_member40;
	float m_f44;
	unsigned char m_flag48;
};

GettingBuiltBehaviorModuleData::~GettingBuiltBehaviorModuleData()
{
}
