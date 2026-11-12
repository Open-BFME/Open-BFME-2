// cl: /MD
// ?shouldActivate@AISpellBookStructureBreaker@@QAE_NPAVObject@@@Z, retail
// 0x005D7D93, 111 bytes. Renamed from placeholder Rva005EE816::rva005D7D93:
// the WorldBuilder twin is AISpellBookStructureBreaker::shouldActivate in EA's
// own AISpellBookPowers/AISpellBookStructureBreaker.cpp (assert myAI, line 35).
// Evidence: slot 6 of 0x00875EAC, pin Rva005EE816, calls rowed getControllingPlayer twice plus pinned record chain and rowed 0x005EEAC6 then pinned 0x005EE8DD; +0x28 finder.
class Object;
class Player;

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../GameLogic/Object/object.h"

#include "../../Include/Common/Rva002A8AB1Record.h"

#include "../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;

#include "../../Include/GameLogic/AISpellBookBase.h"

#include "../../Include/Common/Rva005EE816.h"

class AISpellBookStructureBreaker
{
public:
	bool shouldActivate(Object *source);
private:
	char m_pad00[0x28];
	AISpellBookBase m_28;
};

bool AISpellBookStructureBreaker::shouldActivate(Object *source)
{
	Player *controllingPlayer = source->getControllingPlayer();
	Rva002A8AB1Record *playerRecord = TheSkirmishAIManager->rva002A8AB1(controllingPlayer);
	void *searchPlayer = playerRecord->rva002C6ACB();
	if (searchPlayer == 0)
		return false;
	Coord3D structureCenter;
	structureCenter.x = 0.0f;
	structureCenter.y = 0.0f;
	structureCenter.z = 0.0f;
	if (m_28.findDenseStructureCenter((Player *)searchPlayer, source->getControllingPlayer(), &structureCenter))
		return ((Rva005EE816 *)this)->rva005EE8DD(&structureCenter, source);
	return false;
}
