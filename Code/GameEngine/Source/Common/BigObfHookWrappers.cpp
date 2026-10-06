// cl: /DNDEBUG /MD
// Twenty-two 89-byte __cdecl anti-tamper hook wrappers, one shape. Ported from
// the Open-BFME-1 donor game/GameEngine/Source/Common/BigObfHookWrappers.cpp
// (reference/open-bfme-1 @ 6583b3c1), whose thirty-two BFME 1 members are the
// same function compiled to 100 bytes there.
//
// Retail (target evidence, every member):
//
//     hook = G.m_hook;                       ; mov eax,[G]
//     if (hook) goto hot;
//     if (G.m_alt) { hot: ... }              ; cmp [G+4],eax
//     return fallback(a, b);                 ; out-of-line tail block
//   hot:
//     pa = G.m_a; pb = G.m_b;                ; G+0x88 and G+0x8C, loaded
//     State o(&a, &b);                       ; before the 32-byte local's
//     return hook(pa, pb, (__int64)(int)&o); ; __thiscall initializer runs
//
// The four global loads sit at offsets 0, 4, 0x88 and 0x8C from one base in
// all twenty-two members, the layout the donor's slot object declares. Six
// distinct slot bases are shared among them. `lea eax,<local>` / `cdq` /
// `push edx` / `push eax` is the donor's sign-extended 64-bit third argument.
// Block order (hot block falls through from the second test, fallback parked
// after its `ret`) is what the donor's `goto` reproduces; carried from the
// donor, rechecked here by the byte gate.
//
// IDENTITY IS NOT RECOVERED. Every name is address-derived. The 32-byte state
// initializers are the ledger's own rows (each member's REL32 lands on one);
// they are called under the names and signatures those rows carry, so two
// spellings appear: a this-returning method and a constructor. The fallbacks
// are unrowed obfuscated bodies, pinned in reverse/symbols.csv from each
// member's REL32. Five members were already pinned as callees of matched rows
// (?Rva00077140@@YAHHH@Z, the donor's BFME 1 placeholder carried into a BFME 2
// pin, and four ?bfmeHash...@@YAIII@Z); those keep their pinned names and
// signatures so their callers' references resolve to these bodies.

typedef int (__cdecl *BigObfHook)( void *, void *, __int64 );

struct BigObfSlot
{
	BigObfHook  m_hook;
	BigObfHook  m_alt;
	char        m_pad[ 0x80 ];
	void       *m_a;
	void       *m_b;
};

#define BFME_OBF_SLOT( VA )                                               \
	extern BigObfSlot g_ObfSlot##VA;

// State initializer rowed as ?rvaXXXXXXXX@RvaXXXXXXXX@@QAEPAU1@PAX0@Z.
#define BFME_OBF_STATE_METHOD( ADDR )                                     \
	struct Rva##ADDR                                                      \
	{                                                                     \
		int m_bits[ 8 ];                                                  \
		Rva##ADDR *rva##ADDR( void *a1, void *a2 );                       \
	};

// State initializer rowed as ??0RvaXXXXXXXX@@QAE@PAI0@Z.
#define BFME_OBF_STATE_CTOR( ADDR )                                       \
	class Rva##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		Rva##ADDR( unsigned int *a, unsigned int *b );                    \
		unsigned int m_bits[ 8 ];                                         \
	};

#define BFME_OBF_WRAPPER_M( NAME, T, SLOT, ADDR, FALLBACK )               \
	T __cdecl FALLBACK( T a, T b );                                       \
	T __cdecl NAME( T a, T b );                                           \
	T __cdecl NAME( T a, T b )                                            \
	{                                                                     \
		if ( SLOT.m_hook )                                                \
			goto hot;                                                     \
		if ( SLOT.m_alt )                                                 \
		{                                                                 \
	hot:                                                                  \
			void *pa = SLOT.m_a;                                          \
			void *pb = SLOT.m_b;                                          \
			BigObfHook hook = SLOT.m_hook;                                \
			Rva##ADDR o;                                                  \
			o.rva##ADDR( &a, &b );                                        \
			return hook( pa, pb, (__int64)(int)&o );                      \
		}                                                                 \
		return FALLBACK( a, b );                                          \
	}

