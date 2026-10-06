// ?rva005170CD@Rva005170CD@@QAEXXZ @0x005170CD 36B
// cl: /Ireference/shims/bfme2_ascii /MD
// Unlock reset: conditional Rva00437E9C(0) plus clear trailing flag plus tail jmp to rva00516F3F. Evidence: callees 0x00437E9C pin-only 0x00516F3F rowed; offsets 0x298 0x2B0; callers 0x005A3652 0x005A640F 0x005A652D unclaimed; prev 0x00517048 next 0x0051719B.
#include "ascii_string.h"

void __cdecl Rva00437E9C(int value);

struct Rva00516F3F
{
	char m_data[0x18];
	void rva00516F3F();
};

struct Rva005170CDInner
{
	Rva00516F3F base;
	int m_18;
};

class Rva005170CD
{
public:
	void rva005170CD();
private:
	char m_pad0[0x298];
	Rva005170CDInner m_inner;
};

void Rva005170CD::rva005170CD()
{
	if (m_inner.m_18 != 0)
		Rva00437E9C(0);
	Rva005170CDInner *q = &m_inner;
	q->m_18 = 0;
	return q->base.rva00516F3F();
}
