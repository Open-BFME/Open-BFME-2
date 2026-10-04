// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??0Rva005DC87B@@QAE@ABVAsciiString@@@Z @0x005DC85F (28 bytes).
// Derived ctor over Rva005DC73C: base ctor with tactic name, then zeroes
// dword at +0x58, then stores vtable 0x00876808. Layout Rva005DC87B over
// Rva005DC73C over Rva004ECECD with int at +0x58 proven by Xfer TU
// Rva005DC87BXfer.cpp and sizes in Rva004ECECDTacticCtors.cpp. Callers
// 0x005A9C47 0x005A9D5C pass SiegeGates/SimpleSiege names. Base dtor/ctor
// resolve via pins/rows; identity is address-derived via pin.
#include "ascii_string.h"

class Rva005DC73C
{
public:
	virtual ~Rva005DC73C();
	Rva005DC73C(const AsciiString &name);
private:
	unsigned char m_pad04[0x58 - 4];
};

class Rva005DC87B : public Rva005DC73C
{
public:
	virtual ~Rva005DC87B();
	Rva005DC87B(const AsciiString &name);
private:
	int m_58;
};

Rva005DC87B::Rva005DC87B(const AsciiString &name)
	: Rva005DC73C(name)
	, m_58(0)
{
}
