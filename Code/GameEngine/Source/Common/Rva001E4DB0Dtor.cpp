// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1Rva001E4DB0@@UAE@XZ @0x001E4DB0 59B
// Virtual dtor storing vtable 0x007DE8B4, destroying AsciiString at +0x10
// via rowed releaseBuffer 0x00036410, then base Rva001E3624 dtor 0x001E3624.
// Base size 0x10 from member offset (same as Rva004211CA precedent).
// Evidence: vtable store, lea ecx+0x10 releaseBuffer call, base call,
// callers 0x001E67A6 0x001E6806 0x004DA4BA, neighbours Rva001E4954Destroy.
#include "ascii_string.h"

class Rva001E3624
{
public:
	virtual ~Rva001E3624();
private:
	char m_pad04[0x0C];
};

class Rva001E4DB0 : public Rva001E3624
{
public:
	virtual ~Rva001E4DB0();
private:
	AsciiString m_10;
};

Rva001E4DB0::~Rva001E4DB0()
{
}
