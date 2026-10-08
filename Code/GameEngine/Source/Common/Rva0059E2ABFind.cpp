// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva0059E2AB@Rva0059E2AB@@QAEPAXPAX@Z @0x0059E2AB 44B: Find-or-default via +0x28 name through Logic+0xb0 manager; neighbours OpaqueScalarDeletingDtorsB13 Rva0059E2FDContains; caller 0x004FCA05.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

class Rva002104B6
{
public:
	void *rva002104B6(void *a1);
};

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
