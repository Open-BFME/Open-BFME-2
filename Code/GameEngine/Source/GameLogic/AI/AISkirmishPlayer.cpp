// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// AISkirmishPlayer, Zero Hour's AISkirmishPlayer.cpp bodies (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference) as BFME 2 kept them.
// Identity: AISkirmishPlayer's vftable 0x00C62AF8 (installed by the rowed
// ctor 0x004EF3A3) against AIPlayer's 0x00C62DC8, slot by slot. BFME 2 cut
// the skirmish overrides of update, onUnitProduced, buildSpecificAITeam,
// checkReadyTeams, checkQueuedTeams, findDozer, queueDozer, selectTeamToBuild
// and selectTeamToReinforce down to the base call (tail jumps into the
// AIPlayer slot bodies), and startTraining to a forward to AIPlayer's.
// getAiEnemy (slot 12) keeps Zero Hour's 5-second re-acquire, with BFME's
// logic frame rate read from its global.
#include "ascii_string.h"
#include <math.h>
typedef bool Bool;
typedef int Int;
typedef float Real;
#define NULL 0
#define PI 3.14159265359f

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

extern int g_Va00DBA4E4;
#define LOGICFRAMES_PER_SECOND g_Va00DBA4E4

class Object;
class Team;
class TeamPrototype;
class WorkOrder;
class SpecialPowerTemplate;
class Waypoint;
class ThingTemplate;

#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

inline Real sqr(Real x) { return x * x; }

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum PlayerType
{
	PLAYER_HUMAN = 0
};

// Player::getCurrentEnemy 0x002A9BBD is rowed under an address name.
class Rva002A9BBD
{
public:
	void *rva002A9BBD();
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Relationship getRelationship(const Team *that) const;
	Bool hasAnyObjects(Bool includeReserved) const;
	Bool rva002AB312() const;		// ZH hasAnyUnits
	Bool rva002AB3FA() const;		// ZH hasAnyBuildFacility
	Bool hasAnyUnits() const { return rva002AB312(); }
	Bool hasAnyBuildFacility() const { return rva002AB3FA(); }
	Bool isSkirmishAIPlayer();
	void onStructureUndone(Object *structure);	// 0x0047A69C, empty in BFME 2
	Int getMpStartIndex() const { return m_mpStartIndex; }
	Player *getCurrentEnemy() { return (Player *)((Rva002A9BBD *)this)->rva002A9BBD(); }

	unsigned char m_pad00[0x4C];
	AsciiString m_playerName;		// +0x4C
	NameKeyType m_playerNameKey;		// +0x50
	Int m_playerIndex;			// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	PlayerType m_playerType;		// +0x5C
	unsigned char m_pad60[0x2E0 - 0x60];
	Int m_mpStartIndex;			// +0x2E0
	unsigned char m_pad2E4[0x2EC - 0x2E4];
	Team *m_defaultTeam;			// +0x2EC
};

class PlayerList
{
public:
	Int getPlayerCount() const { return m_playerCount; }
	Player *getNthPlayer(Int playerIndex);
private:
	unsigned char m_pad00[0x14];
	Int m_playerCount;			// +0x14
};
extern PlayerList *ThePlayerList;

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};
extern ScriptEngine *TheScriptEngine;

static const Real HUGE_DIST = 1000000.0f;

// The locomotor set lives at AIUpdateInterface +0x1CC; Pathfinder's rowed
// findBrokenBridge (0x002E99F9) takes it through its own view.
struct Rva002E99F9Arg1;
typedef Rva002E99F9Arg1 LocomotorSet;

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	// The AICommandInterface base sits at +0x20.
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
	LocomotorSet &getLocomotorSet() { return *(LocomotorSet *)m_locomotorSet; }
private:
	unsigned char m_pad00[0x1CC];
	unsigned char m_locomotorSet[4];	// +0x1CC
};

