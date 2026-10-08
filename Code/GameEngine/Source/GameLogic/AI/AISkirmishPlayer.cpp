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
typedef bool Bool;
typedef int Int;
typedef float Real;
#define NULL 0

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

class AIUpdateInterface
{
public:
	LocomotorSet &getLocomotorSet() { return *(LocomotorSet *)m_locomotorSet; }
private:
	unsigned char m_pad00[0x1CC];
	unsigned char m_locomotorSet[4];	// +0x1CC
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;			// +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai;		// +0x258
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
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;		// +0x10
};
extern AI *TheAI;

class TeamPrototype
{
public:
	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const { return m_name; }

	char m_pad000[0x14];
	AsciiString m_name;			// +0x14
	char m_pad018[0x218 - 0x18];
	Int m_maxInstances;			// +0x218
};

class Team
{
public:
	TeamPrototype *getPrototype() const { return m_proto; }
private:
	char m_pad000[0x30];
	TeamPrototype *m_proto;			// +0x30
};

class TeamInQueue
{
public:
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_next; }

	TeamInQueue *m_prev;			// +0x04 (after the vfptr)
	TeamInQueue *m_next;			// +0x08
	char m_pad0C[0x1C - 0x0C];
	Team *m_team;				// +0x1C
private:
	virtual ~TeamInQueue();
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
	virtual void tl10(); virtual void tl11(); virtual void tl12();
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
