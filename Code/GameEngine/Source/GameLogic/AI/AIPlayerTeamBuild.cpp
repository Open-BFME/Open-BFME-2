// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <list>
#include <vector>

// GameLogic comes from the canonical GameLogicObjectLookupView.h.
#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef float Real;
#define NULL 0

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class ThingTemplate;
class Player;
class Team;

#include "../../Common/GameLogicObjectLookupView.h"
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
	ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }
	unsigned char m_pad000[0x64];
	AsciiString m_name;				// +0x64
	unsigned char m_pad068[0x109 - 0x68];
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
	ObjectID getObjectID() const { return m_objectID; }
	Bool isSupplyBuilding() const { return m_isSupplyBuilding; }
	Int getDesiredGatherers() const { return m_desiredGatherers; }
	Int getCurrentGatherers() const { return m_currentGatherers; }
	void setCurrentGatherers(Int count) { m_currentGatherers = count; }

	unsigned char m_pad00[0x2C];
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

class AICommandInterface
{
public:
	void rva0047971C(const Rva0035149F &path, Object *ignoreObject, CommandSourceType cmdSource);
	void rva0026C3AC(Object *obj, CommandSourceType cmdSource);
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

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
	const ThingTemplate *findTemplate(const AsciiString &name) { return (const ThingTemplate *)rva002D06CA(&name); }
	ThingTemplate *firstTemplate() const { return m_firstTemplate; }
private:
	char m_pad00[0x0C];
	ThingTemplate *m_firstTemplate;		// +0x0C
};
extern Rva002D06CA *TheThingFactory;

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
	char m_pad02C[0xF4 - 0x2C];
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

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData;		// +0x18
	const TAiData *getAiData() const { return m_aiData; }
};
extern AI *TheAI;

struct TCreateUnitsInfo
{
	Int minUnits;			// +0x00
	Int maxUnits;			// +0x04
	Int m_08;
	Int m_0C;
	AsciiString unitThingName;	// +0x10
	Int m_14;
};

class TeamPrototype
{
public:
	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const { return m_name; }

	const AsciiString &getOwnerName() const { return m_owner; }
	const AsciiString &getProductionCondition() const { return m_productionCondition; }
	Bool getExecuteActions() const { return m_executeActions; }

	char m_pad000[0x10];
	AsciiString m_owner;			// +0x10
	AsciiString m_name;			// +0x14
	char m_pad018[0x130 - 0x18];
	TCreateUnitsInfo m_unitsInfo[7];	// +0x130
	Int m_numUnitsInfo;			// +0x1D8
	Coord3D m_homeLocation;			// +0x1DC
	Bool m_hasHomeLocation;			// +0x1E8
	char m_pad1E9[0x210 - 0x1E9];
	Bool m_bfme210;				// +0x210
	char m_pad211[0x218 - 0x211];
	Int m_maxInstances;			// +0x218
	Int m_productionPriority;		// +0x21C
	char m_pad220[0x23C - 0x220];
	AsciiString m_productionCondition;	// +0x23C
	Bool m_executeActions;			// +0x240
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

class Rva0055B156
{
public:
	void rva0055B156(int val);
};

class Team
{
public:
	char m_pad000[0x04];
	Rva0055B156 m_bfme04;			// +0x04
	char m_pad005[0x30 - 0x05];
	TeamPrototype *m_proto;			// +0x30
	char m_pad034[0x5D - 0x34];
	Bool m_active;				// +0x5D
	Bool m_created;				// +0x5E
	char m_pad05F[0x110 - 0x5F];
	Bool m_bfme110;				// +0x110
	Bool m_bfme111;				// +0x111

	void rva0039D889(Bool flag);
	void disband();
	Bool rva0039DFF8();
	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	const AsciiString &getOwnerName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getOwnerName(); }
	const AsciiString &getName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getName(); }
	TeamPrototype *getPrototype() const { return m_proto; }
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
	virtual void slot05();
	virtual void slot06();
public:
	virtual void onUnitProduced(Object *factory, Object *unit);	// +0x1C
	virtual void onStructureProduced(Object *factory, Object *bldg);	// +0x20
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);	// +0x24
protected:
	virtual void slot10();
