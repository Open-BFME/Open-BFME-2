// cl: /MD /GX
// ??1Rva004EF41D@@UAE@XZ @0x004EF41D 56B derived dtor with EH.
// Evidence: stores vtable 0x00C62AF8 at [this], calls rowed AIPlayer::clearTeamsInQueue 0x004F05D6, calls rowed base ??1Rva004F07E6 0x004F07E6, EH prolog handler 0x00792BB5, caller 0x004EF638, chain from 0x004F07E6.
#include "../../Include/GameLogic/AIPlayerClass.h"
class AISkirmishPlayer : public AIPlayer
{
public:
	virtual ~AISkirmishPlayer();
	// Retail's table 0x00C62AF8: the rowed AISkirmishPlayer overrides in slots 3 to
	// 5, 7, 9, 10, 12, 13, 16, 17 and 20 to 25, and the shared `return true`
	// 0x0050B5C6 in slot 11 (Zero Hour's inline isSkirmishAI).
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *pos, int playerNdx, float weaponRadius);
	virtual void update();
	virtual void onUnitProduced(Object *factory, Object *unit);
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, bool priorityBuild);
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto, float recruitRadius, const Coord3D *pos);
	virtual bool isSkirmishAI() { return true; }
	virtual Player *getAiEnemy();
	virtual bool checkBridges(Object *unit, Waypoint *way);
protected:
	virtual void xfer(Xfer *xfer);
	virtual void checkReadyTeams();
	virtual void checkQueuedTeams();
	virtual Object *findDozer(const Coord3D *pos);
	virtual void queueDozer();
	virtual bool selectTeamToBuild();
	virtual bool selectTeamToReinforce(int minPriority);
	virtual bool startTraining(WorkOrder *order, bool busyOK, AsciiString teamName);
	virtual bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);
};
#include <new>
AISkirmishPlayer::~AISkirmishPlayer()
{
	((AIPlayer *)this)->clearTeamsInQueue();
}
