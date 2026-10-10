// ?selectTeamToReinforce@AIPlayer@@MAE_NH@Z
// partial score=0.8128917635500246 date=2026-10-10
// ?selectTeamToReinforce@AIPlayer@@MAE_NH@Z
// partial score=0.7939423069063325 date=2026-10-09
// Target4F3DB1..4F418A; ZH AIPlayer selectTeamToReinforce with BFME2 record, recruit-type and null-order deltas.
// cl: /I. /O1 /Ob1 /G7 /arch:SSE /Oy- /Ireference/shims/moduledata /ICode/GameEngine/Source/Common /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AIPlayer's factory search and team-build feasibility, Zero Hour's
// AIPlayer.cpp bodies (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) with BFME 2's additions read off
// retail:
//  - findFactory 0x004F09CF (371 bytes): ZH's walk of TheGameLogic's object
//    list for this player's idle, built, unsold, enabled factories with a
//    production interface (Object::rva0028BC58(0)). BFME 2 checks a private
//    status bit (+0x438 & 1), asks the player's build table at +0x738 for a
//    build index (0x0037EE4C) and passes it to TheBuildAssistant's
//    isPossibleToMakeUnit (slot +0x64); with the player flag at +0x735 a busy
//    factory whose first queued entry (type 1 or 3) is a different template
//    flagged at +0x633 also counts as available.
//  - isPossibleToBuildTeam 0x004F0B42 (323 bytes): ZH's cost sum over the
//    prototype's unit infos (+0x130, count +0x1D8), with BFME 2's early
//    success when 0x002A8AB1 finds a record for the player, cost from the
//    build index (0x0037E649) or the template (0x0033A69A), and free units
//    (template +0x11B & 0x20).
//  - findDozer 0x004F0C85 (345 bytes, vtable slot +0x50): ZH's closest idle
//    dozer search; queueDozer is slot +0x54 and the repair dozer is +0x50.
//  - rva004F13D8 0x004F13D8 (398 bytes): BFME 2's check that the minimum
//    unit counts can be met from units already on the field (default team,
//    prototype flag +0x210 or team flags +0x110/+0x111) and the player's
//    money; its only callers are isAGoodIdeaToBuildTeam's paths.
//  - isAGoodIdeaToBuildTeam 0x004F1566 (237 bytes): ZH's production
//    condition (TeamPrototype 0x003A0E6E), instance limit (+0x218 against
//    countTeamInstances 0x0039D954) and build-queue duplicate checks, then
//    BFME 2's on-field shortcut (rva004F13D8) before isPossibleToBuildTeam and
//    ZH's two debug-AI messages (GlobalData +0x9B8). The queue walk calls
//    dlink_next_TeamBuildQueue, which retail folded into the shared
//    mov eax,[ecx+8] getter at 0x0030F45F. It is virtual: retail's AIPlayer
//    vtable (0x00862DC8) holds it at +0x64.
//  - checkQueuedTeams 0x004F1653 (430 bytes, vtable +0x44): ZH's two
//    build-queue walks. BFME 2 disbands an expired team before unlinking it,
//    calls Team 0x0039D889(false) before each ready-queue move, iterates team
//    members through the out-of-line 24-byte DLINK_ITERATOR<Object>, and runs
//    the production-condition script found by owner and name (0x003573C4)
//    through 0x0020D451. Reading the prototype through an inline getter, not
//    the raw field, is what gives retail's edi/ebx assignment.
//  - computeCenterAndRadiusOfBase 0x004F1801 (466 bytes): ZH's two
//    build-list walks with the bounding circle radius at template +0xB0 and
//    m_baseCenterSet at +0x40. Reading each location's x and y into locals
//    before the sums, rather than copying the Coord3D, gives retail's paired
//    loads.
//  - checkReadyTeams 0x004F2FC4 (498 bytes, vtable +0x40): ZH's ready-queue
//    walk. BFME 2 finds the start script by owner and production condition
//    (0x003573C4), calls Team 0x0039D889(false) after the unlink and has no
//    skirmish clearTeamFlags; the 60-second timeout scales the frame-rate
//    global at VA 0x00DBA4E4. The ready-queue next getter (+0x10) is retail's
//    shared mov eax,[ecx+0x10] at 0x001DB09D.
//  - TeamInQueue::includesADozer 0x004F10C2 (36 bytes), dozerInQueue
//    0x004F19D3 (35 bytes) and queueDozer 0x004F288C (349 bytes, vtable
//    +0x54): ZH's bodies over the dozer KindOf bit (template +0x109 & 0x40).
//    queueDozer walks TheThingFactory's template list (+0xC, next +0x484),
//    keeps ZH's priority WorkOrder team and debug message and calls
//    startTraining (+0x60) with the team's name. The WorkOrder and
//    TeamInQueue constructors are declared throw() because retail's
//    new-expressions carry no EH cleanup states.
//  - startTraining 0x004F2063 (370 bytes, vtable +0x60): ZH's factory
//    queueing and "Queuing ... for ..." message. BFME 2 refuses an order
//    whose flag +0x28 is set; when 0x002A8AB1 finds a record for the player
//    it instead asks the record (0x004EC088, kind 1) for each missing unit
//    of the team found by the order's id (+0x24), adds it to the team's
//    list at +4 (0x0055B156) and sets the flag. The factory path passes
//    findFactory's build index to queueCreateUnit (+0x20) and
//    requestUniqueUnitID (+0x08) takes BFME 2's four arguments.
//  - repairStructure 0x004F2F66 (94 bytes, vtable +0x38): ZH's two-entry
//    repair queue (+0x48, count +0x60) over the body module at +0x254.
//  - doUpgradesAndSkills 0x004F31B6 (519 bytes, vtable +0x4C): ZH's skillset
//    pick and science purchases. AISideInfo's five 0x54-byte skillsets start
//    at +0x14 and its next link is +0x1BC; the random pick passes
//    AIPlayer.cpp line 2961. Reading the side list through an inline
//    getAiData() gives retail's edi/esi assignment, and the one-character
//    appends inline StringBase<char>::concat(&c, 1) on the argument slot.
//  - selectTeamToBuild 0x004F35A5 (523 bytes, vtable +0x58): ZH's two
//    candidate lists over Player's team-prototype list at +0x32C, priority
//    +0x21C, home-location flag +0x1E8 and the random pick at AIPlayer.cpp
//    line 1841. The list base ctor/dtor are the pool copies 0x002AC026 and
//    0x002ABB44; the timer scales by TAiData's poor/wealthy mods +0x24/+0x1C.
//  - onUnitProduced 0x004F4962 (523 bytes, vtable +0x1C): BFME 1's matched
//    body (ZH plus the isMoving test before the goal-position push). BFME 2
//    hands the order's string and int (+0x20/+0x1C) to Object 0x00291298
//    before marking the order found. /D_CRTIMP= makes the inline vector
//    free a direct call, as retail has it.
//  - onStructureProduced 0x004F33EC (441 bytes, vtable +0x20): BFME 1's
//    matched body (ZH minus the hole search). The Dict keys are the
//    StaticNameKeys at VA 0x00DBDCC4 "objectName" (read the same way by
//    Object::updateObjValuesFromMapProperties 0x002951AB), 0x00DBDCD4 and
//    0x00DBDCFC; BuildListInfo's name getters are the folded by-value copies
//    of +4 (0x00564DF2) and +8 (0x000AF1DD). BFME 2 caches the building in
//    the script engine (0x0020A5FF) under an empty name.
//  - buildSpecificAITeam 0x004F2464 (1064 bytes, vtable +0x24): BFME 1's
//    matched body (ZH plus the rva004F13D8 shortcut before
//    isPossibleToBuildTeam and the two-name findTeam/createInactiveTeam).
//    BFME 2 also skips required units with a zero count, copies the unit
//    info's int, string and int (+0x08/+0x0C/+0x14) into each WorkOrder
//    (+0x1C/+0x20/+0x2C) with the optional flag +0x29, clears the
//    prototype's unit count (0x0039D761) when its flag +0x31D is set, stamps
//    the team id (+0x34) into every order after Team 0x0039D889(true), runs
//    the production script only when it has an action, and marks a
//    prototype with nothing buildable (+0x31C).
//  - WorkOrder::validateFactory 0x004F33BD (47 bytes): ZH's body unchanged;
//    it was rowed under a donor placeholder name in BfmeConv1001.cpp.
//  - queueUnits 0x004F46A9 (559 bytes): ZH's recruit-then-train walk. BFME 2
//    recruits with tryToRecruit's extra int from the order (+0x2C) and a
//    100000 radius without a home, calls tryToRecruit once per branch (the
//    two calls tail-merge into retail's shared push sequence), skips a null
//    AI, activates the team after each recruit, skips orders flagged +0x29
//    and validates the factory only when 0x002A8AB1 has no record for the
//    player. isWaitingToBuild is a count test written as an early return,
//    which keeps the recruit loop top-tested as retail has it.
//  - recruitSpecificAITeam 0x004F437E (811 bytes, vtable +0x28): ZH's body
//    with BFME 2's position argument (null means the prototype's home),
//    owner-and-name findTeam/createInactiveTeam, no home-position warning and
//    tryToRecruit's extra int from the unit info (+0x14); the two recruit
//    calls tail-merge as in queueUnits. A recruit moves to the given position
//    or, without one, the home location (else the team centroid from Team
//    0x0039DA2A). The disband deletes the team through its virtual
//    destructor and global delete.
//  - updateBridgeRepair 0x004F418A (500 bytes): ZH's body with the timer at
//    +0x68 reset from the frame-rate global, the repair order through
//    AICommandInterface 0x0036F19B (ZH aiRepair) and the return move adjusted
//    by TheAI's pathfinder (+0x10) over the AI's locomotor set (+0x1CC).
//    The first queue walk holds the count in a local that only guards the
//    shift loop, which is how retail keeps it in edi across the lookup; the
//    two Coord3D initialisations copy member-wise (movss) as retail does.
#include <list>
#include <vector>

