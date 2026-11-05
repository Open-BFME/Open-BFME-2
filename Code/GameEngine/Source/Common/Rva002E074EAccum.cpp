// stlport
// cl: /DNDEBUG /MD
// ?rva002E074E@Rva002E074E@@QAEXPAVSpawnArmy@@@Z, retail 0x002E074E 22B.
// Accumulate rowed 0x004E1755 into this+0x298. Caller at 0x004FAF50.
// Evidence: callee rowed 0x004E1755; ret 4 one arg; neighbours share /O1.
#include "../../Include/Common/SpawnArmy.h"
class Rva002E074E
{
public:
	void rva002E074E(SpawnArmy *p);
private:
	char m_pad[0x298];
	int m_298;
};
void Rva002E074E::rva002E074E(SpawnArmy *p)
{
	m_298 += p->rva004E1755();
}
