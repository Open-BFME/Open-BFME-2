// cl: /O1 /DNDEBUG /MD
//
// ?rva002E6329@@YAPAXPAX0000@Z @0x002E6329 33B: chaining forwarder (free
// function, 5 args, void* return). Retail forwards all five args plus a zero
// to the pinned cdecl sibling at 0x002E6184, then returns arg1. Honest
// address-derived names.

struct Rva002E6329Owner
{
	// ?rva002E6184@Rva002E6329Owner@@SAXPAX0000H@Z: static void
	// (void*x5, int); address from retail REL32.
	static void rva002E6184(void *a, void *b, void *c, void *d, void *e, int f);
};

// ?rva002E6329@@YAPAXPAX0000@Z
void *rva002E6329(void *a, void *b, void *c, void *d, void *e)
{
	Rva002E6329Owner::rva002E6184(a, b, c, d, e, 0);
	return a;
}
