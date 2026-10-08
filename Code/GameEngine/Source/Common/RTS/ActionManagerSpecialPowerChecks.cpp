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
enum CellShroudStatus { ACTION_OBJECT_SHROUD_FOGGED = 3, ACTION_OBJECT_SHROUD_SHROUDED = 4 };

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

enum KindOfType { CAPTURE_FORBIDDEN_KIND = 0x6f };
enum SpecialPowerType { CAPTURE_POWER = 0x1d };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
struct Rva0028AC4EEntry;
class Module;
class SpecialPowerModuleInterface;
class SpecialPowerTemplate;
class Object : public Thing
{
public:
 bool isKindOf(KindOfType) const;
 bool hasSpecialPower(SpecialPowerType) const;
 bool rva002943B2(const Player *);
	void *rva0028BD17() const;
	ObjectID getSoleHealingBenefactor() const;
	bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
	Player *getControllingPlayer() const;	// 0x0028AFA9
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const;	// 0x0028BB9E
	const Rva0028AC4EEntry *rva0028AC4E() const;	// 0x0028AC4E
	float GetRelativeAngle(const Coord3D *pos) const;	// 0x000B4542
	friend class ActionManager;
protected:
	Module *findModule(NameKeyType) const;	// 0x0028B6D6
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
	SpecialPowerType getSpecialPowerType() const { return getFinalOverride()->m_type; }
	unsigned int m_flags;	// +0x18
	SpecialPowerType m_type;	// +0x1C
	char m_pad20[0x54 - 0x20];
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
 bool rva0041C79C(const Object *, const Object *, CommandSourceType, class CapturePowerView *);
	bool canHijackVehicle(const Object *, const Object *, CommandSourceType);
	bool canGetHealedAt(const Object *, const Object *, CommandSourceType);
	bool canGetRepairedAt(const Object *, const Object *, CommandSourceType);
	bool canMakeObjectDefector(const Object *, const Object *, CommandSourceType);
	bool canConvertObjectToCarBomb(const Object *, const Object *, CommandSourceType);
	bool validateLocationForForbiddenObjects(const Object *obj, const Coord3D *pos, const SpecialPowerTemplate *sp);
	bool canDoSpecialPowerAtObject(const Object *obj, const Object *target, CommandSourceType commandSource,
		const SpecialPowerTemplate *spTemplate, unsigned int commandOptions, bool checkSourceRequirements);
	bool rva0041BA61(const Object *obj);
	bool rva0041CE27(Object *obj, Object *target, int);
	bool canTransferSuppliesAt(const Object *obj, const Object *transferDest);
	bool canDockAt(const Object *obj, const Object *dockDest, CommandSourceType commandSource,
		bool checkDockUpdate);
	bool canFireWeaponAtLocation(const Object *obj, const Coord3D *loc, CommandSourceType commandSource,
		WeaponSlotType slot, const Object *objectInWay);
	bool rva0041C138(const Object *obj, const Object *target, CommandSourceType commandSource);
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

// BFME1 ba7ddda7 ActionManager::canCaptureBuilding is the semantic guide.
// BFME2 41C79C..41C96C RET16 receives its module as the fourth argument;
// its template override +60 filter supersedes the legacy capture restrictions.
// The local chain is 64 bytes, with seven-dword masks at +8 and +24.
class BfmeFixedStorage0004543D {
public:
 BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &) throw();
 unsigned words[7];
};
struct Rva00045411BitSet {
 Rva00045411BitSet(int, int);
 unsigned words[7];
};
template<int N> class BitFlags { public: unsigned m_bits[7]; };
// Native second mask at DFEFA4 is seven clear words. Use the existing
// default-mask definition; this caller supplies its first verified DIR32 site.
extern BitFlags<116> KINDOFMASK_NONE;
class Rva0004584D : public Rva000421C8 {
public:
 Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &);
 virtual ~Rva0004584D() {}
 virtual bool allow(Object *);
 BfmeFixedStorage0004543D m08, m24;
};
class ObjectFilter { public: bool isValid() const; };
struct Rva2225E0Filter { bool accepts(Object *, Player *); };
class CapturePowerView {
public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual float getPercentReady() const = 0;
 virtual void slot0c() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
};
class Team;
class HasTeam2EC
{
public:
	char m_pad[0x2ec];
	Team *m_team2ec;
};
class VisIface
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual bool isGarrisonable() const;
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual HasTeam2EC *GetThing(Player *p);
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void d55();
	virtual void d56();
	virtual void d57();
	virtual void d58();
	virtual void d59();
	virtual void d60();
	virtual void d61();
	virtual void d62();
	virtual void d63();
	virtual void d64();
	virtual void d65();
	virtual void d66();
	virtual void d67();
	virtual void d68();
	virtual unsigned int CheckActive(int v);
 virtual void d70();
 virtual void d71();
 virtual void d72();
 virtual int getStealthUnitsContained() const;
};
class Team
{
public:
	Relationship getRelationship(const Team *that) const;
};
static __declspec(noinline) bool Rva0041B80FCheck(Object *visObj, Object *teamObj);
static __declspec(noinline) bool Rva0041B80FCheck(Object *visObj, Object *teamObj)
{
	VisIface *vis = *reinterpret_cast<VisIface **>(reinterpret_cast<char *>(visObj) + 0x250);
	if (vis && vis->CheckActive(0) > 0)
	{
		HasTeam2EC *h = vis->GetThing(teamObj->getControllingPlayer());
		if (h)
		{
			Team *t1 = h->m_team2ec;
			Team *t2 = *reinterpret_cast<Team **>(reinterpret_cast<char *>(teamObj) + 0x304);
			if (t2->getRelationship(t1) != ENEMIES)
				return true;
		}
	}
	return false;
}