public:
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
	virtual void slot18();
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
	unsigned char m_pad34[0x48 - 0x34];
	ObjectID m_structuresToRepair[MAX_STRUCTURES_TO_REPAIR];	// +0x48
	ObjectID m_repairDozer;		// +0x50
	Coord3D m_repairDozerOrigin;	// +0x54
	Int m_structuresInQueue;	// +0x60
	Bool m_dozerQueuedForRepair;	// +0x64
};

enum { DOZER_TASK_BUILD = 0 };

Object *AIPlayer::findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex)
{
	Object *busyFactory = NULL;
	if (thing == NULL)
		return NULL;
	if (buildIndex != NULL)
		*buildIndex = -1;

	for (Object *factory = TheGameLogic->getFirstObject(); factory != NULL; factory = factory->m_next)
	{
		if (factory->getControllingPlayer() != m_player)
			continue;
		if ((factory->m_template->m_kindOf10F & 0x80) == 0)
			continue;
		if (factory->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			continue;
		if (factory->testStatus(OBJECT_STATUS_SOLD))
			continue;
		if (factory->m_disabledMask.any())
			continue;
		ProductionUpdateInterface *production = (ProductionUpdateInterface *)factory->rva0028BC58(0);
		if (production == NULL)
			continue;
		if (factory->m_privateStatus & 1)
			continue;

		Player *owner = factory->getControllingPlayer();
		Int index = owner->m_738.rva0037EE4C(thing, -1, 0);
		if (index != -1)
		{
			if (!TheBuildAssistant->isPossibleToMakeUnit(factory, NULL, index))
				continue;
			if (buildIndex != NULL)
				*buildIndex = index;
		}
		else if (!TheBuildAssistant->isPossibleToMakeUnit(factory, thing, -1))
			continue;

		if (production->getProductionCount() <= 0)
			return factory;
		if (m_player->m_bfme735)
		{
			ProductionEntry *entry = production->firstProduction();
			if (entry != NULL)
			{
				switch (entry->m_type)
				{
				case 1:
				case 3:
					ThingTemplate *entryThing = entry->m_thing;
					if (entryThing != NULL && entryThing->m_bfme633 && !thing->isEquivalentTo(entryThing))
						return factory;
				}
			}
		}
		if (busyOK)
			busyFactory = factory;
	}
	return busyOK ? busyFactory : NULL;
}

Bool AIPlayer::isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney)
{
	if (g_00DFEEF8->rva002A8AB1(m_player) != NULL)
		return true;

	notEnoughMoney = false;
	Bool anyIdle = false;
	Int cost = 0;
	for (Int i = 0; i < proto->m_numUnitsInfo; ++i)
	{
		const ThingTemplate *thing = (const ThingTemplate *)TheThingFactory->rva002D06CA(&proto->m_unitsInfo[i].unitThingName);
		if (thing == NULL)
			continue;
		if (findFactory(thing, true, NULL) == NULL)
			return false;
		Int buildIndex;
		if (findFactory(thing, false, &buildIndex) != NULL)
			anyIdle = true;
		Int thingCost;
		if (buildIndex == -1)
			thingCost = thing->rva0033A69A(m_player, 0, -1);
		else
			thingCost = m_player->m_738b.rva0037E649(buildIndex, NULL);
		if (thing->m_bfme11B & 0x20)
			thingCost = 0;
		cost = (Int)(cost + thingCost * ((float)(proto->m_unitsInfo[i].maxUnits + proto->m_unitsInfo[i].minUnits) * 0.5f));
	}
	cost = (Int)((float)cost * TheAI->m_aiData->m_teamResourcesToBuild);
	if (m_player->m_money < (unsigned int)cost)
	{
		notEnoughMoney = true;
		return false;
	}
	if (anyIdle)
		return true;
	if (!requireIdleFactory)
		return true;
	return false;
}

