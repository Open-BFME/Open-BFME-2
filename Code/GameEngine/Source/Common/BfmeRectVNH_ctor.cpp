// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeRectVNH_ctor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeRectVNH::BfmeRectVNH 0x003FD498 (66B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5: VNE-family ctor with AsciiString at +0xC. Retail 0x003BC090, 133B.
// Base unsigned*0.03f clamp inlines; derived vftable then StringBase copy at +0xC.

#include "StringInline.h"

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);
	virtual ~BfmeBaseVNH();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};


class BfmeRectVNH : public BfmeBaseVNH
{
public:
	BfmeRectVNH(unsigned w, const AsciiString &s, char f);

	AsciiString m_name;
};

// ??0BfmeRectVNH@@QAE@IABVAsciiString@@D@Z
BfmeRectVNH::BfmeRectVNH(unsigned w, const AsciiString &s, char f)
	: BfmeBaseVNH(w, f)
	, m_name(s)
{
}
