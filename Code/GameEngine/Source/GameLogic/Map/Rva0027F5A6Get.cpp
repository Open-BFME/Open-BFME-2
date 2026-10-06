// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0027F5A6@Rva0027F5A6@@QAE?AVAsciiString@@XZ @0x0027F5A6 27B
// AsciiString by-value getter copying member at +0x50. Evidence: retail copies
// +0x50 via rowed StringBase<char> copy ctor 0x000365F0 then returns hidden out;
// callers in Map payload code; prev/next Map TUs share flags.
#include "ascii_string.h"

class Rva0027F5A6
{
public:
	AsciiString rva0027F5A6();
private:
	char m_pad00[80];
	AsciiString m_str;
};

AsciiString Rva0027F5A6::rva0027F5A6()
{
	return m_str;
}
