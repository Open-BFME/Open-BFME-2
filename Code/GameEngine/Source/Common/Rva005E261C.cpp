// cl: /O1 /DNDEBUG /MD
// ?rva005E261C@Rva005E261C@@QAEXXZ @0x005E261C 40B.
// If +0x20 dword <0 return; else calls pinned 0x005E2460 (this-only void).
// Then if +8->+8 byte 0 return; else virtual slot +0x1C on +8 object
// then tail-jmps to rowed 0x005E2439 (this-only void). Address-derived.
class Rva005E2460
{
public:
	void rva005E2460();
};

class Rva005E261CInner
{
public:
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void _s3();
	virtual void _s4();
	virtual void _s5();
	virtual void _s6();
	virtual void rva005E261CSlot();
	unsigned char m_pad4[4];
	unsigned char m_8flag;
};

class Rva005E2439
{
public:
	void rva005E2439();
};

class Rva005E261C
{
public:
	void rva005E261C();
protected:
	unsigned char m_pad[8];
	Rva005E261CInner *m_8;
	unsigned char m_pad2[0x20 - 0x0C];
	int m_20;
};

void Rva005E261C::rva005E261C()
{
	if (m_20 < 0)
		return;
	((Rva005E2460 *)this)->rva005E2460();
	if (m_8->m_8flag == 0)
		return;
	m_8->rva005E261CSlot();
	((Rva005E2439 *)this)->rva005E2439();
}
