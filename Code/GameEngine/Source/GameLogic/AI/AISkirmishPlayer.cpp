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
	Player *getCurrentEnemy() { return (Player *)((Rva002A9BBD *)this)->rva002A9BBD(); }

	unsigned char m_pad00[0x4C];
	AsciiString m_playerName;		// +0x4C
	NameKeyType m_playerNameKey;		// +0x50
	Int m_playerIndex;			// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	PlayerType m_playerType;		// +0x5C
	unsigned char m_pad60[0x2EC - 0x60];
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

class AIPlayer
{
public:
	virtual void update();
	virtual void onUnitProduced(Object *factory, Object *unit);
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);
protected:
	virtual void checkReadyTeams();
	virtual void checkQueuedTeams();
	virtual Object *findDozer(const Coord3D *searchPosition);
	virtual void queueDozer();
	virtual Bool selectTeamToBuild();
	virtual Bool selectTeamToReinforce(Int minPriority);
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);

public:
	static void getPlayerStructureBounds(Region2D *bounds, Int playerNdx);
protected:
	unsigned char m_pad04[0x0C - 0x04];
	Player *m_player;			// +0x0C
	unsigned char m_pad10[0x34 - 0x10];
	Coord3D m_baseCenter;			// +0x34
	unsigned char m_pad40[0x78 - 0x40];
};

class AISkirmishPlayer : public AIPlayer
{
public:
	virtual void update();
	virtual void onUnitProduced(Object *factory, Object *unit);
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);
	virtual Player *getAiEnemy();
protected:
	virtual void checkReadyTeams();
	virtual void checkQueuedTeams();
	virtual Object *findDozer(const Coord3D *pos);
	virtual void queueDozer();
	virtual Bool selectTeamToBuild();
	virtual Bool selectTeamToReinforce(Int minPriority);
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);

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
