// cl: /MD /GX
//
// ActionManager special-power location checks called in a row by the
// placement validator 0x0041D60B.
//
//   0x0041C9F8  when the power template's final override has flag bit 4
//               (+0x18), true only if no alive object passing the 0x002614EC
//               filter (override +0x78, the caster's controlling player) is
//               within the override's +0x7C range of the location (2D)
//
// Retail evaluates the range into a spilled local between building the
// filter temporaries and linking them; the assignment inside the call is
// what gives that order.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.

#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
// Preserve the independently rowed Object getter's ABI spelling. Its target
// numeric status threshold 3 corresponds to the reference's object fog state.
enum CellShroudStatus { ACTION_OBJECT_SHROUD_FOGGED = 3 };

#include "../../../../../reference/shims/bfme2_ascii/string_base.h"

enum ObjectID { INVALID_OBJECT_ID = 0 };

enum Relationship { ENEMIES, NEUTRAL, ALLIES };

enum ObjectStatusTypes { OBJECT_STATUS_UNDER_CONSTRUCTION = 2, OBJECT_STATUS_SOLD = 0x13 };

class Thing { public: bool isAboveTerrain() const; };

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask() { return -1; }
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
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

// Both retail filter tables (VA BFAD10 and BCECF0) have 76CC7A in slot 2.
// The four-byte body returns -1. Define the all-players mask directly; its
// byte-identical ICF owner is FileClass::Get_File_Handle.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object : public Thing
{
public:
	void *rva0028BD17() const;
	ObjectID getSoleHealingBenefactor() const;
	bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
	Player *getControllingPlayer() const;	// 0x0028AFA9
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
};

struct BfmeWideHit
{
	Object *m_object;
	float m_distance;
};

struct BfmeWidePayload
{
	BfmeWideHit *m_begin;
	BfmeWideHit *m_end;
};

struct BfmeWideResult
{
	~BfmeWideResult();	// 0x0004AA28
	BfmeWidePayload *m_value;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFinalOverride() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}
	char m_pad00[0x18];
	bool flag2() const { return (m_flags >> 2) & 1; }
	bool flag4() const { return (m_flags >> 4) & 1; }
	unsigned int m_flags;	// +0x18
	char m_pad1C[0x54 - 0x1C];
	float m_54;		// +0x54
	char m_pad58[0x60 - 0x58];
	char m_60[4];		// +0x60
	char m_pad64[0x78 - 0x64];
	char m_78[4];		// +0x78
	float m_7C;		// +0x7C
};

class ActionManager
{
public:
	bool canRepairObject(const Object *, const Object *, CommandSourceType);
	bool canHijackVehicle(const Object *, const Object *, CommandSourceType);
	bool canGetHealedAt(const Object *, const Object *, CommandSourceType);
	bool canGetRepairedAt(const Object *, const Object *, CommandSourceType);
	bool canMakeObjectDefector(const Object *, const Object *, CommandSourceType);
	bool canConvertObjectToCarBomb(const Object *, const Object *, CommandSourceType);
	bool validateLocationForForbiddenObjects(const Object *obj, const Coord3D *pos, const SpecialPowerTemplate *sp);
};

bool ActionManager::validateLocationForForbiddenObjects(const Object *obj, const Coord3D *pos, const SpecialPowerTemplate *sp)
{
	if (!sp->getFinalOverride()->flag4())
		return true;
	Player *player = obj->getControllingPlayer();
	float range;
	Object *found = ThePartitionManager->getClosestObject(pos, (range = sp->getFinalOverride()->m_7C), 1,
		Rva0026119DFilter().link(&Rva002614ECFilter(sp->getFinalOverride()->m_78, player, true)));
	return found == 0;
}

// BFME1 ba7ddda7 ActionManager.cpp supplies the nested visibility predicate
// and car-bomb collision algorithm. Target evidence: complete 88B boundary
// 41B85D..41B8B5 and 108B boundary 41B9B0..41BA1C RET12; reserved signed IDs
// at Object+74; Player fields +54/+5C; target status438 and module vector244.
// Module+0C virtuals4/4/C corroborate the reference collision interface.
// The same-TU static helper preserves retail's optimized EDI/ESI argument ABI.
// Borrowed views describe only the fields and slots read by these bodies.
struct ShroudPlayerView
{
	char pad[0x54];
	int index;
	char pad58[4];
	int type;
};