// KINDOF_COMMANDCENTER is bit 1 of the kind-of byte at ThingTemplate +0x10A
// (as in the rowed Player::doFindCommandCenter view).
class ThingTemplate
{
public:
	Bool isKindOfCommandCenter() const { return (m_kindOf10A & 2) != 0; }
	const AsciiString &getName() const { return m_name; }
private:
	unsigned char m_pad000[0x64];
	AsciiString m_name;			// +0x64
	unsigned char m_pad068[0x10A - 0x68];
	unsigned char m_kindOf10A;		// +0x10A
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOfCommandCenter() const { return getTemplate()->isKindOfCommandCenter(); }
	const Coord3D *getPosition() const { return &m_position; }
	Object *getNextObject() const { return m_next; }
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAI() { return m_ai; }
	Team *getTeam() const { return m_team; }
	void setTeam(Team *team);
private:
	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;			// +0x38
	unsigned char m_pad44[0x8C - 0x44];
	Object *m_next;				// +0x8C
	unsigned char m_pad90[0x258 - 0x90];
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team;				// +0x304
};

// BuildListInfo::getTemplateName is the shared copy-out of the AsciiString at
// +0x08 (0x000AF1DD), pinned under an address name.
class BuildListInfo
{
public:
	AsciiString rva000AF1DD() const;	// getTemplateName
	const Coord3D *getLocation() const { return &m_location; }
	// Built from components: adjustBuildList keeps the rotated location in
	// registers and block-copies a filled temporary into place.
	void setLocation(Real x, Real y, Real z) { Coord3D loc; loc.x = x; loc.y = y; loc.z = z; m_location = loc; }
	void setInitiallyBuilt(Bool b) { m_isInitiallyBuilt = b; }
	Real getAngle() const { return m_angle; }
	void setAngle(Real angle) { m_angle = angle; }
	BuildListInfo *getNext() const { return m_next; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_location;			// +0x0C
	Real m_angle;				// +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	Bool m_isInitiallyBuilt;		// +0x24
	unsigned char m_pad25[0x2C - 0x25];
	BuildListInfo *m_next;			// +0x2C
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getNext() const { return m_next; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_location;			// +0x0C
	unsigned char m_pad18[0x1C - 0x18];
	Waypoint *m_next;			// +0x1C
};

class Pathfinder
{
public:
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int flags);
	Int FindBrokenBridge(Rva002E99F9Arg1 *locoSet, const Coord3D * volatile from, const Coord3D *to);
	void RemoveObjectFromPathfindMap(Object *obj);	// 0x002E718A
	void removeObjectFromPathfindMap(Object *obj) { RemoveObjectFromPathfindMap(obj); }
};

class AIData
{
public:
	unsigned char m_pad00[0x66];
	Bool m_rotateSkirmishBases;		// +0x66
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;		// +0x10
	unsigned char m_pad14[0x18 - 0x14];
	AIData *m_aiData;			// +0x18
};
extern AI *TheAI;

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

// BFME 2's unit entry is 0x18 bytes (AIPlayerTeamBuild.cpp's view).
struct TCreateUnitsInfo
{
	Int minUnits;			// +0x00
	Int maxUnits;			// +0x04
	Int m_08;			// +0x08
	AsciiString m_bfmeString0C;	// +0x0C
	AsciiString unitThingName;	// +0x10
	Int m_14;			// +0x14
};

class TeamPrototype
{
public:
	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const { return m_name; }
	const AsciiString &getOwnerName() const { return m_owner; }
	Bool getIsSingleton() const { return (m_flags & 1) != 0; }

	char m_pad000[0x10];
	AsciiString m_owner;			// +0x10
	AsciiString m_name;			// +0x14
	Int m_flags;				// +0x18
	char m_pad01C[0x130 - 0x1C];
	TCreateUnitsInfo m_unitsInfo[7];	// +0x130
	Int m_numUnitsInfo;			// +0x1D8
	Coord3D m_homeLocation;			// +0x1DC
	Bool m_hasHomeLocation;			// +0x1E8
	char m_pad1E9[0x218 - 0x1E9];
	Int m_maxInstances;			// +0x218
};

class Team
{
public:
	virtual ~Team();
	TeamPrototype *getPrototype() const { return m_proto; }
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *pos, Real maxDist, Int a, Int b, Int c);
	Bool hasAnyObjects(Bool ignoreBuilding);
	__forceinline void deleteInstance() { ::delete this; }
private:
	char m_pad004[0x30 - 0x04];
	TeamPrototype *m_proto;			// +0x30
};

