// stlport
// cl: /O1 /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
//
// ?rva0056AA54@@YG_NPAX0@Z @0x0056AA54 82B.
// Probe: construct a local SpawnArmy with arg 0 via pinned 0x004E30D5,
// invoke the slot-0x10 virtual on the +0xC holder of the first argument
// with (second-arg, local), return (local.m_48 == 1), then tear down the
// local via rowed 0x004E3184. Sibling shape of other EH locals with
// explicit dtor calls. Honest address-derived name.
#include "ascii_string.h"

#include "../../Include/Common/SpawnArmy.h"

class Rva0056AA54Holder
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void rvaMethod(void *b, SpawnArmy *local);
};

struct Rva0056AA54Arg
{
	char m_pad[0xC];
	Rva0056AA54Holder m_holder;
};

bool __stdcall rva0056AA54(void *owner, void *context)
{
	SpawnArmy local(0);
	((Rva0056AA54Arg *)owner)->m_holder.rvaMethod(context, &local);
	bool ok = (local.m_48 == 1);
	return ok;
}
