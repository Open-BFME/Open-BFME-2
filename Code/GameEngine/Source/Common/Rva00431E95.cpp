// cl: /MD
// ?rva00431E95@Rva00431E95@@QAEHPAX@Z @0x00431E95 65B.
// Evidence: chain via 0x004319F2; helper new 12B with vtable g_00C3C9AC plus final
// Rva00575674 call; rowed new 0x0002FDA0 rva00575674 0x00575674 Rva004319F2Update;
// callers 0x004320B1; prev Rva00431C35 next Rva00431F0C same dir same flags.
void __cdecl Rva004319F2Update();

extern const void *const g_00C3C9AC[];

struct Rva00431E95Helper
{
	void *m_vptr;
	void *m_04;
	void *m_08;
};

struct Rva00431E95Param
{
	char m_pad[0x10];
	void *m_10;
};

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *o);
};

class Rva00431E95
{
	void *m_00;
	void *m_04;
public:
	int rva00431E95(void *p);
};

void *__cdecl operator new(unsigned int size);

int Rva00431E95::rva00431E95(void *p)
{
	Rva004319F2Update();
	Rva00431E95Param *par = (Rva00431E95Param *)p;
	void *mem = operator new(12);
	Rva00431E95Helper *h;
	if (mem != 0)
	{
		void *v = par->m_10;
		h = (Rva00431E95Helper *)mem;
		h->m_04 = m_04;
		h->m_vptr = (void *)g_00C3C9AC;
		h->m_08 = v;
	}
	else
	{
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
	return 1;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C3C9AC@@3QBQBXB=??_7Rva00431A34@@6B@")
