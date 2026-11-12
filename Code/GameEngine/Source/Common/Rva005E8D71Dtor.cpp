// cl: /Ob2 /EHsc /MD
// ??1Rva005E8D71@@UAE@XZ retail 0x005E8D71 60B
// MI dtor second base at +8 via pin 0x005E12D1 plus base vtable restore to g_00BC6F20.
// Twin of rowed 0x005E92F7 60B: EH_prolog then vptr stores C77F88/C77F68 then
// member-base call then BC6F20.
// Native parent EH independently selects cleanup7A3FCA, which restores this
// from EBP-10 and tail-calls the existing counted-base destructor4E84A4.
// Use that canonical base: its whole7B body and BC6F20 deleting slot7E5EE
// establish the consumed8B prefix; original class name remains unproved.

#include "../../Include/Common/Rva0007DF07.h"

class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
};

class Rva005E8D71 : public Rva0007DF07, public Rva005E12D1
{
public:
	virtual ~Rva005E8D71();
	virtual void rva005E8CF8();
	virtual void *rva005E8DB5();
};

Rva005E8D71::~Rva005E8D71()
{
}
