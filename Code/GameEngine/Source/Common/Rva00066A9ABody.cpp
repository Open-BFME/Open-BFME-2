// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Dump range 1 (0x00066A9A 55B): head calls plus dual guarded tail.
// Head calls the pinned 0x00077F80 on this, then the pinned 0x0007E89C
// through the retail global at 0x00DE2000 when non-null. Tail reuses the
// proven 0x680B3 pattern: +0x3850 call plus +0x3854 tail jmp into pinned
// 0x000EA1F3/0x000E6FC8. Honest address-derived names.

extern void *g_00DE2000;

class Rva00066A9ASub
{
public:
	void headB();
	void tailA();
	void tailB();
};

class Rva00066A9AHost
{
public:
	void rva00066A9A();
	void headA();

	char m_pad[0x3850];
	Rva00066A9ASub *m_3850; // +0x3850
	Rva00066A9ASub *m_3854; // +0x3854
};

void Rva00066A9AHost::rva00066A9A()
{
	headA();
	Rva00066A9ASub *g = (Rva00066A9ASub *)g_00DE2000;
	if (g)
		g->headB();
	if (m_3850)
		m_3850->tailA();
	if (m_3854)
		m_3854->tailB();
}
