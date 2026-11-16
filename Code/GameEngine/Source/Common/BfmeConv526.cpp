// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv526.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBSF@BfmeThingBSF@@QAEPAV1@PAGPAX@Z 0x004D04FF (31B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
#define BFME_STRINGBASE_PUBLIC_COPY
#include "../../../../reference/shims/bfme2_ascii/string_base.h"

class BfmeThingBSF
{
public:
	BfmeThingBSF *bfmeGoBSF(unsigned short *src, void *what);
	unsigned short m_bfmeKey;
	unsigned char m_bfmePad[2];
	unsigned char m_bfmeSub[sizeof(StringBase<char>)];
};

BfmeThingBSF *BfmeThingBSF::bfmeGoBSF(unsigned short *src, void *what)
{
	m_bfmeKey = *src;
	// Retail copy-constructs the string following the two-byte key.
	reinterpret_cast<StringBase<char> *>(m_bfmeSub)->StringBase<char>::StringBase(*static_cast<const StringBase<char> *>(what));
	return this;
}