class TeamInQueue
{
public:
	TeamInQueue() throw();
	virtual ~TeamInQueue();
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_next; }

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
	char m_pad28[0x30 - 0x28];
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

class GlobalData
{
public:
	char m_pad000[0x9B8];
	Int m_debugAI;				// +0x9B8
};
extern GlobalData *TheWritableGlobalData;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_name;
	}
private:
	unsigned char m_pad[0x10];
	AsciiString m_name;			// +0x10
};

class TerrainLogic
{
public:
	virtual void tl00(); virtual void tl01(); virtual void tl02();
	virtual void tl03(); virtual void tl04(); virtual void tl05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const;	// +0x18
	virtual void tl07(); virtual void tl08(); virtual void tl09();
	virtual void tl10(); virtual void tl11();
	virtual void getMaximumPathfindExtent(Region3D *extent) const;	// +0x30
	virtual void tl13(); virtual void tl14(); virtual void tl15();
	virtual void tl16(); virtual void tl17(); virtual void tl18();
	virtual void tl19(); virtual void tl20(); virtual void tl21();
	virtual void tl22(); virtual void tl23(); virtual void tl24();
	virtual void tl25(); virtual void tl26(); virtual void tl27();
	virtual void tl28(); virtual void tl29(); virtual void tl30();
	virtual void tl31(); virtual void tl32(); virtual void tl33();
	virtual void tl34(); virtual void tl35();
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos, const AsciiString &label);	// +0x90
};
extern TerrainLogic *TheTerrainLogic;

Int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
public:
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *pos, Int playerNdx, Real weaponRadius);	// +0x10
	virtual void update();						// +0x14
protected:
	virtual void slot06();
public:
	virtual void onUnitProduced(Object *factory, Object *unit);	// +0x1C
	virtual void onStructureProduced(Object *factory, Object *bldg);	// +0x20
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);	// +0x24
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius, const Coord3D *pos);	// +0x28
	virtual Bool isSkirmishAI();					// +0x2C
	virtual Player *getAiEnemy();					// +0x30
	virtual Bool checkBridges(Object *unit, Waypoint *way);	// +0x34
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

	Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney);
public:
	void prependTo_TeamReadyQueue(TeamInQueue *team);
protected:
	Bool rva004F13D8(TeamPrototype *proto);	// BFME 2 on-field shortcut
	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}

public:
	static void getPlayerStructureBounds(Region2D *bounds, Int playerNdx);
protected:
	TeamInQueue *m_teamBuildQueue;		// +0x04
	TeamInQueue *m_teamReadyQueue;		// +0x08
	Player *m_player;			// +0x0C
	unsigned char m_pad10[0x34 - 0x10];
	Coord3D m_baseCenter;			// +0x34
	unsigned char m_pad40[0x44 - 0x40];
	Real m_baseRadius;			// +0x44
	unsigned char m_pad48[0x78 - 0x48];
};

class AISkirmishPlayer : public AIPlayer
{
public:
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius);
	virtual void update();
	virtual void onUnitProduced(Object *factory, Object *unit);
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius, const Coord3D *pos);
	virtual Bool checkBridges(Object *unit, Waypoint *way);
	virtual Player *getAiEnemy();
