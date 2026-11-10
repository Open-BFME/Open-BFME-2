// cl: /O1 /G7 /MD /DNDEBUG /arch:SSE
//
// ?Init@Command@@QAEXH_N@Z, retail 0x002A71BC..0x002A7389 (461 bytes, RET 8):
// Command::Init(int playerIndex, bool isHero), the command point holder at
// Player +0x60. Target facts: the sole caller Player::rva002A99FA 0x002A99FA
// passes the player index and a bare byte; the body range-checks the index
// against 20 and needs ThePlayerList and TheGameLogic. In a multiplayer game
// (gate 0x0023C6FD) the player count (PlayerList 0x002A7C0B) selects one of
// seven {initial, maximum} pair rows of TheWritableGlobalData from +0xE14
// (counts 2 or fewer up to 8 or more; normal pair first, hero pair second);
// the start adds the +0x18 count times the normal initial and the +0x1C count
// times the hero initial. Otherwise the player (getNthPlayer 0x002A7A29) type
// at +0x5C picks the human pairs at +0xDEC or the computer pairs at +0xE04; a
// human in a tactical living world game (TheLivingWorldLogic +0xB4) adds the
// world player's 0x002E14DD value. The +0x2C flag keeps larger stored totals,
// and with TheGameInfo set and game mode 3 the maximum is scaled by the
// percentage at TheGameInfo +0x6C.
//
// Identity: WorldBuilder 0x00E9B810 Command::Init in
// Code\GameEngine\Source\Common\Rts\Command.cpp (callgraph match), whose
// assert texts name m_commandPointsTotal (+0x04), m_commandPointsMax (+0x10)
// and lwPlayer. The other field and type names are structural inferences.
// TheWritableGlobalData is read through the global each time (no local), which
// keeps it in EAX in the per-player branch as retail does.

class Player;

#include "../../../Include/Common/PlayerList.h"

class GameLogic;
class GlobalData;
class GameInfo;
class LivingWorldLogic;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern GameInfo *TheGameInfo;
extern LivingWorldLogic *TheLivingWorldLogic;

#include "../../../Include/Common/BfmeGlob939D.h"

struct Rva002E0CD4
{
	int rva002E14DD() const;
};

struct CommandPointsPair
{
	int initial;
	int maximum;
};

struct CommandPointsDataView
{
	char m_pad000[0xDEC];
	CommandPointsPair human[2];		// +0xDEC normal, +0xDF4 hero
	char m_padDFC[8];
	CommandPointsPair computer[2];		// +0xE04 normal, +0xE0C hero
	CommandPointsPair multiplayer[7][2];	// +0xE14, one row per player count
};

struct CommandPlayerView
{
	char m_pad00[0x5C];
	int m_type;
};

struct CommandLivingWorldView
{
	char m_pad00[0x98];
	Rva002E0CD4 *m_player;
	char m_pad9C[0xB4 - 0x9C];
	bool m_tactical;
};

struct CommandGameLogicView
{
	char m_pad000[0x114];
	int m_mode;
};

struct CommandGameInfoView
{
	char m_pad00[0x6C];
	int m_percentage;
};

#define COMMAND_DATA ((CommandPointsDataView *)TheWritableGlobalData)

class Command
{
public:
	void Init(int playerIndex, bool isHero);
private:
	int m_00;
	int m_commandPointsTotal;
	int m_08;
	int m_0C;
	int m_commandPointsMax;
	int m_playerIndex;
	int m_normalCount;
	int m_heroCount;
	char m_pad20[0x2C - 0x20];
	bool m_keepLarger;
};

void Command::Init(int playerIndex, bool isHero)
{
	if (playerIndex < 0 || playerIndex >= 20 || !ThePlayerList || !TheGameLogic)
		return;
	m_playerIndex = playerIndex;
	int maxPoints = 0;
	int points = 0;
	if (((BfmeGlob939D *)TheGameLogic)->bfmeCall939D()) {
		int count = ThePlayerList->rva002A7C0B(true);
		CommandPointsDataView *data = COMMAND_DATA;
		CommandPointsPair *normal = 0;
		CommandPointsPair *hero = 0;
		if (count >= 8) { hero = &data->multiplayer[6][1]; normal = &data->multiplayer[6][0]; }
		else if (count >= 7) { hero = &data->multiplayer[5][1]; normal = &data->multiplayer[5][0]; }
		else if (count >= 6) { hero = &data->multiplayer[4][1]; normal = &data->multiplayer[4][0]; }
		else if (count >= 5) { hero = &data->multiplayer[3][1]; normal = &data->multiplayer[3][0]; }
		else if (count == 4) { hero = &data->multiplayer[2][1]; normal = &data->multiplayer[2][0]; }
		else if (count == 3) { hero = &data->multiplayer[1][1]; normal = &data->multiplayer[1][0]; }
		else { hero = &data->multiplayer[0][1]; normal = &data->multiplayer[0][0]; }
		if (isHero) { points = hero->initial; maxPoints = hero->maximum; }
		else { points = normal->initial; maxPoints = normal->maximum; }
		points += m_normalCount * normal->initial;
		points += m_heroCount * hero->initial;
	} else {
		Player *player = ThePlayerList->getNthPlayer(m_playerIndex);
		if (!player)
			return;
		if (((CommandPlayerView *)player)->m_type == 0) {
			if (isHero) { points = COMMAND_DATA->human[1].initial; maxPoints = COMMAND_DATA->human[1].maximum; }
			else { points = COMMAND_DATA->human[0].initial; maxPoints = COMMAND_DATA->human[0].maximum; }
			CommandLivingWorldView *world = (CommandLivingWorldView *)TheLivingWorldLogic;
			if (world && world->m_tactical) {
				Rva002E0CD4 *lwPlayer = world->m_player;
				if (lwPlayer)
					points += lwPlayer->rva002E14DD();
			}
		} else {
			if (isHero) { points = COMMAND_DATA->computer[1].initial; maxPoints = COMMAND_DATA->computer[1].maximum; }
			else { points = COMMAND_DATA->computer[0].initial; maxPoints = COMMAND_DATA->computer[0].maximum; }
		}
	}
	if (!m_keepLarger || maxPoints > m_commandPointsMax)
		m_commandPointsMax = maxPoints;
	if (!m_keepLarger || points > m_commandPointsTotal)
		m_commandPointsTotal = points;
	if (TheGameInfo && ((CommandGameLogicView *)TheGameLogic)->m_mode == 3)
		m_commandPointsMax = m_commandPointsMax * ((CommandGameInfoView *)TheGameInfo)->m_percentage / 100;
}
