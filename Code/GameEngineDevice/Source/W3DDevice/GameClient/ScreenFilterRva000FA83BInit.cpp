// cl: /O1 /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?init@Rva000FA83B@@QAEPAV1@XZ @ 0x000FA83B, 115 bytes.
// Screen-filter object init installing vtable 0x00BCF2F8.
//
// Target facts (retail game.dat, ImageBase 0x400000, read-only): 115B
// contiguous 0xFA83B-0xFA8AE, exit ret at 0xFA8AD; frameless thiscall (push
// ecx/push ebx/push esi, this in ESI, returns this in EAX, ret C3), no EH
// prolog, SSE movss/xorps float fields. Stores: [esi]=0xBCF2F8,
// +0x04/+0x08/+0x0C=0, +0x10=0 (byte), +0x14=1.0f (from VA 0xBBB8D8),
// +0x18=15, +0x1C=0 (byte), +0x20/+0x24/+0x28=0.0f,
// +0x2C=0, +0x30=0 (byte); explicit vector-base construction at +0x34 via
// the single direct call (E8 -> 0x211E58, rowed _Vector_base<BfmeE16>);
// +0x40..+0x5C=0 (8 dwords).
//
// Identity (independent of bytes): vtable 0xBCF2F8 slot1 is the matched
// sibling shutdown 0xFA8AE (?shutdown@Rva007DCA80, same source file family
// ScreenFilterRva007DCA80Shutdown.cpp, // cl: /O1 /DNDEBUG /MD); sole
// retail caller is the static-init wrapper at RVA 0x7AC910 (mov ecx,
// 0xDEC0E0; call 0xFA83B; push 0xBB6ED6; call _atexit), verified by decode;
// successor adjacency 0xFA83B+115=0xFA8AE (matched row); layout mirrors the
// sibling shader/vec/texture-surface shape (zeros, float pad words, vector
// at +0x34, trailing zeroed dwords).
//
// Provenance: BFME1 ScreenFilter family at verified pointer 6583b3c1 (no
// fetch): sibling BFME2 shutdown row notes a BFME1 donor compiled /O1, and
// BFME1 ScreenMotionBlurFilterConstructor.cpp shows the clean vptr-plus-
// zeroing ctor shape. No ZH match/packet covers 0xFA83B, so no ZH body is
// ported. Exact BFME1 donor file for this init is not pinned; the class
// name is therefore address-based (Rva000FA83B), not a donor claim.
//
// Method: TU-local raw storage + MSVC explicit-ctor-call for the vector
// base (Rva0026AFDA banked-partial precedent, same lea/push/lea/call split
// with stores around it), vtable via address-named extern (W3DFloorDrawCtor
// precedent; immediate is DIR32-masked in comparison). Zero new pins: the
// only call resolves to rowed 0x211E58. Inferences (field purposes, global
// 0xDEC0E0 identity, slot 0/2-7 names) are not claimed.
#include <vector>

extern "C" const void *const vtbl_00BCF2F8[];

struct BfmeE16 { float x, y, z, w; };

typedef _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > BfmeE16VecBase;

class Rva000FA83B
{
public:
	Rva000FA83B *init();

private:
	const void *m_vptr;			// +0x00 (vtbl_00BCF2F8)
	int m_04;				// +0x04
	int m_08;				// +0x08
	int m_0C;				// +0x0C
	unsigned char m_10;			// +0x10
	float m_14;				// +0x14 (1.0f)
	int m_18;				// +0x18 (15)
	unsigned char m_1C;			// +0x1C
	float m_20;				// +0x20
	float m_24;				// +0x24
	float m_28;				// +0x28
	int m_2C;				// +0x2C
	unsigned char m_30;			// +0x30
	unsigned char m_pad31[3];		// +0x31..0x33 (alignment pad; retail never stores)
	unsigned char m_vec34[0xC];		// +0x34 (vector<BfmeE16> storage)
	int m_40;				// +0x40
	int m_44;				// +0x44
	int m_48;				// +0x48
	int m_4C;				// +0x4C
	int m_50;				// +0x50
	int m_54;				// +0x54
	int m_58;				// +0x58
	int m_5C;				// +0x5C
};

// ?init@Rva000FA83B@@QAEPAV1@XZ @0xFA83B
Rva000FA83B *Rva000FA83B::init()
{
	m_14 = 1.0f;
	*(unsigned int *)this = (unsigned int)vtbl_00BCF2F8;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_18 = 15;
	m_1C = 0;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2C = 0;
	m_30 = 0;
	// Explicit in-place base construction (MSVC explicit-ctor-call): emits
	// the guard-free direct 0x211E58 call staged mid-body after the stores
	// above, matching retail's lea/push/lea/call split.
	((BfmeE16VecBase &)m_vec34)._STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >::_Vector_base(_STL::allocator<BfmeE16>());
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5C = 0;
	return this;
}
