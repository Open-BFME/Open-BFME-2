// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD

// ??4Rva0039D769@@QAEAAV0@ABV0@@Z @0x0039D769 (61B).
// Copy-assignment over a 0x18-byte array element: three dwords at +0x00/+0x04
// +0x08, two AsciiStrings at +0x0C/+0x10 via the pinned assign at 0x000366F0,
// then the dword at +0x14, returning *this. Retail shape is three dword moves
// plus two string assigns plus the tail move. Caller at 0x003A0DF6 copies into
// the +0x130 array with 0x18 stride. Owner unproven so the name keeps the
// address token.

#include "ascii_string.h"

class Rva0039D769
{
public:
	Rva0039D769 &operator=(const Rva0039D769 &rhs);

private:
	int m00; // +0x00
	int m04; // +0x04
	int m08; // +0x08
	AsciiString m0C; // +0x0C
	AsciiString m10; // +0x10
	int m14; // +0x14
};

Rva0039D769 &Rva0039D769::operator=(const Rva0039D769 &rhs)
{
	m00 = rhs.m00;
	m04 = rhs.m04;
	m08 = rhs.m08;
	m0C = rhs.m0C;
	m10 = rhs.m10;
	m14 = rhs.m14;
	return *this;
}
