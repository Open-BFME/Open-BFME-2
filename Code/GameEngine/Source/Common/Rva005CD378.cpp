// cl: /O1 /MD
// class-gate: allow StringBase private validate for row ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0
// ?rva005CD378@Rva005CD378@@QAEXXZ @0x005CD378 45B: thiscall void calling wide validate then rowed 0x005CCB5B then pinned 0x002BF6A7 via +0x10 and virtual slot +0x10 via +0x14 both with +0x20->+0x18; evidence rows/pins and Rva005D20E5Wrap pattern
template <typename T> class StringBase
{
	friend class Rva005CD378;
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

class Rva005CD378Virt
{
public:
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void _s3();
	virtual void rvaSlot(int a);
};

struct Rva005CD378Inner
{
	char m_pad[0x18];
	int m_18;
};

class Rva005CD378
{
public:
	void rva005CD378();
private:
	char m_pad00[0x10];
	Rva002BF6A7 *m_10;
	Rva005CD378Virt *m_14;
	char m_pad18[0x08];
	Rva005CD378Inner *m_20;
};

void Rva005CD378::rva005CD378()
{
	((StringBase<unsigned short> *)this)->validate();
	((Rva005CCB5B *)this)->rva005CCB5B();
	m_10->rva002BF6A7(m_20->m_18);
	m_14->rvaSlot(m_20->m_18);
}
