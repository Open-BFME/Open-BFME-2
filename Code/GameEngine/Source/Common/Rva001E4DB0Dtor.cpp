// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1LocomotorTemplate@@UAE@XZ @0x001E4DB0 59B
// Virtual dtor storing vtable 0x007DE8B4, destroying AsciiString at +0x10
// via rowed releaseBuffer 0x00036410, then base Overridable dtor 0x001E3624.
// Base size 0x10 from member offset (same as Rva004211CA precedent).
// Evidence: vtable store, lea ecx+0x10 releaseBuffer call, base call,
// callers 0x001E67A6 0x001E6806 0x004DA4BA, neighbours Rva001E4954Destroy.
#include "ascii_string.h"

class Overridable
{
public:
	virtual ~Overridable();
private:
	char m_pad04[0x0C];
};

class LocomotorTemplate : public Overridable
{
public:
	virtual ~LocomotorTemplate();
private:
	AsciiString m_10;
};

LocomotorTemplate::~LocomotorTemplate()
{
}
