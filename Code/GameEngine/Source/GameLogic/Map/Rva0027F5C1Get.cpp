// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0027F5C1@Rva0027F5C1@@QAE?AVAsciiString@@XZ @0x0027F5C1 27B
// AsciiString by-value getter copying member at +0x54. Evidence: retail copies
// +0x54 via rowed StringBase<char> copy ctor 0x000365F0 then returns hidden out;
// callers in Map payload code; prev Rva0027F5A6Get same shape offset 0x50.
#include "ascii_string.h"

class Rva0027F5C1
{
public:
	AsciiString rva0027F5C1();
private:
	char m_pad00[84];
	AsciiString m_str;
};

AsciiString Rva0027F5C1::rva0027F5C1()
{
	return m_str;
}
