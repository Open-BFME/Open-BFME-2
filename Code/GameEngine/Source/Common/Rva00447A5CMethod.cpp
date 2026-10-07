// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva00447A5C@Rva00447A5C@@QAEXVUnicodeString@@@Z @0x00447A5C 55B
// By-value UnicodeString set into +0x1B0 via rowed set 0x00037150 then releaseBuffer 0x00036E70.
// Evidence: called from unclaimed 0x0044941F; callees rowed; neighbours 0x00447A42 0x00447A93; same 55B recipe as Rva00447A93Method.
#include "unicode_string.h"

class Rva00447A5C
{
public:
	void rva00447A5C(UnicodeString arg);
private:
	char m_pad[0x1B0];
	UnicodeString m_1B0;
};

void Rva00447A5C::rva00447A5C(UnicodeString arg)
{
	StringBase<unsigned short> &dst = (StringBase<unsigned short> &)m_1B0;
	dst.set(arg);
}
