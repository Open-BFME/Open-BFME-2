// cl: /O1 /DNDEBUG /MD /EHsc
//
// Guarded forwarders 0x004FB303 (37B) and 0x004FB328 (40B): null-check the
// pointer at +0x00, then forward to a callee subobject at +0x120 / +0xFC
// with the 0x00E04508 channel constant, addresses of the +0x18/+0x80 fields
// and the target's +0x14 field. The callees (0x0059BB50, 0x0059C93C) are
// pinned, not recovered.

// Shared global provider: reverse/data_ledger.csv 0x00A04508.
extern unsigned int g_Va00E04508;

class Rva0059BB50
{
public:
	void rva0059BB50(int a, int b, int c, int d);
};

class Rva0059C93C
{
public:
	void rva0059C93C(int a, int b, int c, int d, int e);
};

struct Rva004FB303Target
{
	char m_pad[0x14];
	int val14;	// +0x14 forwarded field
};

class Rva004FB303Owner
{
public:
	void rva004FB303();
	void rva004FB328();

private:
	void *m_00;	// +0x00 (null-checked)
	int m_04;	// +0x04 (pad)
	int m_08;	// +0x08 (forwarded by 0x004FB328)
	char m_pad0C[0x0C];	// +0x0C
	int m_18;	// +0x18 (address taken)
	char m_pad1C[0x64];	// +0x1C..0x7F
	int m_80;	// +0x80 (address taken)
};

void Rva004FB303Owner::rva004FB303()
{
	Rva004FB303Target *t = (Rva004FB303Target *)m_00;
	if (!t)
		return;
	((Rva0059BB50 *)((char *)this + 0x120))->rva0059BB50((int)&m_80, t->val14, (int)&m_18, (int)&g_Va00E04508);
}

void Rva004FB303Owner::rva004FB328()
{
	Rva004FB303Target *t = (Rva004FB303Target *)m_00;
	if (!t)
		return;
	((Rva0059C93C *)((char *)this + 0xFC))->rva0059C93C((int)&m_80, t->val14, (int)&m_18, (int)&g_Va00E04508, m_08);
}

// ---- 0x004FB222 (92B): two-argument attach. Stores the target pointer at
// +0x00, forwards its +0x14 field to the +0x18 subobject (pinned 0x00502FE9),
// sets +0x08 to 5, forwards the int argument to the +0x8C/+0xEC/+0xFC/+0x120
// subobjects (rowed 0x0059D74B/0x0059CE80/0x0059BD2D, empty 0x0047A69C via
// the existing Gen alias pin), then clears the global byte 0x00E04508.
class Rva0042094D;

class Rva0059D74B
{
public:
	void rva0059D74B(Rva0042094D *p);
};

class Rva0059CE80
{
public:
	void rva0059CE80(const void *p);
};

class Rva0059BD2D
{
public:
	void rva0059BD2D(const void *p);
};

class Rva00502FE9
{
public:
	void rva00502FE9(int v);
};

class Gen_003bcb40
{
public:
	void m(int v);
};


class Rva004FB222Owner
{
public:
	void rva004FB222(Rva004FB303Target *t, int v);

private:
	void *m_00;	// +0x00 (stored target)
	int m_04;	// +0x04 (pad)
	int m_08;	// +0x08 (set to 5)
};

void Rva004FB222Owner::rva004FB222(Rva004FB303Target *t, int v)
{
	m_00 = t;
	((Rva00502FE9 *)((char *)this + 0x18))->rva00502FE9(t->val14);
	m_08 = 5;
	((Rva0059D74B *)((char *)this + 0x8C))->rva0059D74B((Rva0042094D *)v);
	((Rva0059CE80 *)((char *)this + 0xEC))->rva0059CE80((const void *)v);
	((Rva0059BD2D *)((char *)this + 0xFC))->rva0059BD2D((const void *)v);
	((Gen_003bcb40 *)((char *)this + 0x120))->m(v);
	*(unsigned char *)&g_Va00E04508 = 0;
}

// ---- 0x004FB219 (9B): frameless byte setter. Identity not recovered;
// honest address-derived name on a standalone one-byte class.
class Rva004FB219Owner
{
public:
	void rva004FB219(unsigned char v);

private:
	unsigned char m_00;	// +0x00
};

void Rva004FB219Owner::rva004FB219(unsigned char v)
{
	m_00 = v;
}
