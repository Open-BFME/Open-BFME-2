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
class TeamPrototype;
class WorkOrder;
struct Coord3D;

enum PlayerType
{
	PLAYER_HUMAN = 0
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_pad00[0x54];
	Int m_playerIndex;			// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	PlayerType m_playerType;		// +0x5C
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

	unsigned char m_pad04[0x78 - 0x04];
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

// ?getAiEnemy@AISkirmishPlayer@@UAEPAVPlayer@@XZ present-unmatched @0x004EFDAB 49B: calls acquireEnemy 0x004EFB3D, unrowed
Player *AISkirmishPlayer::getAiEnemy()
{
	if (TheGameLogic->getFrame() >= m_frameToCheckEnemy)
	{
		m_frameToCheckEnemy = TheGameLogic->getFrame() + 5 * LOGICFRAMES_PER_SECOND;
		acquireEnemy();
	}
	return m_currentEnemy;
}
