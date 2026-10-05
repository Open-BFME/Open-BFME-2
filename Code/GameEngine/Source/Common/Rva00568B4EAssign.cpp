// cl: /Ireference/shims/bfme2_ascii /O1 /Ob0
// stlport
//
// ??4Rva00568B4E@@QAEAAV0@ABV0@@Z @0x00568B4E 51B: copy-assign with two AsciiStrings
// at +0/+4 via rowed StringBase<char>::set 0x000366F0, ints at +8/+0xC, byte at +0x10.
// Same recipe as Rva00381E56Assign; caller at 0x00568ED0 unclaimed.
#include "ascii_string.h"

class Rva00568B4E
{
public:
	Rva00568B4E &operator=(const Rva00568B4E &other);

private:
	AsciiString m00; // +0
	AsciiString m04; // +4
	int m08; // +8
	int m0C; // +12
	unsigned char m10; // +16
};

Rva00568B4E &Rva00568B4E::operator=(const Rva00568B4E &other)
{
	((StringBase<char> *)&m00)->set(*(const StringBase<char> *)&other.m00);
	((StringBase<char> *)&m04)->set(*(const StringBase<char> *)&other.m04);
	m08 = other.m08;
	m0C = other.m0C;
	m10 = other.m10;
	return *this;
}
