// cl: /MD
// ?rva005E7855@Rva005E7855@@QAEXXZ @0x005E7855 69B
// Chain via just-landed 0x005E73B2: five no-arg virtual takes-0 calls on
// member at +0x0C (slots 0x0C 0x14 0x1C 0x24 0x04) then if m_1C != 0 tail to
// rowed check 0x005E73B2 then clear m_21. Evidence: packet disassembly plus
// callers 0x005E7C19 0x005E7DD6 plus prev/next flags.
class Rva005E7855Target
{
public:
	virtual void slot0(int);
	virtual void slot1(int);
	virtual void slot2(int);
	virtual void slot3(int);
	virtual void slot4(int);
	virtual void slot5(int);
	virtual void slot6(int);
	virtual void slot7(int);
	virtual void slot8(int);
	virtual void slot9(int);
};

class Rva005E73B2
{
public:
	void rva005E73B2();
};

class Rva005E7855
{
public:
	void rva005E7855();
private:
	char m_pad0[0x0C];
	Rva005E7855Target *m_C;
	char m_pad10[0x1C - 0x10];
	int m_1C;
	char m_pad20[0x21 - 0x20];
	unsigned char m_21;
};

void Rva005E7855::rva005E7855()
{
	Rva005E7855Target *p = m_C;
	p->slot3(0);
	p->slot5(0);
	p->slot7(0);
	p->slot9(0);
	p->slot1(0);
	if (m_1C != 0)
		((Rva005E73B2 *)this)->rva005E73B2();
	m_21 = 0;
}
