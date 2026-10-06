// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva004E04D9@Rva004E04D9@@QAEXXZ @0x004E04D9 36B.
// Reset for the Rva004E04FD layout (see Rva004E04FDCtor.cpp/Rva004E0513Xfer.cpp):
// zeroes ints at +0x00/+0x08/+0x04 in that order (retail `and [mem],0`
// size-opt), releases the UnicodeString at +0x0C (rowed 0x00036E70) and the
// AsciiString at +0x10 (rowed 0x00036410), then clears the byte at +0x14.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva004E04D9
{
public:
	void rva004E04D9();
private:
	int m_00;
	int m_04;
	int m_08;
	UnicodeString m_0C;
	AsciiString m_10;
	unsigned char m_14;
};

void Rva004E04D9::rva004E04D9()
{
	m_00 = 0;
	m_08 = 0;
	m_04 = 0;
	m_0C.clear();
	m_10.clear();
	m_14 = 0;
}