static __declspec(noinline) bool isObjectShroudedForAction(
	const Object *a, const Object *b, CommandSourceType c)
{
	if (b) {
		int id = *reinterpret_cast<const int *>(reinterpret_cast<const char *>(b) + 0x74);
		if (id >= 0x05f5e0fc && id <= 0x05f5e0ff)
			return false;
	}
	if (a && b && a->getControllingPlayer()) {
		if (reinterpret_cast<ShroudPlayerView *>(a->getControllingPlayer())->type == 0 &&
			c != CMD_FROM_SCRIPT &&
			b->getShroudStatusForPlayer(reinterpret_cast<ShroudPlayerView *>(
				a->getControllingPlayer())->index) >= ACTION_OBJECT_SHROUD_FOGGED)
			return true;
	}
	return false;
}

class BfmeCarBombCollideView
{
public:
	virtual void slot0() = 0;
	virtual bool wouldLikeToCollideWith(const Object *) const = 0;
	virtual bool isHijackedVehicleCrateCollide() const = 0;
	virtual bool isCarBombCrateCollide() const = 0;
};

class BfmeActionBehaviorView
{
public:
	virtual void slot0() = 0;
	virtual BfmeCarBombCollideView *getCollide() = 0;
};

bool ActionManager::canConvertObjectToCarBomb(
	const Object *a, const Object *b, CommandSourceType c)
{
	if (!a || !b)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(b) + 0x438) & 1)
		return false;
	if (isObjectShroudedForAction(a, b, c))
		return false;
	void **modules = *reinterpret_cast<void ***>(
		reinterpret_cast<char *>(const_cast<Object *>(a)) + 0x244);
	for (; *modules; ++modules) {
		BfmeActionBehaviorView *module = reinterpret_cast<BfmeActionBehaviorView *>(
			reinterpret_cast<char *>(*modules) + 0x0c);
		BfmeCarBombCollideView *collide = module->getCollide();
		if (collide && collide->wouldLikeToCollideWith(b) && collide->isCarBombCrateCollide())
			return true;
	}
	return false;
}

// BFME1 ba7ddda7 ActionManager.cpp canMakeObjectDefector, with native
// Object status byte +438. Relationship enum ENEMIES=0 is already rowed.
// The complete 64-byte body ends at 41BA5C; the adjacent five-byte stub
// is outside this function and is not included in its extent.
bool ActionManager::canMakeObjectDefector(
	const Object *obj, const Object *target, CommandSourceType commandSource)
{
	if (!obj || !target)
		return false;
	if (obj->getRelationship(target) != ENEMIES)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x438) & 1)
		return false;
	if (isObjectShroudedForAction(obj, target, commandSource))
		return false;
	return true;
}

class ActionRepairBodyView
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual float getHealth() const = 0;
	virtual void slot5() = 0;
	virtual float getMaxHealth() const = 0;
};

// BFME1 ba7ddda7 canGetRepairedAt is the semantic guide. Native 41BBE4
// omits the reference's isMobile and KINDOF_VEHICLE checks. Template
// KINDOF_AIRCRAFT/FS_AIRFIELD/REPAIR_PAD tests occupy +109/10C/10B;
// Object status and body fields are +438 and +254. No complete layouts
// or target KindOf enum identities beyond the reference relationship
// are asserted by these borrowed accesses.
bool ActionManager::canGetRepairedAt(
	const Object *obj, const Object *dest, CommandSourceType source)
{
	if (!obj || !dest)
		return false;
	if (obj->getRelationship(dest) != ALLIES)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(obj) + 0x438) & 1)
		return false;
	if (obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) ||
		dest->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || dest->testStatus(OBJECT_STATUS_SOLD))
		return false;
	const unsigned char *objTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(obj) + 4);
	const unsigned char *destTemplate;
	if (objTemplate[0x109] & 0x10) {
		if (!obj->isAboveTerrain())
			return false;
		destTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(dest) + 4);
		if (!(destTemplate[0x10c] & 8))
			return false;
	} else {
		destTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(dest) + 4);
		if (!(destTemplate[0x10b] & 0x80))
			return false;
	}
	ActionRepairBodyView *body = *reinterpret_cast<ActionRepairBodyView *const *>(reinterpret_cast<const char *>(obj) + 0x254);
	if (body->getHealth() == body->getMaxHealth())
		return false;
	if (isObjectShroudedForAction(obj, dest, source))
		return false;
	return true;
}

