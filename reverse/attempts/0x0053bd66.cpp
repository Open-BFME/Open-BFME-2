// ?getCommandAvailability@ControlBar@@QBE?AW4CommandAvailability@@PBVCommandButton@@PAVGameWindow@@PAVObject@@PAM_N@Z
// partial score=0.98 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// ?getRappellerCount@@YAHPAVObject@@@Z  Native 0x0053BC7E..0x0053BCC4 (70 bytes)
// ControlBar getRappellerCount: counts the contained objects whose template is
// KindOf 43 (bit 3 of the template byte 0x10D). The contain module sits at
// Object +0x250 and its vtable slot 70 (0x118) returns the contained-items
// list handle by hidden pointer (an unused word then the list pointer).
// Evidence: ZH ControlBarCommand.cpp getRappellerCount (same loop over
// ContainedItemsList) and the WB twin 0x111BE20 (contain +0x258 slot 69 then
// Thing::getTemplate and BitFlags test 0x2B). The only retail caller is
// ControlBar::getCommandAvailability 0x0053BD66 which passes the object in EAX
// (a private convention of this static helper), so both live in this unit.
//
// ?getCommandAvailability@ControlBar@@QBE?AW4CommandAvailability@@PBVCommandButton@@PAVGameWindow@@PAVObject@@PAM_N@Z
// Native 0x0053BD66..0x0053CEB5 (4431 bytes of code; the 29-target jump table
// and its 60-byte index table follow up to 0x0053CF65).
// Named WB twin 0x01118A40 (13216 bytes; ControlBarCommand.cpp asserts
// 1442..2611) gives the statement structure and the case order of the switch
// over the command type (cases 0x39 0x35 1 0x16 0x22 0x21 0x32 0x33 0x3C 0x3B
// 3 0x2E 0x2D/0x31 6 7 8 0x17 0x1A 0x10 0x11 0x28 0x18/0x20/0x25/0x26
// 0x2A-0x2C 0x1B 0x23 0x0E 0x27 0x34 in both images); Zero Hour's
// ControlBarCommand.cpp getCommandAvailability is the donor shape. BFME2
// argument order (command, window, object, percent out, force) comes from the
// recursive call at 0x0053BEE8 and the existing caller pin.
//
// DRAFT STATUS (helper agent, NEAR, not landable yet): 1314 of 1335 retail
// instructions align; the static above stays exact. Remaining differences:
//  1. Frame: retail packs the case 0x10 out Coord3D (getClosestPointOnLand)
//     into the science vector's slot at ebp-0x2C (sub esp 0x5C). Here the
//     Coord3D gets its own slot at ebp-0x38 (sub esp 0x68), which also moves
//     the castle filter/mask from -0x68/-0x48 to -0x74/-0x54. Probes show cl
//     never lets the case 0x18 vector reuse a slot of anything declared before
//     it (only later locals reuse the vector's slot). Placements tried: block
//     scope, case scope, switch scope, function scope, ctor/dtor wrapper types,
//     inline helper, const-ref vector, brace-less cases.
//  2. Case 0x18 science loop: retail loads begin into EAX for the empty test
//     and copies it to EDI for the loop (one extra mov edi,eax); cl here loads
//     straight into EDI. Likely tied to (1).
// Codegen facts established: KindOf and disabled-type tests are raw-int
// inline helpers (test byte form); BitFlags::test is the bool shift form;
// upgrade affordability and isUpgradeInQueue go through inline wrappers (the
// argument is materialised before the vtable load); the type check before the
// 0x53BA87 predicate reads the field directly; case 0x28 uses a conditional
// temporary with an empty destructor (gives the and [ebp-0x10],0 flag store).
// Pins needed: ?rva0053BA87@ControlBar@@QBEHPBVCommandButton@@PAVObject@@@Z
// = 0x0053BA87 (thiscall spelling; the rowed stdcall name cannot load ECX) and
// ?Rva0053BA4D@@YAXPAVObject@@PAX@Z = 0x0053BA4D (the contain-iteration
// callback; unrowed, unpinned).

#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <vector>
#undef free
#include "ascii_string.h"
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum BuildableStatus { BSTATUS_YES = 0 };
enum ScienceType { SCIENCE_INVALID = -1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum WeaponStatus { READY_TO_FIRE = 0 };
enum BattlePlanStatus { PLANSTATUS_NONE = 0 };
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};

typedef _STL::vector<ScienceType> ScienceVec;

class Module { public: virtual void moduleSlot0(); };
class Player;
class Weapon;
class Drawable;
class CreateAHeroData;
class Rva00373EC6;
class Rva002A7DDEArg;
class BfmeMemberRV;
class UpgradeTemplate { public: Int m_pad0; Int m_upgradeType; };

class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;

class ThingTemplate {
public:
	bool isKindOf43() const { return (m_kindOf[5] & 8) != 0; }
	__forceinline UnsignedInt isKindOf(int bit) const { return ((const UnsignedInt *)m_kindOf)[bit >> 5] & (1 << (bit & 31)); }
	BuildableStatus getBuildable() const;
	char m_pad000[0x108];
	unsigned char m_kindOf[32];
};

struct ContainedNode {
	ContainedNode *m_next;
	ContainedNode *m_prev;
	class Object *m_data;
};
struct ContainedList {
	ContainedNode *m_node;
};
struct ContainedItems {
	ContainedItems();
	void *m_unused;
	const ContainedList *m_list;
};
struct ContainedSnapshot {
	~ContainedSnapshot() {}
	void *m_unused;
	const ContainedList *m_list;
	Bool isEmpty() const { return m_list->m_node->m_next == m_list->m_node; }
};

