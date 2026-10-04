// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00328C5E@@QAE@HHHHPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, retail 0x00328C5E, 103 bytes.
// Outer parser binding ctor: bases Rva00328B9A at +0x00 and Rva00328BFC at +0x0c
// plus four scalar members at +0x18..+0x24. Chain from 0x00328B9A now rowed.
// Caller 0x00328D4A constructs this. Vtables 0x0080D8D8 and 0x0080D8E4 set by compiler.
// Evidence: rowed base ctors 0x00328B9A 0x00328BFC plus EH prolog plus ret 0x18.
#include "ascii_string.h"

class BfmeParserRegistryVE;

class Rva00328B9A
{
public:
	Rva00328B9A(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
	virtual ~Rva00328B9A();
private:
	void *m_04;
	void *m_08;
};

class Rva00328BFC
{
public:
	Rva00328BFC(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
	virtual ~Rva00328BFC();
private:
	void *m_04;
	void *m_08;
};

class Rva00328C5E : public Rva00328B9A, public Rva00328BFC
{
public:
	Rva00328C5E(int a, int b, int c, int d, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
};

Rva00328C5E::Rva00328C5E(int a, int b, int c, int d, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: Rva00328B9A(registry, parentLabel)
	, Rva00328BFC(registry, parentLabel)
	, m_18(a)
	, m_1c(b)
	, m_20(c)
	, m_24(d)
{
}
