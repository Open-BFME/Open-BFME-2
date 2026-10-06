// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005E197E@Rva005E197E@@QAEXXZ retail 0x005E197E 54B
// Evidence: unlock same shape as Rva005D3AF2Method.cpp with double indirection +0x10 to +8 for rowed slot1 0x005CB260 and pinned no-arg int 0x005CB265 plus always-clear +0x1C via rowed 0x002BED91; callers 0x005E1AD3 0x005E1C04
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

struct Rva002BED91
{
	void *m_ptr;
	void clear();
};

struct Rva005E197EOuter
{
	char m_pad[8];
	void *m_ptr08;
};

class Rva005E197E
{
public:
	void rva005E197E();
private:
	char m_pad00[0x10];
	Rva005E197EOuter *m_10;
	char m_pad14[0x1C - 0x14];
	Rva002BED91 m_1C;
};

void Rva005E197E::rva005E197E()
{
	void *v = m_1C.m_ptr;
	if (v == 0)
		return;
	if (((Rva005CB265 *)m_10->m_ptr08)->Rva005CB265::rva005CB265() == (int)v)
		((Rva005CB260 *)m_10->m_ptr08)->rva005CB260();
	m_1C.clear();
}
