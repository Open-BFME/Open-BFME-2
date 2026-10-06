// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??0Rva00567960@@QAE@HPBURva00567CCDInfo@@@Z @0x00567CCD 135B.
// MI ctor for Rva00567960 (dtor at 0x00567960 proves the class and its
// +8 second base): zeroes +4, builds AsciiString "Button", constructs the
// +8 base via rowed 0x005C802B with (arg1, Button-addr-as-int), copies
// arg2+0/+4 to +0x10/+0x14 via Mid base so copies precede derived vtables,
// installs derived vtables and stores Rva00567BFDGet(arg2+4) to +0x18.
// Evidence: ret 8 two args; and [esi+4] 0; StringBase 0x37BA0 plus
// releaseBuffer 0x36410 around the +8 base call; Get 0x567BFD.
#include "ascii_string.h"

class CommandButton
{
};

const CommandButton *Rva00567BFDGet(int stance);

// Two levels at +0: the ctor installs vtable 0x00C7A630 while the dtor's final store is
// 0x00BC6F20 (Rva00567960Dtor.cpp), so they are two classes; each inline ctor/dtor's store
// of the other level is dead and dropped. One name per vtable keeps DIR32 consistent.
class Rva00567960Base
{
public:
	virtual ~Rva00567960Base();
	int m_4;
};

class Rva00567960BaseMid : public Rva00567960Base
{
public:
	virtual ~Rva00567960BaseMid();
	Rva00567960BaseMid() { m_4 = 0; }
};

class Rva005C802B
{
public:
	virtual ~Rva005C802B();
	Rva005C802B(int a1, int a2);
private:
	int m_04;
};

struct Rva00567CCDInfo
{
	int m_00;
	int m_04;
};

struct Rva00567CCDMid
{
	Rva00567CCDMid(const Rva00567CCDInfo *a2) : m_10(a2->m_00), m_14(a2->m_04) {}
	int m_10;
	int m_14;
};

class Rva00567960 : public Rva00567960BaseMid, public Rva005C802B, public Rva00567CCDMid
{
public:
	Rva00567960(int a1, const Rva00567CCDInfo *a2);
private:
	const CommandButton *m_18;
};

Rva00567960::Rva00567960(int a1, const Rva00567CCDInfo *a2)
	: Rva005C802B(a1, (int)&AsciiString("Button")), Rva00567CCDMid(a2)
{
	m_18 = Rva00567BFDGet(a2->m_04);
}
