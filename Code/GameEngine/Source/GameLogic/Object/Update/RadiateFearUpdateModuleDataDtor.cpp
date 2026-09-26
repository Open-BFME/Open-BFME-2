// cl: /O1 /DNDEBUG /MD /GX
//
// ??1RadiateFearUpdateModuleData@@UAE@XZ, retail 0x0049C1EE, 48 bytes.
// ModuleData dtor: tears down the VictimFilter at +0x1C through the folded
// 0x360D26 body (Rva003623E5Filter pin), then restores the Snapshot base
// vtable 0x00BBB554. Empty derived body with EH state 0 (EH prolog, no base
// call since Snapshot dtor is inline). Shape follows PillageModuleDataDtor.
// Layout from the rowed ctor 0x49C06C (table 0xC510B8 with VictimFilter at
// +0x1C, size 0x130 via factory 0x24E6E8). Caller is the slot-0 ??_G at
// 0x49C1D2 (vtable 0x850FF0).

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

class __declspec(novtable) RadiateFearUpdateModuleData : public Snapshot
{
public:
	virtual ~RadiateFearUpdateModuleData();

private:
	unsigned char m_pad04[0x1C - 4]; // +0x04..+0x1B
	Rva003623E5Filter m_victimFilter; // +0x1C
	unsigned char m_tail[0x130 - 0x1C - 4]; // +0x20.. (POD tail)
};

RadiateFearUpdateModuleData::~RadiateFearUpdateModuleData()
{
}
