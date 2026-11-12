// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
// Split from AIPlayerTeamBuild.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
//    startTraining (+0x60) with the team's name. Retail's new-expressions
//    carry no EH cleanup states: the WorkOrder (0x004F10E6) and TeamInQueue
//    (0x004EF5CE) constructors are defined in this unit ahead of their
//    users without throw(), so cl infers they cannot throw.
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
//  - selectTeamToReinforce 0x004F3DB1 (985 bytes, vtable +0x5C): ZH's
//    search for the highest-priority auto-reinforcing prototype (template
//    info at +0x12C, flag +0xE7) with a short team. BFME 2 skips queueing
//    and training when 0x002A8AB1 finds a record for the player, passes
//    the unit info's int (+0x14) to tryToRecruit and guards the null order
//    and queue entry. Only the merged new-expressions of the in-unit
//    nothrow constructors give retail's allocation (the chosen team in ebx).
//  - updateBridgeRepair 0x004F418A (500 bytes): ZH's body with the timer at
//    +0x68 reset from the frame-rate global, the repair order through
//    AICommandInterface 0x0036F19B (ZH aiRepair) and the return move adjusted
//    by TheAI's pathfinder (+0x10) over the AI's locomotor set (+0x1CC).
//    The first queue walk holds the count in a local that only guards the
//    shift loop, which is how retail keeps it in edi across the lookup; the
//    two Coord3D initialisations copy member-wise (movss) as retail does.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <windows.h>
#include <list>

// Keep the inlined node comparison local, as in GameClientXfer.cpp, so
// this unit does not emit an incompatible STLport base-iterator COMDAT.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L> &a,
                              const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}
#include <vector>

// GameLogic comes from the canonical GameLogicObjectLookupView.h.
#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"

// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
// Retail's push_back is one shared copy (0x002CE7DC); this unit's own copy led link order.
template <> void vector<Coord3D, allocator<Coord3D> >::push_back(const Coord3D &);
}
#include <math.h>
class ThingTemplate;
class Player;
class Team;

#include "../../Common/GameLogicObjectLookupView.h"

// Declaration-only: the rowed vector<Coord3D> members are bound, this TU emits no per-flag copy.
namespace _STL {
template <> void vector<Coord3D, allocator<Coord3D> >::_M_insert_overflow(Coord3D*, const Coord3D&, const __false_type&, size_t, bool);
}
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

#include "../../../Include/Common/ThingTemplate.h"