protected:
	virtual void checkReadyTeams();
	virtual void checkQueuedTeams();
	virtual Object *findDozer(const Coord3D *pos);
	virtual void queueDozer();
	virtual Bool selectTeamToBuild();
	virtual Bool selectTeamToReinforce(Int minPriority);
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);
	virtual Bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);

	Int getMyEnemyPlayerIndex();
	void acquireEnemy();
	void adjustBuildList(BuildListInfo *list);

	Int m_curFlankBaseDefense;		// +0x78
	Int m_curFrontBaseDefense;		// +0x7C
	Real m_curFlankLeftDefenseAngle;	// +0x80
	Real m_curFlankRightDefenseAngle;	// +0x84
	Real m_curFrontLeftDefenseAngle;	// +0x88
	Real m_curFrontRightDefenseAngle;	// +0x8C
	Real m_curLeftFlankRightDefenseAngle;	// +0x90
	Real m_curRightFlankLeftDefenseAngle;	// +0x94
	unsigned int m_frameToCheckEnemy;	// +0x98
	Player *m_currentEnemy;			// +0x9C
};

// ?onUnitProduced@AISkirmishPlayer@@UAEXPAVObject@@0@Z @0x004EF455 5B
void AISkirmishPlayer::onUnitProduced(Object *factory, Object *unit)
{
	AIPlayer::onUnitProduced(factory, unit);
}

// ?selectTeamToReinforce@AISkirmishPlayer@@MAE_NH@Z present-unmatched @0x004EF45A 5B: its tail-jump target, AIPlayer::selectTeamToReinforce 0x004F3DB1, is unrowed
Bool AISkirmishPlayer::selectTeamToReinforce(Int minPriority)
{
	return AIPlayer::selectTeamToReinforce(minPriority);
}

// ?selectTeamToBuild@AISkirmishPlayer@@MAE_NXZ @0x004EF45F 5B
Bool AISkirmishPlayer::selectTeamToBuild()
{
	return AIPlayer::selectTeamToBuild();
}

// ?getMyEnemyPlayerIndex@AISkirmishPlayer@@IAEHXZ @0x004EF464 56B
Int AISkirmishPlayer::getMyEnemyPlayerIndex()
{
	Int playerNdx;
	if (m_currentEnemy)
		return m_currentEnemy->getPlayerIndex();
	// For now, return first human player, as there should only be one. jba
	for (playerNdx = 0; playerNdx < ThePlayerList->getPlayerCount(); playerNdx++)
	{
		if (ThePlayerList->getNthPlayer(playerNdx)->m_playerType == PLAYER_HUMAN)
			break;
	}
	return playerNdx;
}

// ?buildSpecificAITeam@AISkirmishPlayer@@UAEXPAVTeamPrototype@@_N@Z @0x004EF49C 5B
void AISkirmishPlayer::buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild)
{
	AIPlayer::buildSpecificAITeam(teamProto, priorityBuild);
}

// ?checkReadyTeams@AISkirmishPlayer@@MAEXXZ @0x004EF4B7 5B
void AISkirmishPlayer::checkReadyTeams()
{
	AIPlayer::checkReadyTeams();
}

// ?checkQueuedTeams@AISkirmishPlayer@@MAEXXZ @0x004EF4BC 5B
void AISkirmishPlayer::checkQueuedTeams()
{
	AIPlayer::checkQueuedTeams();
}

// ?update@AISkirmishPlayer@@UAEXXZ @0x004EF520 5B
void AISkirmishPlayer::update()
{
	AIPlayer::update();
}

// ?queueDozer@AISkirmishPlayer@@MAEXXZ @0x004EF525 5B
void AISkirmishPlayer::queueDozer()
{
	AIPlayer::queueDozer();
}

// ?findDozer@AISkirmishPlayer@@MAEPAVObject@@PBUCoord3D@@@Z @0x004EF52A 5B
Object *AISkirmishPlayer::findDozer(const Coord3D *pos)
{
	return AIPlayer::findDozer(pos);
}

// ?startTraining@AISkirmishPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z @0x004EF651 79B
Bool AISkirmishPlayer::startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName)
{
	return AIPlayer::startTraining(order, busyOK, teamName);
}

