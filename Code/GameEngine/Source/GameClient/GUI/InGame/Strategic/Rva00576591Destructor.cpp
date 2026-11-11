// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva00576591@@UAE@XZ, retail 0x00576591..0x005765D1 (64 bytes, EH); pinned
// until now as the opaque ??1Rva00576591@@UAE@XZ. A StrategicHUD panel
// holder (vtable 0x0086E798 over the rowed holder base Rva005D12E3): on the way out it
// tells the notifier at +0x30 of the object it keeps at +8 that it is gone
// (rowed setter 0x005CD5FA, argument 1), then the base destructor runs.
// Class name address-derived; owner types are views of the accessed prefix.
#include "../../../../../Include/Common/Rva005CD5FA.h"

struct Rva00576591Owner
{
	char m_pad00[0x30];
	Rva005CD5FA m_notifier; // +0x30
};

class Rva005D12E3
{
public:
	virtual ~Rva005D12E3();
protected:
	void *m_04;
	Rva00576591Owner *m_owner; // +8
};

class Rva00576591 : public Rva005D12E3
{
public:
	virtual ~Rva00576591();
};

Rva00576591::~Rva00576591()
{
	m_owner->m_notifier.rva005CD5FA(1);
}