static unsigned captureWord(const Object *p, int offset) {
 return *reinterpret_cast<const unsigned *>(reinterpret_cast<const char *>(p) + offset);
}
bool ActionManager::rva0041C79C(const Object *obj, const Object *target,
 CommandSourceType commandSource, CapturePowerView *module)
{
 if (!obj || !target) return false;
 if (!obj->hasSpecialPower(CAPTURE_POWER)) return false;
 const char *objectTemplate = *reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(target) + 4);
 if (*reinterpret_cast<const unsigned *>(objectTemplate + 0x110) & 0x20000) return false;
 if (!(*reinterpret_cast<const unsigned *>(objectTemplate + 0x108) & 0x80)) return false;
 if (!module) return false;
 if (module->getPercentReady() < 1.0f) return false;
 if ((*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x438) & 1) && !((unsigned char)(captureWord(target, 0x110) >> 28) & 1)) return false;
 const ObjectFilter *filter = reinterpret_cast<const ObjectFilter *>(reinterpret_cast<const char *>(module->getSpecialPowerTemplate()->getFinalOverride()) + 0x60);
 if (filter->isValid()) {
  if (!reinterpret_cast<Rva2225E0Filter *>(const_cast<ObjectFilter *>(filter))->accepts(const_cast<Object *>(target), 0)) return false;
 } else {
  objectTemplate = *reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(target) + 4);
  if (!(*reinterpret_cast<const unsigned *>(objectTemplate + 0x10c) & 0x20000)) return false;
  if (target->isKindOf(CAPTURE_FORBIDDEN_KIND)) return false;
  Rva0004584D filter(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&Rva00045411BitSet(0, 0x32)), *reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
  if (!ThePartitionManager->getClosestObject(reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(target) + 0x38), 150.0f, 1, &filter)) return false;
 }
 if (target->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || target->testStatus(OBJECT_STATUS_SOLD)) return false;
 if (captureWord(target, 0x80)) return false;
 if (isObjectShroudedForAction(obj, target, commandSource)) return false;
 Relationship r = obj->getRelationship(target);
 if (r != ENEMIES && r == ALLIES) return false;
 if (const_cast<Object *>(target)->rva002943B2(obj->getControllingPlayer())) return false;
 VisIface *contain = *reinterpret_cast<VisIface *const *>(reinterpret_cast<const char *>(target) + 0x250);
 if (contain && contain->isGarrisonable()) {
  int count = contain->CheckActive(0);
  int stealth = contain->getStealthUnitsContained();
  if (count - stealth > 0) return false;
 }
 if (Rva0041B80FCheck(const_cast<Object *>(target), const_cast<Object *>(obj))) return false;
 return true;
}

