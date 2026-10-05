// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva00333B02@Rva00333B02@@QAEXVAsciiString@@@Z @0x00333B02 52B: by-value AsciiString setter storing to +0x10 via rowed StringBase set 0x000366F0 with EH releaseBuffer 0x00036410. Evidence: this+0x10 set plus by-value release callers 0x00334308 0x00334468 0x003B659D 0x003B6FE6 unblocks 0x00334212 0x0033436F.
#include "ascii_string.h"

class Rva00333B02
{
public:
	void rva00333B02(AsciiString s);
private:
	char m_pad[0x10];
	AsciiString m_10;
};

void Rva00333B02::rva00333B02(AsciiString s)
{
	AsciiString &dst = m_10;
	((StringBase<char> *)&dst)->set(*(const StringBase<char> *)&s);
}
