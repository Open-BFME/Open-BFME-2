// cl: /DNDEBUG /MD
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva00452FE0Same.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva00452FE0Same@@YAHABURva00452FE0Key@@0@Z 0x00301B24 (48B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail RVA 0x00452FE0. Shared by the two key comparisons at 0x00453320 and
// 0x00453380, which both reach it through a stand-in declaration over a
// four-byte inner struct. The bytes read two words from each argument, so the
// real parameter is eight bytes wide and gets an address-derived name.

// pinned at ILT 0x000162E8 in targets/game/reverse/symbols.csv as
// ?bfmeSameUW@@YADPAXPAVBfmeItemUW@@0@Z
class BfmeItemUW
{
public:
	unsigned char m_bfmePad000[ 8 ];
	void *m_bfmePayload;
};

char __cdecl bfmeSameUW( void *payload, BfmeItemUW *item, void *other );

struct Rva00452FE0Key
{
	BfmeItemUW *m_bfmeItem;
	int m_bfmeSerial;
};

int __cdecl Rva00452FE0Same( const Rva00452FE0Key &first,
	const Rva00452FE0Key &second )
{
	if( first.m_bfmeSerial == second.m_bfmeSerial )
	{
		void *theirs = second.m_bfmeItem->m_bfmePayload;
		BfmeItemUW *item = first.m_bfmeItem;
		void *mine = item->m_bfmePayload;

		if( bfmeSameUW( mine, item, theirs ) )
			return 1;
	}

	return 0;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?bfmeSameSX@@YA_NABUBfmeInnerSX@@0@Z=?Rva00452FE0Same@@YAHABURva00452FE0Key@@0@Z")
