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

enum KindOfType { CAPTURE_FORBIDDEN_KIND = 0x6f };
enum SpecialPowerType { CAPTURE_POWER = 0x1d };
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
 bool rva0041C79C(const Object *, const Object *, CommandSourceType, class CapturePowerView *);
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
