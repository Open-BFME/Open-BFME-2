// ?rva006ccaf0@@YAXPBD@Z
// partial score=0.95 date=2026-10-05
// ?rva006ccaf0@@YAXPBD@Z
// partial score=0.95 date=2026-10-04
// ?rva006ccaf0@@YAXPBD@Z
// cl: /O2 /MD /EHsc
// ?rva006ccaf0@@YAXPBD@Z @ 0x006CCAF0 (139B).
//
// Address-derived recovery of the Apt value-name registration that names a
// freshly created value. It builds an EAStringC from the caller's name, asks
// the unrowed Apt name factory 0x006CC530 for the canonical name, constructs
// the rowed AptValueNameEntry 0x006DCD20 through the named-value cache at
// 0x00E182E0, sets the entry's key through 0x006DE870 and finishes with the
// entry's virtual Release (slot 1). The SEH frame is the EAStringC temporary's
// destructor 0x006D3010, which is the same shape the rowed Apt clusters
// Rva006ffce0Cluster.cpp and Rva006ffc30Cluster.cpp already carry.
//
// The name factory 0x006CC530 is cdecl with six stack arguments -- retail
// pushes 0, 1, 1, the out EAStringC*, then 0, 0 -- and returns the canonical
// char* it built. Its body is unnamed, so the spelling here is address-derived.

class EAStringC
{
public:
	EAStringC();
	EAStringC(const char *value);
	~EAStringC();
};

// 0x006CC530: cdecl, six stack arguments (0, 0, out string, 1, 1, 0); returns
// the canonical char* it wrote. Unnamed body; address-derived here. The
// declaration order is the reverse of retail's push sequence, which is why the
// out pointer is the third parameter rather than the first.
//
// The callee writes through its out argument, but the pointer-vs-reference
// spelling is not what the pushes can settle: both spellings give the same six
// pushes and both were measured. What the pushes DO show is that the EAStringC
// sits at [esp+8] and that the caller reloads its own argument straight out of
// [esp+0x14] rather than spilling it, so the body needs no named local for it.
const char *rva006CC530(int zero, int zero2, EAStringC &out, int one,
                        int oneAgain, int zero3);

class Rva006DCD20
{
public:
	// 0x006DE870: thiscall, one stack argument; appends the run into the entry's
	// key buffer. Unnamed body; address-derived here.
	//
	// The key is taken BY REFERENCE, and that is what decides the register
	// tuple. Retail keeps the caller's name in esi across the EAStringC ctor
	// (`push esi / mov eax,[esp+0x14] / push eax / lea ecx,[esp+8] / call`) and
	// reloads it off its own argument slot only at the key call
	// (`mov eax,[esp+0x1c] / push eax`). Spelled by value, MSVC instead sinks a
	// `push edi / mov edi,[esp+0x1c]` to the head of the frame, which adds four
	// bytes ahead of everything and shifts every later displacement. A
	// reference parameter is the one spelling that makes MSVC spend esi here.
	void rva006DE870(const char *&key);

	virtual void slot0();
	virtual void release();
};

// The named-value cache that lives at 0x00E182E0. Retail enters the 0x006FFD80
// ctor with `mov ecx,0x00E182E0`, so the cache is reached through that address
// rather than through a pointer loaded out of .bss. Naming the cache TYPE
// rather than a pointer to it is what reproduces the immediate form: naming an
// object type makes this an object expression, and MSVC materializes such an
// address as an immediate `mov ecx,<addr>` instead of a load through .bss.
class Rva006DCD20Cache
{
public:
	Rva006DCD20 *rva006FFD80(const char *name);
};

extern Rva006DCD20Cache g_bfmeAptNameCacheAtE182E0;

// ?rva006ccaf0@@YAXPBD@Z @ 0x006CCAF0 (139B)
void rva006ccaf0(const char *name)
{
	{
		EAStringC wanted(name);
		const char *canonical = rva006CC530(0, 0, wanted, 1, 1, 0);

		Rva006DCD20 *entry = g_bfmeAptNameCacheAtE182E0.rva006FFD80(canonical);
		entry->slot0();
		entry->rva006DE870(name);
		entry->release();
	}
}