class Rva0041C96C
{
public:
 bool rva0041C96C(const Object *, const Object *, CommandSourceType);
};

static __forceinline bool actionTargetStatusBit6(const Object *target)
{
	return (*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(target) + 0x94) >> 6) & 1;
}
// BFME1 ba7ddda7 canSnipeVehicle supplies a semantic lead. No native
// caller establishes that method or its original class, so retain a neutral owner. Native omits the donor's vehicle/drone tests;
// tests +94 bit6 and +1C8 bit5 after the enemy and visibility checks.
// Native consumes two Object pointers and a command source; ECX is unused.
// Complete 88-byte control flow ends at 41C9C4 (RET12).
bool Rva0041C96C::rva0041C96C(
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
	if (actionTargetStatusBit6(target))
		return false;
	unsigned char flags = *reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x1c8);
	if (static_cast<unsigned char>(~static_cast<unsigned char>(flags >> 5)) & 1)
		return true;
	return false;
}

// canDoSpecialPowerAtObject's views. Object +0x250 is the contain module
// (the same interface rva0041C79C reads through VisIface), +0x274 the
// object containing this one; the contain list's slot 0x48 picks a rider.
// BFME1 ba7ddda7 calls the three contain slots list(), allow() and
// slot15c(); BFME2 moved them to 0x7C, 0x98 and 0x170.
class ActionSpecialPowerModuleView
{
public:
	virtual void s00(); virtual void s01();
	virtual float getPercentReady() const;	// +0x08
	virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
	virtual void s07(); virtual void s08(); virtual void s09(); virtual void s10();
	virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17();
	virtual bool isReady(int);	// +0x48
};

class ActionContainListView
{
public:
	virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
	virtual void l04(); virtual void l05(); virtual void l06(); virtual void l07();
	virtual void l08(); virtual void l09(); virtual void l10(); virtual void l11();
	virtual void l12(); virtual void l13(); virtual void l14(); virtual void l15();
	virtual void l16(); virtual void l17();
	virtual Object *pick(int, int, float, int, int);	// +0x48
};

class ActionContainView
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual bool slot10();	// +0x10
	virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
	virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
	virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
	virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
	virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
	virtual void c28(); virtual void c29(); virtual void c30();
	virtual ActionContainListView *getList();	// +0x7C
	virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
	virtual void c36(); virtual void c37();
	virtual bool allow(const Object *, bool, bool);	// +0x98
	virtual void c39(); virtual void c40(); virtual void c41(); virtual void c42();
	virtual void c43(); virtual void c44(); virtual void c45(); virtual void c46();
	virtual void c47(); virtual void c48(); virtual void c49(); virtual void c50();
	virtual void c51(); virtual void c52(); virtual void c53(); virtual void c54();
	virtual void c55(); virtual void c56(); virtual void c57(); virtual void c58();
	virtual void c59(); virtual void c60(); virtual void c61(); virtual void c62();
	virtual void c63(); virtual void c64(); virtual void c65(); virtual void c66();
	virtual void c67(); virtual void c68();
	virtual int slot114(int);	// +0x114
	virtual void c70();
	virtual void c71(); virtual void c72(); virtual void c73(); virtual void c74();
	virtual void c75(); virtual void c76(); virtual void c77(); virtual void c78();
	virtual void c79(); virtual void c80(); virtual void c81(); virtual void c82();
	virtual void c83(); virtual void c84(); virtual void c85(); virtual void c86();
	virtual void c87(); virtual void c88(); virtual void c89(); virtual void c90();
	virtual void c91();
	virtual bool canAccept(const Object *, bool);	// +0x170
};

struct ActionModuleView
{
	char m_pad00[4];
	const unsigned char *m_data;	// +0x04
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

static inline const unsigned char *actionTemplate(const Object *o)
{
	return *reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(o) + 4);
}

static inline ActionContainView *actionContain(const Object *o)
{
	return *reinterpret_cast<ActionContainView *const *>(reinterpret_cast<const char *>(o) + 0x250);
}

