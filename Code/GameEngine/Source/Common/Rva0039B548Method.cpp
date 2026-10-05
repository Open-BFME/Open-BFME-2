// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva0039B548@Rva003BD306Target@@QAEXXZ @0x0039B548 55B
// Clear method: zero m_38/m_0C, 0.0f to m_10, global float to m_1C,
// empty AsciiString at +8 via rowed releaseBuffer, zero m_20, then rowed
// Rva003BD306Target::rva0039B28F(1) on same this. Evidence: pin-only callee
// ?rva0039B28F@Rva003BD306Target@@QAEXH@Z proves owner Rva003BD306Target;
// callers 0x0029405F 0x004BDA78; float global g_Va00BBB8D8 (?g_Va00BBB8D8@@3MA);
// neighbours Rva0039B2E6 Rva0039B632 share flags.
#include "ascii_string.h"

extern float g_Va00BBB8D8;

class Rva003BD306Target
{
public:
	void rva0039B28F(int v);
	void rva0039B548();
private:
	char m_pad00[8];
	AsciiString m_str08;
	int m_0C;
	float m_10;
	char m_pad14[0x1C - 0x14];
	float m_1C;
	unsigned char m_20;
	char m_pad21[0x38 - 0x21];
	int m_38;
};

void Rva003BD306Target::rva0039B548()
{
	m_38 = 0;
	m_10 = 0.0f;
	m_1C = g_Va00BBB8D8;
	m_str08.clear();
	m_0C = 0;
	m_20 = 0;
	rva0039B28F(1);
}
