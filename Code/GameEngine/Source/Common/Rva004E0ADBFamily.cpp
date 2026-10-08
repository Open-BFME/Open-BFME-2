// cl: /MD
//
// Dump-range-25 packet family: seven homogeneous forwarders around the
// unrowed EH pair 0x004E0918/0x004E0988 (pinned as honest address-derived
// candidates; bodies deferred). A 16-byte Four plus trailing ints is packed
// and forwarded: Y::rva004E0ADB(Four,int) builds the 20-byte packet for
// 0x004E0918, Y::rva004E0B02(Four,int,int) the 24-byte packet for 0x004E0988.
// X methods forward this plus the packet to the member Y at +0x08 or
// the absolute Y at 0x00E04424, then 0x4E0CCB runs the rowed Rva004E0705
// gate 0x004E08A9 plus the rowed 0x004E0A96 flush, and 0x4E0C49 sweeps the
// [m_30..m_34) vslot-6 loop plus the 0xDFEF10+0xFC store to m_20.
// X's +0x20 int matches Rva004E0705::m_20 and the 0x4E08A9 call reuses the
// same this, so X is likely Rva004E0705 itself; kept address-named until the
// +0x08 member and +0x30 tail are proven against its other views.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002BA8F1Logic;

class Rva004E0705
{
public:
	bool rva004E08A9(bool check);
};
class Rva004E0A96
{
public:
	void rva004E0A96();
};

struct Rva004EFour
{
	int a;
	int b;
	int c;
	int d;
};

struct Rva004E20Packet
{
	Rva004EFour f;
	int e;
	int m_pad;
};

struct Rva004E24Packet
{
	Rva004EFour f;
	int e1;
	int e2;
};

class Rva004E0918
{
public:
	void rva004E0ADB(Rva004EFour f, int e);
	void rva004E0B02(Rva004EFour f, int e1, int e2);
	void rva004E0918(void *pkt);
	void rva004E0988(void *pkt);
};

class Rva004E0C49Elem
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
};

// The target call site passes the +0x2C subobject as ECX to RVA 0x0052B17F.
// Keep the local type and method address-derived; the subobject's semantic
// class remains unresolved.
class Rva0052B17F
{
public:
	void rva0052B17F();
};

extern Rva004E0918 g_00E04424;

struct Holder0052B003
{
	void rva0052B003(int value);
};

class Rva004E0B60
{
public:
	void rva004E0B60(Rva004EFour f, int e);
	void rva004E0B9B(Rva004EFour f, int e1, int e2);
	void rva004E0C49();
	void rva004E0CA3();
	bool rva004E0CCB();
	void rva004E0D19(int arg);
	void rva004E0CB6();

private:
	char m_pad[8];
	Rva004E0918 m_08;
	char m_pad09[0x20 - 0x09];
	int m_20;
	char m_pad24[0x2C - 0x24];
	void *m_2C;
	Rva004E0C49Elem **m_30;
	Rva004E0C49Elem **m_34;
};

// ?rva004E0ADB@Rva004E0918@@QAEXURva004EFour@@H@Z @0x004E0ADB 39B.
void Rva004E0918::rva004E0ADB(Rva004EFour f, int e)
{
	Rva004E20Packet pkt;
	pkt.f = f;
	pkt.e = e;
	rva004E0918(&pkt);
}

void Rva004E0918::rva004E0B02(Rva004EFour f, int e1, int e2)
{
	Rva004E24Packet pkt;
	pkt.f = f;
	pkt.e1 = e1;
	pkt.e2 = e2;
	rva004E0988(&pkt);
}

void Rva004E0B60::rva004E0B60(Rva004EFour f, int e)
{
	m_08.rva004E0ADB(f, e);
	g_00E04424.rva004E0ADB(f, e);
}

void Rva004E0B60::rva004E0B9B(Rva004EFour f, int e1, int e2)
{
	m_08.rva004E0B02(f, e1, e2);
	g_00E04424.rva004E0B02(f, e1, e2);
}

void Rva004E0B60::rva004E0C49()
{
	Rva004E0C49Elem **end = m_34;
	for (Rva004E0C49Elem **p = m_30; p != end; ++p)
		(*p)->v6();
	m_20 = *(int *)((char *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic) + 0xFC);
	Rva004EFour f = { 0x5FF3A9, 0, 0, 0 };
	rva004E0B60(f, (int)this);
}

// ?rva004E0CA3@Rva004E0B60@@QAEXXZ @0x004E0CA3 19B.
// Calls the address-derived +0x2C subobject method at 0x0052B17F, then tails
// to the rowed same-this sweep at 0x004E0C49.
void Rva004E0B60::rva004E0CA3()
{
	((Rva0052B17F *)m_2C)->rva0052B17F();
	rva004E0C49();
}

bool Rva004E0B60::rva004E0CCB()
{
	Rva004EFour f = { 0x9CC208, 0, 0, 0 };
	rva004E0B60(f, (int)this);
	if (((Rva004E0705 *)this)->rva004E08A9(true))
	{
		((Rva004E0A96 *)this)->rva004E0A96();
		return true;
	}
	return false;
}

void Rva004E0B60::rva004E0D19(int arg)
{
	Rva004EFour f = { 0x9CB265, 0, 0, 0 };
	rva004E0B9B(f, (int)this, arg);
}

// ?rva004E0CB6@Rva004E0B60@@QAEXXZ @ 0x004E0CB6 (21B).
// Calls Holder0052B003::rva0052B003(0) at 0x0052B003 through m_2C, then
// tail-jmps to rowed rva004E0C49. Caller 0x004FC437. Class proven by the
// tail edge and prev/next in this TU.
void Rva004E0B60::rva004E0CB6()
{
	((Holder0052B003 *)m_2C)->rva0052B003(0);
	rva004E0C49();
}