Object *AIPlayer::findDozer(const Coord3D *searchPosition)
{
	Object *candidateObject;
	Object *fallbackDozer = NULL;
	Bool shouldQueueDozer = true;
	Object *closestIdleDozer = NULL;
	Real closestIdleDistanceSquared = 0;

	for (candidateObject = TheGameLogic->getFirstObject(); candidateObject;
		candidateObject = candidateObject->m_next)
	{
		Player *candidateOwner = candidateObject->getControllingPlayer();
		if (candidateOwner == m_player)
		{
			const ThingTemplate *candidateTemplate = candidateObject->m_template;
			if ((candidateTemplate->m_kindOf109 & 0x40) != 0)
			{
				AIUpdateInterface *candidateAI = candidateObject->m_ai;
				if (candidateAI == NULL)
					continue;

				DozerAIInterface *dozerInterface = candidateAI->getDozerAIInterface();
				if (dozerInterface)
				{
					SupplyTruckAIInterface *supplyTruckInterface =
						candidateAI->getSupplyTruckAIInterface();
					if (!dozerInterface->isAnyTaskPending() && supplyTruckInterface)
					{
						if (supplyTruckInterface->isCurrentlyFerryingSupplies()
							|| supplyTruckInterface->isForcedIntoWantingState())
							continue;
					}
					if (candidateObject->m_id == m_repairDozer)
						continue;
					shouldQueueDozer = false;
					if (dozerInterface->isTaskPending(DOZER_TASK_BUILD))
						continue;
					if (!dozerInterface->isAnyTaskPending())
						fallbackDozer = candidateObject;
					if (fallbackDozer == NULL)
						fallbackDozer = candidateObject;
					if (fallbackDozer && !dozerInterface->isAnyTaskPending())
					{
						Real dozerDistanceSquared;
						Real deltaX = searchPosition->x - fallbackDozer->m_pos.x;
						Real deltaY = searchPosition->y - fallbackDozer->m_pos.y;
						dozerDistanceSquared = deltaX * deltaX + deltaY * deltaY;
						if (closestIdleDozer == NULL)
						{
							closestIdleDozer = fallbackDozer;
							closestIdleDistanceSquared = dozerDistanceSquared;
						}
						else if (dozerDistanceSquared < closestIdleDistanceSquared)
						{
							closestIdleDozer = fallbackDozer;
							closestIdleDistanceSquared = dozerDistanceSquared;
						}
					}
				}
			}
		}
	}
	if (shouldQueueDozer)
		queueDozer();
	if (closestIdleDozer)
		return closestIdleDozer;
	return fallbackDozer;
}

Bool TeamInQueue::includesADozer()
{
	WorkOrder *order;
	for (order = m_workOrders; order; order = order->m_next)
	{
		if ((order->m_thing->m_kindOf109 & 0x40) && !order->m_isResourceGatherer)
			return true;
	}
	return false;
}

Bool AIPlayer::rva004F13D8(TeamPrototype *proto)
{
	const TCreateUnitsInfo *unitInfo = &proto->m_unitsInfo[0];
	Bool result = true;
	float totalCost = 0.0f;
	for (Int i = 0; i < proto->m_numUnitsInfo; ++i)
	{
		const ThingTemplate *thing = (const ThingTemplate *)TheThingFactory->rva002D06CA(&unitInfo[i].unitThingName);
		if (unitInfo[i].maxUnits <= 0)
			continue;

		Int count = 0;
		for (Object *object = TheGameLogic->getFirstObject(); object; object = object->m_next)
		{
			if (!object->m_template->isEquivalentTo(thing))
				continue;
			if (object->getControllingPlayer() != m_player)
				continue;

			Team *team = object->m_team;
			Bool eligible = false;
			if (team == m_player->m_defaultTeam)
				eligible = true;
			if (!team->m_active)
				continue;
			if (team->m_proto->m_bfme210)
				eligible = true;
			if (team->m_bfme110)
				eligible = team->m_bfme111;
			if (!eligible)
				continue;
			if (object->m_ai && !object->m_ai->m_bfme3BE)
				continue;
			if (object->m_disabledMask.m_bits[0] & 8)
				continue;
			++count;
		}

		if (count >= unitInfo[i].minUnits)
			continue;
		Int buildIndex;
		if (!findFactory(thing, false, &buildIndex))
		{
			result = false;
			break;
		}
		Int thingCost;
		if (buildIndex == -1)
			thingCost = thing->rva0033A69A(m_player, 0, -1);
		else
			thingCost = m_player->m_738b.rva0037E649(buildIndex, NULL);
		totalCost += (float)((unitInfo[i].minUnits - count) * thingCost);
		if ((float)m_player->m_money < totalCost)
		{
			result = false;
			break;
		}
	}
	return result;
}

