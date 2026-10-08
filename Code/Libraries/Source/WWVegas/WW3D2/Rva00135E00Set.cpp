// cl: /DNDEBUG /MD
// ?rva00135E00@Rva00135E00@@QAEXHHH@Z @0x00135E00 35B.
// Flag-plus-three setter: low two bits of +0 forced to 3 keeping bit 31
// then three args stored at +4 +8 +0xC. Evidence: unlock lane; neighbour
// 0x00135E86 same flags; caller 0x001371F9; ret 0xC three args.
class Rva00135E00
{
public:
	void rva00135E00(unsigned int a, unsigned int b, unsigned int c);
private:
	unsigned int m_0;
	unsigned int m_4;
	unsigned int m_8;
	unsigned int m_c;
};
void Rva00135E00::rva00135E00(unsigned int a, unsigned int b, unsigned int c)
{
	unsigned int v = m_0;
	v &= 0x80000003;
	v |= 3;
	m_0 = v;
	m_4 = a;
	m_8 = b;
	m_c = c;
}

// Address-derived name: Rva00135E3A (38B, retail 0x00135E3A). Vslot 10 gate,
// conditional vslot 11 call, then the +0x54 object's vslot 2 as a tail jump.
class Rva00135E3AInner
{
public:
	virtual void v00();
	virtual void v01();
	virtual int v02();
};

class Rva00135E3A
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual bool v10();
	virtual void v11();
	int rva00135E3A();
private:
	char m_pad04[0x50];
	Rva00135E3AInner *m_54;
};

int Rva00135E3A::rva00135E3A()
{
	if (!v10())
		v11();
	if (!m_54)
		return 0;
	return m_54->v02();
}
