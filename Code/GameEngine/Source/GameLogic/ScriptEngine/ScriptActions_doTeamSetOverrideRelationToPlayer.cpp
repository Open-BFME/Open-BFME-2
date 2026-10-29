// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?doTeamSetOverrideRelationToPlayer@ScriptActions@@QAEXABVAsciiString@@0PAVObject@@@Z @0x003C43F3 86B.
// Script free function finding Team named then Player by name key and calling
// rowed Team map register 0x003A2D53 with player index key plus object.
// Evidence: leaf lane plus caller 0x003CC9B9 plus prev 0x003C43A3 next 0x003C4449
// share /O1 /EHsc and two-AsciiString void stdcall shape plus ScriptEngine
// global 0xDFE16C plus NameKeyGenerator 0xDF36A4 plus PlayerList 0xDFEEE8.
class Object;
class Team;
class Player;
#include "ascii_string.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
extern PlayerList *ThePlayerList;
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex; // +0x54
};
class Team
{
public:
	void rva003A2D53(int key, Object *val);
};
void ScriptActions::doTeamSetOverrideRelationToPlayer(const AsciiString &teamName, const AsciiString &playerName, Object *obj)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	NameKeyType key = TheNameKeyGenerator->nameToKey(playerName);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	if (team == 0)
		return;
	if (player == 0)
		return;
	team->rva003A2D53(player->m_playerIndex, obj);
}