// ?checkBridges@AISkirmishPlayer@@UAE_NPAVObject@@PAVWaypoint@@@Z @0x004EF6A0 154B
// BFME 2's path test takes the unit itself (QuickDoesPathExist 0x002F477E)
// and findBrokenBridge returns the bridge's id instead of filling one in.
Bool AISkirmishPlayer::checkBridges(Object *unit, Waypoint *way)
{
	const Coord3D *pos = unit->getPosition();
	Coord3D unitPos;
	unitPos.x = pos->x;
	unitPos.y = pos->y;
	unitPos.z = pos->z;
	AIUpdateInterface *ai = unit->getAI();
	if (!ai) return false; // no ai
	LocomotorSet &locoSet = ai->getLocomotorSet();
	Waypoint *curWay;
	for (curWay = way; curWay; curWay = curWay->getNext()) {
		if (TheAI->pathfinder()->QuickDoesPathExist(unit, &unitPos, curWay->getLocation(), 0)) {
			continue;
		}
		ObjectID brokenBridge = (ObjectID)TheAI->pathfinder()->FindBrokenBridge(&locoSet, &unitPos, curWay->getLocation());
		if (brokenBridge) {
			repairStructure(brokenBridge);
			return true;
		}
	}
	return false;
}

// ?isAGoodIdeaToBuildTeam@AISkirmishPlayer@@MAE_NPAVTeamPrototype@@@Z @0x004EF73A 323B
// BFME 2 adds AIPlayer's on-field shortcut (rva004F13D8) before the
// factory and money test.
Bool AISkirmishPlayer::isAGoodIdeaToBuildTeam(TeamPrototype *proto)
{
	// Check condition.
	if (!proto->evaluateProductionCondition()) {
		return false;
	}
	// check build limit
	if (proto->countTeamInstances() >= proto->m_maxInstances) {
		if (TheWritableGlobalData->m_debugAI) {
			AsciiString str;
			str.format("Team %s not chosen - %d already exist.", proto->getName().str(), proto->countTeamInstances());
			TheScriptEngine->AppendDebugMessage(str, false);
		}
		return false;	// Max already built.
	}

	for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		if (team->m_team->getPrototype() == proto) {
			return false; // currently building one of these.
		}
	}
	Bool needMoney;
	if (!rva004F13D8(proto) && !isPossibleToBuildTeam(proto, true, needMoney)) {
		if (TheWritableGlobalData->m_debugAI) {
			AsciiString str;
			if (needMoney) {
				str.format("Team %s not chosen - Not enough money.", proto->getName().str());
			} else {
				str.format("Team %s not chosen - Factory/tech missing or busy.", proto->getName().str());
			}
			TheScriptEngine->AppendDebugMessage(str, false);
		}
		return false;
	}
	return true;
}

