// ?update@AutoPickUpUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.85 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit);	// 0x00045411
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Player *player, bool flag) : m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class TerrainLogic
{
public:
	void *rva0027F108(const Coord3D *pos, float radius, bool flag, int unused);
};
extern TerrainLogic *TheTerrainLogic;

class Rva2225E0Filter
{
public:
	bool rva00361B12(const BfmeFixedStorage0004543D *mask, Player *a, Player *b) const;
private:
	int m_index;
};

enum KindOfType { KINDOF_37 = 0x25, KINDOF_61 = 0x3D };
enum SpecialPowerType { SPECIAL_POWER_39 = 0x27 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

class SpecialPowerModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10();
	virtual void doSpecialPowerAtObject(Object *target, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
};

class ContainModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68();
	virtual unsigned int getRemainingAmmo(const void *descriptor);
};

class BodyModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04();
	virtual float getHealth() const;
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;
	Player *getControllingPlayer() const;
	float getVisionRange() const;
	void fireCurrentWeapon(Object *target, int id);
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
	const Coord3D *getPosition() const { return &m_pos; }
	int getID() const { return m_id; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Object *getContainedBy() const { return m_containedBy; }
private:
	char m_pad00[0x38];
	Coord3D m_pos;				// +0x38
	char m_pad44[0x74 - 0x44];
	int m_id;				// +0x74
	char m_pad78[0x250 - 0x78];
	ContainModuleInterface *m_contain;	// +0x250
	BodyModuleInterface *m_body;		// +0x254
	char m_pad258[0x274 - 0x258];
	Object *m_containedBy;			// +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_privateStatus;		// +0x438
};

struct AutoPickUpEatObjectEntry
{
	int m_filter;
	float m_myHealth;
	float m_targetHealth;
};

struct AutoPickUpEatObjectEntries
{
	unsigned int size() const { return m_finish - m_start; }
	AutoPickUpEatObjectEntry *m_start;
	AutoPickUpEatObjectEntry *m_finish;
	AutoPickUpEatObjectEntry *m_end;
};

class ModuleData;
struct AutoPickUpUpdateModuleData
{
	void *m_vtable;
	int m_unused04;
	int m_scanDelayTime;				// +0x08
	Rva2225E0Filter m_pickUpFilter;			// +0x0C
	float m_scanDistance;				// +0x10
	AutoPickUpEatObjectEntries m_eatObjectEntries;	// +0x14
	bool m_autoThrowObject;				// +0x20
	bool m_runFromButton;				// +0x21
	int m_runFromButtonNumber;			// +0x24
	bool m_canScanWhileAttackingOrMoving;		// +0x28
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
	unsigned int m_storage[3];
};
class AutoPickUpUpdateInterface
{
public:
	virtual void anchor();
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	virtual UpdateSleepTime update();
	bool rva00495DD4();
	const AutoPickUpUpdateModuleData *getAutoPickUpUpdateModuleData() const
	{
		return (const AutoPickUpUpdateModuleData *)m_moduleData;
	}
private:
	unsigned int m_count24;
	bool m_flag28;
	bool m_flag29;
};