Bool AIPlayer::isAGoodIdeaToBuildTeam(TeamPrototype *proto)
{
	if (!proto->evaluateProductionCondition())
		return false;

	if (proto->countTeamInstances() >= proto->m_maxInstances)
		return false;

	for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		if (team->m_team->m_proto == proto)
			return false;
	}

	if (rva004F13D8(proto))
		return true;

	Bool needMoney;
	if (!isPossibleToBuildTeam(proto, true, needMoney))
	{
		if (TheWritableGlobalData->m_debugAI)
		{
			AsciiString str;
			if (needMoney)
				str.format("Team %s not chosen - Not enough money.", proto->getName().str());
			else
				str.format("Team %s not chosen - Factory/tech missing or busy.", proto->getName().str());
			TheScriptEngine->AppendDebugMessage(str, false);
		}
		return false;
	}
	return true;
}

void AIPlayer::checkQueuedTeams()
{
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team && team->isBuildTimeExpired())
			{
				if (team->isMinimumBuilt())
				{
					if (team->areBuildsComplete())
					{
						removeFrom_TeamBuildQueue(team);
						team->m_team->rva0039D889(false);
						prependTo_TeamReadyQueue(team);
					}
					else
					{
						continue;
					}
				}
				else
				{
					team->disband();
					removeFrom_TeamBuildQueue(team);
					team->deleteInstance();
				}
				iter = iterate_TeamBuildQueue();
			}
		}
	}

	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team && team->isAllBuilt())
			{
				removeFrom_TeamBuildQueue(team);
				team->m_team->rva0039D889(false);
				prependTo_TeamReadyQueue(team);
				iter = iterate_TeamBuildQueue();
				continue;
			}
			Bool anyIdle = false;
			for (DLINK_ITERATOR<Object> it = team->m_team->iterate_TeamMemberList(); !it.done(); it.advance())
			{
				Object *obj = it.cur();
				if (obj && obj->getAI() && obj->getAI()->isIdle())
					anyIdle = true;
			}
			if (anyIdle && team->m_team->getPrototype()->getExecuteActions())
			{
				AsciiString scope;
				const AsciiString &cond = team->m_team->getPrototype()->getProductionCondition();
				Script *script = TheScriptEngine->rva003573C4(team->m_team->getOwnerName(), cond, &scope);
				if (script)
					TheScriptEngine->rva0020D451(scope, script->getAction(), script, cond, (int)team->m_team);
			}
		}
	}
}

Bool AIPlayer::dozerInQueue()
{
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team && team->includesADozer())
				return true;
		}
	}
	return false;
}

Bool AIPlayer::startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName)
{
	if (order->m_bfmeFlag28)
		return false;
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_player);
	if (record)
	{
		Team *team = TheTeamFactory->findTeamByID(order->m_bfmeUnsigned24);
		if (team)
		{
			for (Int i = order->m_numCompleted; i < order->m_numRequired; i++)
			{
				void *unit = record->rva004EC088(1, &team->m_bfme04, &order->m_thing->getName());
				if (unit)
					team->m_bfme04.rva0055B156((int)unit);
			}
		}
		order->m_bfmeFlag28 = true;
		return true;
	}
	Int buildIndex;
	Object *factory = findFactory(order->m_thing, busyOK, &buildIndex);
	if (factory)
	{
		ProductionUpdateInterface *pu = (ProductionUpdateInterface *)factory->rva0028BC58(0);
		if (pu && pu->getProductionCount() == 0)
		{
			if (pu->queueCreateUnit(order->m_thing, buildIndex, pu->requestUniqueUnitID(-1, 0, AsciiString::TheEmptyString, 0)))
			{
				order->m_factoryID = factory->m_id;
				if (TheWritableGlobalData->m_debugAI)
				{
					AsciiString teamStr = "Queuing ";
					teamStr.concat(order->m_thing->getName());
					teamStr.concat(" for ");
					teamStr.concat(teamName);
					TheScriptEngine->AppendDebugMessage(teamStr, false);
				}
				return true;
			}
		}
	}
	return false;
}

