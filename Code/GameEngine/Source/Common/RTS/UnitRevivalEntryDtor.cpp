// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// ??1UnitRevivalEntry@@QAE@XZ retail 0x001EB63C (78 B) and its member's
// destructor ??1Rva001EB05E@@QAE@XZ retail 0x001EB05E (54 B).
// Target evidence: UnitRevivalTracker::xfer (0x0037F38F neighbourhood,
// UnitRevivalTrackerXfer.cpp) destroys its 0xD8-byte UnitRevivalEntry local
// through 0x001EB63C (the name its pin carries). The body releases the
// AsciiStrings at +0xD4 and +0xD0 under EH states 1 and 0, then calls the
// out-of-line 0x001EB05E on the member at +0xB0, which releases an
// AsciiString at +0x10 (state 0) and a UnicodeString at +0x0C (wide
// releaseBuffer 0x00036E70). Both destructors are empty in source: the
// member teardown is the whole body. The +0xB0 member's class is unnamed
// (address name).
#include "ascii_string.h"
#include "unicode_string.h"

class Rva001EB05E
{
public:
	~Rva001EB05E();

private:
	unsigned char m_pad00[0xC];
	UnicodeString m_0C;			// +0x0C
	AsciiString m_10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
};

Rva001EB05E::~Rva001EB05E()
{
}

class UnitRevivalEntry
{
public:
	~UnitRevivalEntry();

private:
	unsigned char m_pad00[0xB0];
	Rva001EB05E m_B0;			// +0xB0
	AsciiString m_D0;			// +0xD0
	AsciiString m_D4;			// +0xD4
};

// ?UnitRevivalEntry::~UnitRevivalEntry present-unmatched
UnitRevivalEntry::~UnitRevivalEntry()
{
}
