// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003C4449Do@@YGXABVAsciiString@@0@Z @0x003C4449 83B.
// Script free function finding Team named then Player by name key and
// calling rowed armor remove 0x003A28ED. Evidence: chain lane via 0x003A28ED
// just landed; prev 0x003C43A3 and next 0x003C4570 share /O1 /EHsc and
// two-AsciiString void stdcall shape plus ScriptEngine global 0xDFE16C;
// caller at 0x003CC9DE; ret 8 two args.
class Object;
class Team;
class Player;
#include "ascii_string.h"
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
};
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
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
class Player
{
public:
	char m_pad[0x54];
	NameKeyType m_key;
};
class Rva003A28ED
{
public:
	bool rva003A28ED(NameKeyType key);
};
extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
void __stdcall Rva003C4449Do(const AsciiString &teamName, const AsciiString &playerName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	NameKeyType key = TheNameKeyGenerator->nameToKey(playerName);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	if (team == 0)
		return;
	if (player == 0)
		return;
	((Rva003A28ED *)team)->rva003A28ED(player->m_key);
}
