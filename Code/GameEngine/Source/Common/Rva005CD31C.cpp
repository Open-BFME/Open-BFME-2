// cl: /MD
// class-gate: allow StringBase private validate for row ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0
// ?rva005CD31C@Rva005CD31C@@QAEXXZ @0x005CD31C 47B: thiscall void like 0x005CD378 but null-checked cached +0x20->+0x18 in edi; evidence rows 0xB3FD0 0x5CCB5B pin 0x2BF6A7 sibling 0x005CD378
template <typename T> class StringBase
{
	friend class Rva005CD31C;
	void validate() const;
};

class Rva005CCB5B
{
public:
	void rva005CCB5B();
};

class Rva002BF6A7
{
public:
	void rva002BF6A7(int a);
};

class Rva005CD31CVirt
{
public:
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void _s3();
	virtual void rvaSlot(int a);
};

struct Rva005CD31CInner
{
	char m_pad[0x18];
	int m_18;
};

class Rva005CD31C
{
public:
	void rva005CD31C();
private:
	char m_pad00[0x10];
	Rva002BF6A7 *m_10;
	Rva005CD31CVirt *m_14;
	char m_pad18[0x08];
	Rva005CD31CInner *m_20;
};

void Rva005CD31C::rva005CD31C()
{
	((StringBase<unsigned short> *)this)->validate();
	((Rva005CCB5B *)this)->rva005CCB5B();
	int v = m_20->m_18;
	if (v == 0)
		return;
	m_10->rva002BF6A7(v);
	m_14->rvaSlot(v);
}