UpdateSleepTime AutoPickUpUpdate::update()
{
	Object *object = getObject();
	const AutoPickUpUpdateModuleData *data = getAutoPickUpUpdateModuleData();
	if (object->isEffectivelyDead())
		return UPDATE_SLEEP_NONE;

	bool allowed;
	if (!data->m_canScanWhileAttackingOrMoving
		&& (object->isKindOf(KINDOF_37) || object->isKindOf(KINDOF_61)))
		allowed = false;
	else
		allowed = true;

	if (!rva00495DD4())
		return UPDATE_SLEEP_NONE;
	if (!allowed)
		return UPDATE_SLEEP_NONE;

	m_flag28 = false;

	if (data->m_autoThrowObject && object->getContainedBy()
		&& object->getContain()->getRemainingAmmo(0) == 1)
	{
		Coord3D position = *object->getPosition();
		Object *found = ThePartitionManager->getClosestObject(&position,
			object->getVisionRange(), 0,
			Rva00261409Filter(object->getControllingPlayer(), true, 4).link(
				Rva0026119DFilter().link(
					Rva00261513Filter(object, true, -1.0f).link(
						&Rva00261058(object->getControllingPlayer(), false)))));
		if (found)
		{
			object->fireCurrentWeapon(found, found->getID());
			return UPDATE_SLEEP_NONE;
		}
	}

	if (object->getContainedBy() && object->getContain()->getRemainingAmmo(0) == 0)
	{
		Coord3D position = *object->getPosition();
		BfmeFixedStorage0004543D mask(0, 0x6C);
		Object *found = ThePartitionManager->getClosestObject(&position,
			getAutoPickUpUpdateModuleData()->m_scanDistance, 0,
			Rva002614ECFilter(&data->m_pickUpFilter, object->getControllingPlayer(), true).link(
				&Rva003959FA(mask)));
		if (found)
		{
			SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(SPECIAL_POWER_39);
			if (power)
			{
				power->doSpecialPowerAtObject(found, 0x2000);
				return UPDATE_SLEEP_NONE;
			}
		}
	}

	if (!object->getContain())
		return UPDATE_SLEEP_FOREVER;

	if (object->getContain()->getRemainingAmmo(0) == 0)
	{
		unsigned int i = 0;
		if (i < data->m_eatObjectEntries.size())
		{
			unsigned int offset = 0;
			do
			{
				const AutoPickUpEatObjectEntry *entry = (const AutoPickUpEatObjectEntry *)
					((const char *)data->m_eatObjectEntries.m_start + offset);
				if (object->getBodyModule()->getHealth() <= entry->m_myHealth)
				{
					Object *found = ThePartitionManager->getClosestObject(object->getPosition(),
						data->m_scanDistance, 0,
						Rva002614ECFilter(entry, object->getControllingPlayer(), true).link(
							&Rva0026119DFilter()));
					if (found && found->getBodyModule()->getHealth() <= entry->m_targetHealth)
					{
						SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(SPECIAL_POWER_39);
						if (power)
						{
							power->doSpecialPowerAtObject(found, 0x4000);
							return UPDATE_SLEEP_NONE;
						}
					}
				}
				++i;
				offset += sizeof(AutoPickUpEatObjectEntry);
			} while (i < data->m_eatObjectEntries.size());
		}
	}

	if (object->getContain()->getRemainingAmmo(0) != 0)
		return UPDATE_SLEEP_NONE;

	{
		Coord3D position = *object->getPosition();
		if (data->m_pickUpFilter.rva00361B12(&BfmeFixedStorage0004543D(0, 0x5E), 0, 0))
		{
			const Coord3D *point = (const Coord3D *)TheTerrainLogic->rva0027F108(&position,
				getAutoPickUpUpdateModuleData()->m_scanDistance, true, 1);
			SpecialPowerModuleInterface *power = m_object->findSpecialPowerModuleInterface(SPECIAL_POWER_39);
			if (power && point)
			{
				Coord3D target;
				target.x = point->x;
				target.y = point->y;
				target.z = point->z;
				power->doSpecialPowerAtLocation(&target, 0x2000);
				return UPDATE_SLEEP_NONE;
			}
		}
		Object *found = ThePartitionManager->getClosestObject(&position,
			getAutoPickUpUpdateModuleData()->m_scanDistance, 0,
			&Rva002614ECFilter(&data->m_pickUpFilter, object->getControllingPlayer(), true));
		if (found)
		{
			SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(SPECIAL_POWER_39);
			if (power)
				power->doSpecialPowerAtObject(found, 0x2000);
		}
	}
	return UPDATE_SLEEP_NONE;
}
