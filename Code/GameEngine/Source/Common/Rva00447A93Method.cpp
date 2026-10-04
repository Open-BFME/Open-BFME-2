// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva00447A93@Rva00447A93@@QAEXVUnicodeString@@@Z @0x00447A93 55B
// By-value UnicodeString set into +0x1B4 via rowed set 0x00037150 then releaseBuffer 0x00036E70.
// Evidence: called from 1 unclaimed site; callees rowed; prev/next neighbours.
#include "unicode_string.h"

class Rva00447A93
{
public:
	void rva00447A93(UnicodeString arg);
private:
	char m_pad[0x1B4];
	UnicodeString m_1B4;
};

void Rva00447A93::rva00447A93(UnicodeString arg)
{
	StringBase<unsigned short> &dst = (StringBase<unsigned short> &)m_1B4;
	dst.set(arg);
}
