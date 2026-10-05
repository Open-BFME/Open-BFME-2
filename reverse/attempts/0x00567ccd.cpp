// ??0Rva00567960@@QAE@HPBURva00567CCDInfo@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??0Rva00567960@@QAE@HPAURva00567CCDInfo@@@Z @0x00567CCD 135B.
// MI ctor for Rva00567960 (dtor at 0x00567960 proves the class and its
// +8 second base): zeroes +4, builds AsciiString "Button", constructs the
// +8 base via rowed 0x005C802B with (arg1, Button), copies arg2+0/+4 to
// +0x10/+0x14, installs derived vtables and stores Rva00567BFDGet(arg2+4)
// to +0x18. Evidence: ret 8 two args; and [esi+4] 0; StringBase 0x37BA0
// plus releaseBuffer 0x36410 around the +8 base call; Get 0x567BFD.
// Row 0x005C802B names (int int) Rva005C802B but the bytes pass Button as
// second arg to the +8 Rva005C7CBB-line base; declared here as (int
// AsciiString) for honest codegen.
#include "ascii_string.h"

class CommandButton
{
};

const CommandButton *Rva00567BFDGet(int stance);

class Rva00567960Base
{
public:
	virtual ~Rva00567960Base();
	Rva00567960Base() { m_4 = 0; }
	int m_4;
};

class Rva005C7CBB
{
public:
	virtual ~Rva005C7CBB();
	Rva005C7CBB(int a1, const AsciiString &a2);
private:
	int m_04;
};

struct Rva00567CCDInfo
{
	int m_00;
	int m_04;
};

class Rva00567960 : public Rva00567960Base, public Rva005C7CBB
{
public:
	Rva00567960(int a1, const Rva00567CCDInfo *a2);
private:
	int m_10;
	int m_14;
	const CommandButton *m_18;
};

// ??0Rva00567960@@QAE@HPAURva00567CCDInfo@@@Z present-unmatched
Rva00567960::Rva00567960(int a1, const Rva00567CCDInfo *a2)
	: Rva005C7CBB(a1, AsciiString("Button")), m_10(a2->m_00), m_14(a2->m_04)
{
	m_18 = Rva00567BFDGet(a2->m_04);
}