// GameLogic comes from the canonical GameLogicObjectLookupView.h.
#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef float Real;
#define NULL 0

#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include <math.h>
class ThingTemplate;
class Player;
class Team;
template <class OBJCLASS> class DLINK_ITERATOR;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13,
	OBJECT_STATUS_RECONSTRUCTING = 0x15
};

template <int N>
class BitFlags
{
public:
	Bool any() const;
	Bool test(Int bit) const { return (m_bits[0] & (1 << bit)) != 0; }
	unsigned int m_bits[1];
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
	Int rva0033A69A(const Player *player, Int a, Int b) const;
	const AsciiString &getName() const { return m_name; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }
	unsigned char m_pad000[0x64];
	AsciiString m_name;				// +0x64
	unsigned char m_pad068[0xB0 - 0x68];
	Real m_boundingCircleRadius;			// +0xB0
	unsigned char m_padB4[0x109 - 0xB4];
	unsigned char m_kindOf109;			// +0x109, bit 0x40 = KINDOF_DOZER
	unsigned char m_pad10A[0x10F - 0x10A];
	unsigned char m_kindOf10F;			// +0x10F, bit 0x80 = factory
	unsigned char m_pad110[0x11B - 0x110];
	unsigned char m_bfme11B;			// +0x11B, bit 0x20 = free to build
	unsigned char m_pad11C[0x484 - 0x11C];
	ThingTemplate *m_nextThingTemplate;		// +0x484
	unsigned char m_pad488[0x633 - 0x488];
	unsigned char m_bfme633;			// +0x633
};

