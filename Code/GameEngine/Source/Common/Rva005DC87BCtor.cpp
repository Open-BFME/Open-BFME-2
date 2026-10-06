// cl: /Ireference/shims/bfme2_ascii /MD
// ??0Rva005DC87B@@QAE@ABVAsciiString@@@Z @0x005DC85F (28 bytes).
// Derived ctor over AITacticOffensive: base ctor with tactic name, then zeroes
// dword at +0x58, then stores vtable 0x00876808. Layout AITacticSiege over
// AITacticOffensive over AITactic with int at +0x58 proven by Xfer TU
// Rva005DC87BXfer.cpp and sizes in Rva004ECECDTacticCtors.cpp. Callers
// 0x005A9C47 0x005A9D5C pass SiegeGates/SimpleSiege names. Base dtor/ctor
// resolve via pins/rows; identity is address-derived via pin.
#include "ascii_string.h"

class AITacticOffensive
{
public:
	virtual ~AITacticOffensive();
	AITacticOffensive(const AsciiString &name);
private:
	unsigned char m_pad04[0x58 - 4];
};

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
	AITacticSiege(const AsciiString &name);
private:
	int m_58;
};

AITacticSiege::AITacticSiege(const AsciiString &name)
	: AITacticOffensive(name)
	, m_58(0)
{
}
