// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: string-pair value family (ColorToWrite/RiverTexture
// callers). The base object holds two AsciiString members with an int
// between them plus zeroed tail bytes; subclasses carry the 0xBD3Axx
// vtables (their ctors use caller-ebp without frame setup and are not
// clean-C++ recoverable).
//
// ?rva00151248@Rva00151248@@QAEXXZ, retail 0x00151248 (64 bytes).
// Reset method: clears both strings through AsciiString::clear (alternatename
// to releaseBuffer 0x36410), zeroes the int, then three CRT memset calls
// (/O1 has no intrinsics, so 0x10/4/1-byte memsets stay calls).

#include <string.h>

#include "ascii_string.h"

class Rva00151248
{
public:
	void rva00151248();

private:
	AsciiString m_first;
	int m_second;
	AsciiString m_third;
	char m_tail0C[0x10];
	int m_tail1C;
	char m_tail20;
};

// ?rva00151248@Rva00151248@@QAEXXZ
void Rva00151248::rva00151248()
{
	m_first.clear();
	m_second = 0;
	m_third.clear();
	memset(m_tail0C, 0, 0x10);
	memset(&m_tail1C, 0, 4);
	memset(&m_tail20, 0, 1);
}
