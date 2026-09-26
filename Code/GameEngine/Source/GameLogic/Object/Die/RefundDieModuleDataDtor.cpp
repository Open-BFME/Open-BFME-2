// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ??1RefundDieModuleData@@UAE@XZ, retail 0x00255067, 48 bytes.
// ModuleData dtor: tears down the filter at +0x40 through the folded 0x360D26
// body (Rva003623E5Filter pin), then restores the Snapshot base vtable
// 0x00BBB554. Empty derived body with EH state 0 (EH prolog 0xB71C4A, no base
// call since Snapshot dtor is inline). Shape follows the landed
// PillageModuleDataDtor/SpecialEnemySenseUpdateModuleDataDtor (TU-local
// Snapshot with inline BBB554-restoring dtor, novtable derived, empty body).
// Layout from the rowed ctor 0x2538DB (base 0x38 via Rva00253510, Upgrade at
// +0x38, Percent at +0x3C, Building filter at +0x40 via 0x3623E5, size 0x44
// via factory 0x253940) and table 0xBF0700. Caller is the slot-0 ??_G at
// 0x25504B (vtable 0xBF0660).

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

class __declspec(novtable) RefundDieModuleData : public Snapshot
{
public:
	virtual ~RefundDieModuleData();

private:
	unsigned char m_pad04[0x38 - 4]; // +0x04..+0x37
	int m_upgradeRequired; // +0x38
	float m_refundPercent; // +0x3C
	Rva003623E5Filter m_building; // +0x40
};

RefundDieModuleData::~RefundDieModuleData()
{
}
