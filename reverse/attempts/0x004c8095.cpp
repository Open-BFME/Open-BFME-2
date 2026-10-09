// ?rva004C8095@PlayerHealSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.985 date=2026-10-09
// cl: /MD /GX
//
// PlayerHealSpecialPower's three doSpecialPower overrides: slots 10, 11 and
// 12 of the class's +0x10 special-power interface vftable 0x00C5E308, so
// `this` is that subobject (the Object at -0x08). Each runs the
// SpecialPowerModule base first, Zero Hour style, then hands a location to
// the class's own helper 0x004C8095 on the primary this (pinned by address
// on these three call sites): the power's own position for doSpecialPower
// (0x004C8198, 31 bytes), the target Object's position for
// doSpecialPowerAtObject (0x004C8175, 35 bytes) and the given location for
// doSpecialPowerAtLocation (0x004C8155, 32 bytes).
// The base doSpecialPower 0x0049490F is the Zero Hour body (script-fired
// commands skip the paused and disabled tests), pinned on that evidence.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
class Player;
template<int N> class BitFlags { public: bool any() const; };
class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;		// +0x38
public:
	unsigned char pad44[0x1C8-0x44];
	BitFlags<11> m_disabledMask;
};

class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(unsigned int options);					// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);		// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C8095(const Coord3D *loc);
};

void PlayerHealSpecialPower::doSpecialPower(unsigned int options)
{
	SpecialPowerModule::doSpecialPower(options);
	rva004C8095(m_object->getPosition());
}

void PlayerHealSpecialPower::doSpecialPowerAtObject(Object *obj, unsigned int options)
{
	SpecialPowerModule::doSpecialPowerAtObject(obj, options);
	rva004C8095(obj->getPosition());
}

void PlayerHealSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C8095(loc);
}

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


extern PartitionManager *ThePartitionManager;
static __forceinline float healRadius(const PlayerHealSpecialPowerModuleData *data) { return data->m_healRadius; }

void PlayerHealSpecialPower::rva004C8095(const Coord3D *loc)
{
	Object *obj = m_object;
	if (obj->m_disabledMask.any())
		return;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;

	const PlayerHealSpecialPowerModuleData *data = (const PlayerHealSpecialPowerModuleData *)m_moduleData;
	ObjectCreationList::create(data->m_dispatchList, m_object, loc, 0, 0);

	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(loc, healRadius((const PlayerHealSpecialPowerModuleData *)m_moduleData), 0, &Rva0026119DFilter(), 0);
	Object *other;
	while ((other = iter.next()) != 0)
		((Rva004C7F5C *)this)->rva004C7F5C(other);
}
