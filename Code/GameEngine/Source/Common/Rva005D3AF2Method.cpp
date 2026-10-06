// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005D3AF2@Rva005D3AF2@@QAEXXZ retail 0x005D3AF2 52B
// Evidence: unlock-lane body with rowed slot1 0x005CB260 and pinned no-arg int 0x005CB265 getters on +0x18 pointer compared against +0x1C holder first dword then clears +0x1C via rowed 0x002BED91; same shape as Rva005796B3Method.cpp and Rva005F3F14Method.cpp; callers 0x005D3C23 0x005D3C4F 0x005D3CB3 0x005D3D54 0x005D3DDE; neighbours share // cl: /O1 /MD /EHsc
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

class Rva005D3AF2
{
public:
	void rva005D3AF2();
private:
	char m_00[0x18];
	void *m_18;
	Rva002BED91 m_1C;
};

void Rva005D3AF2::rva005D3AF2()
{
	if (m_18 == 0)
		return;
	void *v = m_1C.m_ptr;
	if (v == 0)
		return;
	if (((Rva005CB265 *)m_18)->Rva005CB265::rva005CB265() != (int)v)
		return;
	((Rva005CB260 *)m_18)->rva005CB260();
	m_1C.clear();
}