#define BFME_OBF_WRAPPER_C( NAME, T, SLOT, ADDR, FALLBACK )               \
	T __cdecl FALLBACK( T a, T b );                                       \
	T __cdecl NAME( T a, T b );                                           \
	T __cdecl NAME( T a, T b )                                            \
	{                                                                     \
		if ( SLOT.m_hook )                                                \
			goto hot;                                                     \
		if ( SLOT.m_alt )                                                 \
		{                                                                 \
	hot:                                                                  \
			void *pa = SLOT.m_a;                                          \
			void *pb = SLOT.m_b;                                          \
			BigObfHook hook = SLOT.m_hook;                                \
			Rva##ADDR o( (unsigned int *)&a, (unsigned int *)&b );        \
			return hook( pa, pb, (__int64)(int)&o );                      \
		}                                                                 \
		return FALLBACK( a, b );                                          \
	}

BFME_OBF_SLOT( 00DC22AC )
BFME_OBF_SLOT( 00DC28BC )
BFME_OBF_SLOT( 00DC2D48 )
BFME_OBF_SLOT( 00DC34DC )
BFME_OBF_SLOT( 00DC4B98 )
BFME_OBF_SLOT( 00DC51A8 )

BFME_OBF_STATE_METHOD( 0022C6B6 )
BFME_OBF_STATE_METHOD( 0022C743 )
BFME_OBF_STATE_METHOD( 0022C7C9 )
BFME_OBF_STATE_METHOD( 0022C856 )
BFME_OBF_STATE_METHOD( 003F17D6 )
BFME_OBF_STATE_METHOD( 003F1863 )
BFME_OBF_STATE_METHOD( 003F18F0 )
BFME_OBF_STATE_METHOD( 003F1976 )
BFME_OBF_STATE_CTOR( 00434C67 )
BFME_OBF_STATE_CTOR( 00434CF4 )
BFME_OBF_STATE_CTOR( 00434D7A )
BFME_OBF_STATE_CTOR( 00434E07 )
BFME_OBF_STATE_METHOD( 0056EED8 )
BFME_OBF_STATE_METHOD( 0056EF65 )
BFME_OBF_STATE_METHOD( 0056EFF2 )
BFME_OBF_STATE_METHOD( 0056F07F )
BFME_OBF_STATE_METHOD( 0056F10C )
BFME_OBF_STATE_METHOD( 0056F192 )
BFME_OBF_STATE_METHOD( 0056F21F )
BFME_OBF_STATE_METHOD( 0056F2A5 )
BFME_OBF_STATE_METHOD( 0056F32B )
BFME_OBF_STATE_METHOD( 0056F3B1 )

