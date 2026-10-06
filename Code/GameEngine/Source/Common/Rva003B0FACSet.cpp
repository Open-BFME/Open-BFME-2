// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva003B0FAC@Rva003B0FAC@@QAEXABVAsciiString@@H@Z @0x003B0FAC 26B
// Unlock lane: set AsciiString member at +0x10 then store int at +0x14.
// Evidence: callee StringBase set 0x000366F0 rowed; callers 0x003B15D6 twice; prev ConstIntGetters5 next Disp8 same dir.
#include "ascii_string.h"
class Rva003B0FAC
{
public:
	void rva003B0FAC(const AsciiString &s, int v);
private:
	char m_pad[0x10];
	AsciiString m_str;
	int m_val;
};

void Rva003B0FAC::rva003B0FAC(const AsciiString &s, int v)
{
	((StringBase<char> *)&m_str)->set(*(const StringBase<char> *)&s);
	m_val = v;
}
