// cl: /O1 /DNDEBUG /MD
//
// ??1Rva004FF2C0@@UAE@XZ @0x004FF2C0 18B: dtor restoring own vtable plus
// Snapshot member at +0x2c then tail-jmp to base dtor.
// Evidence: packet disasm with vtable 0x00C63B34 at +0 plus Snapshot vtable
// 0x00BBB554 at +0x2c plus pinned base ??1Rva004FBCBE 0x004FBCBE, caller
// deleting dtor 0x004FF2D2 in OpaqueScalarDeletingDtorsB11.cpp.

extern const void *const g_00BBB554[];

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

// ??1Snapshot@@UAE@XZ present-unmatched
inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BBB554;
}

class Rva004FBCBE
{
public:
	virtual ~Rva004FBCBE();
};

class Rva004FF2C0 : public Rva004FBCBE
{
public:
	virtual ~Rva004FF2C0();
private:
	char m_pad04[0x2c - 4];
	Snapshot m_2c;
};

Rva004FF2C0::~Rva004FF2C0()
{
}