void AIPlayer::queueDozer()
{
	if (dozerInQueue())
		return;

	Bool canBuildUnits = m_player->getCanBuildUnits();
	m_player->setCanBuildUnits(true);
	const ThingTemplate *tTemplate = TheThingFactory->firstTemplate();
	while (tTemplate)
	{
		if (tTemplate->m_kindOf109 & 0x40)
		{
			Object *factory = findFactory(tTemplate, true, NULL);
			if (factory)
			{
				WorkOrder *order = new WorkOrder;
				order->m_thing = tTemplate;
				order->m_factoryID = INVALID_OBJECT_ID;
				order->m_numRequired = 1;
				order->m_required = true;
				order->m_isResourceGatherer = false;
				order->m_next = NULL;
				TeamInQueue *team = new TeamInQueue;
				prependTo_TeamBuildQueue(team);
				team->m_priorityBuild = true;
				team->m_workOrders = order;
				team->m_frameStarted = TheGameLogic->getFrame();
				team->m_team = m_player->m_defaultTeam;
				AsciiString teamName = "DOZER - building one at the ";
				teamName.concat(factory->m_template->getName());
				TheScriptEngine->AppendDebugMessage(teamName, false);
				m_teamDelay = 0;
				startTraining(order, team->m_priorityBuild, team->m_team->getName());
				break;
			}
		}
		tTemplate = tTemplate->friend_getNextTemplate();
	}
	m_player->setCanBuildUnits(canBuildUnits);
}

void AIPlayer::repairStructure(ObjectID structure)
{
	Object *structureObj = TheGameLogic->findObjectByID(structure);
	if (structureObj == NULL)
		return;
	if (structureObj->getBodyModule() == NULL)
		return;
	if (structureObj->getBodyModule()->getDamageState() == BODY_PRISTINE)
		return;
	Int i;
	for (i = 0; i < m_structuresInQueue; i++)
	{
		if (m_structuresToRepair[i] == structureObj->getID())
			return;
	}
	if (m_structuresInQueue == MAX_STRUCTURES_TO_REPAIR)
		return;
	m_structuresToRepair[m_structuresInQueue] = structureObj->getID();
	m_structuresInQueue++;
}

enum { INVALID_SKILLSET_SELECTION = -1 };

// Retail inlines the one-character append as StringBase<char>::concat(&c, 1).
static __forceinline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