class Object;
enum BodyDamageType { BODY_PRISTINE = 0 };
class Rva0037EE4C
{
public:
	Int rva0037EE4C(const ThingTemplate *thing, Int a, Int b);
};
class Rva0037E6E8
{
public:
	Int rva0037E649(Int index, Object *obj);
};

enum ScienceType { SCIENCE_INVALID = -1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

class TeamPrototype;
// Retail calls the team list's base destructor (0x002ABB44) with no EH state
// transition before it, here and in Player at 0x002AE8BC, so cl saw it as
// nothrow; list<int>'s 0x004EC395 keeps the stores everywhere.
namespace _STL {
template <> inline _List_base<TeamPrototype *, allocator<TeamPrototype *> >::~_List_base() throw()
{
	clear();
	_M_node.deallocate(_M_node._M_data, 1);
}
}
typedef _STL::list<TeamPrototype *> PlayerTeamList;

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }
private:
	mutable NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_objectName;
extern const StaticNameKey TheKey_objectInitialHealth;
extern const StaticNameKey TheKey_objectUnsellable;

class Dict
{
public:
	Dict(Int numPairsToPreAllocate = 0);
	~Dict() { releaseData(); }
	void setBool(Int key, Bool value);
	void setInt(Int key, Int value);
	void setAsciiString(Int key, const AsciiString &value);
private:
	void releaseData();
	void *m_data;
};

class BuildListInfo
{
public:
	// getBuildingName and getTemplateName: retail calls the folded by-value
	// AsciiString copies of +4 and +8.
	AsciiString rva00564DF2() const;
	AsciiString rva000AF1DD() const;
	Int getHealth() const { return m_health; }
	Bool getUnsellable() const { return m_unsellable; }
	void setUnderConstruction(Bool construction) { m_underConstruction = construction; }
	BuildListInfo *getNext() const { return m_next; }
	const Coord3D *getLocation() const { return &m_location; }
	ObjectID getObjectID() const { return m_objectID; }
	Bool isSupplyBuilding() const { return m_isSupplyBuilding; }
	Int getDesiredGatherers() const { return m_desiredGatherers; }
	Int getCurrentGatherers() const { return m_currentGatherers; }
	void setCurrentGatherers(Int count) { m_currentGatherers = count; }

	unsigned char m_pad00[0x0C];
	Coord3D m_location;			// +0x0C
	unsigned char m_pad18[0x2C - 0x18];
	BuildListInfo *m_next;			// +0x2C
	unsigned char m_pad30[0x34 - 0x30];
	Int m_health;				// +0x34
	unsigned char m_pad38[0x39 - 0x38];
	Bool m_unsellable;			// +0x39
	unsigned char m_pad3A[0x45 - 0x3A];
	Bool m_underConstruction;		// +0x45
	Bool m_isSupplyBuilding;		// +0x46
	unsigned char m_pad47[0x48 - 0x47];
	ObjectID m_objectID;			// +0x48
	unsigned char m_pad4C[0x78 - 0x4C];
	Int m_desiredGatherers;			// +0x78
	Int m_currentGatherers;			// +0x7C
};

