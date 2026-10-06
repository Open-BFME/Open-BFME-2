// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three two-dword setters recovered from the Open-BFME-1 donor
// game/GameEngine/Source/Common/SmallLeafBodies2.cpp (reference/open-bfme-1),
// recompiled /Os. Each is byte-identical to retail once relocations are masked,
// at a unique masked placement on unclaimed .text:
//
//   ?set@Rva002997C0PairSlot@@QAEXHH@Z  0x0040CB00  17 B  lead 0x58
//   ?set@Rva0035EE30PairSlot@@QAEXHH@Z  0x0054287A  17 B  lead 0x14
//   ?set@Rva004784D0PairSlot@@QAEXHH@Z  0x00313D28  23 B  lead 0x1AC
//
// Only these three instantiations are kept here; the donor's other sixty-eight
// definitions are omitted.
//
// IDENTITY IS NOT RECOVERED for any of them: nothing in the image names the
// type these are members of, so the names are address-derived and disclaim
// identity.  What the bytes do settle is the shape, and it is the same shape for
// all three:
//
//   mov eax,[esp+4] / mov edx,[esp+8] / mov [ecx+<D>],eax
//   / mov [ecx+<D>+4],edx / ret 8
//
// `ret 8` is the stdcall cleanup of two dword arguments pushed by the caller,
// and ecx is the `this` of a non-static member -- so this is a two-dword value
// setter, and the two words are adjacent members.  <D> differs per type, which
// is what the LEAD parameter carries.
//
// The 0x1AC instance is four bytes longer than its two siblings because that
// displacement does not fit a signed byte: the two stores widen from disp8 to
// disp32, which is the whole of the size difference and is not a code-shape
// difference.

#define BFME_TWO_DWORD_SETTER( NAME, LEAD )                                   \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( int first, int second );                                    \
                                                                              \
		char m_lead[ LEAD ];                                                  \
		int  m_first;                                                         \
		int  m_second;                                                        \
	};                                                                        \
	void NAME::set( int first, int second )                                   \
	{                                                                         \
		m_first = first;                                                      \
		m_second = second;                                                    \
	}

BFME_TWO_DWORD_SETTER( Rva002997C0PairSlot, 0x58 )
BFME_TWO_DWORD_SETTER( Rva0035EE30PairSlot, 0x14 )
BFME_TWO_DWORD_SETTER( Rva004784D0PairSlot, 0x1AC )