// WorldBuilder's debug ActionManager.cpp (lines 2380..2718) names this
// ActionManager::canDoSpecialPowerAtObject; the pinned REL32 caller in
// CommandButtonHuntUpdate::scanClosestTarget confirms it. BFME1 ba7ddda7
// supplies the case bodies; BFME2 adds the template's +0x60 object filter,
// the capture-power exception for dead targets and the 0x0041BA61 veto
// ahead of the switch. The case values follow retail's tables at 0x0041D387
// (targets) and 0x0041D3AB (index); the enumerator names are not recovered.
bool ActionManager::canDoSpecialPowerAtObject(const Object *obj, const Object *target,
	CommandSourceType commandSource, const SpecialPowerTemplate *spTemplate,
	unsigned int commandOptions, bool checkSourceRequirements)
{
	if (!spTemplate)
		return false;

	if (checkSourceRequirements && !obj->hasSpecialPower(spTemplate->getSpecialPowerType()))
		return false;

	ActionSpecialPowerModuleView *module =
		reinterpret_cast<ActionSpecialPowerModuleView *>(obj->getSpecialPowerModule(spTemplate));

	bool capturePower = false;
	bool isCapture = spTemplate->getSpecialPowerType() == CAPTURE_POWER ||
		spTemplate->getSpecialPowerType() == 0x1a;
	bool filterValid = reinterpret_cast<const ObjectFilter *>(spTemplate->getFinalOverride()->m_60)->isValid();
	if (filterValid) {
		Rva2225E0Filter *filter =
			reinterpret_cast<Rva2225E0Filter *>(const_cast<char *>(spTemplate->getFinalOverride()->m_60));
		if (!filter->accepts(const_cast<Object *>(target), obj->getControllingPlayer()))
			return false;
	}

	if (isCapture) {
		if (filterValid)
			capturePower = true;
		else
			capturePower = rva0041C79C(obj, target, commandSource,
				reinterpret_cast<CapturePowerView *>(module));
	}
	bool canCapture = capturePower && isCapture;

	if (!target ||
		((*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(target) + 0x438) & 1) && !canCapture))
		return false;

	if (rva0041BA61(obj))
		return false;

	Relationship r = obj->getRelationship(target);
	if (module) {
		if (checkSourceRequirements) {
			if (module->getPercentReady() < 1.0f)
				return false;
			if (!module->isReady(0))
				return false;
		}

		if (isObjectShroudedForAction(obj, target, commandSource))
			return false;

		switch (spTemplate->getSpecialPowerType()) {
		case 39:
		case 40: {
			int id = *reinterpret_cast<const int *>(reinterpret_cast<const char *>(target) + 0x74);
			if (id >= 0x05f5e0fc && id <= 0x05f5e0ff) {
				static const NameKeyType key = TheNameKeyGenerator->nameToKey("GrabPassengerSpecialPower");
				ActionModuleView *grab = reinterpret_cast<ActionModuleView *>(obj->findModule(key));
				if (grab && grab->m_data[0x80] && actionTemplate(target)[0x5eb])
					return true;
				return false;
			}
			if (target->testStatus((ObjectStatusTypes)0x63))
				return false;
			ActionContainView *contain = actionContain(obj);
			if ((commandOptions & 2) && (commandOptions & 1) && !obj->testStatus((ObjectStatusTypes)0x26)) {
				if (!contain->canAccept(target, true))
					return false;
			}
			if (!contain)
				return false;
			const Object *container = *reinterpret_cast<const Object *const *>(reinterpret_cast<const char *>(target) + 0x274);
			if (container) {
				ActionContainListView *list = actionContain(container) ? actionContain(container)->getList() : 0;
				if (!list)
					return false;
			}
			if (actionTemplate(target)[0x115] & 0x20) {
				ActionContainListView *list = actionContain(target) ? actionContain(target)->getList() : 0;
				if (!list)
					return false;
				target = list->pick(0, 0, 0.0f, 0, 0);
				if (!target)
					return false;
			} else if (target->testStatus((ObjectStatusTypes)0x3f))
				return false;
			bool allowed = true;
			unsigned int kindFlags = *reinterpret_cast<const unsigned int *>(actionTemplate(target) + 0x118);
			if ((kindFlags & 0x10) && spTemplate->getSpecialPowerType() != 40)
				allowed = false;
			if ((kindFlags & 0x100) && spTemplate->getSpecialPowerType() != 39)
				allowed = false;
			if (allowed && contain->allow(target, true, false))
				return true;
			return false;
		}
		case 32: case 42: case 45: case 49: case 59: case 64: case 71: case 129:
		case 132: case 151:
			return true;
		case 130:
			if (r == ENEMIES)
				return true;
			if ((r == ALLIES || r == NEUTRAL) && (actionTemplate(target)[0x11d] & 0x10))
				return true;
			return false;
		case 147:
			return true;
		case 57: case 68: case 69: case 144: {
			unsigned char bit = (unsigned char)(*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(target) + 0x94) >> 6);
			bit = (unsigned char)~bit;
			bit &= 1;
			return bit;
		}
		case 138:
			if (actionTemplate(target)[0x108] & 0x80)
				return canRepairObject(obj, target, commandSource);
			return false;
		case 29:
			return rva0041C79C(obj, target, commandSource, reinterpret_cast<CapturePowerView *>(module));
		case 51:
			if (rva0041CE27(const_cast<Object *>(obj), const_cast<Object *>(target), 0))
				return *reinterpret_cast<void *const *>(reinterpret_cast<const char *>(target) + 0x258) &&
					!(actionTemplate(target)[0x108] & 4);
			return false;
		case 16: case 28: case 35: case 47: case 50: case 52: case 53: case 54:
		case 58: case 60: case 61: case 62: case 63: case 65: case 66: case 67:
		case 70: case 72: case 73: case 74: case 75: case 76: case 77: case 78:
		case 79: case 80: case 82: case 84: case 85: case 86: case 87: case 89:
		case 90: case 91: case 92: case 93: case 94: case 95: case 96: case 97:
		case 99: case 100: case 101: case 103: case 104: case 106: case 107: case 111:
		case 112: case 113: case 115: case 118: case 119: case 120: case 121: case 123:
		case 124: case 126: case 128: case 133: case 134: case 135: case 136: case 137:
		case 140: case 141: case 142: case 143: case 145: case 146: case 148: case 149:
		case 150: case 152: case 153:
			return false;
		}
	}
	return false;
}

