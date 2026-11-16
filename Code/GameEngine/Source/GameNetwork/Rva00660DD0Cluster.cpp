// cl: /GS
//
// Two FESL transaction builders from the 0x00660DD0 neighbourhood. They are
// __thiscall members whose `this` is unused: each resets the message handed in
// its single argument, stamps the 'fsys' category at +0x1C and adds the "TXN"
// key with a transaction name loaded from a fixed data address before the
// reset() call. The names are address-derived; the pointed-to strings are
// copied DIR32 sites, not identity evidence.

#include "../../Include/GameNetwork/Rva007E8810Message.h"

const char * rva00E0A1C0;	// retail RVA 0x00A0A1C0 (.data, 8 bytes), defined here: nothing else owns it
const char * rva00E0A1B4;	// retail RVA 0x00A0A1B4 (.data, 8 bytes), defined here: nothing else owns it

class Rva00660DD0
{
public:
	void rva00660DD0(Rva007E8810Message *msg);
	void rva00660E00(Rva007E8810Message *msg);
};

void Rva00660DD0::rva00660DD0(Rva007E8810Message *msg)
{
	const char *name = rva00E0A1C0;

	msg->reset();
	msg->m_1C = 'fsys';
	msg->addString("TXN", name);
}

void Rva00660DD0::rva00660E00(Rva007E8810Message *msg)
{
	const char *name = rva00E0A1B4;

	msg->reset();
	msg->m_1C = 'fsys';
	msg->addString("TXN", name);
}
