// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004CFEB9@Rva004CFEB9@@QAE?AVAsciiString@@XZ, retail 0x004CFEB9, 104 bytes.
// Target evidence: reads signed dword +0 and dword +4, adds 0x10000 to the
// first value only when it is negative, formats "%d(%d)" into a local
// AsciiString, copies that local to the hidden return object, then releases it.
// Identity inference: no direct caller or owner evidence identifies the class;
// keep the two-field view and method address-derived.
#include "ascii_string.h"

class Rva004CFEB9
{
public:
	AsciiString rva004CFEB9();

private:
	int m_value0;
	int m_value4;
};

AsciiString Rva004CFEB9::rva004CFEB9()
{
	AsciiString result;
	int value = m_value0;
	if (value < 0)
		value += 0x10000;
	result.format("%d(%d)", value, m_value4);
	return result;
}