class AIUpdateInterface
{
public:
	bool rva00262BEC();	// 0x00262BEC
};

class Pathfinder
{
public:
	int GetGroundLayer(const Coord3D *pos);	// 0x002E9871
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
};
extern AI *TheAI;

// The canDoSpecialPower* veto: true when the object's AIUpdateInterface
// passes 0x00262BEC (locomotor goal type 1 or 4 with a path) and the
// pathfinder reports a layer at or above 0x11 500 units over its position.
// Retail calls it on the source object from canDoSpecialPower (0x0041CD08),
// canDoSpecialPowerAtObject (0x0041D0C4) and canDoSpecialPowerAtLocation
// (0x0041D658); the name is not recovered.
bool ActionManager::rva0041BA61(const Object *obj)
{
	if (TheAI && obj) {
		AIUpdateInterface *ai = *reinterpret_cast<AIUpdateInterface *const *>(reinterpret_cast<const char *>(obj) + 0x258);
		if (ai && ai->rva00262BEC()) {
			const Coord3D *objPos = reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(obj) + 0x38);
			Coord3D pos;
			pos.x = objPos->x;
			pos.y = objPos->y;
			pos.z = objPos->z + 500.0f;
			if (TheAI->pathfinder()->GetGroundLayer(&pos) >= 0x11)
				return true;
		}
	}
	return false;
}

// canTransferSuppliesAt's views: the supply-truck interface the source's
// AIUpdateInterface returns from slot 0x178 and the warehouse dock's box
// count. BFME1 ba7ddda7 reads the same slots at 0x13C, 0x00 and 0x10.
class ActionSupplyTruckView
{
public:
	virtual int getNumberBoxes() const;	// +0x00
	virtual void t01() const; virtual void t02() const; virtual void t03() const;
	virtual bool isAvailableForSupplying() const;	// +0x10
};

