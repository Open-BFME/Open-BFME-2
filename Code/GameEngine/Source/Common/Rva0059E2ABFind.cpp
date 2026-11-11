// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva0059E2AB@Rva0059E2AB@@QAEPAXPAX@Z @0x0059E2AB 44B: Find-or-default via +0x28 name through Logic+0xb0 manager; neighbours OpaqueScalarDeletingDtorsB13 Rva0059E2FDContains; caller 0x004FCA05.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

#include "../../Include/Common/Rva002104B6.h"

class Rva002BA8F1Logic
{
public:
	unsigned char m_pad[0xb0];
	Rva002104B6 *m_b0;
};

class Rva0059E2AB
{
public:
	void *rva0059E2AB(void *def);
	void *rva0059E2D7(void *def);
private:
	unsigned char m_pad[0x28];
	StringBase<char> m_28;
};

// ?isEmpty@?$StringBase@D@@QBE_NXZ present-unmatched
// ?rva002104B6@Rva002104B6@@QAEPAXPAX@Z present-unmatched
void *Rva0059E2AB::rva0059E2AB(void *def)
{
	if (m_28.isEmpty())
		return def;
	void *found = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b0->rva002104B6(&m_28);
	return found != 0 ? found : def;
}

// 0x0059E2D7 5B, directly after the body it enters (tail jump into rva0059E2AB); no referencing site found in
// this pass; address-named.
void *Rva0059E2AB::rva0059E2D7(void *def)
{
	return rva0059E2AB(def);
}
