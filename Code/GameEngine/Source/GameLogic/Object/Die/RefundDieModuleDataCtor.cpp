// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ??0RefundDieModuleData@@QAE@XZ at retail 0x002538DB (67 bytes).
// RefundDie ModuleData ctor over the unidentified SEH intermediate base
// 0x00253510 (pinned opaque as Rva00253510): base call, own vtable 0x00BF0660,
// BuildingRequired member at +0x40 via the rowed-filter helper 0x003623E5,
// and-zero UpgradeRequired at +0x38, float-zero RefundPercent at +0x3C,
// matching the class parse table at 0x00BF0700 (rowed proc 0x25391E).
// Factory 0x00253940 builds size 0x44. Identity votes: the ModuleFactory
// registrar maps the RefundDie INI name to factory 0x253940 which sole-calls
// this ctor and pushes the class proc; the rowed RefundDie pool key lives in
// this family.

class Rva00253510
{
public:
	Rva00253510();
	virtual ~Rva00253510();

protected:
	unsigned char m_pad[0x38 - 4];
};

// ??1Rva00253510@@UAE@XZ present-unmatched
Rva00253510::~Rva00253510()
{
}

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();

private:
	int m_handle;
};

// ??1Rva003623E5Filter@@QAE@XZ present-unmatched
Rva003623E5Filter::~Rva003623E5Filter()
{
}

class RefundDieModuleData : public Rva00253510
{
public:
	RefundDieModuleData();
	virtual ~RefundDieModuleData();

protected:
	int m_upgradeRequired; // +0x38
	float m_refundPercent; // +0x3C
	Rva003623E5Filter m_building; // +0x40
};

RefundDieModuleData::RefundDieModuleData()
	: Rva00253510(), m_building()
{
	m_refundPercent = 0.0f;
	m_upgradeRequired = 0;
}

// ??1RefundDieModuleData@@UAE@XZ present-unmatched
RefundDieModuleData::~RefundDieModuleData()
{
}
