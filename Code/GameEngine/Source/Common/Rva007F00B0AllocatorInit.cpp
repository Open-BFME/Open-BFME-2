// Address-derived reconstruction of retail 0x007F00B0 (98 bytes).
// The caller and the neighbouring FESL allocator bodies establish a three-
// pointer interface object: vptr, acquire callback, release callback.
// Transferred to BFME2 retail 0x0065CF90: identical logic, but the three
// embedded addresses are game-specific (BFME2 values measured from retail:
// default acquire 0x00A5CEC0, table 0x00CE1DFC, default release 0x00A5CED0).

extern "C" const void *const vtbl_00CE1DFC[];  // ??_7Rva007F0080Owner@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE1DFC=??_7Rva007F0080Owner@@6B@")

struct Rva007F00B0Allocator
{
	void *m_vtable;
	void *m_allocate;
	void *m_release;
};

typedef void *(__cdecl *Rva007F00B0Allocate)(unsigned int, int);

extern class GenAlloc *g_genAlloc;

void *operator new(unsigned int size);

void Rva007F00B0(void *allocate, void *release)
{
	Rva007F00B0Allocator *p;

	if ((*(Rva007F00B0Allocator **)&g_genAlloc))
		return;

	if (allocate)
	{
		p = (Rva007F00B0Allocator *)((Rva007F00B0Allocate)allocate)(12, 0);
		if (p)
			p->m_allocate = allocate;
		else
			goto clear;
	}
	else
	{
		p = (Rva007F00B0Allocator *)::operator new(12);
		if (p)
			p->m_allocate = (void *)0x00A5CEC0;
		else
			goto clear;
	}

	p->m_vtable = (void *)((unsigned int)vtbl_00CE1DFC);
	if (!release)
		release = (void *)0x00A5CED0;
	p->m_release = release;
	(*(Rva007F00B0Allocator **)&g_genAlloc) = p;
	return;

clear:
	(*(Rva007F00B0Allocator **)&g_genAlloc) = 0;
}

