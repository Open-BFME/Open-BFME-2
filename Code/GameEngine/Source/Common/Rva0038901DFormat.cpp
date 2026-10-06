// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
//
// ?rva0038901D@Rva0038901D@@QAE?AVAsciiString@@XZ @0x0038901D, 100B.
// Formats four dwords at this+0..+C as "%d.%d.%d.%d" via rowed
// AsciiString::format 0x00038150 into a stack temp, then copy-constructs
// the hidden return through rowed StringBase<char> copy 0x000365F0 and
// releases the temp through rowed releaseBuffer 0x00036410. Callers
// 0x00389092 (this+0x130 thunk) and 0x00582871/86 (IP compare) prove the
// RVO shape. Honest address name; class and method identity unproven.
#include "ascii_string.h"


class Rva0038901D
{
public:
	AsciiString rva0038901D();
private:
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

AsciiString Rva0038901D::rva0038901D()
{
	AsciiString tmp;
	tmp.format("%d.%d.%d.%d", m_a, m_b, m_c, m_d);
	return tmp;
}

class Rva00389081
{
public:
	AsciiString rva00389081();
private:
	char m_pad[0x130];
	Rva0038901D m_inner;
};

AsciiString Rva00389081::rva00389081()
{
	return m_inner.rva0038901D();
}
