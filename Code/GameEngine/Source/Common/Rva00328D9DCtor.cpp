// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00328D9D@@QAE@HHPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, retail 0x00328D9D, 71 bytes.
// Derived ctor over base Rva00328A75: forwards list head g_00DFF0B8 plus four
// stack args to rowed base ctor 0x00328D4A, installs vtable 0x0080D8F0, then
// calls rowed Rva002E373CClear. Same recipe as Rva002E3DE3Ctor.
// Chain from 0x00328D4A now rowed. Caller 0x000AF34D.
// Evidence: push 0x009FF0B8 plus rowed base plus ret 0x10 plus Clear row.
#include "ascii_string.h"

class BfmeParserRegistryVE;

extern int g_00DFF0B8;

void Rva002E373CClear();

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

class Rva00328D9D : public Rva00328A75
{
public:
	Rva00328D9D(int a, int b, BfmeParserRegistryVE *registry, const AsciiString *label);
	virtual ~Rva00328D9D();
};

Rva00328D9D::Rva00328D9D(int a, int b, BfmeParserRegistryVE *registry, const AsciiString *label)
	: Rva00328A75(reinterpret_cast<int>(&g_00DFF0B8), a, b, registry, label)
{
	Rva002E373CClear();
}
