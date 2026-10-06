// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// __thiscall constructors that open with the vftable-plus-zeroed-dword head and
// then store their arguments straight into the members that follow it.
//
// The head is the one FunctorBindInvokers.cpp measured and
// FunctorBindWrapperCtors.cpp landed constructors for: a vftable slot at +0x00
// and one unmodelled dword at +0x04, split into a base whose own constructor
// zeroes that dword.  Every body here begins
//
//     mov eax,ecx / ... / mov [eax+4],0 / mov [eax],<vftable>
//
// -- `mov eax,ecx` with no other use of eax is a constructor returning `this`,
// and the +0x04 store landing BEFORE the +0x00 store is the base's dead vftable
// write being dropped, which a single class cannot produce (probed: it emits
// the vftable first).  What differs between the two shapes here is only what
// is stored after that, so they are grouped by argument shape and each body is
// named for its own address; no class name has been recovered for either.
//
// Dedicated TU: only the two placed bodies are defined; the donor's other
// twelve definitions are omitted.

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04( 0 ) {}

	virtual void vptrZeroAnchor();

	unsigned int m_unmodelled_04;
};

// mov dl,[esp+8] / mov eax,ecx / mov cl,[esp+4] / <head> /
// mov [eax+8],cl / mov [eax+9],dl / ret 8
#define BFME_VPTR_ZERO_BYTE_BYTE_CTOR( NAME )                                 \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned char first, unsigned char second );                    \
                                                                              \
		unsigned char m_first;                                                \
		unsigned char m_second;                                                \
	};                                                                        \
	NAME::NAME( unsigned char first, unsigned char second )                   \
		: m_first( first ), m_second( second ) {}

// mov edx,[esp+8] / mov eax,ecx / mov ecx,[esp+4] / mov [eax+8],ecx /
// mov ecx,[esp+0xC] / <head> / mov [eax+0xC],dl / mov [eax+0x10],ecx / ret 0xC
#define BFME_VPTR_ZERO_PTR_BYTE_PTR_CTOR( NAME )                              \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *first, unsigned char second, void *third );               \
                                                                              \
		void          *m_first;                                               \
		unsigned char  m_second;                                              \
		void          *m_third;                                               \
	};                                                                        \
	NAME::NAME( void *first, unsigned char second, void *third )              \
		: m_first( first ), m_second( second ), m_third( third ) {}

BFME_VPTR_ZERO_BYTE_BYTE_CTOR( Rva00149F20VptrZeroObject )
BFME_VPTR_ZERO_PTR_BYTE_PTR_CTOR( Rva002ED5C0VptrZeroObject )