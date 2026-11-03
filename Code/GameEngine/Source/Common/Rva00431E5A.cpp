// cl: /MD
// ?rva00431E5A@Rva00431E5A@@QAEXXZ @0x00431E5A 59B: thiscall method with early-out on AreBothButtonsStillDown then helper new 8B with vtable 0x0083C97C plus final Rva00575674 call. Evidence: chain via 0x004319F2; rowed AreBothButtonsStillDown 0x004319D4 Rva004319F2Update 0x004319F2 new 0x0002FDA0 rva00575674 0x00575674; vtables g_00C3C97C; prev Rva00431C35 next Rva00431E95 same dir same flags.
int __cdecl AreBothButtonsStillDown();
void __cdecl Rva004319F2Update();

extern "C" const void *const __identifier("??_7Rva004318FC@@6B@")[];

struct Rva00431E5AHelper
{
	void *m_vptr;
	void *m_parent;
};

class Object;
#include "../../Include/Common/Rva00575674.h"

class Rva00431E5A
{
	void *m_00;
	void *m_04;
public:
	void rva00431E5A();
};

#include <new>

void Rva00431E5A::rva00431E5A()
{
	if ((unsigned char)AreBothButtonsStillDown() != 0)
		return;
	Rva004319F2Update();
	void *mem = operator new(8);
	Rva00431E5AHelper *h;
	if (mem != 0)
	{
		h = (Rva00431E5AHelper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)__identifier("??_7Rva004318FC@@6B@");
	}
	else
	{
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}
