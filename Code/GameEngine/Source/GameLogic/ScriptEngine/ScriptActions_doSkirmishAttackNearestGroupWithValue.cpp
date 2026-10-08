// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
//
// ScriptActions::doSkirmishAttackNearestGroupWithValue, retail 0x003C0F44
// (166B; ret 0xC).
// Target identity: executeAction case 261 (SKIRMISH_ATTACK_NEAREST_GROUP_WITH_VALUE)
// calls it with parameter 0's string and parameters 1 and 2's ints, as
// Zero Hour's ScriptActions.cpp does. Target body follows the donor: team by
// name (getTeamNamed 0x003584E9), a new AI group (0x002FEC4B) filled from the
// team (0x003A0F62), the controlling player (0x0039D7CF), the group centre
// (0x0036D035) and, for comparisons 3 and 4 (GREATER_EQUAL, GREATER), the
// nearest group found from the player index's enemy mask
// (PlayerList::getPlayersWithRelationship 0x002A7C70, ALLOW_ENEMIES) by the
// pinned TheShroudManager forwarder 0x00739820; the group then attack-moves
// there (0x00372B09, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT). Target differences
// from the donor: the lookup lives on TheShroudManager, takes the mask rather
// than the player index and relationship, and has no greater flag; its int
// third argument (0) is unnamed.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

enum { ALLOW_ENEMIES = 0x04 };
enum { NO_MAX_SHOTS_LIMIT = 0x7fffffff };

class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	unsigned char m_pad[0x54];
	Int m_playerIndex;	// +0x54
};

class PlayerList
{
public:
	Int getPlayersWithRelationship(Int srcPlayerIndex, UnsignedInt allowedRelationships, bool ignoreSelf);
};
extern PlayerList *ThePlayerList;

class AIGroup
{
public:
	bool getCenter(Coord3D *center);
	void groupAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	Player *getControllingPlayer() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class ShroudManager
{
public:
	void rva00739820(const Coord3D *sourceLocation, Int playerMask, Int unknown, Int valueRequired, Coord3D *outLocation);
};
// The data ledger owns the global under its PartitionManager-typed name.
class PartitionManager;
extern PartitionManager *TheShroudManager;

class ScriptActions
{
protected:
	void doSkirmishAttackNearestGroupWithValue(const AsciiString &teamName, Int comparison, Int value);
};

void ScriptActions::doSkirmishAttackNearestGroupWithValue(const AsciiString &teamName, Int comparison, Int value)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Player *player = team->getControllingPlayer();

	if (!player)
		return;

	Coord3D loc;
	Coord3D groupLoc;
	theGroup->getCenter(&groupLoc);
	if (comparison == Parameter::GREATER_EQUAL || comparison == Parameter::GREATER) {
		((ShroudManager *)TheShroudManager)->rva00739820(&groupLoc,
			ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(), ALLOW_ENEMIES, false),
			0, value, &loc);
	}

	theGroup->groupAttackMoveToPosition(&loc, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT);
}