// ?Rva00077140@@YAHHH@Z @0x0022CB03 89B
BFME_OBF_WRAPPER_M( Rva00077140, int, g_ObfSlot00DC22AC, 0022C6B6, Rva002264B3Fallback )
// ?Rva0022CB5CHook@@YAHHH@Z @0x0022CB5C 89B
BFME_OBF_WRAPPER_M( Rva0022CB5CHook, int, g_ObfSlot00DC22AC, 0022C743, Rva00226588Fallback )
// ?Rva0022CBB5Hook@@YAHHH@Z @0x0022CBB5 89B
BFME_OBF_WRAPPER_M( Rva0022CBB5Hook, int, g_ObfSlot00DC22AC, 0022C7C9, Rva0022665EFallback )
// ?Rva0022CC0EHook@@YAHHH@Z @0x0022CC0E 89B
BFME_OBF_WRAPPER_M( Rva0022CC0EHook, int, g_ObfSlot00DC22AC, 0022C856, Rva00226733Fallback )
// ?bfmeHash0002A473@@YAIII@Z @0x003F1D23 89B
BFME_OBF_WRAPPER_M( bfmeHash0002A473, unsigned int, g_ObfSlot00DC34DC, 003F17D6, Rva003F0906Fallback )
// ?Rva003F1D7CHook@@YAHHH@Z @0x003F1D7C 89B
BFME_OBF_WRAPPER_M( Rva003F1D7CHook, int, g_ObfSlot00DC34DC, 003F1863, Rva003F09DFFallback )
// ?Rva003F1DD5Hook@@YAHHH@Z @0x003F1DD5 89B
BFME_OBF_WRAPPER_M( Rva003F1DD5Hook, int, g_ObfSlot00DC34DC, 003F18F0, Rva003F0AB8Fallback )
// ?Rva003F1E2EHook@@YAHHH@Z @0x003F1E2E 89B
BFME_OBF_WRAPPER_M( Rva003F1E2EHook, int, g_ObfSlot00DC34DC, 003F1976, Rva003F0B92Fallback )
// ?bfmeHash00010AFA@@YAIII@Z @0x0043538F 89B
BFME_OBF_WRAPPER_C( bfmeHash00010AFA, unsigned int, g_ObfSlot00DC51A8, 00434C67, Rva00434548Fallback )
// ?Rva004353E8Hook@@YAHHH@Z @0x004353E8 89B
BFME_OBF_WRAPPER_C( Rva004353E8Hook, int, g_ObfSlot00DC51A8, 00434CF4, Rva00434621Fallback )
// ?Rva00435441Hook@@YAHHH@Z @0x00435441 89B
BFME_OBF_WRAPPER_C( Rva00435441Hook, int, g_ObfSlot00DC51A8, 00434D7A, Rva004346FBFallback )
// ?Rva0043549AHook@@YAHHH@Z @0x0043549A 89B
BFME_OBF_WRAPPER_C( Rva0043549AHook, int, g_ObfSlot00DC51A8, 00434E07, Rva004347D4Fallback )
// ?bfmeHash0002BB70@@YAIII@Z @0x0056F52C 89B
BFME_OBF_WRAPPER_M( bfmeHash0002BB70, unsigned int, g_ObfSlot00DC28BC, 0056EED8, Rva0056DE2BFallback )
// ?bfmeHash00013412@@YAIII@Z @0x0056F585 89B
BFME_OBF_WRAPPER_M( bfmeHash00013412, unsigned int, g_ObfSlot00DC2D48, 0056EF65, Rva0056DF04Fallback )
// ?Rva0056F5DEHook@@YAHHH@Z @0x0056F5DE 89B
BFME_OBF_WRAPPER_M( Rva0056F5DEHook, int, g_ObfSlot00DC4B98, 0056EFF2, Rva0056DFD9Fallback )
// ?Rva0056F637Hook@@YAHHH@Z @0x0056F637 89B
BFME_OBF_WRAPPER_M( Rva0056F637Hook, int, g_ObfSlot00DC4B98, 0056F07F, Rva0056E0AEFallback )
// ?Rva0056F690Hook@@YAHHH@Z @0x0056F690 89B
BFME_OBF_WRAPPER_M( Rva0056F690Hook, int, g_ObfSlot00DC28BC, 0056F10C, Rva0056E187Fallback )
// ?Rva0056F6E9Hook@@YAHHH@Z @0x0056F6E9 89B
BFME_OBF_WRAPPER_M( Rva0056F6E9Hook, int, g_ObfSlot00DC2D48, 0056F192, Rva0056E261Fallback )
// ?Rva0056F742Hook@@YAHHH@Z @0x0056F742 89B
BFME_OBF_WRAPPER_M( Rva0056F742Hook, int, g_ObfSlot00DC2D48, 0056F21F, Rva0056E336Fallback )
// ?Rva0056F79BHook@@YAHHH@Z @0x0056F79B 89B
BFME_OBF_WRAPPER_M( Rva0056F79BHook, int, g_ObfSlot00DC4B98, 0056F2A5, Rva0056E40CFallback )
// ?Rva0056F7F4Hook@@YAHHH@Z @0x0056F7F4 89B
BFME_OBF_WRAPPER_M( Rva0056F7F4Hook, int, g_ObfSlot00DC4B98, 0056F32B, Rva0056E4E2Fallback )
// ?Rva0056F84DHook@@YAHHH@Z @0x0056F84D 89B
BFME_OBF_WRAPPER_M( Rva0056F84DHook, int, g_ObfSlot00DC2D48, 0056F3B1, Rva0056E5BCFallback )
