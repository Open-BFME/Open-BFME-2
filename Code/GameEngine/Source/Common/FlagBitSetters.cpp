// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// 6 bodies that set or clear one bit of a member according to a byte
// argument (one of the six is placed here; see the note below):
//
//     mov al,[esp+4] / test al,al / mov eax,[ecx+<D>] / je +N /
//     or eax,<MASK> / mov [ecx+<D>],eax / ret 4 /
//     and eax,~<MASK> / mov [ecx+<D>],eax / ret 4
//
// WHAT THE BYTES SHOW.  One byte argument, one dword member, and two exits that
// differ only in `or <MASK>` versus `and` its exact complement -- which is what
// `if ( on ) m_flags |= MASK; else m_flags &= ~MASK;` compiles to.  The member
// is loaded ONCE, before the branch, and both arms write it back; that hoist is
// the compiler's and needs nothing from the source.  The masks are single bits.
//
// The argument is spelled `unsigned char` because only al is read; the bytes
// cannot distinguish it from `bool` or `signed char`.  Members ahead of the
// flag word are a lead array: their total size is all the displacement
// witnesses.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_FLAG_BIT_SETTER( NAME, LEAD, MASK )                              \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void setFlag( unsigned char on );                                     \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		unsigned int m_flags;                                                 \
	};                                                                        \
	void NAME::setFlag( unsigned char on )                                    \
	{                                                                         \
		if ( on )                                                             \
			m_flags |= ( MASK );                                              \
		else                                                                  \
			m_flags &= ~( MASK );                                             \
	}

// ?setFlag@Rva004784A0FlagBit@@QAEXE@Z
// retail 0x00313D14, 20 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/FlagBitSetters.cpp (reference/open-bfme-1 @
// 6d943426). Byte-identical to retail once relocations are masked (unique hit
// on unclaimed .text). Only the placed body is defined here; the donor's other
// five setters are omitted.
BFME_FLAG_BIT_SETTER( Rva004784A0FlagBit, 0x38, 0x2u )