void AIPlayer::doUpgradesAndSkills()
{
	if (TheGameLogic->getFrame() < 2)
		return;

	Bool checkScience = m_player->getSciencePurchasePoints() > 0;
	if (!checkScience)
		return;
	const AISideInfo *sideInfo = TheAI->getAiData()->m_sideInfo;
	while (sideInfo)
	{
		if (sideInfo->m_side == m_player->getSide())
			break;
		sideInfo = sideInfo->m_next;
	}
	if (sideInfo == NULL)
		return;

	if (m_skillsetSelector == INVALID_SKILLSET_SELECTION)
	{
		Int limit = 0;
		if (sideInfo->m_skillSet2.m_numSkills > 0)
		{
			limit = 1;
			if (sideInfo->m_skillSet3.m_numSkills > 0)
			{
				limit = 2;
				if (sideInfo->m_skillSet4.m_numSkills > 0)
				{
					limit = 3;
					if (sideInfo->m_skillSet5.m_numSkills > 0)
						limit = 4;
				}
			}
		}
		if (isSkirmishAI())
			m_skillsetSelector = GetGameLogicRandomValue(0, limit, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIPlayer.cpp", 2961);
		else
			m_skillsetSelector = 0;
	}

	if (m_player->getSciencePurchasePoints() > 0)
	{
		const TSkillSet *skillset;
		switch (m_skillsetSelector)
		{
		default:
		case 0: skillset = &sideInfo->m_skillSet1; break;
		case 1: skillset = &sideInfo->m_skillSet2; break;
		case 2: skillset = &sideInfo->m_skillSet3; break;
		case 3: skillset = &sideInfo->m_skillSet4; break;
		case 4: skillset = &sideInfo->m_skillSet5; break;
		}
		Int i;
		for (i = 0; i < skillset->m_numSkills; i++)
		{
			ScienceType science = skillset->m_skills[i];
			if (m_player->isCapableOfPurchasingScience(science))
			{
				if (m_player->attemptToPurchaseScience(science))
				{
					AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
					msg.concat(" purchases from SkillSet");
					concatChar(msg, (char)('1' + m_skillsetSelector));
					concatChar(msg, ' ');
					msg.concat(TheScienceStore->rva001FF5F2(science));
					msg.concat(".");
					TheScriptEngine->AppendDebugMessage(msg, false);
				}
			}
		}
	}
}

Bool AIPlayer::selectTeamToBuild()
{
	PlayerTeamList::const_iterator t;
	const Int invalidPri = -99999;
	Int hiPri = invalidPri;
	PlayerTeamList candidateList1;
	for (t = m_player->getPlayerTeams()->begin(); t != m_player->getPlayerTeams()->end(); ++t)
	{
		if (isAGoodIdeaToBuildTeam(*t))
		{
			candidateList1.push_back(*t);
			Int pri = (*t)->m_productionPriority;
			if (pri > hiPri)
				hiPri = pri;
		}
	}

	if (selectTeamToReinforce(hiPri))
		return true;

	if (hiPri == invalidPri)
		return false;

	if (TheWritableGlobalData->m_debugAI)
		TheScriptEngine->AppendDebugMessage("**AI** Selecting team to build", false);

	PlayerTeamList candidateList;
	Int count = 0;
	for (t = candidateList1.begin(); t != candidateList1.end(); ++t)
	{
		if ((*t)->m_productionPriority == hiPri)
		{
			candidateList.push_back(*t);
			count++;
		}
	}

	Int which = GetGameLogicRandomValue(0, count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIPlayer.cpp", 1841);

	TeamPrototype *teamProto = NULL;
	Int i = 0;
	for (t = candidateList.begin(); t != candidateList.end(); ++t)
	{
		if (i == which)
		{
			teamProto = *t;
			break;
		}
		i++;
	}
	if (teamProto)
	{
		if (!teamProto->m_hasHomeLocation && !isSkirmishAI())
		{
			AsciiString teamStr = "Error : team '";
			teamStr.concat(teamProto->getName());
			teamStr.concat("' has no Home Position (or Origin).");
			TheScriptEngine->AppendDebugMessage(teamStr, false);
		}
		buildSpecificAITeam(teamProto, false);
		m_readyToBuildTeam = false;
		m_teamTimer = m_teamSeconds * LOGICFRAMES_PER_SECOND;
		if (m_player->m_money < TheAI->getAiData()->m_resourcesPoor)
			m_teamTimer = m_teamTimer / TheAI->getAiData()->m_teamPoorMod;
		else if (m_player->m_money > TheAI->getAiData()->m_resourcesWealthy)
			m_teamTimer = m_teamTimer / TheAI->getAiData()->m_teamWealthyMod;
		return true;
	}
	return false;
}

void AIPlayer::checkReadyTeams()
{
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamReadyQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			Bool timeExpired = team->m_frameStarted + 60 * LOGICFRAMES_PER_SECOND < TheGameLogic->getFrame();
			Bool allIdle = true;
			Bool anyIdle = false;
			if (team->m_reinforcement)
			{
				Object *obj = TheGameLogic->findObjectByID(team->m_reinforcementID);
				if (obj && obj->getAI())
				{
					allIdle = obj->getAI()->isIdle();
					anyIdle = allIdle;
				}
			}
			else
			{
				allIdle = team->m_team->rva0039DFF8();
				for (DLINK_ITERATOR<Object> it = team->m_team->iterate_TeamMemberList(); !it.done(); it.advance())
				{
					Object *obj = it.cur();
					if (obj->getAI() && obj->getAI()->isIdle())
						anyIdle = true;
				}
			}
			if (anyIdle && team->m_team->getPrototype()->getExecuteActions())
			{
				Script *script = TheScriptEngine->rva003573C4(team->m_team->getOwnerName(), team->m_team->getPrototype()->getProductionCondition(), NULL);
				if (script && script->getAction())
					allIdle = true;
			}
			if (timeExpired)
				allIdle = true;
			if (allIdle)
			{
				if (!team->m_sentToStartLocation)
					team->m_sentToStartLocation = true;
				removeFrom_TeamReadyQueue(team);
				team->m_team->rva0039D889(false);
				if (team->m_reinforcement)
				{
					Object *obj = TheGameLogic->findObjectByID(team->m_reinforcementID);
					if (obj && obj->getAI())
						obj->getAI()->joinTeam();
				}
				else
				{
					team->m_team->setActive();
					if (TheWritableGlobalData->m_debugAI)
					{
						AsciiString teamName = team->m_team->getPrototype()->getName();
						teamName.concat(" - team activated.");
						TheScriptEngine->AppendDebugMessage(teamName, false);
					}
				}
				team->deleteInstance();
				iter = iterate_TeamReadyQueue();
			}
		}
	}
}