class Player
{
public:
	BuildListInfo *getBuildList() const { return m_buildList; }
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
	Int getSciencePurchasePoints() const { return m_sciencePurchasePoints; }
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
	const AsciiString &getSide() const { return m_side; }
	Bool isCapableOfPurchasingScience(ScienceType science) const;
	Bool attemptToPurchaseScience(ScienceType science);

	unsigned char m_pad000[0x24];
	Int m_sciencePurchasePoints;		// +0x24
	unsigned char m_pad028[0x50 - 0x28];
	NameKeyType m_playerNameKey;		// +0x50
	unsigned char m_pad054[0x58 - 0x54];
	AsciiString m_side;			// +0x58
	unsigned char m_pad05C[0x94 - 0x5C];
	unsigned int m_money;				// +0x94
	unsigned char m_pad098[0x278 - 0x98];
	BuildListInfo *m_buildList;		// +0x278
	unsigned char m_pad27C[0x2EC - 0x27C];
	Team *m_defaultTeam;			// +0x2EC
	unsigned char m_pad2F0[0x32C - 0x2F0];
	PlayerTeamList m_playerTeamPrototypes;	// +0x32C
	unsigned char m_pad330[0x338 - 0x330];
	Bool m_canBuildUnits;			// +0x338
	Bool getCanBuildUnits() const { return m_canBuildUnits; }
	void setCanBuildUnits(Bool canBuild) { m_canBuildUnits = canBuild; }
	unsigned char m_pad339[0x735 - 0x339];
	Bool m_bfme735;					// +0x735
	unsigned char m_pad736[0x738 - 0x736];
	union
	{
		Rva0037EE4C m_738;			// +0x738
		Rva0037E6E8 m_738b;
	};
};

class DozerAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Bool isTaskPending(int task);		// +0x18
	virtual void slot1c();
	virtual Bool isAnyTaskPending();		// +0x20
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual Bool isCurrentlyFerryingSupplies();	// +0x14
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void setForceWantingState(Bool forceWanting);	// +0x2C
	virtual Bool isForcedIntoWantingState();	// +0x30
};

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };

// The rowed wrapper at 0x0047971C takes the exit path by reference; its
// placeholder class is this vector of points.
class Rva0035149F : public _STL::vector<Coord3D>
{
};

class Object;

class LocomotorSet;

class AICommandInterface
{
public:
	void rva0047971C(const Rva0035149F &path, Object *ignoreObject, CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
	void rva0026C3AC(Object *obj, CommandSourceType cmdSource);
	void rva0036F19B(Object *obj, CommandSourceType cmdSource);	// ZH aiRepair
};

class StateMachine
{
public:
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }

	unsigned char m_pad00[0x24];
	Coord3D m_goalPosition;			// +0x24
};

class AIUpdateInterface
{
public:
	// The AICommandInterface base sits at +0x20.
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)((const char *)this + 0x1CC); }
	Bool isMoving() const;
	StateMachine *getStateMachine() const { return m_stateMachine; }
	const Coord3D *getGoalPosition() const { return getStateMachine()->getGoalPosition(); }

	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual void slot0dc();
	virtual void slot0e0();
	virtual void slot0e4();
	virtual void slot0e8();
	virtual void slot0ec();
	virtual void slot0f0();
	virtual void slot0f4();
	virtual void slot0f8();
	virtual void slot0fc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13c();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14c();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15c();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16c();
	virtual void slot170();
	virtual DozerAIInterface *getDozerAIInterface();		// +0x174
	virtual void slot178();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();	// +0x17C
	virtual void slot180();
	virtual void slot184();
	virtual void slot188();
	virtual void slot18c();
	virtual void slot190();
	virtual void slot194();
	virtual void slot198();
	virtual void joinTeam();					// +0x19C
	virtual void slot1a0();
	virtual void slot1a4();
	virtual void slot1a8();
	virtual void slot1ac();
	virtual void slot1b0();
	virtual void slot1b4();
	virtual Bool isIdle() const;					// +0x1B8

	unsigned char m_pad004[0x30 - 0x04];
	StateMachine *m_stateMachine;			// +0x30
	unsigned char m_pad034[0x3BE - 0x34];
	Bool m_bfme3BE;					// +0x3BE
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual BodyDamageType getDamageState() const;	// +0x20
};

