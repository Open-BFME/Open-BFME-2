// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0039AF76@Rva0039AF76@@QAEXABVAsciiString@@@Z @0x0039AF76 37B
// Evidence: unlock 37B; this+8 AsciiString assigned from arg via pinned 0x366F0; global 0xDF36A4 nameToKey row 0x9FA65 to this+0xC; caller 0x39B2E6 pushes [esi+0x10]; unblocks 0x39B2E6.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva0039AF76
{
public:
	void rva0039AF76(const AsciiString &name);
private:
	char m_pad00[8];
	AsciiString m_str08;
	NameKeyType m_key0C;
};

void Rva0039AF76::rva0039AF76(const AsciiString &name)
{
	m_str08 = name;
	m_key0C = TheNameKeyGenerator->nameToKey(name);
}
