// ?rva004C8095@PlayerHealSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.98 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX
// Retail 0x004C8095, 192B: PlayerHealSpecialPower::rva004C8095 (name pinned:
// the location member, ret 4). Same role as BFME 1's PlayerHealSpecialPower
// slot-13 body (reference/open-bfme-1/game/GameEngine/Source/GameLogic/
// Object/SpecialPower/PlayerHealSpecialPowerRva00263CA0.cpp): unless the
// object's disabled flags (Object+0x1C8, BitFlags<11>::any) are set and with
// a controlling player, run the module data's dispatch OCL (+0xA8) at the
// location, then heal (0x004C7F5C) every object within the heal radius
// (+0x84) around it, scanned with the alive filter (vftable 0x00BFAD10, as in
// ReplenishUnitsBehaviorUpdate.cpp) through the native range query.

class Object;
class Player;
struct Coord3D;

template <int N> class BitFlags
{
public:
	bool any() const;
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[0x1C8];
	BitFlags<11> m_disabledMask;
};

class ObjectCreationList
{
public:
	void create(void *primaryObj, void *primary, void *secondary, int createOwner);
	static void create(ObjectCreationList *ocl, Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, int createOwner)
	{
		if (ocl)
			ocl->create(primaryObj, (void *)primary, (void *)secondary, createOwner);
	}
};

struct PlayerHealSpecialPowerModuleData
{
	unsigned char m_pad00[0x84];
	float m_healRadius;
	unsigned char m_pad88[0xA8 - 0x88];
	ObjectCreationList *m_dispatchList;
};

// The per-object heal, address-named as rowed.
class Rva004C7F5C
{
public:
	void rva004C7F5C(Object *obj);
};

class PlayerHealSpecialPower
{
public:
	void rva004C8095(const Coord3D *loc);
private:
	void *m_vtable;
	const PlayerHealSpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

void PlayerHealSpecialPower::rva004C8095(const Coord3D *loc)
{
	Object *obj = m_object;
	if (obj->m_disabledMask.any())
		return;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;

	const PlayerHealSpecialPowerModuleData *data = m_moduleData;
	ObjectCreationList::create(data->m_dispatchList, m_object, loc, 0, 0);

	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(loc, m_moduleData->m_healRadius, 0, &Rva0026119DFilter(), 0);
	Object *other;
	while ((other = iter.next()) != 0)
		((Rva004C7F5C *)this)->rva004C7F5C(other);
}
