// cl: /MD
// ?rva004FA659@LivingWorldBuildingNuggetSpawnArmy@@QAEXXZ @0x004FA659 19B: thiscall, compares dwords
// at +0x20/+0x24, forwards (m_20 != m_24) as unsigned char to member at +4
// via rowed LivingWorldBuilding::rva004E060C. Callers at 0x004FAA52/0x004FABC2/
// 0x004FAEF7; runProductionPhase (0x004FAA81) calls it on its own this, and
// +4/+0x20/+0x24 are the nugget's building and m_queue begin/end. Neighbour
// Rva004FA830Ctor.cpp carries // cl: /O1 /MD.
#include "../../Include/GameLogic/LivingWorldBuilding.h"

class LivingWorldBuildingNuggetSpawnArmy
{
public:
	void rva004FA659();

private:
	char m_pad0[4];
	LivingWorldBuilding *m_4;
	char m_pad8[0x20 - 8];
	int m_20;
	int m_24;
};

void LivingWorldBuildingNuggetSpawnArmy::rva004FA659()
{
	m_4->rva004E060C(m_20 != m_24);
}
