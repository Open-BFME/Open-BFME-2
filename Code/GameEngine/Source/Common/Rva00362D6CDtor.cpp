// cl: /O1 /DNDEBUG /MD /GX
// ??1Rva00362D6C@@UAE@XZ @0x00362D6C 81B: virtual dtor with Rva00419BA5 guard plus Rva00362CF2 member.
// Evidence: caller 0x00362E92 deleting dtor in OpaqueScalarDeletingDtorsB06.cpp (vtable 0x00C17068#0); callees rowed rva00419BA5 0x00419BA5 plus pinned ??1Rva00362CF2 0x00362CF2 plus g_00BBB554 base; vptr stores 0x00C17068 then 0x00BBB554; members +0x18 +0x1C +0x30; neighbours SubsystemNameGetters4 ConstIntGetters4 default flags.
extern const void *const g_00BBB554[];

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BBB554;
}

class Rva00419BA5
{
public:
	void rva00419BA5();
};

class Rva0040AD80ReferenceState : public Snapshot
{
public:
	void releaseReferences();
};

class Rva00362CF2 : public Rva0040AD80ReferenceState
{
public:
	virtual ~Rva00362CF2();
};

class Rva00362D6C : public Snapshot
{
public:
	virtual ~Rva00362D6C();
private:
	unsigned char m_pad04[0x18 - 0x04];
	Rva00419BA5 *m_18; // +0x18
	int m_1C; // +0x1C
	unsigned char m_pad20[0x30 - 0x20];
	Rva00362CF2 m_30; // +0x30
};

Rva00362D6C::~Rva00362D6C()
{
	if (m_18) {
		m_18->rva00419BA5();
		m_18 = 0;
	}
	m_1C = 0;
}

Rva00362CF2::~Rva00362CF2()
{
	releaseReferences();
}
