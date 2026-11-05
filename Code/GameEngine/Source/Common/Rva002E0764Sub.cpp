// stlport
// cl: /DNDEBUG /MD
// ?rva002E0764@Rva002E0764@@QAEXPAVSpawnArmy@@@Z, retail 0x002E0764 27B.
// Subtract rowed 0x004E1755 from this+0x298, clamp to 0. Sibling of 0x002E074E accum.
// Evidence: callee rowed 0x004E1755; ret 4 one arg; neighbours share /O1.
#include "../../Include/Common/SpawnArmy.h"
class Rva002E0764
{
public:
	void rva002E0764(SpawnArmy *p);
private:
	char m_pad[0x298];
	int m_298;
};
void Rva002E0764::rva002E0764(SpawnArmy *p)
{
	m_298 -= p->rva004E1755();
	if (m_298 < 0)
		m_298 = 0;
}