typedef void (*ContainIterateFunc)(class Object *obj, void *userData);

class ContainModule {
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30();
	virtual Int v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void iterateContained(ContainIterateFunc func, void *userData, Bool reverse);
	virtual UnsignedInt getContainCount(Int mode) const;
	virtual ContainedItems getContainedItemsList() const;
	virtual ContainedSnapshot getContainedSnapshot() const;
};

class AIDozerView {
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual Bool isTaskPending(Int task);
	virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
	virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
	virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
	virtual void v27(); virtual void v28(); virtual void v29();
	virtual Int getQueueCount();
};

#define SLOTS10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AIUpdateInterface {
public:
	SLOTS10(a0) SLOTS10(a1) SLOTS10(a2) SLOTS10(a3) SLOTS10(a4) SLOTS10(a5) SLOTS10(a6) SLOTS10(a7) SLOTS10(a8)
	virtual void a90(); virtual void a91(); virtual void a92();
	virtual AIDozerView *getDozerAIInterface();
	virtual void a94(); virtual void a95(); virtual void a96(); virtual void a97(); virtual void a98(); virtual void a99();
	SLOTS10(b0) SLOTS10(b1) SLOTS10(b2)
	virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34();
	virtual void b35(); virtual void b36(); virtual void b37();
	virtual Bool isMoving();
};

class ObjectModule254 {
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual Int getState();
};

class ProductionUpdateInterface {
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade);
	Bool isQueued(const UpgradeTemplate *upgrade) { return isUpgradeInQueue(upgrade); }
	virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16();
	virtual Int getProductionCount();
	virtual void v18(); virtual void v19(); virtual void v20();
	virtual Int firstProduction();
};

class FoundationView {
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual Bool isBusy();
};

class Rva0028BD17View {
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual Bool isDone();
	virtual Bool canAffordActivate(Player *player);
	virtual Bool isActivatable();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18();
	virtual Bool isUpgradable();
	virtual void v20(); virtual void v21();
	virtual Bool canAffordUpgrade(Player *player);
	virtual void v23(); virtual void v24();
	virtual Bool isActive();
};

class Rva0028C197View {
public:
	SLOTS10(v0) SLOTS10(v1)
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual Bool canProduce(const ThingTemplate *tt);
};

class Overridable { public: const Overridable *friend_getFinalOverride() const; };
class SpecialPowerTemplate : public Overridable {
public:
	Int getSpecialPowerType() const { return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_type; }
	char m_pad000[0x1c];
	Int m_type;
};

class SpecialPowerModuleInterface {
public:
	virtual void v00();
	virtual Bool isReady() const;
	virtual Real getPercentReady() const;
	virtual Bool isPaused() const;
	virtual void v04(); virtual void v05();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
	virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17();
	virtual Bool isUsable(Int mode);
};

class CommandFilterInterface {
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5();
	virtual Bool rejects(const class CommandButton *command);
};
class BattlePlanInterface {
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual UnsignedInt getValidCommandMask();
};
class Rva0044E642AddImm32Field { public: Int get() const; };

class Rva0039567CCmpBoolField { public: Bool get() const; };
class Rva00395F57 { public: Bool canUnpack(Bool b); };
class Rva00397F45 { public: Bool rva00397F45(Player *player, Int flag); };
class Rva0039718B { public: Bool rva0039718B(Player *player); };
class Rva00395686 { public: Bool rva00395686(Player *player, ThingTemplate *tt); };
class Rva00395A82 { public: Real rva00395A82(); };
class Rva003974CE { public: Int apply(Int (__cdecl *func)(class Object *, Int), Int userData); };
class CastleBehavior {
public:
	static Module *rva000395708(class Object *obj);
	static NameKeyType rva0003955DA();
};
struct CastleMemberView { char m_pad000[0x18]; ObjectID m_castleID; };

class BattlePlanUpdate { public: BattlePlanStatus getActiveBattlePlan() const; };
NameKeyType Rva0045EE2CGet();

class Rva00373EB6 { public: unsigned char rva00373EB6(); };
class Rva0029FCB4 { public: ScienceVec rva0029FCB4(); };
class Rva00331682Holder { public: bool test(const void *key) const; };
class Rva0028B7C1DwordField { public: Int get() const; };
class Rva0035B164 { public: Int rva0035B164(Int cur); };
class Rva0028F528 { public: Int rva0028F528(); };
class Rva002A7DDE { public: Bool rva002A7DDE(Rva002A7DDEArg *arg); };
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(); };

class BfmeFixedStorage0004543D {
public:
	BfmeFixedStorage0004543D() { memset(m_bits, 0, sizeof(m_bits)); }
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &that);
	UnsignedInt m_bits[7];
};
struct CommandCastleKindFilter { BfmeFixedStorage0004543D mask; Bool matched; };
Int __cdecl Rva0053B946(class Object *object, CommandCastleKindFilter *filter);
void __cdecl Rva0053BA4D(class Object *object, void *userData);

template <int N> class BitFlags {
public:
	bool any() const;
	bool test(int bit) const { return ((m_bits[bit >> 5] >> (bit & 31)) & 1) != 0; }
	Int count() const { return ((Rva0028F528 *)this)->rva0028F528(); }
	UnsignedInt m_bits[(N + 31) / 32];
};

