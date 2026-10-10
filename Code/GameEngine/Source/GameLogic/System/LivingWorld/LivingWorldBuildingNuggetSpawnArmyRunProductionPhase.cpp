// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport

// LivingWorldBuildingNuggetSpawnArmy::runProductionPhase (retail 0x004FAA81,
// 353 bytes, slot 44 of the vtable at 0x00863398).  Identity is a WorldBuilder
// callgraph lead (WB 0x0130AAB0, LivingWorldBuildingNuggetSpawnArmy.cpp asserts
// at lines 416..455) whose callee sequence and control flow agree with retail.
// The front of the production queue (vector<ObjectID> at +0x20, the second
// base's +0x14) is tested through the second base's slot 4 against a
// SpawnArmy temporary (Rva004E3184, int-ctor 0x004E30D5, dtor 0x004E3184);
// an unproducible entry is dropped, otherwise the build counter at +0x2C runs
// up to the temporary's +0x48 before the army is placed at the region's
// garrison spot and spawned.  Callee owners keep their ledger spellings, so
// the temporary is passed under the Rva00319CED view where those rows use it.
//
// canQueueUnit (retail 0x004FA83E, 247 bytes, slot 7 of the second base's
// table 0x00C633FC; WB 0x01309FE0 LivingWorldBuildingNuggetSpawnArmy.cpp
// asserts 171..208): refuses once the queue reaches the module data's +0x14
// limit; otherwise the unit must be producible (slot 4), accepted by the
// living-world logic check 0x002B2646, and by the owning player's 0x002E1155
// (unrowed, address-named pin); a template with the +0x113 bit 2 kind also
// needs the building player's 0x002E12F3 and no army of it already queued
// (HasArmyQueuedInAnyBuilding 0x002E118E).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ObjectID { INVALID_ID = 0 };

namespace _STL
{
// Rowed vector<ObjectID>::erase at 0x0025BF5D.
template <> ObjectID *vector<ObjectID, allocator<ObjectID> >::erase(ObjectID *);
}

class Rva00319CED;

struct Rva003F0F13Elem
{
	float a;
	float b;
};

class Rva004E3184
{
public:
	Rva004E3184(int v);
	virtual ~Rva004E3184();

	char m_pad04[0x1C];
	Rva003F0F13Elem m_pos;	// +0x20 placement spot
	char m_pad28[0x20];
	int m_48;	// +0x48 production time (int-ctor sets 1)
	char m_pad4C[0x0C];
};

class LivingWorldRegion
{
public:
	void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *out);
	bool CanSpawnUnitWithinCPLimit(Rva00319CED *ctx) const;

	char m_pad0[0x13C];
	int m_ownerId;	// +0x13C owning player's LivingWorld id
};

struct Rva004FAA81Building
{
	char m_pad0[0x24];
	LivingWorldRegion *m_region;	// +0x24
};

class Rva002E2903Player;
struct Rva002B6A04Player;
struct LivingWorldArmy;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class LivingWorldLogic
{
public:
	LivingWorldArmy *spawnArmy(Rva004E3184 *desc, Rva002B6A04Player *player, bool b);
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002E112A
{
public:
	bool rva002E112A(Rva00319CED *ctx);
};

class LivingWorldPlayer
{
public:
	void OnUnitDequeued(Rva00319CED *ctx);
	bool rva002E1155(Rva00319CED *ctx);
	bool rva002E12F3(int id);
	bool HasArmyQueuedInAnyBuilding(void *army, int *index, int flags);
};

struct Arg54;
class Rva002B2646
{
public:
	bool rva002B2646(Arg54 *nugget, Arg54 *id);
};
class Rva00319CED
{
public:
	void *rva004E23C1();
};
class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
};
struct Rva004FA83ETemplate
{
	unsigned char m_pad000[0x113];
	unsigned char m_kind113;	// +0x113, bit 2 tested
};
class Rva0037DCA5
{
public:
	void *rva0037DC52();
};
class Rva004E0705
{
public:
	Rva002E2903Player *rva004E0705();
};
struct Rva004FA83EData
{
	unsigned char m_pad00[0x14];
	unsigned int m_maxQueue;	// +0x14
};

class Rva004FA659
{
public:
	void rva004FA659();
};

