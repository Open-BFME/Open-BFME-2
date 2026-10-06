// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0027F5DC@Rva0027F5DC@@QAE?AVAsciiString@@XZ @0x0027F5DC 27B
// AsciiString by-value getter copying member at +0x58. Evidence: retail copies
// +0x58 via rowed StringBase<char> copy ctor 0x000365F0 then returns hidden out;
// callers in Map payload code; prev Rva0027F5C1Get same shape offset 0x54.
#include "ascii_string.h"

class Rva0027F5DC
{
public:
	AsciiString rva0027F5DC();
private:
	char m_pad00[88];
	AsciiString m_str;
};

AsciiString Rva0027F5DC::rva0027F5DC()
{
	return m_str;
}
