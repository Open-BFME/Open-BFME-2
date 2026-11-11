// cl: /MD
// ?rva004FCA5A@Rva004FCA5A@@QAE PAXABVRva00376A62@@@Z at 0x004FCA5A (54B). Pointer-array search via forward.
// Evidence: array at this+0xA4/+0xA8 of Rva00376A62*; call 0x59E872 with arg; return [found+4] else null;
// chain lane via 0x59E872; same loop shape as tree predicate without tree.
template <typename T> class StringBase {
	void *m_data;
};
class Rva00376A62 {
	unsigned char m_pad[8];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
	void *m_end_of_storage;
	StringBase<char> m_14;
public:
	bool rva0059E872(const Rva00376A62 &o);
};

class Rva004FCA5A {
	unsigned char m_pad[0xA4];
	Rva00376A62 **m_begin;
	Rva00376A62 **m_end;
public:
	void *rva004FCA5A(const Rva00376A62 &val);
};

void *Rva004FCA5A::rva004FCA5A(const Rva00376A62 &val)
{
	Rva00376A62 **last = m_end;
	Rva00376A62 **first = m_begin;
	for (; first != last; ++first) {
		Rva00376A62 *p = *first;
		if (p->rva0059E872(val))
			return *(void **)((char *)p + 4);
	}
	return 0;
}

struct Rva0059E647Arg;
class Rva002E2903Player;
#include "../../Include/Common/Rva0059E2FD.h"

#include "../../Include/Common/LivingWorldScenario.h"

class LivingWorldScenario::OwnershipSet
{
public:
	void spawnBuildingsInRegionsForPlayer(Rva0059E647Arg *player);
	void spawnArmiesInRegionsForPlayer(Rva0059E647Arg *player);
};

class Rva002B7582Sets
{
public:
	void rva004FCA11(void *key, Rva002E2903Player *player);
private:
	char m_pad00[0x98];
	LivingWorldScenario::OwnershipSet **m_begin; // +0x98
	LivingWorldScenario::OwnershipSet **m_end;   // +0x9C
};

// ?rva004FCA11@Rva002B7582Sets@@QAEXPAXPAVRva002E2903Player@@@Z @0x004FCA11 (73B)
void Rva002B7582Sets::rva004FCA11(void *key, Rva002E2903Player *player)
{
	LivingWorldScenario::OwnershipSet **last = m_end;
	LivingWorldScenario::OwnershipSet **it = m_begin;
	if (it != last)
	{
		for (; it != last; ++it)
		{
			LivingWorldScenario::OwnershipSet *set = *it;
			if (((Rva0059E2FD *)set)->rva0059E31F(*(const Rva0059E2FD *)key))
			{
				set->spawnBuildingsInRegionsForPlayer((Rva0059E647Arg *)player);
				set->spawnArmiesInRegionsForPlayer((Rva0059E647Arg *)player);
				break;
			}
		}
	}
}