class Object
{
public:
	Player *getControllingPlayer() const;
	BodyModuleInterface *getBodyModule() const { return m_body; }
	ObjectID getID() const { return m_id; }
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BC58(Int which);
	AIUpdateInterface *getAI() const { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOfDozer() const { return (getTemplate()->m_kindOf109 & 0x40) != 0; }
	void setTeam(Team *team);
	void rva00291298(AsciiString name, Int value);
	void updateObjValuesFromMapProperties(Dict *properties);
	void setStatus(ObjectStatusTypes status, Bool set);
	void clearStatus(ObjectStatusTypes status) { setStatus(status, false); }

	void *m_vtable;
	ThingTemplate *m_template;			// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;					// +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id;					// +0x74
	unsigned char m_pad078[0x8C - 0x78];
	Object *m_next;					// +0x8C
	unsigned char m_pad090[0x1C8 - 0x90];
	BitFlags<11> m_disabledMask;			// +0x1C8
	unsigned char m_pad1CC[0x254 - 0x1CC];
	BodyModuleInterface *m_body;			// +0x254
	AIUpdateInterface *m_ai;			// +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team;					// +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus;			// +0x438
};

class BuildAssistant
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual Bool isPossibleToMakeUnit(Object *factory, const ThingTemplate *thing, Int buildIndex);	// +0x64
};
extern BuildAssistant *TheBuildAssistant;

class ProductionEntry
{
public:
	void *m_vtable;
	Int m_type;
	ThingTemplate *m_thing;
};

class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Int requestUniqueUnitID(Int a, Int b, const AsciiString &name, Int d);	// +0x08
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual Bool queueCreateUnit(const ThingTemplate *unitType, Int quantity, Int productionID);	// +0x20
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Int getProductionCount() const;		// +0x44
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual ProductionEntry *firstProduction() const;	// +0x54
};

class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString &);};
extern ThingFactory *TheThingFactory;

struct Rva002A8AB1Record
{
	void *rva004EC088(Int kind, void *list, const void *name);
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

enum { MAX_KEY_SKILLS = 20 };
struct TSkillSet
{
	Int m_numSkills;
	ScienceType m_skills[MAX_KEY_SKILLS];
};

class AISideInfo
{
public:
	void *m_vtable;
	AsciiString m_side;			// +0x04
	Int m_easy;				// +0x08
	Int m_normal;				// +0x0C
	Int m_hard;				// +0x10
	TSkillSet m_skillSet1;			// +0x14
	TSkillSet m_skillSet2;			// +0x68
	TSkillSet m_skillSet3;			// +0xBC
	TSkillSet m_skillSet4;			// +0x110
	TSkillSet m_skillSet5;			// +0x164
	AsciiString m_baseDefenseStructure1;	// +0x1B8
	AISideInfo *m_next;			// +0x1BC
};

struct TAiData
{
	char m_pad000[0x0C];
	unsigned int m_resourcesWealthy;	// +0x0C
	unsigned int m_resourcesPoor;	// +0x10
	char m_pad014[0x1C - 0x14];
	Real m_teamWealthyMod;		// +0x1C
	char m_pad020[0x24 - 0x20];
	Real m_teamPoorMod;		// +0x24
	float m_teamResourcesToBuild;	// +0x28
	char m_pad02C[0x5C - 0x2C];
	Real m_maxRecruitDistance;	// +0x5C
	char m_pad060[0xF4 - 0x60];
	AISideInfo *m_sideInfo;		// +0xF4
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// The rowed body at 0x001FF5F2 under its pinned address spelling
// (Zero Hour's getInternalNameForScience).
class ScienceStore
{
public:
	AsciiString rva001FF5F2(ScienceType science) const;
};
extern ScienceStore *TheScienceStore;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Pathfinder
{
public:
	Bool adjustToPossibleDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
	char m_pad14[0x18 - 0x14];
	TAiData *m_aiData;		// +0x18
	const TAiData *getAiData() const { return m_aiData; }
	Pathfinder *pathfinder() { return m_pathfinder; }
};
extern AI *TheAI;

struct TCreateUnitsInfo
{
	Int minUnits;			// +0x00
	Int maxUnits;			// +0x04
	Int m_08;			// +0x08
	AsciiString m_bfmeString0C;	// +0x0C
	AsciiString unitThingName;	// +0x10
	Int m_14;			// +0x14
};

#include "Common/Snapshot.h"
class TeamTemplateInfo:public Snapshot {
public:
 TCreateUnitsInfo m_unitsInfo[7];Int m_numUnitsInfo;Coord3D m_homeLocation;Bool m_hasHomeLocation;
 char m_padBD[0xE7-0xBD];Bool m_automaticallyReinforce;char m_padE8[0xEC-0xE8];Int m_maxInstances;mutable Int m_productionPriority;
};
class TeamPrototype
{
public:
	const TeamTemplateInfo *getTemplateInfo()const{return (const TeamTemplateInfo *)((const char *)this+0x12c);}
	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const { return m_name; }
	Bool getIsSingleton() const { return (m_flags & 1) != 0; }
	void rva0039D761();		// clears m_numUnitsInfo

