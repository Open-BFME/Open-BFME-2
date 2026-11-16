// cl: /MD
// ?rva005D4F0E@Rva005D4F0E@@QAEXXZ @0x005D4F0E 25B
// Triple clear: this+0 via rowed 0x0057C2CC then this+0xC via rowed 0x005D4E8B then tail jmp to rowed clear 0x002BED91 at this+8.
// Evidence: callees all rowed; callers at 0x005D5012 and jmp at 0x005D4F7F; unblocks 0x005D4F7D.
class Rva0057C2CC
{
public:
	void rva0057C2CC();
	char m_pad[8];
};
#include "../../Include/Common/Rva002BED91.h"
class Rva005D4E8B
{
public:
	void rva005D4E8B();
	void *m_ptr;
};
struct Rva005F4AD7
{
	void *m_ptr;
	~Rva005F4AD7();
	Rva005F4AD7(const Rva005F4AD7 &other) throw();
	Rva005F4AD7 &operator=(const Rva005F4AD7 &other);
};
class Rva005EE26F
{
public:
	Rva005F4AD7 rva005EE26F(int a, int b);
};
class Rva005D4F0E
{
public:
	void rva005D4F0E();
	void rva005D4F27(int a, int b);
private:
	Rva0057C2CC m_00;
	Rva002BED91 m_08;
	Rva005D4E8B m_0C;
};
void Rva005D4F0E::rva005D4F0E()
{
	m_00.rva0057C2CC();
	m_0C.rva005D4E8B();
	m_08.clear();
}
// ?rva005D4F7D@Rva005D4F7D@@QAEXXZ @0x005D4F7D 7B forwarder via m_p at +0 tail jmp to rowed 0x005D4F0E. Evidence: caller jmp at 0x0057B9EB chain from 0x005D4F0E.
class Rva005D4F7D
{
public:
	void rva005D4F7D();
private:
	Rva005D4F0E *m_p;
};
void Rva005D4F7D::rva005D4F7D()
{
	m_p->rva005D4F0E();
}

// ?rva005D4F27@Rva005D4F0E@@QAEXHH@Z @0x005D4F27 86B (EH, RET 8): a Clear
// sibling that first stores a value computed by the +8 holder's target into
// the +0xC member, then clears the +8 holder. Retail tests the +8 pointer,
// calls the rowed value-return forwarder 0x005EE26F on it (the temporary's
// sret slot reuses the dead second argument), assigns the temporary to
// the +0xC member through the rowed Rva005F4AD7 assignment 0x005FD4FF,
// destroys it (0x005F4AD7) and tail-clears the holder (0x002BED91). Names
// are address-derived.
void Rva005D4F0E::rva005D4F27(int a, int b)
{
	if (m_08.m_00)
	{
		*reinterpret_cast<Rva005F4AD7 *>(&m_0C) = reinterpret_cast<Rva005EE26F *>(m_08.m_00)->rva005EE26F(a, b);
		m_08.clear();
	}
}