// ?acquireEnemy@AISkirmishPlayer@@IAEXXZ @0x004EFB3D 622B
void AISkirmishPlayer::acquireEnemy()
{
	Player *bestEnemy = NULL;
	Real bestDistanceSqr = HUGE_DIST * HUGE_DIST;

	if (m_currentEnemy)
	{
		Bool inBadShape = !m_currentEnemy->hasAnyUnits() || !m_currentEnemy->hasAnyBuildFacility();
		if (!inBadShape)
			return;
	}

	// look for the closest enemy.
	Int i;
	for (i = 0; i < ThePlayerList->getPlayerCount(); i++)
	{
		Player *curPlayer = ThePlayerList->getNthPlayer(i);
		if (m_player->getRelationship(curPlayer->getDefaultTeam()) == ENEMIES)
		{
			if (curPlayer->hasAnyObjects(false) == false)
				continue;	// not much of an enemy.
			if (curPlayer->m_playerName.compare("PlyrCreeps") == 0)
				continue;
			// If a player is out of units, or out of build facilities, we can lower his priority.
			Bool inBadShape = !curPlayer->hasAnyUnits() || !curPlayer->hasAnyBuildFacility();

			Coord3D enemyPos = m_baseCenter;
			Region2D bounds;
			getPlayerStructureBounds(&bounds, i);
			enemyPos.x = bounds.lo.x + bounds.width() / 2;
			enemyPos.y = bounds.lo.y + bounds.height() / 2;
			Real curDistSqr = sqr(enemyPos.x - m_baseCenter.x) + sqr(enemyPos.y - m_baseCenter.y);

			// Fudge for in bad shape. If an enemy is crippled, concentrate on the other ones.
			if (inBadShape)
				curDistSqr = HUGE_DIST * HUGE_DIST * 0.5f;
			// See if other ai's are attacking this target.
			Int k;
			for (k = 0; k < ThePlayerList->getPlayerCount(); k++)
			{
				if (k == i)
					continue;	// don't count self.
				Player *somePlayer = ThePlayerList->getNthPlayer(k);
				if (somePlayer->isSkirmishAIPlayer() && (somePlayer->getCurrentEnemy() == curPlayer))
				{
					// Some ai is already targeting this guy.  Add a distance penalty.
					curDistSqr += (500 * 500);
				}
				if (somePlayer->isSkirmishAIPlayer() && (somePlayer->getCurrentEnemy() == m_player))
				{
					// he is attacking me.  So I will (gently) prefer to attack him.
					curDistSqr -= (25 * 25);
					if (curDistSqr < 0)
						curDistSqr = 0;
				}
			}

			if (curDistSqr < bestDistanceSqr)
			{
				bestEnemy = curPlayer;
				bestDistanceSqr = curDistSqr;
			}
		}
	}
	if (bestEnemy != NULL && (bestEnemy != m_currentEnemy))
	{
		m_currentEnemy = bestEnemy;
		AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
		msg.concat(" acquiring target enemy player: ");
		msg.concat(TheNameKeyGenerator->keyToName(m_currentEnemy->getPlayerNameKey()));
		TheScriptEngine->AppendDebugMessage(msg, false);
	}
}

// ?computeSuperweaponTarget@AISkirmishPlayer@@UAEXPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z @0x004EFDDC 493B
// BFME 2 picks the cluster-mine power by template name instead of power type,
// and AIPlayer's slot returns nothing.
void AISkirmishPlayer::computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius)
{
	Region2D bounds;
	getPlayerStructureBounds(&bounds, playerNdx);

	const AsciiString &powerName = power->getName();
	if (powerName.compare("SuperweaponClusterMines") == 0)
	{
		// hackus brutus - mine the entrances to our base.
		AsciiString pathLabel;
		Int mode = GetGameLogicRandomValue(0, 2, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AISkirmishPlayer.cpp", 1136);
		if (mode==1) {
				pathLabel.format("%s%d", "Flank", m_player->getMpStartIndex()+1);
		}	else if (mode==2) {
				pathLabel.format("%s%d", "Backdoor", m_player->getMpStartIndex()+1);
		}	else {
			pathLabel.format("%s%d", "Center", m_player->getMpStartIndex()+1);
		}

		Coord3D goalPos;
		goalPos.x = m_baseCenter.x;
		goalPos.y = m_baseCenter.y;
		goalPos.z = m_baseCenter.z;
		Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &goalPos, pathLabel );
		if (way) {
			goalPos = *way->getLocation();
		} else {
			Region2D bounds;
			getPlayerStructureBounds(&bounds, getMyEnemyPlayerIndex());
			goalPos.x = bounds.lo.x + bounds.width()/2;
			goalPos.y = bounds.lo.y + bounds.height()/2;
		}
		Coord2D offset;
		offset.x = goalPos.x-m_baseCenter.x;
		offset.y = goalPos.y-m_baseCenter.y;
		offset.normalize();
		Real dx = offset.x * m_baseRadius;
		Real dy = offset.y * m_baseRadius;
		Coord3D *ret = retPos;
		*ret = m_baseCenter;
		ret->x += dx;
		ret->y += dy;
		ret->z = TheTerrainLogic->getGroundHeight(ret->x, ret->y);
		return;
	}

	AIPlayer::computeSuperweaponTarget(power, retPos, playerNdx, weaponRadius);
}

