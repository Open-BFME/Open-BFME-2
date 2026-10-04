// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00328A75@@QAE@HHHPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, retail 0x00328D4A, 83 bytes.
// Ctor of Rva00328A75 (vtable 0x0080D8C4): allocates Rva00328C5E (0x28 bytes)
// via rowed operator new 0x0002FDA0 and forwards this plus four scalars.
// Chain from 0x00328C5E now rowed. Caller 0x00328D9D.
// Evidence: push 0x28 plus rowed new plus rowed inner ctor plus ret 0x14
// plus dtor row ??1Rva00328A75@@UAE@XZ plus vtable xref 0x0080D8C4.
#include "ascii_string.h"

class BfmeParserRegistryVE;

void *__cdecl operator new(unsigned int);

class Rva00328C5E
{
public:
	Rva00328C5E(int a, int b, int c, int d, BfmeParserRegistryVE *registry, const AsciiString *label);
	virtual ~Rva00328C5E();
private:
	char m_pad[0x28 - 4];
};

class Rva00328A75
{
public:
	Rva00328A75(int a, int b, int c, BfmeParserRegistryVE *registry, const AsciiString *label);
	virtual ~Rva00328A75();
private:
	Rva00328C5E *m_04;
	int m_08;
};

Rva00328A75::Rva00328A75(int a, int b, int c, BfmeParserRegistryVE *registry, const AsciiString *label)
{
	m_04 = new Rva00328C5E(reinterpret_cast<int>(this), a, b, c, registry, label);
}
