// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?Rva0009072BAlloc@@YAPAXHH@Z @0x0009072B 40B
// Gap between FrameDataManagerCounts 0x0009070B and Disp8ByteOneSetters 0x00090753.
// Allocates size bytes via rowed operator new[] 0x0002FDE0, zeroes via CRT memset
// thunk 0x006291AE, stores header at +0 and size at +4, returns pointer.
// Callers at 0x0009199B and 0x001067B3 forward two ints; landing unblocks 2.
#pragma function(memset)

extern "C" void *memset(void *dst, int value, unsigned int size);
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

// ?Rva00090714Free@@YAXPAPAX@Z @0x00090714 23B
// Gap between FrameDataManagerCounts 0x0009070B and Rva0009072BAlloc 0x0009072B.
// Frees *p via rowed operator delete[] 0x0002FD80 and zeroes *p.
// Callers at 0x000908A1 0x00091992 0x001067D8; landing unblocks 2.
void Rva00090714Free(void **p)
{
	void *v = *p;
	if (v != 0) {
		operator delete[](v);
		*p = 0;
	}
}

void *Rva0009072BAlloc(int header, int size)
{
	void *p = operator new[](size);
	memset(p, 0, size);
	((int *)p)[1] = size;
	((int *)p)[0] = header;
	return p;
}
