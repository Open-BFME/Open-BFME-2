// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ?rva005D0507@Rva005D0507@@QAEHXZ, retail 0x005D0507, 38 bytes.
// Combined length of two AsciiString targets plus one for terminator.
// Reads this+0 and this+8 as AsciiString pointers, inlines getLength on each
// m_text with null to zero, returns sum plus one via lea.
// Evidence: dual mov-mov-test-movzx shape with lea eax eax+edx+1, no calls,
// caller 0x0002CB02 pushes eax into getBufferForRead, LINK 3 files 79B.
#include "ascii_string.h"
class Rva005D0507
{
public:
	int rva005D0507();
private:
	AsciiString *m_0;
	char m_pad[4];
	AsciiString *m_8;
};
int Rva005D0507::rva005D0507()
{
	return m_0->getLength() + m_8->getLength() + 1;
}