void AIPlayer::onUnitProduced(Object *factory, Object *unit)
{
	Bool found = false;
	Bool supplyTruck = false;

	// factory could be NULL at the start of the game.
	if (factory == NULL)
		return;

	for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		// find work order entry and delete it
		WorkOrder *order;
		if (found)
			break;
		for (order = team->m_workOrders; order; order = order->m_next)
		{
			if (order->m_factoryID == factory->getID() && order->m_numCompleted < order->m_numRequired &&
				unit->getTemplate()->isEquivalentTo(order->m_thing))
			{
				// found associated order, mark it complete.
				order->m_numCompleted++;
				// put new unit into the team under construction
				if (team->m_team)
					unit->setTeam(team->m_team);
				if (team->m_reinforcement)
					team->m_reinforcementID = unit->getID();
				AIUpdateInterface *ai = unit->getAI();
				if (team->m_team->getPrototype()->m_hasHomeLocation)
				{
					if (ai)
					{
						Rva0035149F path;
						if (ai->isMoving())
							path.push_back(*ai->getGoalPosition());
						path.push_back(team->m_team->getPrototype()->m_homeLocation);
						ai->getCommandInterface()->rva0047971C(path, NULL, CMD_FROM_AI);
					}
				}

				order->m_factoryID = INVALID_OBJECT_ID; // no longer using this factory.
				if (ai)
				{
					// tell it to start gathering resources.
					SupplyTruckAIInterface *supplyTruckAI = ai->getSupplyTruckAIInterface();
					if (supplyTruckAI)
					{
						if (order->m_isResourceGatherer)
							supplyTruck = true;
						else
							supplyTruck = false;
						supplyTruckAI->setForceWantingState(supplyTruck);
						if (supplyTruck)
						{
							// assign to a supply depot.
							for (BuildListInfo *info = m_player->getBuildList(); info; info = info->getNext())
							{
								if (info->isSupplyBuilding() && info->getDesiredGatherers() > 0 &&
									info->getDesiredGatherers() > info->getCurrentGatherers())
								{
									Object *obj = TheGameLogic->findObjectByID(info->getObjectID());
									if (obj)
									{
										info->setCurrentGatherers(info->getCurrentGatherers() + 1);
										ai->getCommandInterface()->rva0026C3AC(obj, CMD_FROM_PLAYER);
									}
								}
							}
						}
					}
				}
				unit->rva00291298(order->m_bfmeString20, order->m_bfmeInt1C);
				found = true;
				break;
			}
		}
	}
	if (!supplyTruck && unit->isKindOfDozer())
	{
		if (m_dozerQueuedForRepair)
		{
			m_repairDozer = unit->getID();
			m_dozerQueuedForRepair = false;
		}
		else
		{
			m_buildDelay = 0;
			m_structureTimer = 1;
		}
	}

	m_teamDelay = 0; // Cause the update queues & selection to happen immediately.
}

void AIPlayer::onStructureProduced(Object *factory, Object *bldg)
{
	m_teamDelay = 0;
	m_buildDelay = 0;
	BuildListInfo *info;
	for (info = m_player->getBuildList(); info; info = info->getNext())
	{
		if (info->getObjectID() != bldg->getID())
			continue;
		Dict d;
		d.setAsciiString(TheKey_objectName, info->rva00564DF2());
		d.setInt(TheKey_objectInitialHealth, info->getHealth());
		d.setBool(TheKey_objectUnsellable, info->getUnsellable());

		info->setUnderConstruction(false);
		bldg->updateObjValuesFromMapProperties(&d);
		bldg->clearStatus(OBJECT_STATUS_UNDER_CONSTRUCTION);
		bldg->clearStatus(OBJECT_STATUS_RECONSTRUCTING);

		TheScriptEngine->addObjectToCache(bldg, AsciiString(""));
		if (TheWritableGlobalData->m_debugAI)
		{
			AsciiString bldgName = bldg->getTemplate()->getName();
			bldgName.concat(" - Building completed.");
			TheScriptEngine->AppendDebugMessage(bldgName, false);
		}
		checkForSupplyCenter(info, bldg);
		return;
	}

	for (info = m_player->getBuildList(); info; info = info->getNext())
	{
		const ThingTemplate *bldgPlan = TheThingFactory->findTemplate(info->rva000AF1DD());
		if (!bldgPlan)
			continue;
		if (!bldgPlan->isEquivalentTo(bldg->getTemplate()))
			continue;
	}
}
