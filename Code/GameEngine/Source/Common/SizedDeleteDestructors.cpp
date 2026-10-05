// Scalar deleting destructor with a sized indirect deallocation.
//
// Ported from Open-BFME-1
// Code/GameEngine/Source/Common/SizedDeleteDestructors.cpp (near-miss donor:
// ??_GRva00891D40SizedDeleting@@UAEPAXI@Z @0x00891D40, class size 4). The BFME2
// body at 0x006CD6C0 is the same shape with class size 0x1C and the
// deallocator pointer at 0x00E17730.
//
// WHAT THE BODY IS. MSVC 7.1's scalar deleting destructor `??_G` again, but
// the deallocation is not `??3@YAXPAX@Z`: two arguments are pushed -- the
// object and a CONSTANT -- and the call goes indirectly through a pointer in
// .data. The constant is what a SIZED deallocation function receives:
// `operator delete( void *, size_t )` is handed sizeof(class), so it fixes
// the padding declared below.
//
// The indirection is the other half. A class-level `operator delete` is called
// directly by name; what MSVC emits as `call dword ptr [<address>]` is that
// operator's body being INLINED and the body being a call through a function
// pointer -- a deallocator installed at run time. Written that way, and only
// that way, the bytes come out as retail's.
//
// IDENTITY IS NOT RECOVERED. The name is derived from the address.

extern void ( __cdecl *g_Va00E17730 )( void *storage, unsigned int size );

class SizedDeleteBase
{
public:
	virtual ~SizedDeleteBase();

	static void operator delete( void *storage, unsigned int size )
	{
		g_Va00E17730( storage, size );
	}
};

class Rva006CD6C0SizedDeleting : public SizedDeleteBase
{
public:
	virtual ~Rva006CD6C0SizedDeleting();

	char m_pad[ 24 ];
};

// The complete destructor the retail ??_G calls lives at 0x006CC4C0 (ledger
// pin) and is a 52-byte body at 0x006DAFA0 behind a jump stub -- NOT this
// empty spelling, which exists only to give MSVC the vftable use that emits
// ??_G (without a defined dtor nothing is emitted at all, and `delete` on a
// declared-only dtor compiles to a virtual call through the vftable instead
// of a static ??_G reference; both measured). Landing the true 52-byte body
// is a separate RE job; trimming this def would change ??_G emission.

// ??1Rva006CD6C0SizedDeleting@@UAE@XZ present-unmatched
Rva006CD6C0SizedDeleting::~Rva006CD6C0SizedDeleting()
{
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_Va00E17730@@3P6AXPAXI@ZA=?g_bfmeAptFreeSizeAtE17730@@3P6AXPAXI@ZA")
