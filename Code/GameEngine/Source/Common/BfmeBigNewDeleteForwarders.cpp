// cl: /DNDEBUG /MD
//
// ?bfmeBigAllocPR@@YAPAXI@Z (retail 0x00023790, 5 bytes) and
// ?bfmeBigFreePM@@YAXPAX@Z (retail 0x000237A0, 5 bytes): out-of-line
// forwarders to the global allocator. Each is a single tail jump, to the
// rowed ::operator new (0x0002FDA0) and ::operator delete (0x0002FD60)
// respectively. The names are the address-derived ones symbols.csv pins for
// their 7 and 4 calling units; the true identity (plausibly an allocator
// helper's allocate/deallocate) is not witnessed.

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

void *bfmeBigAllocPR(unsigned int size)
{
	return operator new(size);
}

void bfmeBigFreePM(void *block)
{
	operator delete(block);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_bfmeMalloc1149=?bfmeBigAllocPR@@YAPAXI@Z")
#pragma comment(linker, "/alternatename:_bfmeMalloc1150=?bfmeBigAllocPR@@YAPAXI@Z")