	const AsciiString &getOwnerName() const { return m_owner; }
	const AsciiString &getProductionCondition() const { return m_productionCondition; }
	Bool getExecuteActions() const { return m_executeActions; }

	char m_pad000[0x10];
	AsciiString m_owner;			// +0x10
	AsciiString m_name;			// +0x14
	Int m_flags;				// +0x18
	char m_pad01C[0x130 - 0x1C];
	TCreateUnitsInfo m_unitsInfo[7];	// +0x130
	Int m_numUnitsInfo;			// +0x1D8
	Coord3D m_homeLocation;			// +0x1DC
	Bool m_hasHomeLocation;			// +0x1E8
	char m_pad1E9[0x210 - 0x1E9];
	Bool m_bfme210;				// +0x210
	char m_pad211[2];
	Bool m_automaticallyReinforce; // +0x213
	char m_pad214[0x218 - 0x214];
	Int m_maxInstances;			// +0x218
	Int m_productionPriority;		// +0x21C
	char m_pad220[0x23C - 0x220];
	AsciiString m_productionCondition;	// +0x23C
	Bool m_executeActions;			// +0x240
	char m_pad241[0x31C - 0x241];
	Bool m_bfme31C;				// +0x31C
	Bool m_bfme31D;				// +0x31D
	char m_pad31E[0x334-0x31E];Team *m_teamInstances;
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
};

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

// BFME2's team-member iterator is a 24-byte object returned through a hidden
// pointer by Team::iterate_TeamMemberList (0x263864); advance is out of line
// at 0x263526.
template <> class DLINK_ITERATOR<Object>
{
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
private:
	Object *m_cur;
	unsigned char m_state[20];
};

class TeamPoolView {public:virtual ~TeamPoolView();};
#include "Common/Snapshot.h"
class Rva0055B156:public Snapshot
{
public:
	void rva0055B156(int val);
};

class Team:public TeamPoolView,public Rva0055B156
{
public:
	virtual ~Team();
	Rva0055B156 *getSnapshotView(){return this;}
	char m_pad008[0x30 - 0x08];
	TeamPrototype *m_proto;			// +0x30
	unsigned int m_id;			// +0x34
	Object *m_firstMember;
	char m_pad03C[0x5D - 0x3C];
	Bool m_active;				// +0x5D
	Bool m_created;				// +0x5E
	char m_pad05F[0x110 - 0x5F];
	Bool m_bfme110;				// +0x110
	Bool m_bfme111;				// +0x111

	Team *dlink_next_TeamInstanceList() const;
	Bool rva0039DEC4();
	void countObjectsByThingTemplate(Int,const ThingTemplate *const *,Bool,Int *,Bool) const;
	Object *getFirstItemIn_TeamMemberList() const {return m_firstMember;}
	void rva0039D889(Bool flag);
	void disband();
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *pos, Real maxDist, Int a, Int b, Int c);
	Bool rva0039DFF8();
	Bool hasAnyObjects(Bool ignoreBuilding);
	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	const AsciiString &getOwnerName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getOwnerName(); }
	const AsciiString &getName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getName(); }
	TeamPrototype *getPrototype() const { return m_proto; }
	void rva0039DA2A(Coord3D *center) const;
	__forceinline void deleteInstance() { ::delete this; }
};

class WorkOrder
{
public:
	WorkOrder() throw();
	virtual void v00();

	const ThingTemplate *m_thing;		// +0x04
	ObjectID m_factoryID;			// +0x08
	WorkOrder *m_next;			// +0x0C
	Int m_numCompleted;			// +0x10
	Int m_numRequired;			// +0x14
	Bool m_required;			// +0x18
	Bool m_isResourceGatherer;		// +0x19
	Int m_bfmeInt1C;			// +0x1C
	AsciiString m_bfmeString20;		// +0x20
	unsigned int m_bfmeUnsigned24;		// +0x24
	Bool m_bfmeFlag28;			// +0x28
	Bool m_bfmeFlag29;			// +0x29
	Int m_bfmeInt2C;			// +0x2C

	Bool isWaitingToBuild() const { if (m_numCompleted >= m_numRequired) return false; return true; }
	void validateFactory(Player *thisPlayer);
};