// BFME1 ba7ddda7 canGetHealedAt; target native status predicate calls,
// template bits +109 bit0/+10C bit0 and body field +254.
bool ActionManager::canGetHealedAt(
	const Object *obj, const Object *dest, CommandSourceType source)
{
	if (!obj || !dest)
		return false;
	if (obj->getRelationship(dest) != ALLIES)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(dest) + 0x438) & 1)
		return false;
	if (obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) ||
		dest->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || dest->testStatus(OBJECT_STATUS_SOLD))
		return false;
	const unsigned char *objTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(obj) + 4);
	if (!(objTemplate[0x109] & 1))
		return false;
	const unsigned char *destTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(dest) + 4);
	if (!(destTemplate[0x10c] & 1))
		return false;
	if (isObjectShroudedForAction(obj, dest, source))
		return false;
	ActionRepairBodyView *body = *reinterpret_cast<ActionRepairBodyView *const *>(reinterpret_cast<const char *>(obj) + 0x254);
	if (body && body->getHealth() == body->getMaxHealth())
		return false;
	return true;
}

// BFME1 ba7ddda7 canHijackVehicle; native status +438 and modules +244;
// target template flag +109 bit4 and collision predicate virtual slot +8.
bool ActionManager::canHijackVehicle(
	const Object *obj, const Object *target, CommandSourceType source)
{
	if (!obj || !target)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x438) & 1)
		return false;
	if (isObjectShroudedForAction(obj, target, source))
		return false;
	if (obj->getRelationship(target) != ENEMIES)
		return false;
	const unsigned char *targetTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(target) + 4);
	if (targetTemplate[0x109] & 0x10)
		return false;
	void **modules = *reinterpret_cast<void ***>(
		reinterpret_cast<char *>(const_cast<Object *>(obj)) + 0x244);
	for (; *modules; ++modules) {
		BfmeActionBehaviorView *module = reinterpret_cast<BfmeActionBehaviorView *>(
			reinterpret_cast<char *>(*modules) + 0x0c);
		BfmeCarBombCollideView *collide = module->getCollide();
		if (collide && collide->wouldLikeToCollideWith(target) && collide->isHijackedVehicleCrateCollide())
			return true;
	}
	return false;
}

class ActionRepairModuleView
{
public:
	virtual void slot0() = 0; virtual void slot1() = 0;
	virtual void slot2() = 0; virtual void slot3() = 0;
	virtual void slot4() = 0; virtual void slot5() = 0;
	virtual void slot6() = 0; virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual bool slot9() = 0;
};

// ZH ActionManager::canRepairObject provides the repair algorithm. Native
// target requires ALLIES, filters MordorWorker, permits dead targets with
// template+632 set, tests template+11A bit6 and module slot9, then excludes
// contained builders and a target assigned to another healing benefactor.
// The module interface identity and extra target flag meanings remain unknown.
bool ActionManager::canRepairObject(
	const Object *obj, const Object *target, CommandSourceType source)
{
	if (!obj || !target)
		return false;
	const unsigned char *objTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(obj) + 4);
	if (objTemplate && reinterpret_cast<const StringBase<char> *>(objTemplate + 0x64)->compare("MordorWorker") == 0)
		return false;
	if (obj->getRelationship(target) != ALLIES)
		return false;
	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x438) & 1) {
		const unsigned char *deadTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(target) + 4);
		if (!deadTemplate[0x632])
			return false;
	}
	const unsigned char *targetTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(target) + 4);
	unsigned int kindFlags = *reinterpret_cast<const unsigned int *>(targetTemplate + 0x108);
	if (kindFlags & 0x01400000)
		return false;
	if (obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || target->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return false;
	if (targetTemplate[0x10c] & 0x40)
		return false;
	objTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(obj) + 4);
	if (!(objTemplate[0x109] & 0x40))
		return false;
	if (!(kindFlags & 0x80))
		return false;
	ActionRepairBodyView *body = *reinterpret_cast<ActionRepairBodyView *const *>(reinterpret_cast<const char *>(target) + 0x254);
	if (body->getHealth() == body->getMaxHealth())
		return false;
	targetTemplate = *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(target) + 4);
	if (targetTemplate[0x11a] & 0x40)
		return false;
	ActionRepairModuleView *module = static_cast<ActionRepairModuleView *>(target->rva0028BD17());
	if (module && module->slot9())
		return false;
	if (isObjectShroudedForAction(obj, target, source))
		return false;
	if (*reinterpret_cast<void *const *>(reinterpret_cast<const char *>(obj) + 0x274))
		return false;
	ObjectID benefactor = target->getSoleHealingBenefactor();
	if (benefactor && benefactor != *reinterpret_cast<const ObjectID *>(reinterpret_cast<const char *>(obj) + 0x74))
		return false;
	return true;
}