class WeaponTemplateView { public: char m_pad000[0xec]; Int m_clipSize; };
class Weapon {
public:
	Bool rva002C96D8();
	WeaponStatus computeStatus(bool *unused) const;
	Real getPercentReadyToFire() const;
	char m_pad000[4];
	const WeaponTemplateView *m_template;
	char m_pad008[0xc - 8];
	Int m_slot;
	char m_pad010[0x18 - 0x10];
	UnsignedInt m_lastFireFrame;
};
class WeaponSet { public: Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const; };

class ExperienceTracker { public: Int getVeterancyLevel() const { return m_level; } char m_pad000[0x24]; Int m_level; };

class Object {
	friend class ControlBar;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ContainModule *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	__forceinline UnsignedInt isKindOf(int bit) const { return getTemplate()->isKindOf(bit); }
	Bool testStatus(ObjectStatusTypes status) const;
	Player *getControllingPlayer() const;
	Bool isLocallyControlled() const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *spt) const;
	void *rva0028BC58(Int mode);
	void *rva0028BCF4() const;
	void *rva0028BD17() const;
	void *rva0028BD92(Int type);
	void *rva0028C197() const;
	Rva00373EC6 *rva0028F4BC();
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	Bool rva002940B9(const UpgradeTemplate *upgrade);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Bool isDisabled() const { return m_disabled.any(); }
	__forceinline UnsignedInt isDisabledByType(int type) const { return m_disabled.m_bits[type >> 5] & (1 << (type & 31)); }
protected:
	Module *findModule(NameKeyType key) const;
public:
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x38 - 8];
	Coord3D m_pos;
	char m_pad044[0x94 - 0x44];
	char m_disabledPowers[0x10c - 0x94];
	BitFlags<591> m_modelConditions;
	char m_pad15c[0x1c8 - 0x10c - sizeof(BitFlags<591>)];
	BitFlags<11> m_disabled;
	char m_pad1cc[0x250 - 0x1cc];
	ContainModule *m_contain;
	ObjectModule254 *m_module254;
	AIUpdateInterface *m_ai;
	char m_pad25c[0x264 - 0x25c];
	ExperienceTracker *m_experience;
	char m_pad268[0x330 - 0x268];
	WeaponSet m_weaponSet;
	char m_pad331[0x437 - 0x331];
	unsigned char m_scriptStatus;
	unsigned char m_438;
	char m_pad439[0x43b - 0x439];
	Bool m_singleUseCommandUsed;
};

static Int getRappellerCount(Object *obj)
{
	ContainModule *contain = obj->getContain();
	if (contain == 0)
		return 0;
	Int num = 0;
	ContainedItems items = contain->getContainedItemsList();
	ContainedNode *end = items.m_list->m_node;
	for (ContainedNode *it = end->m_next; it != end; it = it->m_next)
	{
		if (it->m_data->getTemplate()->isKindOf43())
			++num;
	}
	return num;
}

class Rva0037E421 { public: void *rva0037E7A5(Int index); };
class Rva0037E6E8 { public: Real rva0037E898(Int index, Int *cost, Object *obj); };

class Player {
public:
	Object *findNaturalCommandCenter();
	Object *rva002AC629();
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const;
	Bool rva002AA8EF(const UpgradeTemplate *upgrade) const;
	Bool allowedToBuild(const ThingTemplate *tt) const;
	Bool canBuild(const ThingTemplate *tt) const;
	unsigned char rva002AA00C(ThingTemplate *tt, Int count);
	Bool hasScience(ScienceType science) const;
	Bool rva002AB82D(CreateAHeroData *hero) const;
	Bool rva002AB855(CreateAHeroData *hero) const;
	Bool isPlayerActive() const;
	char m_pad000[0x5c];
	Int m_playerType;
	char m_pad060[0x94 - 0x60];
	UnsignedInt m_money;
	char m_pad098[0x738 - 0x98];
	char m_heroes[0x750 - 0x738];
	Int m_750;
};

class CommandButton {
public:
	const ThingTemplate *rva0035B570() const;
	Int getCommandType() const { return m_commandType; }
	UnsignedInt getOptions() const { return m_options; }
	BfmeFixedStorage0004543D getCastleKindOf() const { return m_castleKindOf; }
	char m_pad000[0x14];
	Int m_commandType;
	char m_pad018[0x1c - 0x18];
	UnsignedInt m_options;
	char m_pad020[0x24 - 0x20];
	const UpgradeTemplate *m_upgrade;
	const UpgradeTemplate **m_upgradesBegin;
	const UpgradeTemplate **m_upgradesEnd;
	const UpgradeTemplate **m_upgradesCap;
	Bool m_requireAllUpgrades;
	char m_pad035[0x44 - 0x35];
	const SpecialPowerTemplate *m_specialPower;
	char m_pad048[0x80 - 0x48];
	WeaponSlotType m_weaponSlot;
	char m_pad084[0xc0 - 0x84];
	Int m_heroIndex;
	char m_pad0c4[0x101 - 0xc4];
	Bool m_hideIfCantBuild;
	char m_pad102[0x106 - 0x102];
	Bool m_specialPowerEnabled;
	char m_pad107[0x108 - 0x107];
	Int m_requiredLevel;
	char m_pad10c[0x110 - 0x10c];
	BfmeFixedStorage0004543D m_castleKindOf;
	char m_pad12c[0x188 - 0x12c];
	AsciiString *m_chainBegin;
	AsciiString *m_chainEnd;
};