class TeamInQueue
{
public:
	TeamInQueue() throw();
	virtual ~TeamInQueue();
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_next; }
	TeamInQueue *dlink_next_TeamReadyQueue() const { return m_nextReady; }
	Bool isBuildTimeExpired();
	Bool isMinimumBuilt();
	Bool areBuildsComplete();
	Bool isAllBuilt();
	Bool includesADozer();
	void disband() { if (m_team) m_team->disband(); }
	__forceinline void deleteInstance() { ::delete this; }

	TeamInQueue *m_prev;			// +0x04
	TeamInQueue *m_next;			// +0x08
	TeamInQueue *m_prevReady;		// +0x0C
	TeamInQueue *m_nextReady;		// +0x10
	WorkOrder *m_workOrders;		// +0x14
	Bool m_priorityBuild;			// +0x18
	char m_pad19[0x1C - 0x19];
	Team *m_team;				// +0x1C
	char m_pad20[0x24 - 0x20];
	unsigned int m_frameStarted;		// +0x24
	Bool m_sentToStartLocation;		// +0x28
	char m_pad29;
	Bool m_reinforcement;			// +0x2A
	char m_pad2B;
	ObjectID m_reinforcementID;		// +0x2C
};

class GlobalData
{
public:
	char m_pad000[0x9B8];
	Int m_debugAI;				// +0x9B8
};
extern GlobalData *TheWritableGlobalData;
extern int g_Va00DBA4E4;
#define LOGICFRAMES_PER_SECOND g_Va00DBA4E4

class Script
{
public:
	void *getAction() const { return m_action; }
private:
	char m_pad00[0x34];
	void *m_action;				// +0x34
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
	void addObjectToCache(Object *obj, const AsciiString &name);
	Script *rva003573C4(const AsciiString &owner, const AsciiString &name, AsciiString *outName);
	void rva0020D451(AsciiString &scope, void *action, Script *script, const AsciiString &scriptName, int flags);
};
extern ScriptEngine *TheScriptEngine;

enum { MAX_STRUCTURES_TO_REPAIR = 2 };

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
public:
	virtual void update();						// +0x14
protected:
	virtual void slot06();
public:
	virtual void onUnitProduced(Object *factory, Object *unit);	// +0x1C
	virtual void onStructureProduced(Object *factory, Object *bldg);	// +0x20
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);	// +0x24
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius, const Coord3D *pos);	// +0x28
	virtual Bool isSkirmishAI();					// +0x2C
protected:
	virtual void slot12();
	virtual void slot13();
public:
	virtual void repairStructure(ObjectID structure);		// +0x38
protected:
	virtual void slot15();
	virtual void checkReadyTeams();					// +0x40
	virtual void checkQueuedTeams();				// +0x44
	virtual void doTeamBuilding();					// +0x48
	virtual void doUpgradesAndSkills();				// +0x4C
	virtual Object *findDozer(const Coord3D *searchPosition);	// +0x50
	virtual void queueDozer();					// +0x54
	virtual Bool selectTeamToBuild();				// +0x58
	virtual Bool selectTeamToReinforce(Int minPriority);		// +0x5C
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);	// +0x60
	virtual Bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);	// +0x64

	Object *findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex);
	Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney);
	Bool rva004F13D8(TeamPrototype *proto);
	Bool dozerInQueue();
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
	void computeCenterAndRadiusOfBase(Coord3D *center, Real *radius);
	Bool getBaseCenter(Coord3D *pos) const { *pos = m_baseCenter; return m_baseCenterSet; }
	void queueSupplyTruck();
	void queueUnits();
	void updateBridgeRepair();
	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}
	DLINK_ITERATOR<TeamInQueue> iterate_TeamReadyQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamReadyQueue, &TeamInQueue::dlink_next_TeamReadyQueue);
	}

public:
	void removeFrom_TeamBuildQueue(TeamInQueue *team);
	void prependTo_TeamReadyQueue(TeamInQueue *team);
	void removeFrom_TeamReadyQueue(TeamInQueue *team);
	void prependTo_TeamBuildQueue(TeamInQueue *team);
	void reverse_TeamBuildQueue();

private:
	TeamInQueue *m_teamBuildQueue;	// +0x04
	TeamInQueue *m_teamReadyQueue;	// +0x08
	Player *m_player;		// +0x0C
	Bool m_readyToBuildTeam;	// +0x10
	Int m_teamTimer;		// +0x14
	Int m_structureTimer;		// +0x18
	Int m_teamSeconds;		// +0x1C
	Int m_buildDelay;		// +0x20
	Int m_teamDelay;		// +0x24
	unsigned char m_pad28[0x30 - 0x28];
	Int m_skillsetSelector;		// +0x30
	Coord3D m_baseCenter;		// +0x34
	Bool m_baseCenterSet;		// +0x40
	unsigned char m_pad41[0x48 - 0x41];
	ObjectID m_structuresToRepair[MAX_STRUCTURES_TO_REPAIR];	// +0x48
	ObjectID m_repairDozer;		// +0x50
	Coord3D m_repairDozerOrigin;	// +0x54
	Int m_structuresInQueue;	// +0x60
	Bool m_dozerQueuedForRepair;	// +0x64
	Bool m_dozerIsRepairing;	// +0x65
	Int m_bridgeTimer;		// +0x68
};