// ?getAiEnemy@AISkirmishPlayer@@UAEPAVPlayer@@XZ @0x004EFDAB 49B
Player *AISkirmishPlayer::getAiEnemy()
{
	if (TheGameLogic->getFrame() >= m_frameToCheckEnemy)
	{
		m_frameToCheckEnemy = TheGameLogic->getFrame() + 5 * LOGICFRAMES_PER_SECOND;
		acquireEnemy();
	}
	return m_currentEnemy;
}

// ?adjustBuildList@AISkirmishPlayer@@IAEXPAVBuildListInfo@@@Z @0x004EF87D 668B
// Zero Hour's body; the last loop still looks up list (not cur) as in ZH.
// The command center's removal reaches Player::onStructureUndone, an empty
// RET 4 in BFME 2 (0x0047A69C).
void AISkirmishPlayer::adjustBuildList(BuildListInfo *list)
{
	Bool foundStart = false;
	Coord3D startPos;

	// Find our command center location.
	Object *obj;
	for( obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject() )
	{
		Player *owner = obj->getControllingPlayer();
		if (owner==m_player) {
			// See if it's a command center.
			if (obj->isKindOfCommandCenter()) {
				foundStart = true;
				startPos = *obj->getPosition();
				m_player->onStructureUndone(obj);
				TheAI->pathfinder()->removeObjectFromPathfindMap(obj);
				TheGameLogic->destroyObject(obj);
				break;
			}
		}
	}
	if (!foundStart) {
		return;
	}
	// Find the location of the command center in the build list.
	Bool foundInBuildList = false;
	Coord3D buildPos;
	BuildListInfo *cur = list;
	while (cur) {
		const ThingTemplate *tTemplate = TheThingFactory->findTemplate(cur->rva000AF1DD());
		if (tTemplate && tTemplate->isKindOfCommandCenter()) {
			foundInBuildList = true;
			buildPos = *cur->getLocation();
			cur->setInitiallyBuilt(true);
		}
		cur = cur->getNext();
	}
	Region3D bounds;
	TheTerrainLogic->getMaximumPathfindExtent(&bounds);
	/* calculate section of 3x3 grid:
		6 7 8
		3 4 5
		0 1 2 */

	Int gridIndex = 0;
	if (startPos.x > bounds.lo.x + bounds.width()/3) {
		gridIndex++;
	}
	if (startPos.x > bounds.lo.x + 2*bounds.width()/3) {
		gridIndex++;
	}

	if (startPos.y > bounds.lo.y + bounds.height()/3) {
		gridIndex+=3;
	}
	if (startPos.y > bounds.lo.y + 2*bounds.height()/3) {
		gridIndex+=3;
	}

	Real angle = 0;
	if (TheAI->getAiData()->m_rotateSkirmishBases) {
		switch (gridIndex) {
			case 0 : angle = 0; break;
			case 1 : angle = PI/4; break;// 45 degrees.
			case 2 : angle = PI/2; break; // 90 degrees;
			case 3 : angle = -PI/4; break; // -45 degrees.
			case 4 : angle = 0; break;
			case 5 : angle = 3*PI/4; break; // 135 degrees.
			case 6 : angle = -PI/2; break; // -90 degrees;
			case 7 : angle = -3*PI/4; break; // -135 degrees.
			case 8 : angle = PI; break; // 180 degrees.
		}
	}

	angle += 3*PI/4;

	Real s = sin(angle);
	Real c = cos(angle);

	cur = list;
	while (cur) {
		const ThingTemplate *tTemplate = TheThingFactory->findTemplate(list->rva000AF1DD());
		if (tTemplate && tTemplate->isKindOfCommandCenter()) {
			foundInBuildList = true;
			const Coord3D *loc = cur->getLocation();
			Coord3D curPos;
			curPos.x = loc->x;
			curPos.y = loc->y;
			curPos.z = loc->z;
			// Transform to new coords.
			curPos.x -= buildPos.x;
			curPos.y -= buildPos.y;
			Real newX = curPos.x*c - curPos.y*s;
			Real newY = curPos.y*c + curPos.x*s;
			curPos.x = newX + startPos.x;
			curPos.y = newY + startPos.y;
			cur->setLocation(curPos.x, curPos.y, curPos.z);
			cur->setAngle(cur->getAngle());
		}
		cur = cur->getNext();
	}

}

