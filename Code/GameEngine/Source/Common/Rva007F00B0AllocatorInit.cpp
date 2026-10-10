// Address-derived reconstruction of retail 0x007F00B0 (98 bytes).
// The caller and the neighbouring FESL allocator bodies establish a three-
// pointer interface object: vptr, acquire callback, release callback.
// Transferred to BFME2 retail 0x0065CF90: identical logic, but the three
// embedded addresses are game-specific (BFME2 values measured from retail:
// default acquire 0x00A5CEC0, table 0x00CE1DFC, default release 0x00A5CED0).

void *__cdecl Rva0065CEC0Allocate(unsigned int, int);
void __cdecl Rva0065CED0Release(void *, int);

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
			p->m_allocate = reinterpret_cast<void *>(&Rva0065CEC0Allocate);
		else
			goto clear;
	}

	p->m_vtable = (void *)((unsigned int)vtbl_00CE1DFC);
	if (!release)
		release = reinterpret_cast<void *>(&Rva0065CED0Release);
	p->m_release = release;
	(*(Rva007F00B0Allocator **)&g_genAlloc) = p;
	return;

clear:
	(*(Rva007F00B0Allocator **)&g_genAlloc) = 0;
}

extern "C" void *__cdecl malloc(unsigned int);
extern "C" void __cdecl free(void *);

void *__cdecl Rva0065CEC0Allocate(unsigned int size, int)
{
	return malloc(size);
}

void __cdecl Rva0065CED0Release(void *pointer, int)
{
	free(pointer);
}