enum { DOZER_TASK_BUILD = 0 };

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const {return DLINK_ITERATOR<Team>(m_teamInstances,&Team::dlink_next_TeamInstanceList);}

Bool AIPlayer::selectTeamToReinforce( Int minPriority )
{
	// Find a high production priority team that needs reinforcements.
	PlayerTeamList::const_iterator t;
	Team *curTeam = NULL;
	Int curPriority = minPriority;Int recruitType=-1; // Don't reinforce a team unless it is above min priority.
	const ThingTemplate *curThing = NULL;
	for (t = m_player->getPlayerTeams()->begin(); t != m_player->getPlayerTeams()->end(); ++t)
	{
		TeamPrototype *proto = (*t);
		Bool busy = false;
		for ( DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team->getPrototype() == proto) {
				busy = true; // currently building one of these.
			}
		}
		if (busy) continue;
		if (proto->getTemplateInfo()->m_automaticallyReinforce && proto->getTemplateInfo()->m_productionPriority>curPriority) {
			// Check the team instances.
			for (DLINK_ITERATOR<Team> iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
			{
				Team *team = iter.cur();
				if (team->rva0039DEC4() == false) 
				{
					continue; // empty.
				}
				const TCreateUnitsInfo *unitInfo = &team->getPrototype()->getTemplateInfo()->m_unitsInfo[0];
				for( int i=0; i<team->getPrototype()->getTemplateInfo()->m_numUnitsInfo; i++ )
				{
					if (unitInfo[i].maxUnits < 1) continue;
					const ThingTemplate *thing = TheThingFactory->findTemplate( unitInfo[i].unitThingName );
					if (thing==NULL) continue;
					Int count=0;
					team->countObjectsByThingTemplate(1, &thing, false, &count, true);
					if (count < unitInfo[i].maxUnits) 
					{
						// See if there is a factory available.
						if (NULL != findFactory(thing, false, NULL)) 
						{
							curTeam = team;
							curPriority = proto->getTemplateInfo()->m_productionPriority;
							curThing = thing;recruitType=unitInfo[i].m_14;
						}
					}
				}				
			}
		}
	}
	if (curTeam && curThing) 
	{
		/* We have something to build. */
		TeamInQueue *teamQ=NULL;WorkOrder *order=NULL;
	if(!(m_player?g_00DFEEF8:g_00DFEEF8)->rva002A8AB1(m_player)){
	teamQ = new TeamInQueue;
		// Put in front of queue.
		prependTo_TeamBuildQueue(teamQ);
		teamQ->m_priorityBuild = false;
		teamQ->m_reinforcement = true;

		order = new WorkOrder;
		order->m_thing = curThing;
		order->m_factoryID = (ObjectID)0;
		order->m_numRequired = 1;
		order->m_required = true;
		// prepend to head of list
		order->m_next = NULL;
		teamQ->m_workOrders = order;
		teamQ->m_frameStarted = TheGameLogic->getFrame();
		teamQ->m_team = curTeam; 

		AsciiString teamName = curTeam->getPrototype()->getName();
		teamName.concat(" - AutoReinforcing one ");
		teamName.concat(curThing->getName());
		TheScriptEngine->AppendDebugMessage(teamName, false);
	}

		// start the creation of a new unit
		Coord3D origin;
		origin = curTeam->getPrototype()->getTemplateInfo()->m_homeLocation;
		if (curTeam->getFirstItemIn_TeamMemberList()) 
		{
			origin = curTeam->getFirstItemIn_TeamMemberList()->m_pos;
		}
		Object *unit = curTeam->tryToRecruit(curThing, &origin, TheAI->getAiData()->m_maxRecruitDistance,recruitType,0,0);
		if (unit) 
		{
			if(order)order->m_numCompleted = 1;

			AsciiString teamStr = "Team '";
			teamStr.concat(curTeam->getPrototype()->getName());
			teamStr.concat("' recruits ");
			teamStr.concat(curThing->getName());
			teamStr.concat(" from team '");
			teamStr.concat(unit->m_team->getPrototype()->getName());
			teamStr.concat("'");
			TheScriptEngine->AppendDebugMessage(teamStr, false);

			unit->setTeam(curTeam);

			if(teamQ)teamQ->m_reinforcementID = unit->getID();

			AIUpdateInterface *ai = unit->m_ai;
			if (ai) 
			{
				ai->getCommandInterface()->aiIdle(CMD_FROM_AI);
			}
		} else if(!g_00DFEEF8->rva002A8AB1(m_player)){
			startTraining( order, teamQ->m_priorityBuild, teamQ->m_team->getName());
		}
		m_teamDelay = 0;
		return true;
	}
	return false;
}