class ActionSupplyAIView
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
	virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
	virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
	virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
	virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
	virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
	virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
	virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
	virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43();
	virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
	virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
	virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
	virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59();
	virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63();
	virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67();
	virtual void a68(); virtual void a69(); virtual void a70(); virtual void a71();
	virtual void a72(); virtual void a73(); virtual void a74(); virtual void a75();
	virtual void a76(); virtual void a77(); virtual void a78(); virtual void a79();
	virtual void a80(); virtual void a81(); virtual void a82(); virtual void a83();
	virtual void a84(); virtual void a85(); virtual void a86(); virtual void a87();
	virtual void a88(); virtual void a89(); virtual void a90(); virtual void a91();
	virtual void a92(); virtual void a93();
	virtual const ActionSupplyTruckView *getSupplyTruckAIInterface() const;	// +0x178
};

struct ActionWarehouseDockView
{
	char m_pad00[0x88];
	int m_boxesStored;	// +0x88
};

// ZH/BFME1 ba7ddda7 ActionManager::canTransferSuppliesAt; BFME2 moves the
// dead bit to +0x438, the AI to +0x258 and tests the construction bit
// through testStatus.
bool ActionManager::canTransferSuppliesAt(const Object *obj, const Object *transferDest)
{
	if (!obj || !transferDest)
		return false;

	if (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(transferDest) + 0x438) & 1)
		return false;

	if (obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) ||
		transferDest->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return false;

	if (transferDest->testStatus(OBJECT_STATUS_SOLD))
		return false;

	const ActionSupplyAIView *ai =
		*reinterpret_cast<const ActionSupplyAIView *const *>(reinterpret_cast<const char *>(obj) + 0x258);
	if (!ai)
		return false;

	const ActionSupplyTruckView *supplyTruck = ai->getSupplyTruckAIInterface();
	if (!supplyTruck)
		return false;

	static const NameKeyType key_warehouseUpdate = TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
	const ActionWarehouseDockView *warehouseModule =
		reinterpret_cast<const ActionWarehouseDockView *>(transferDest->findModule(key_warehouseUpdate));
	if (warehouseModule)
		if (warehouseModule->m_boxesStored == 0 || transferDest->getRelationship(obj) == ENEMIES)
			return false;

	static const NameKeyType key_centerUpdate = TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
	Module *centerModule = transferDest->findModule(key_centerUpdate);
	if (centerModule)
		if (supplyTruck->getNumberBoxes() == 0 ||
			transferDest->getControllingPlayer() != obj->getControllingPlayer())
			return false;

	if (!warehouseModule && !centerModule)
		return false;

	if (!supplyTruck->isAvailableForSupplying())
		return false;

	Player *objPlayer = obj->getControllingPlayer();
	if (objPlayer) {
		if (reinterpret_cast<const ShroudPlayerView *>(objPlayer)->type == 0 &&
			transferDest->getShroudStatusForPlayer(reinterpret_cast<const ShroudPlayerView *>(objPlayer)->index) ==
				ACTION_OBJECT_SHROUD_SHROUDED)
			return false;
	}

	return true;
}

// canDockAt's views: the behavior module's dock interface getter at slot
// 0x58 and the dock interface's one-argument docker test at slot 0x40.
class ActionDockUpdateView
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual bool canDocker(const Object *docker);	// +0x40
};

class ActionDockBehaviorView
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
	virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15();
	virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19();
	virtual void b20(); virtual void b21();
	virtual ActionDockUpdateView *getDockUpdateInterface();	// +0x58
};

// ZH/BFME1 ba7ddda7 ActionManager::canDockAt: the dock-interface scan and
// the supply-transfer test survive; BFME2 drops the railed-transport check
// and adds a fourth argument (InGameUI 0x29C88C passes 1 or 0) that gates
// the dock interface's own test of the docker.
bool ActionManager::canDockAt(const Object *obj, const Object *dockDest, CommandSourceType commandSource,
	bool checkDockUpdate)
{
	ActionDockUpdateView *di = 0;
	void *const *modules = *reinterpret_cast<void *const *const *>(reinterpret_cast<const char *>(dockDest) + 0x244);
	for (; *modules; ++modules) {
		if ((di = reinterpret_cast<ActionDockBehaviorView *>(
				reinterpret_cast<char *>(*modules) + 0x0c)->getDockUpdateInterface()) != 0)
			break;
	}
	if (di != 0) {
		if (canTransferSuppliesAt(obj, dockDest) == true)
			return true;
		if (checkDockUpdate)
			return di->canDocker(obj);
	}
	return false;
}

