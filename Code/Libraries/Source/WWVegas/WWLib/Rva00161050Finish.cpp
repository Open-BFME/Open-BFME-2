// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// Retail 0x00161050 (77 bytes), the copy constructor of the 0x24-byte Elem36
// record whose stride the vector helpers in stlport_vector_elem36_push_back.cpp
// and ElementStrideWalks.cpp use. Landed by seat 1 continuing the banked
// attempt reverse/attempts/0x00161050.cpp.
//
// The banked attempt modelled +0x04..+0x13 as four scalar members, which makes
// MSVC emit four direct dword copies and needs only esi/edi. Retail instead
// copies that 16-byte block as a trivially-copyable struct, so MSVC lowers it
// to an inlined 16-byte memcpy that aliases the tail's ecx/edx bases into
// edi/ebx with ebp as the copy temporary. Keeping the three remaining ints as
// scalar members of the same tail forces ecx/edx (the tail bases) to survive
// the block copy, and the copy constructor's `other` pointer is then spilled
// to esi for the trailing +0x20 byte -- exactly retail's ebx+ebp+esi+edi frame.
// Element identity is not recovered; the address-derived name is retained.
struct Rva00161050Block16
{
	int m_words[4];
};

struct Rva00161050Tail
{
	Rva00161050Block16 m_block;	// retail +0x04..+0x13
	int m_word10;			// retail +0x14
	int m_word14;			// retail +0x18
	int m_word18;			// retail +0x1C

	Rva00161050Tail();
	Rva00161050Tail(const Rva00161050Tail &other)
		: m_block(other.m_block),
		  m_word10(other.m_word10),
		  m_word14(other.m_word14),
		  m_word18(other.m_word18)
	{
	}
};

struct Rva00161050
{
	int m0;					// +0x00
	Rva00161050Tail m_tail;			// +0x04
	unsigned char m20;			// +0x20
	char m_pad[3];				// +0x21

	Rva00161050();
	Rva00161050(const Rva00161050 &other);
};

__forceinline Rva00161050::Rva00161050(const Rva00161050 &other)
	: m0(other.m0),
	  m_tail(other.m_tail),
	  m20(other.m20)
{
}

// Native Ghidra extent 0x001610F0..0x00161141, 81 bytes, cdecl RET0.
// The rowed 36-byte copy walk and STLport vector fill call this helper.
// The null guard and inlined copy constructor reproduce the consumed layout
// of the adjacent 77-byte constructor above; the original element identity
// remains unknown. Force inlining retains its standalone byte-exact copy.
inline void *operator new(unsigned int, void *storage) { return storage; }
struct Elem36;

void gen001610F0(Elem36 *slot, const Elem36 *source)
{
	if (slot)
		new (slot) Rva00161050(*reinterpret_cast<const Rva00161050 *>(source));
}
