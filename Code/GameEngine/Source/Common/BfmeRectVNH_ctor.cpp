// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline
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
	bool rva003FD522();

	AsciiString m_name;
};

// ??0BfmeRectVNH@@QAE@IABVAsciiString@@D@Z
BfmeRectVNH::BfmeRectVNH(unsigned w, const AsciiString &s, char f)
	: BfmeBaseVNH(w, f)
	, m_name(s)
{
}


class GameTextInterface
{
public:
#define SLOT(n) virtual void slot##n();
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
    SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
    virtual UnicodeString fetch(const AsciiString &, bool *);
};
extern GameTextInterface *TheGameText;
class InGameUI;
extern InGameUI *TheInGameUI;
class Rva0029B16A
{
public:
    void rva0029B16A(int, int);
};

// WB 105D300 names DelayedWorldTextEventModule::Activate.
// Native passes the existing label at +0C by reference to slot +38,
// receives a four-byte UnicodeString, checks its exists byte and forwards
// the temporary to the established mission-help provider with duration zero.
bool BfmeRectVNH::rva003FD522()
{
    bool exists;
    UnicodeString text = TheGameText->fetch(m_name, &exists);
    if (!exists)
        return false;
    ((Rva0029B16A *)TheInGameUI)->rva0029B16A((int)&text, 0);
    return true;
}
