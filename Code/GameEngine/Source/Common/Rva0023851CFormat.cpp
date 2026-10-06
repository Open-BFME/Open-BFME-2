// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
//
// ?rva0023851C@Rva0023851C@@QAE?AVAsciiString@@XZ @0x0023851C, 100B.
// Formats four dwords at this+0..+C as "%d.%d.%d.%d" via rowed
// AsciiString::format 0x00038150 into a stack temp, then copy-constructs
// the hidden return through rowed StringBase<char> copy 0x000365F0 and
// releases the temp through rowed releaseBuffer 0x00036410. Precedent
// Code/GameEngine/Source/Common/Rva0038901DFormat.cpp (same 100B shape
// and callees); neighbours VersionUnicode.cpp and VersionDestructor.cpp
// carry the same /O1 family. Honest address name; class identity unproven.
#include "ascii_string.h"


class Rva0023851C
{
public:
	AsciiString rva0023851C();
private:
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};
AsciiString Rva0023851C::rva0023851C()
{
	AsciiString tmp;
	tmp.format("%d.%d.%d.%d", m_a, m_b, m_c, m_d);
	return tmp;
}
