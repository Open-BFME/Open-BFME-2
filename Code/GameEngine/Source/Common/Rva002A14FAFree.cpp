// cl: /MD
// ?Rva002A14FAFree@@YGXPAX@Z @0x002A14FA 28B
// Free wrapper around rowed dtor 0x0029E00D plus rowed _free 0x00030830.
// Calls dtor on p+4 unconditionally then frees p when non-null.
// Caller 0x002A1D23; prev vector reserve; unblocks 0x002A1D02.
struct Rva0029E00D
{
	~Rva0029E00D();
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva002A14FAFree(void *p)
{
	((Rva0029E00D *)((char *)p + 4))->~Rva0029E00D();
	if (p)
		free(p);
}