class Rva004FA953Listener
{
public:
	virtual void v00(void *, int);
	virtual void v01(void *, int);
	virtual void v02(void *, int);
	virtual void v03(void *, int);
};

class Rva004FA953List
{
	void *m_begin;
	void *m_end;
	void *m_capacity;
	unsigned int m_index;
};

class Rva004FAA81Primary
{
public:
	virtual void v00();

	Rva004FAA81Building *m_building;	// +0x04
	const Rva004FA83EData *m_data;	// +0x08
};

class Rva004FA992
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual bool canProduce(ObjectID id, Rva004E3184 *desc);	// slot 4
	virtual void v05();
	virtual void v06();
	virtual bool canQueueUnit(ObjectID id);	// slot 7

	void rva004FA992(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value);

	Rva004FA953List m_list;	// +0x04
	_STL::vector<ObjectID> m_queue;	// +0x14
	int m_count;	// +0x20
};

class LivingWorldBuildingNuggetSpawnArmy : public Rva004FAA81Primary, public Rva004FA992
{
public:
	virtual void runProductionPhase();
	virtual bool canQueueUnit(ObjectID id);
	Rva002E2903Player *getOwningPlayer();
};

void LivingWorldBuildingNuggetSpawnArmy::runProductionPhase()
{
	if (m_queue.size() <= 0)
		return;
	ObjectID id = m_queue[0];
	Rva004E3184 army(0);
	if (!canProduce(id, &army))
	{
		m_queue.erase(m_queue.begin());
		m_count = 0;
		rva004FA992(&Rva004FA953Listener::v01, static_cast<Rva004FA992 *>(this), 0);
		return;
	}
	if (++m_count >= army.m_48)
	{
		Rva004FAA81Building *building = m_building;
		LivingWorldRegion *region = building->m_region;
		if (region == 0)
			return;
		Rva003F0F13Elem spot;
		spot.a = 0.0f;
		spot.b = 0.0f;
		region->GetGarrisonArmyPlacementSpot(&spot);
		army.m_pos = spot;
		int ownerId = region->m_ownerId;
		Rva002E2903Player *owner = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(ownerId, 0);
		if (!owner)
			return;
		if (((Rva002E112A *)owner)->rva002E112A((Rva00319CED *)&army) && region->CanSpawnUnitWithinCPLimit((Rva00319CED *)&army))
		{
			if (!TheLivingWorldLogic->spawnArmy(&army, (Rva002B6A04Player *)owner, false))
				return;
			m_queue.erase(m_queue.begin());
			rva004FA992(&Rva004FA953Listener::v01, static_cast<Rva004FA992 *>(this), 0);
			rva004FA992(&Rva004FA953Listener::v03, static_cast<Rva004FA992 *>(this), id);
			((LivingWorldPlayer *)owner)->OnUnitDequeued((Rva00319CED *)&army);
			m_count = 0;
		}
	}
	((Rva004FA659 *)this)->rva004FA659();
}

bool LivingWorldBuildingNuggetSpawnArmy::canQueueUnit(ObjectID id)
{
	unsigned int maxQueue = m_data->m_maxQueue;
	if (m_queue.size() >= maxQueue)
		return false;
	Rva004E3184 army(0);
	LivingWorldPlayer *owner;
	void *summary;
	Rva004FA83ETemplate *tmpl;
	bool result = false;
	if (canProduce(id, &army))
		result = ((Rva002B2646 *)TheLivingWorldLogic)->rva002B2646((Arg54 *)this, (Arg54 *)(int)id)
		&& (owner = (LivingWorldPlayer *)getOwningPlayer()) != 0
		&& owner->rva002E1155((Rva00319CED *)&army)
		&& (summary = ((Rva00319CED *)&army)->rva004E23C1()) != 0
		&& (tmpl = (Rva004FA83ETemplate *)((Rva0037DCA5 *)((Rva0040CB2CIndexedField *)summary)->get(0))->rva0037DC52()) != 0
		&& ((tmpl->m_kind113 & 4) == 0
			|| (((LivingWorldPlayer *)((Rva004E0705 *)m_building)->rva004E0705())->rva002E12F3(id)
				&& !((LivingWorldPlayer *)((Rva004E0705 *)m_building)->rva004E0705())->HasArmyQueuedInAnyBuilding(*(void **)army.m_pad4C, 0, 0)));
	return result;
}
