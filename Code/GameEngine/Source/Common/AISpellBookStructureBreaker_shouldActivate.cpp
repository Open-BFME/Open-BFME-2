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

struct Rva002A8AB1Record
{
public:
	void *rva002C6ACB();
};

class Rva002A8F24
{
public:
	struct Rva002A8AB1Record *rva002A8AB1(void *player);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class AISpellBookBase
{
public:
	bool findDenseStructureCenter(Player *a1, Player *a2, Coord3D *out);
};

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);
};

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
	Player *player = source->getControllingPlayer();
	Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(player);
	void *v = rec->rva002C6ACB();
	if (v == 0)
		return false;
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	if (m_28.findDenseStructureCenter((Player *)v, source->getControllingPlayer(), &pos))
		return ((Rva005EE816 *)this)->rva005EE8DD(&pos, source);
	return false;
}