class GameWindow { public: UnsignedInt winGetStatus(); };
class BuildAssistant {
public:
	SLOTS10(v0) SLOTS10(v1)
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual Int isLocationLegal(Object *builder, const ThingTemplate *tt, Int index);
};
extern BuildAssistant *TheBuildAssistant;
class UpgradeCenter {
public:
	Bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *obj, Bool flag);
	Bool canAfford(Player *player, const UpgradeTemplate *upgrade, Object *obj) { return rva0026F11A(player, upgrade, obj, false); }
};
extern UpgradeCenter *TheUpgradeCenter;
extern GameLogic *TheGameLogic;
class PlayerList;
extern PlayerList *ThePlayerList;
class Pathfinder { public: Bool getClosestPointOnLand(const Coord3D *pos, Object *obj, Coord3D *out); };
class AI { public: char m_pad000[0x10]; Pathfinder *m_pathfinder; };
extern AI *TheAI;
struct DrawableNode { DrawableNode *m_next; DrawableNode *m_prev; Drawable *m_data; };
struct DrawableList { DrawableNode *m_node; };
class DrawableView { public: char m_pad000[0xfc]; Object *m_object; };
class InGameUI {
public:
	SLOTS10(v0) SLOTS10(v1) SLOTS10(v2) SLOTS10(v3) SLOTS10(v4) SLOTS10(v5) SLOTS10(v6)
	virtual void v70(); virtual void v71(); virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables();
};
extern InGameUI *TheInGameUI;

