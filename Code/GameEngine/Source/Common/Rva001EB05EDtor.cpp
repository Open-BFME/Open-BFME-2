// cl: /O1 /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// ??1Rva001EB05E@@QAE@XZ @0x001EB05E 54B
// Evidence: linkbody; two releaseBuffer D at +0x10 then G at +0xC with EH; caller 0x001EB678 member at +0xB0; unblocks 0x001EB63C 0x00299CE4 0x0037DEE4.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva001EB05E
{
public:
	~Rva001EB05E();
private:
	char m_pad00[0xC];
	UnicodeString m_0C;
	AsciiString m_10;
};

// The exact Rva001EB05E destructor is owned by RTS/UnitRevivalEntryDtor.cpp.

// ??1Rva001EB63C@@QAE@XZ @0x001EB63C 78B
// Evidence: chain via 0x001EB05E; pins Rva001EB63C Rva002AE5CFRecord Rva002E2D10Record UnitRevivalEntry; callers 0x001EC957 0x002AD05A; Ascii at 0xD4 0xD0 plus member at 0xB0.
class Rva001EB63C
{
public:
	~Rva001EB63C();
private:
	char m_pad00[0xB0];
	Rva001EB05E m_B0;
	char m_padC4[0xD0 - 0xC4];
	AsciiString m_D0;
	AsciiString m_D4;
};

Rva001EB63C::~Rva001EB63C()
{
}
