// ?rva00524AE7@Rva00524B7A@@UAEXXZ
// partial score=0.93 date=2026-10-05
// cl: /O1 /MD
// ?rva00524AE7@Rva00524B7A@@UAEXXZ @ 0x00524AE7 (147B):
// vtable slot 10 (offset 0x28) of 0x00867DFC, class of ??0Rva00524B7A@@QAE@XZ.
// Layout carried from Code/GameEngine/Source/Common/Rva00524B7ACtor.cpp:
// vtable at +0, base pad 8, m_0C at +0xC, ints +0x10..+0x1C, m_20 at +0x20,
// flags m_24, color m_28, times m_2C/m_30, functor m_34 plus arg m_38.
// Evidence: timeGetTime IAT, rowed FunctorRef invoke 0x0057CC15, tail to
// slot 9 at [eax+0x24], virtual check on +0x0C object at [eax+0x18].
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva0057CC15Ref
{
public:
	void invoke(int a);
};

class Rva00524B7A_0C
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual unsigned char check(int v);
};

class Rva00524B7A
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void tail() = 0;
	virtual void rva00524AE7();
private:
	char m_basePad[8];
	Rva00524B7A_0C *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	int m_2C;
	int m_30;
	Rva0057CC15Ref m_34;
	int m_38;
};

// ?rva00524AE7@Rva00524B7A@@UAEXXZ present-unmatched
void Rva00524B7A::rva00524AE7()
{
	if (m_0C == 0)
		return;
	if ((m_24 & 4) != 0)
	{
		int *pTotal = &m_2C;
		unsigned long now = timeGetTime();
		unsigned int total = (unsigned int)*pTotal;
		int remain = (int)(total + (unsigned int)m_30 - now);
		unsigned int v;
		if (remain <= 0)
			v = 0;
		else
			v = (unsigned int)remain;
		v = v > total ? total : v;
		unsigned int alpha = (v * 255u) / total;
		unsigned char b = (unsigned char)alpha;
		m_28 = (int)(((unsigned int)b << 24) | 0xFFFFFF);
	}
	if ((m_24 & 2) == 0)
		goto check0c;
	if ((m_20 & 0x80) != 0)
		return;
check0c:
	unsigned char r = m_0C->check(m_20);
	if ((r & 2) == 0)
		return;
	if ((m_24 & 2) != 0)
		return;
	m_24 |= 2;
	if (*(void **)&m_34 != 0)
		m_34.invoke(m_38);
	if ((m_20 & 0x84) != 0)
		return;
	return tail();
}
