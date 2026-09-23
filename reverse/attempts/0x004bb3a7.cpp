// ??0CallHelpOnDamageModuleData@@QAE@XZ
// partial score=0.99 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /EHsc /arch:SSE
//
// ??0CallHelpOnDamageModuleData@@QAE@XZ, retail 0x004BB3A7 (116 bytes). EH
// ModuleData ctor over a trivially-constructed base with a declared virtual
// dtor (its unwind state 0 covers the member calls): ors -1 into the +0x08
// word, loads 100.0, installs vtable 0x00C59EB8 automatically, stores the
// +0x0C float and the scaled +0x10 int plus a zero flag, sets up the +0x18
// member through a body-level construct call (OpenContain idiom; the new
// construct spelling pins the same 0x003623E5 body the ??0 pins name),
// copy-builds a 28-byte argument temporary from the zero global through the
// rowed BfmeFixedStorage copy at 0x0004543D, then runs the member filter
// through the pinned applyFilter at 0x00362120 under state 1. Donor: BFME1
// Damage/Die files (same or-minus-one plus float/int member cadence).

class BfmeFixedStorage0004543D
{
	char m_bytes[28];
public:
	// NOTE: the rowed TU marks this nothrow, but this TU must not: the
	// retail body sets unwind state 1 across the copy call, which only
	// happens when the callee is assumed throwing.
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter *construct();
	void applyFilter(BfmeFixedStorage0004543D arg);
};

extern int g_bfmeScaleBase;	// retail 0xDBA4E4, value 5 (DIR32-masked)
extern BfmeFixedStorage0004543D g_bfmeFilterArg;	// retail 0xDFEFA4 zeros (DIR32-masked)

class CallHelpBase
{
public:
	virtual ~CallHelpBase();

protected:
	void *m_unsourced04;	// +0x04, retail never stores it
	int m_or08;	// +0x08, or-minus-one by the derived ctor
};

class CallHelpOnDamageModuleData : public CallHelpBase
{
public:
	CallHelpOnDamageModuleData();
	virtual ~CallHelpOnDamageModuleData();

private:
	float m_float0C;	// +0x0C
	int m_int10;	// +0x10
	bool m_flag14;	// +0x14
	char m_pad15[3];	// +0x15, retail addresses the +0x18 member past it
	Rva003623E5Filter m_filter18;	// +0x18
};

CallHelpOnDamageModuleData::CallHelpOnDamageModuleData()
{
	m_or08 |= -1;
	m_float0C = 100.0f;
	m_int10 = g_bfmeScaleBase * 4;
	m_flag14 = false;
	m_filter18.construct();
	m_filter18.applyFilter(g_bfmeFilterArg);
}