// ?recruitSpecificAITeam@AISkirmishPlayer@@UAEXPAVTeamPrototype@@MPBUCoord3D@@@Z @0x004EFFC9 830B
// Zero Hour's skirmish recruit with BFME 2's owner-qualified team lookups,
// optional recruit position and extra tryToRecruit arguments. Unlike
// AIPlayer's 0x004F437E the skirmish body keeps ZH's missing-home-location
// message and always sends recruits to the prototype's home location.
void AISkirmishPlayer::recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius, const Coord3D *pos)
{
	if (recruitRadius < 1)
		recruitRadius = 99999.0f;
	if (teamProto)
	{
		if (teamProto->getIsSingleton())
		{
			Team *singletonTeam = TheTeamFactory->findTeam(teamProto->getOwnerName(), teamProto->getName());
			if (singletonTeam && singletonTeam->hasAnyObjects(false))
			{
				AsciiString teamStr = "Unable to recruit singleton team '";
				teamStr.concat("' because team already exists.");
				TheScriptEngine->AppendDebugMessage(teamStr, false);
				return;
			}
		}
		if (!teamProto->m_hasHomeLocation)
		{
			AsciiString teamStr = "Error : team '";
			teamStr.concat(teamProto->getName());
			teamStr.concat("' has no Home Position (or Origin).");
			TheScriptEngine->AppendDebugMessage(teamStr, false);
		}
		Team *theTeam = TheTeamFactory->createInactiveTeam(teamProto->getOwnerName(), teamProto->getName());
		AsciiString teamName = teamProto->getName();
		teamName.concat(" - Recruiting.");
		TheScriptEngine->AppendDebugMessage(teamName, false);
		const TCreateUnitsInfo *unitInfo = &teamProto->m_unitsInfo[0];
		Int i;
		Int unitsRecruited = 0;
		for (i = 0; i < teamProto->m_numUnitsInfo; i++)
		{
			const ThingTemplate *thing = TheThingFactory->findTemplate(unitInfo[i].unitThingName);
			if (thing)
			{
				int count = unitInfo[i].maxUnits;
				while (count > 0)
				{
					Object *unit;
					if (pos)
						unit = theTeam->tryToRecruit(thing, pos, recruitRadius, unitInfo[i].m_14, 0, 0);
					else
						unit = theTeam->tryToRecruit(thing, &teamProto->m_homeLocation, recruitRadius, unitInfo[i].m_14, 0, 0);
					if (unit)
					{
						unitsRecruited++;

						AsciiString teamStr = "Team '";
						teamStr.concat(theTeam->getPrototype()->getName());
						teamStr.concat("' recruits ");
						teamStr.concat(thing->getName());
						teamStr.concat(" from team '");
						teamStr.concat(unit->getTeam()->getPrototype()->getName());
						teamStr.concat("'");
						TheScriptEngine->AppendDebugMessage(teamStr, false);

						unit->setTeam(theTeam);

						AIUpdateInterface *ai = unit->getAI();
						if (ai)
							ai->getCommandInterface()->aiMoveToPosition(&teamProto->m_homeLocation, CMD_FROM_AI);
					}
					else
					{
						break;
					}
					count--;
				}
			}
		}
		if (unitsRecruited > 0)
		{
			TeamInQueue *team = new TeamInQueue;
			prependTo_TeamReadyQueue(team);
			team->m_priorityBuild = false;
			team->m_workOrders = NULL;
			team->m_frameStarted = TheGameLogic->getFrame();
			team->m_team = theTeam;
			teamName = teamProto->getName();
			teamName.concat(" - Finished recruiting.");
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}
		else
		{
			if (!theTeam->getPrototype()->getIsSingleton())
			{
				theTeam->deleteInstance();
				theTeam = NULL;
			}
			teamName = teamProto->getName();
			teamName.concat(" - Recruited 0 units, disbanding.");
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}
	}
}