class Object;
enum BodyDamageType { BODY_PRISTINE = 0 };
#include "../../../Include/GameLogic/Rva0037EE4C.h"
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
// Retail's team-list nodes (12 bytes) come from the node pool at 0x009BBD2C (rowed
// FreelistPool::pop 0x002393E2) and go back onto its free list g_00DBBD34 inline:
// the list-base ctor 0x002AC026, clear 0x002AAC74 and dtor 0x002ABB44.
#include "../../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool009BBD2C;
struct PoolNode002ABAC0;
// The free-list head is the +8 member of the complete pool at VA 0xDBBD2C.
class FreelistPool;
extern FreelistPool g_freelistPool009BBD2C;
#define g_00DBBD34 (*(PoolNode002ABAC0 **)((char *)&g_freelistPool009BBD2C + 8))
namespace _STL {
template <> inline _List_node<TeamPrototype *> *allocator<_List_node<TeamPrototype *> >::allocate(size_t, const void *) const
{
	return (_List_node<TeamPrototype *> *)g_freelistPool009BBD2C.pop();
}
// Node release pushes onto the pool free list inline (the generic deallocate stays
// the allocator<char> body 0x0046264A).
static inline void freeTeamNode(_List_node<TeamPrototype *> *node)
{
	*(PoolNode002ABAC0 **)node = g_00DBBD34;
	g_00DBBD34 = (PoolNode002ABAC0 *)node;
}
template <> inline void _List_base<TeamPrototype *, allocator<TeamPrototype *> >::clear()
{
	_List_node<TeamPrototype *> *cur = (_List_node<TeamPrototype *> *)_M_node._M_data->_M_next;
	while (cur != _M_node._M_data)
	{
		_List_node<TeamPrototype *> *tmp = cur;
		cur = (_List_node<TeamPrototype *> *)cur->_M_next;
		freeTeamNode(tmp);
	}
	_M_node._M_data->_M_next = _M_node._M_data;
	_M_node._M_data->_M_prev = _M_node._M_data;
}
template <> inline _List_base<TeamPrototype *, allocator<TeamPrototype *> >::~_List_base() throw()
{
	clear();
	if (_M_node._M_data)
		freeTeamNode(_M_node._M_data);
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

#include "../../../Include/Common/Dict.h"

class BuildListInfo
{
public:
	// getTemplateName: retail calls the folded by-value AsciiString copy of +8.
	AsciiString getTemplateName() const;
	Int getHealth() const { return m_health; }
	Bool getUnsellable() const { return m_unsellable; }
	void setUnderConstruction(Bool construction) { m_underConstruction = construction; }
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

// The building name is the folded by-value copy of +4, rowed under this view.
class Player
{
public:
	BuildListInfo *getBuildList() const { return m_buildList; }
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
	Int getSciencePurchasePoints() const { return m_sciencePurchasePoints; }
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
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

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/Common/StateMachineClass.h"


#include "../../../Include/GameLogic/Module/BodyModule.h"

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
	Bool isKindOfDozer() const { return (getTemplate()->m_kindof[0] & (1U << 14)) != 0; }
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

#include "../../../Include/Common/BuildAssistantClass.h"
extern BuildAssistant *TheBuildAssistant;

#include "../../../Include/GameLogic/Module/ProductionEntry.h"

#include "../../../Include/GameLogic/Module/ProductionUpdateInterface.h"

#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../Include/Common/Rva002A8AB1Record.h"
#include "../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

#include "../../../Include/Common/TeamFactory.h"
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

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

// Zero Hour's ScienceStore::getInternalNameForScience, rowed at 0x001FF5F2.
#include "../../../Include/Common/ScienceStore.h"
extern ScienceStore *TheScienceStore;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../Include/GameLogic/TCreateUnitsInfo.h"

#include "../../../Include/GameLogic/Rva0039D761DwordClearer.h"

// The prototype's TeamTemplateInfo starts at +0x12C (its Snapshot table
// first); selectTeamToReinforce reads the unit infos, the reinforce flag and
// the priority through it.
class TeamTemplateInfo
{
public:
	void *m_vtable;				// +0x00 (prototype +0x12C)
	TCreateUnitsInfo m_unitsInfo[7];	// +0x04
	Int m_numUnitsInfo;			// +0xAC
	Coord3D m_homeLocation;			// +0xB0
	Bool m_hasHomeLocation;			// +0xBC
	char m_padBD[0xE7 - 0xBD];
	Bool m_automaticallyReinforce;		// +0xE7
	char m_padE8[0xEC - 0xE8];
	Int m_maxInstances;			// +0xEC
	Int m_productionPriority;		// +0xF0
};

template <class OBJCLASS> class DLINK_ITERATOR;
#include "../../../Include/Common/Team.h"

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

// Team has two bases, a memory-pool object at +0 and its Snapshot at +4:
// retail's DLINK_ITERATOR<Team> carries the eight-byte member-function
// pointer of a multiple-inheritance class (selectTeamToReinforce).
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Include/Common/TeamBFME2.h"

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

// The WorkOrder and TeamInQueue constructors are defined below, ahead of
// their users and without an exception specification (see TeamInQueue.h).
#define BFME_AIPLAYER_QUEUE_CTORS
#include "WorkOrder.h"

#include "TeamInQueue.h"

// ?TeamInQueue::disband present-unmatched
inline void TeamInQueue::disband() { if (m_team) m_team->disband(); }



#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
extern int BfmeLogicFramesPerSecond;
#define LOGICFRAMES_PER_SECOND BfmeLogicFramesPerSecond

#include "../../../Include/GameLogic/ScriptClass.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class BfmeRoomZC;
class Rva003573C4Owner
{
public:
	void *rva003573C4(const AsciiString &owner, const BfmeRoomZC &name, void *outName);	// rowed 0x003573C4
};
class Rva0020D451Engine
{
public:
	void rva0020D451(const AsciiString &scope, void *action, void *script, void *scriptName, Team *team);	// rowed 0x0020D451
};

enum { MAX_STRUCTURES_TO_REPAIR = 2 };

#include "../../../Include/GameLogic/AIPlayerClass.h"

enum { DOZER_TASK_BUILD = 0 };















enum { INVALID_SKILLSET_SELECTION = -1 };

// Retail inlines the one-character append as StringBase<char>::concat(&c, 1).
static __forceinline void concatChar(AsciiString &asciiString, char c)
{
	((StringBase<char> *)&asciiString)->concat(&c, 1);
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
		if (sideInfo->m_side == m_player->m_side)
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
					reinterpret_cast<StringBase<char> *>(&msg)->concat(" purchases from SkillSet");
					concatChar(msg, (char)('1' + m_skillsetSelector));
					concatChar(msg, ' ');
					msg.concat(TheScienceStore->getInternalNameForScience(science));
					reinterpret_cast<StringBase<char> *>(&msg)->concat(".");
					TheScriptEngine->AppendDebugMessage(msg, false);
				}
			}
		}
	}
}