// canFireWeaponAtLocation's views: the weapon set at Object+0x330, the
// weapon's template at +4 with its float at +0x2C, and the Coord3D overload
// of Weapon::isWithinAttackRange.
extern "C" double __cdecl fabs(double);

struct ActionWeaponTemplateView
{
	char m_pad00[0x2C];
	float m_2C;	// +0x2C
};

class Weapon
{
public:
	char isWithinAttackRange(Object *source, void *pos, float extra, int flag) const;	// 0x002CB902
	char m_pad00[4];
	const ActionWeaponTemplateView *m_template;	// +0x04
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;	// 0x002C7469
};

class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
};

// ZH/BFME1 ba7ddda7 ActionManager::canFireWeaponAtLocation keeps only the
// weapon lookup; BFME2 then passes when the 0x28AC4E entry's 0x1E46E1 value
// is nonzero, otherwise requires attack range and, for KindOf 2 objects
// with a positive template arc, a relative angle within it.
bool ActionManager::canFireWeaponAtLocation(const Object *obj, const Coord3D *loc, CommandSourceType commandSource,
	WeaponSlotType slot, const Object *objectInWay)
{
	if (obj == 0 || loc == 0)
		return false;

	Weapon *weapon = reinterpret_cast<const WeaponSet *>(
		reinterpret_cast<const char *>(obj) + 0x330)->getWeaponInWeaponSlot(slot);
	if (!weapon)
		return false;

	const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
	if (entry && ((Rva001E46E1 *)entry)->rva001E46E1(const_cast<Object *>(obj)) != 0.0f)
		return true;

	if (!weapon->isWithinAttackRange(const_cast<Object *>(obj), (void *)loc, 0.0f, 1))
		return false;

	float arc = weapon->m_template->m_2C;
	if (arc > 0.0f && (actionTemplate(obj)[0x108] & 4)) {
		double angle = fabs(obj->GetRelativeAngle(loc));
		if (angle > arc)
			return false;
	}
	return true;
}

// 0x0041C138's player view: Player::getRelationship(const Team *) is the
// matched 0x002AD0C6 row; the target's team sits at Object+0x304.
class Player
{
public:
	Relationship getRelationship(const Team *that) const;	// 0x002AD0C6
};

// Retail 0x0041C138..0x0041C21B RET12, no REL32 callers. Target evidence:
// the object's KindOf dword has bit 8 set and bit 27 clear, the target is
// KindOf 7, both carry a contain module at +0x250 and the target's +0x10
// slot passes; the same controlling player defers to the +0x98 slot, a
// NEUTRAL player-to-team relationship also needs the +0x114 slot to be 0.
bool ActionManager::rva0041C138(const Object *obj, const Object *target, CommandSourceType commandSource)
{
	if (obj == 0 || target == 0)
		return false;
	unsigned int kindof = *reinterpret_cast<const unsigned int *>(actionTemplate(obj) + 0x108);
	if (!(kindof & 0x100) || (kindof & 0x8000000))
		return false;
	if (!(actionTemplate(target)[0x108] & 0x80))
		return false;
	if (actionContain(obj) == 0)
		return false;
	ActionContainView *contain = actionContain(target);
	if (contain == 0)
		return false;
	if (!contain->slot10())
		return false;
	if (obj->getControllingPlayer() == target->getControllingPlayer())
		return contain->allow(obj, true, true);
	if (obj->getControllingPlayer()->getRelationship(
			*reinterpret_cast<const Team *const *>(reinterpret_cast<const char *>(target) + 0x304)) == NEUTRAL) {
		return contain->slot114(0) == 0 && contain->allow(obj, true, true) ? 1 : 0;
	}
	return false;
}
