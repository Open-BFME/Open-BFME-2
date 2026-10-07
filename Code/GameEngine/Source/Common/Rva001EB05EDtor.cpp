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

Rva001EB05E::~Rva001EB05E()
{
}
