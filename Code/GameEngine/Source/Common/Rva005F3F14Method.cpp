// cl: /MD
// ?rva005F3F14@Rva005F3F14@@QAEXXZ @0x005F3F14 38B.
// Evidence: retail unlock-lane body with rowed slot1 0x005CB260 and pinned
// no-arg int 0x005CB265 getters on +0x08 pointer compared against +0x10 int
// then clears +0x15 byte; same shape as Rva005796B3Method.cpp; caller
// 0x005F3F6B forwards +0x08 pointer as this.
class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005F3F14
{
public:
	void rva005F3F14();
private:
	char m_00[8];
	void *m_08;
	char m_0C[4];
	int m_10;
	char m_14;
	unsigned char m_15;
};

void Rva005F3F14::rva005F3F14()
{
	int v = m_10;
	if (v != 0)
	{
		if (((Rva005CB265 *)m_08)->Rva005CB265::rva005CB265() == v)
			((Rva005CB260 *)m_08)->rva005CB260();
	}
	m_15 = 0;
}

class Rva005F3F6B
{
public:
	void rva005F3F6B();
private:
	char m_00[8];
	Rva005F3F14 *m_08;
};

void Rva005F3F6B::rva005F3F6B()
{
	m_08->rva005F3F14();
}
