// cl: /O1 /GX /arch:SSE /DNDEBUG /MD
//
// ??1SpecialEnemySenseUpdateModuleData@@UAE@XZ, retail 0x0025525B, 48 bytes.
// ModuleData dtor: tears down the filter at +8 through the folded 0x360D26
// body (Rva003623E5Filter pin), then restores the Snapshot base vtable
// 0x00BBB554. Empty derived body; the vector is the only tracked member?
// No, filter is the only tracked member, giving EH state 0 exactly as
// retail (EH prolog 0xB71C4A, no base call since Snapshot dtor is inline).
// Shape follows the landed FlammableUpdateModuleDataDtor (TU-local Snapshot
// with an inline BBB554-restoring dtor, empty derived body). Layout from the
// rowed ctor 0x25404A (vtable 0xBF1AD8 at +0, filter at +8 via construct pin,
// 0.0f at +0xC, 1 at +0x10, size 0x14 via factory 0x25409C) and the own table
// 0xBF1B88. Caller is the slot-0 ??_G at 0x25523F (vtable 0xBF1AD8).

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

class Rva003623E5Filter
{
public:
	~Rva003623E5Filter();
};

class __declspec(novtable) SpecialEnemySenseUpdateModuleData : public Snapshot
{
public:
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	int m_unused04; // +0x04
	Rva003623E5Filter m_filter; // +0x08
	float m_scanRange; // +0x0C
	int m_scanInterval; // +0x10
};

SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
}
