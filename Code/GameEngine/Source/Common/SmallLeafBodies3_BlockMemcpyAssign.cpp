// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three block-assign setters recovered from the Open-BFME-1 donor
// game/GameEngine/Source/Common/SmallLeafBodies3.cpp (reference/open-bfme-1),
// recompiled /Os. Each is byte-identical to retail once relocations are masked,
// at a unique masked placement on unclaimed .text:
//
//   ?set@Rva00299790BlockAssign@@QAEXABUBlockRva00299790BlockAssign@@@Z
//       0x0029A23E  17 B  lead 0x8
//   ?set@Rva003A1030BlockAssign@@QAEXABUBlockRva003A1030BlockAssign@@@Z
//       0x00311493  20 B  lead 0xA4
//   ?set@Rva004094A0BlockAssign@@QAEXABUBlockRva004094A0BlockAssign@@@Z
//       0x0036246B  17 B  lead 0x48
//
// Only these three instantiations are kept here; the donor's other
// thirty-eight definitions are omitted.
//
// IDENTITY IS NOT RECOVERED for any of them: nothing in the image names the
// types these are members of, so the names are address-derived and disclaim
// identity.  What the bytes settle is the shape, and it is the same for all
// three:
//
//   push esi / mov esi,[esp+8] / push edi / lea edi,[ecx+<LEAD>]
//   / movsd / movsd / pop edi / pop esi / ret 4
//
// `ret 4` is the stdcall cleanup of the one pointer-sized argument, and ecx is
// the `this` of a non-static member: so this takes the aggregate BY REFERENCE
// and copies it wholesale into a member at <LEAD>.
//
// THE SHAPE IS THE POINT.  Two spellings of the same assignment are possible
// here and retail picks the bulk one.  Naming the block as a member of an
// aggregate type lets MSVC inline that aggregate's copy constructor as the
// three field-by-field stores the sibling file
// SmallLeafBodies3.cpp's BFME_BLOCK_ASSIGN macro produces; naming it as a
// distinct 12-byte type instead makes this a plain struct copy, which /Os
// lowers to the two `movsd`s above.  Both spellings are 17-20 byte stdcall
// setters for the same operation and they differ at the first byte, so the
// distinction is established by retail's bytes here, not inherited from the
// donor.
//
// The 0xA4 instance is three bytes longer than its siblings because that
// displacement does not fit a signed byte: `lea edi,[ecx+0xA4]` widens to
// disp32. That is the whole of the size difference.

#define BFME_BLOCK_MEMCPY_ASSIGN( NAME, LEAD )                                 \
	struct Block##NAME                                                        \
	{                                                                         \
		unsigned int m_dword[ 3 ];                                            \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( const Block##NAME &value );                                 \
                                                                              \
		char        m_lead[ LEAD ];                                           \
		Block##NAME m_block;                                                  \
	};                                                                        \
	void NAME::set( const Block##NAME &value )                                \
	{                                                                         \
		m_block = value;                                                      \
	}

BFME_BLOCK_MEMCPY_ASSIGN( Rva00299790BlockAssign, 0x8 )
BFME_BLOCK_MEMCPY_ASSIGN( Rva003A1030BlockAssign, 0xA4 )
BFME_BLOCK_MEMCPY_ASSIGN( Rva004094A0BlockAssign, 0x48 )