class ControlBar {
public:
	CommandAvailability getCommandAvailability(const CommandButton *command, GameWindow *win, Object *obj, Real *percent, Bool forceDisabledEvaluation) const;
	Int rva0053BA87(const CommandButton *command, Object *obj) const;
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

class GateBehaviorBase { public: virtual void g00(); };
class GateView : public GateBehaviorBase, public Module {
public:
	virtual void g01(); virtual void g02(); virtual void g03(); virtual void g04(); virtual void g05();
	virtual Bool isOpen();
	virtual void g07(); virtual void g08(); virtual void g09();
	virtual Bool isUsable();
};

struct LandPoint : public Coord3D { ~LandPoint() {} };
struct RappelCheckData { Object *obj; Bool found; };

CommandAvailability ControlBar::getCommandAvailability(const CommandButton *command, GameWindow *win, Object *obj, Real *percent, Bool forceDisabledEvaluation) const
{
	*percent = 1.0f;
	Player *player = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
	if (player == 0)
		return COMMAND_HIDDEN;

	switch (command->getCommandType())
	{
		case 0x20:
			obj = player ? player->findNaturalCommandCenter() : 0;
			break;
		case 0x26:
			obj = player ? player->rva002AC629() : 0;
			break;
	}

	if (obj == 0)
		return COMMAND_HIDDEN;

	if ((obj->m_scriptStatus & 1) || (obj->m_scriptStatus & 2))
		return COMMAND_HIDDEN;

	if (obj->isDisabledByType(5))
		return COMMAND_HIDDEN;

	Bool flagged = obj->m_modelConditions.test(0xd6);
	if (((command->getOptions() & 0x4000000) && !flagged) || ((command->getOptions() & 0x8000000) && flagged))
		return COMMAND_RESTRICTED;

	if (command->getOptions() & 0x40000000)
	{
		AIUpdateInterface *ai = obj->getAI();
		if (ai && ai->isMoving())
			return COMMAND_RESTRICTED;
	}

	if (command->m_commandType != 0x18 && rva0053BA87(command, obj) == COMMAND_HIDDEN)
		return COMMAND_RESTRICTED;

	if (obj->m_singleUseCommandUsed)
		return COMMAND_RESTRICTED;

	ExperienceTracker *expTracker = obj->m_experience;
	if (expTracker == 0)
		return COMMAND_HIDDEN;
	Int level = command->m_requiredLevel;
	if (level > 0 && expTracker->getVeterancyLevel() < level)
		return COMMAND_HIDDEN;

	Bool disabled = obj->isDisabled();
	if (disabled && obj->m_disabled.test(8) && obj->m_disabled.count() == 1)
		disabled = false;

	if (disabled && !forceDisabledEvaluation)
	{
		Int commandType = command->getCommandType();
		if (commandType != 0x11 && commandType != 0x28 && commandType != 0x10
			&& commandType != 0x14 && commandType != 0x15 && commandType != 0x1b)
		{
			if (getCommandAvailability(command, win, obj, percent, true) != COMMAND_HIDDEN)
				return COMMAND_RESTRICTED;
			return COMMAND_HIDDEN;
		}
	}

	if (command->getOptions() & 0x40)
	{
		Bool requireAll = command->m_requireAllUpgrades;
		Bool result = requireAll != 0;
		for (UnsignedInt i = 0; i < (UnsignedInt)(command->m_upgradesEnd - command->m_upgradesBegin); ++i)
		{
			const UpgradeTemplate *upgrade = command->m_upgradesBegin[i];
			if (upgrade)
			{
				if (upgrade->m_upgradeType == 0)
				{
					Bool has = player->rva002AB87D(upgrade);
					if (requireAll)
					{
						if (has)
						{
							result = false;
							break;
						}
					}
					else if (!has)
					{
						result = true;
						break;
					}
				}
				else if (upgrade->m_upgradeType == 1)
				{
					Bool has = obj->rva00290D2B(upgrade);
					if (requireAll)
					{
						if (has)
						{
							result = false;
							break;
						}
					}
					else if (!has)
					{
						if (command->rva0035B570())
						{
							BuildableStatus status = command->rva0035B570()->getBuildable();
							if (status == 2 || (status == 3 && obj->getControllingPlayer()->m_playerType != 1))
								return COMMAND_HIDDEN;
						}
						result = true;
					}
				}
			}
		}
		if (result)
			return COMMAND_RESTRICTED;
	}

	if (command->getOptions() & 0x800)
	{
		Module *member = CastleBehavior::rva000395708(obj);
		if (member)
		{
			Object *castle = TheGameLogic->findObjectByID(((CastleMemberView *)member)->m_castleID);
			if (castle == 0)
				return COMMAND_HIDDEN;
			Module *castleBehavior = castle->findModule(CastleBehavior::rva0003955DA());
			if (castleBehavior)
			{
				CommandCastleKindFilter filter;
				filter.matched = false;
				filter.mask = command->getCastleKindOf();
				((Rva003974CE *)castleBehavior)->apply((Int (__cdecl *)(Object *, Int))Rva0053B946, (Int)&filter);
				if (!filter.matched)
					return COMMAND_HIDDEN;
			}
		}
	}

	ProductionUpdateInterface *pu = (ProductionUpdateInterface *)obj->rva0028BC58(0);
	if (pu && pu->firstProduction() && (command->getOptions() & 0x10000))
		return COMMAND_RESTRICTED;

	Bool queueMaxed = pu ? (pu->getProductionCount() == 20) : false;

	switch (command->getCommandType())
	{
		case 0x39:
		{
			if (obj->findModule(Rva0045EE2CGet()) == 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x35:
		{
			if (!obj->isKindOf(0xe) && !obj->isKindOf(0xf) && !obj->isKindOf(0x9c))
				return COMMAND_RESTRICTED;
			Player *owner = obj->getControllingPlayer();
			if (owner == 0 || owner->m_750 != 0)
				return COMMAND_RESTRICTED;
			Int queued = 0;
			if (obj->isKindOf(0xe) || obj->isKindOf(0xf))
			{
				AIDozerView *dozerAI = obj->getAI() ? obj->getAI()->getDozerAIInterface() : 0;
				if (dozerAI == 0)
					return COMMAND_RESTRICTED;
				queued = dozerAI->getQueueCount();
			}
			if (!owner->allowedToBuild(command->rva0035B570()))
				return COMMAND_NOT_ALLOWED;
			if (!owner->canBuild(command->rva0035B570()))
				return command->m_hideIfCantBuild ? COMMAND_HIDDEN : COMMAND_RESTRICTED;
			if (!owner->rva002AA00C((ThingTemplate *)command->rva0035B570(), queued))
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 1:
		{
			if (command->rva0035B570())
			{
				BuildableStatus status = command->rva0035B570()->getBuildable();
				if (status == 2 || (status == 3 && obj->getControllingPlayer()->m_playerType != 1))
					return COMMAND_HIDDEN;
			}
			if (!obj->isKindOf(0xe) && !obj->isKindOf(0x68))
				return COMMAND_RESTRICTED;
			AIDozerView *dozerAI = obj->getAI() ? obj->getAI()->getDozerAIInterface() : 0;
			void *foundationAI = obj->rva0028BCF4();
			if (dozerAI == 0 && foundationAI == 0)
				return COMMAND_RESTRICTED;
			if (dozerAI && dozerAI->isTaskPending(0) == true)
				return COMMAND_RESTRICTED;
			if (foundationAI)
			{
				FoundationView *foundation = (FoundationView *)obj->rva0028BCF4();
				if (foundation && foundation->isBusy())
					return COMMAND_RESTRICTED;
			}
			if (!player->allowedToBuild(command->rva0035B570()))
				return COMMAND_NOT_ALLOWED;
			if (!player->canBuild(command->rva0035B570()))
				return command->m_hideIfCantBuild ? COMMAND_HIDDEN : COMMAND_RESTRICTED;
			if (!player->rva002AA00C((ThingTemplate *)command->rva0035B570(), 0))
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x16:
		{
			if (obj->m_scriptStatus & 4)
				return COMMAND_HIDDEN;
			if (obj->m_438 & 1)
				return COMMAND_HIDDEN;
			break;
		}

		case 0x22:
		{
			Module *castleBehavior = obj->findModule(CastleBehavior::rva0003955DA());
			if (castleBehavior && ((Rva0039567CCmpBoolField *)castleBehavior)->get()
				&& ((Rva00397F45 *)castleBehavior)->rva00397F45(obj->getControllingPlayer(), 0))
				return COMMAND_ACTIVE;
			return COMMAND_HIDDEN;
		}

		case 0x21:
		{
			Module *castleBehavior = obj->findModule(CastleBehavior::rva0003955DA());
			if (castleBehavior && ((Rva00395F57 *)castleBehavior)->canUnpack(false)
				&& ((Rva00397F45 *)castleBehavior)->rva00397F45(obj->getControllingPlayer(), 0))
			{
				if (!((Rva0039718B *)castleBehavior)->rva0039718B(obj->getControllingPlayer()))
					return COMMAND_CANT_AFFORD;
				*percent = ((Rva00395A82 *)castleBehavior)->rva00395A82();
				if (*percent >= 1.0f)
					return COMMAND_ACTIVE;
				return COMMAND_NOT_READY;
			}
			return COMMAND_HIDDEN;
		}

		case 0x32:
		{
			const ThingTemplate *tt = command->rva0035B570();
			Module *castleBehavior = obj->findModule(CastleBehavior::rva0003955DA());
			if (tt && castleBehavior && ((Rva00395F57 *)castleBehavior)->canUnpack(false)
				&& ((Rva00397F45 *)castleBehavior)->rva00397F45(obj->getControllingPlayer(), 0))
			{
				if (!((Rva00395686 *)castleBehavior)->rva00395686(obj->getControllingPlayer(), (ThingTemplate *)tt))
					return COMMAND_CANT_AFFORD;
				*percent = ((Rva00395A82 *)castleBehavior)->rva00395A82();
				if (*percent >= 1.0f)
					return COMMAND_ACTIVE;
				return COMMAND_NOT_READY;
			}
			return COMMAND_HIDDEN;
		}

		case 0x33:
		{
			Rva0028BD17View *module = (Rva0028BD17View *)obj->rva0028BD17();
			if (module == 0)
				return COMMAND_HIDDEN;
			if (module->isActivatable())
			{
				if (!module->canAffordActivate(obj->getControllingPlayer()))
					return COMMAND_CANT_AFFORD;
				return COMMAND_ACTIVE;
			}
			if (obj->testStatus((ObjectStatusTypes)2))
				return COMMAND_HIDDEN;
			if (!module->isDone())
				return COMMAND_RESTRICTED;
			return COMMAND_DONE;
		}

		case 0x3c:
		{
			Rva0028BD17View *module = (Rva0028BD17View *)obj->rva0028BD17();
			if (module && module->isActive())
				return COMMAND_ACTIVE;
			return COMMAND_HIDDEN;
		}

		case 0x3b:
		{
			Rva0028BD17View *module = (Rva0028BD17View *)obj->rva0028BD17();
			if (module == 0)
				return COMMAND_HIDDEN;
			if (module->isUpgradable())
			{
				if (!module->canAffordUpgrade(obj->getControllingPlayer()))
					return COMMAND_CANT_AFFORD;
				return COMMAND_ACTIVE;
			}
			if (!module->isDone())
				return COMMAND_RESTRICTED;
			return COMMAND_DONE;
		}

		case 3:
		{
			if (obj->m_438 & 1)
				return COMMAND_RESTRICTED;
			const ThingTemplate *tt = command->rva0035B570();
			if (tt == 0)
				return COMMAND_HIDDEN;
			if (tt)
			{
				BuildableStatus status = tt->getBuildable();
				if (status == 2 || (status == 3 && obj->getControllingPlayer()->m_playerType != 1))
					return COMMAND_HIDDEN;
			}
			if (queueMaxed)
				return COMMAND_RESTRICTED;
			if (!player->allowedToBuild(command->rva0035B570()))
				return COMMAND_NOT_ALLOWED;
			if (!player->canBuild(tt))
				return COMMAND_RESTRICTED;
			Int legal = TheBuildAssistant->isLocationLegal(obj, tt, -1);
			if (legal == 7)
				return COMMAND_LIMITED;
			if (legal == 6 || legal == 5)
				return COMMAND_RESTRICTED;
			if (legal == 2)
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x2e:
		{
			if (!((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)obj))
				return COMMAND_HIDDEN;
			if (obj->m_438 & 1)
				return COMMAND_RESTRICTED;
			Player *owner = obj->getControllingPlayer();
			Int index = command->m_heroIndex;
			if (owner == 0 || index == -1)
				return COMMAND_RESTRICTED;
			const ThingTemplate *hero = (const ThingTemplate *)((Rva0037E421 *)owner->m_heroes)->rva0037E7A5(index);
			if (hero && !owner->allowedToBuild(hero))
				return COMMAND_NOT_ALLOWED;
			Int legal = TheBuildAssistant->isLocationLegal(obj, 0, index);
			if (legal == 7)
				return COMMAND_LIMITED;
			if (legal == 6 || legal == 5)
				return COMMAND_RESTRICTED;
			if (legal == 2)
				return COMMAND_CANT_AFFORD;
			Int cost = 0;
			*percent = ((Rva0037E6E8 *)owner->m_heroes)->rva0037E898(index, &cost, obj);
			if (*percent == 0.0f)
				return COMMAND_RESTRICTED;
			if (*percent != 1.0f)
				return COMMAND_NOT_READY;
			if ((UnsignedInt)cost <= owner->m_money)
				return COMMAND_AVAILABLE;
			return COMMAND_CANT_AFFORD;
		}

		case 0x2d:
		case 0x31:
		{
			if (obj->getContain() && obj->getContain()->v31() == 0 && obj->getContain()->getContainCount(0) > 0)
				return COMMAND_RESTRICTED;
			return COMMAND_AVAILABLE;
		}

		case 6:
		{
			if (command->m_upgrade == 0)
				return COMMAND_HIDDEN;
			if (player->rva002AB87D(command->m_upgrade) == true || player->rva002AA8EF(command->m_upgrade) == true)
				return COMMAND_DONE;
			if (!TheUpgradeCenter->canAfford(player, command->m_upgrade, obj))
				return COMMAND_CANT_AFFORD;
			if (queueMaxed)
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 7:
		{
			if (command->m_upgrade == 0)
				return COMMAND_HIDDEN;
			if (obj->isKindOf(0x96) && obj->m_module254->getState() == 3)
				return COMMAND_RESTRICTED;
			if (obj->testStatus((ObjectStatusTypes)2) || (obj->m_438 & 1))
			{
				if (obj->isKindOf(0xbd) || obj->isKindOf(0x9c))
				{
					if (!obj->testStatus((ObjectStatusTypes)0x14))
						return COMMAND_HIDDEN;
				}
			}
			if (pu == 0)
				return COMMAND_RESTRICTED;
			if (obj->rva00290D2B(command->m_upgrade) == true || pu->isQueued(command->m_upgrade) == true)
				return COMMAND_DONE;
			if (queueMaxed)
				return COMMAND_RESTRICTED;
			if (!obj->rva002940B9(command->m_upgrade))
				return COMMAND_RESTRICTED;
			if (!TheUpgradeCenter->canAfford(player, command->m_upgrade, obj))
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 8:
		{
			if (queueMaxed)
				return COMMAND_CANT_AFFORD;
			if (pu == 0)
				return COMMAND_RESTRICTED;
			if (!pu->isQueued(command->m_upgrade))
			{
				static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
				Module *member = obj->findModule(key);
				if (member)
				{
					Object *castle = TheGameLogic->findObjectByID(((CastleMemberView *)member)->m_castleID);
					if (castle && castle->rva00290D2B(command->m_upgrade))
						return COMMAND_DONE;
				}
			}
			if (!TheUpgradeCenter->canAfford(player, command->m_upgrade, obj))
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x17:
		{
			if (obj->getAI() == 0)
				return COMMAND_RESTRICTED;
			UnsignedInt now;
			Weapon *w = obj->m_weaponSet.getWeaponInWeaponSlot(command->m_weaponSlot);
			now = TheGameLogic->getFrame();
			if (w && w->m_template->m_clipSize == 0 && !w->rva002C96D8())
				return COMMAND_AVAILABLE;
			if ((w == 0 || w->computeStatus(0) != READY_TO_FIRE || w->m_lastFireFrame == now || w->m_lastFireFrame == now - 1) && w != 0)
			{
				if (w->computeStatus(0) == 3 || w->rva002C96D8())
					*percent = w->getPercentReadyToFire();
				else
					*percent = 0.0f;
				return COMMAND_NOT_READY;
			}
			break;
		}

		case 0x1a:
		{
			if (getRappellerCount(obj) <= 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x10:
		{
			Bool hasLand = obj->isKindOf(0xbf);
			if (win && (win->winGetStatus() & 0x200))
				return COMMAND_RESTRICTED;
			if (!hasLand && win && !(win->winGetStatus() & 8))
				return COMMAND_RESTRICTED;
			ContainModule *contain = obj->getContain();
			if (contain)
			{
				RappelCheckData data;
				data.found = false;
				data.obj = obj;
				contain->iterateContained(Rva0053BA4D, &data, true);
				if (data.found)
					return COMMAND_HIDDEN;
			}
			Coord3D pos;
			if (hasLand)
			{
				if (!TheAI->m_pathfinder->getClosestPointOnLand(&obj->m_pos, obj, &pos))
					return COMMAND_RESTRICTED;
			}
			break;
		}

		case 0x11:
		{
			if (obj->getContain() == 0 || obj->getContain()->getContainCount(0) <= 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x28:
		{
			Bool empty = obj->getContain() == 0 || obj->getContain()->getContainedSnapshot().isEmpty();
			if (empty)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x18:
		case 0x20:
		case 0x25:
		case 0x26:
		{
			const SpecialPowerTemplate *spt = command->m_specialPower;
			if (!command->m_specialPowerEnabled)
				return COMMAND_HIDDEN;
			if (spt == 0)
				return COMMAND_HIDDEN;
			Player *owner = obj->getControllingPlayer();
			if (owner == 0)
				return COMMAND_HIDDEN;
			if (!owner->isPlayerActive())
				return COMMAND_HIDDEN;
			{
				ScienceType science = SCIENCE_INVALID;
				ScienceVec sciences = ((Rva0029FCB4 *)spt)->rva0029FCB4();
				if (sciences.begin() != sciences.end())
				{
					for (ScienceVec::const_iterator it = sciences.begin(); it != sciences.end(); ++it)
					{
						if (owner->hasScience(*it))
						{
							science = *it;
							break;
						}
					}
					if (science == SCIENCE_INVALID)
						return COMMAND_HIDDEN;
					if (owner->rva002AB82D((CreateAHeroData *)science) || owner->rva002AB855((CreateAHeroData *)science))
						return COMMAND_RESTRICTED;
				}
			}
			if (((const Rva00331682Holder *)obj->m_disabledPowers)->test((const char *)spt + 0x64))
				return COMMAND_RESTRICTED;
			SpecialPowerModuleInterface *spm = obj->getSpecialPowerModule(spt);
			void *module = obj->rva0028BD92(spt->getSpecialPowerType());
			if (module)
			{
				const AsciiString *chainName = (const AsciiString *)((Rva0044E642AddImm32Field *)module)->get();
				if (!((const StringBase<char> *)chainName)->isEmpty())
				{
					const CommandButton *chainedCommand = TheControlBar->findCommandButton(*chainName);
					if (chainedCommand)
					{
						spt = chainedCommand->m_specialPower;
						spm = obj->getSpecialPowerModule(spt);
						module = obj->rva0028BD92(spt->getSpecialPowerType());
					}
				}
			}
			if (spm == 0)
			{
				Bool found = false;
				if (command->m_chainBegin != command->m_chainEnd)
				{
					for (UnsignedInt i = 0; i < (UnsignedInt)(command->m_chainEnd - command->m_chainBegin); ++i)
					{
						const CommandButton *other = TheControlBar->findCommandButton(command->m_chainBegin[i]);
						if (other && other->getCommandType() == 0x18)
						{
							const SpecialPowerTemplate *otherSpt = other->m_specialPower;
							if (otherSpt == 0 || obj->getSpecialPowerModule(otherSpt) == 0)
							{
								found = false;
								break;
							}
							found = true;
						}
					}
				}
			}
			else
			{
				if (!spm->isUsable(0))
					return COMMAND_RESTRICTED;
				if (!spm->isReady())
				{
					*percent = spm->getPercentReady();
					if (*percent <= 0.0f && spm->isPaused())
					{
						*percent = 1.0f;
						return COMMAND_RESTRICTED;
					}
					if (rva0053BA87(command, obj) != COMMAND_HIDDEN)
						return COMMAND_NOT_READY;
					return COMMAND_RESTRICTED;
				}
				if (rva0053BA87(command, obj) == COMMAND_HIDDEN)
					return COMMAND_RESTRICTED;
				if (module)
				{
					if (((CommandFilterInterface *)((char *)module + 0x20))->rejects(command))
						return COMMAND_RESTRICTED;
				}
				else
				{
					if (spm->getSpecialPowerTemplate()->getSpecialPowerType() == 0x24)
					{
						static NameKeyType key = TheNameKeyGenerator->nameToKey("BattlePlanUpdate");
						Module *battlePlan = obj->findModule(key);
						if (battlePlan && (command->getOptions() & ((BattlePlanInterface *)((char *)battlePlan + 0x20))->getValidCommandMask()))
							return COMMAND_ACTIVE;
					}
				}
			}
			break;
		}

		case 0x2a:
		case 0x2b:
		case 0x2c:
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
			GateView *gate = static_cast<GateView *>(obj->findModule(key));
			if (gate == 0)
				gate = static_cast<GateView *>(obj->findModule(TheNameKeyGenerator->nameToKey("GateProxyBehavior")));
			if (!obj->testStatus((ObjectStatusTypes)2) && !(obj->m_438 & 1))
			{
				if (gate && gate->isUsable()
					&& (command->getCommandType() == 0x2c
						|| (command->getCommandType() == 0x2b && !gate->isOpen())
						|| (command->getCommandType() == 0x2a && gate->isOpen() == true)))
					return COMMAND_ACTIVE;
				return COMMAND_RESTRICTED;
			}
			return COMMAND_RESTRICTED;
		}

		case 0x1b:
		{
			Weapon *w = obj->m_weaponSet.getWeaponInWeaponSlot(command->m_weaponSlot);
			if (w)
			{
				const DrawableList *list = TheInGameUI->getAllSelectedDrawables();
				for (DrawableNode *it = list->m_node->m_next; it != list->m_node; it = it->m_next)
				{
					DrawableView *draw = (DrawableView *)it->m_data;
					if (draw && draw->m_object && draw->m_object->isLocallyControlled() && draw->m_object->getCurrentWeapon(0))
					{
						Object *o = draw->m_object;
						Int slot = o->getCurrentWeapon(0)->m_slot;
						if (slot != command->m_weaponSlot)
							return COMMAND_AVAILABLE;
					}
				}
				return COMMAND_ACTIVE;
			}
			return COMMAND_RESTRICTED;
		}

		case 0x23:
		{
			Int current = ((Rva0028B7C1DwordField *)obj)->get();
			Int next = ((Rva0035B164 *)command)->rva0035B164(current);
			if (next == 5 || next == current || obj->m_weaponSet.getWeaponInWeaponSlot((WeaponSlotType)next) == 0)
				return COMMAND_HIDDEN;
		}
		case 0xe:
		{
			if (!(command->getOptions() & 0x2000))
				return COMMAND_AVAILABLE;
			static NameKeyType key = TheNameKeyGenerator->nameToKey("BattlePlanUpdate");
			BattlePlanUpdate *battlePlan = (BattlePlanUpdate *)obj->findModule(key);
			if (battlePlan && battlePlan->getActiveBattlePlan() != 1)
				return COMMAND_RESTRICTED;
			return COMMAND_AVAILABLE;
		}

		case 0x27:
		{
			if (!obj->testStatus((ObjectStatusTypes)0x12))
				return COMMAND_RESTRICTED;
			Rva00373EC6 *horde = obj->rva0028F4BC();
			if (horde && !((Rva00373EB6 *)horde)->rva00373EB6())
				return COMMAND_RESTRICTED;
			return COMMAND_AVAILABLE;
		}

		case 0x34:
		{
			const ThingTemplate *tt = command->rva0035B570();
			Rva0028C197View *producer = (Rva0028C197View *)obj->rva0028C197();
			if (tt && producer && producer->canProduce(tt))
				return COMMAND_AVAILABLE;
			return COMMAND_RESTRICTED;
		}
	}

	return COMMAND_AVAILABLE;
}
