// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003C43A3Do@@YGXABVAsciiString@@0@Z @0x003C43A3 80B.
// Script free function finding Player by name key and Team named then
// calling rowed armor remove. Evidence: chain lane via 0x002AD19E,
// prev doTeamAttackNamed and next Rva003C4570Do share /O1 /EHsc and
// two-AsciiString void stdcall shape plus ScriptEngine global 0xDFE16C.
typedef int Int;
typedef bool Bool;
class Object;
class Team;
class Player;
#include "ascii_string.h"
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
};
extern ScriptEngine *TheScriptEngine;
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
class Rva002AD19E
{
public:
	bool rva002AD19E(void *arg);
};
#define TheNameKeyGen TheNameKeyGenerator
void __stdcall Rva003C43A3Do(const AsciiString &playerName, const AsciiString &teamName)
{
	NameKeyType key = TheNameKeyGen->nameToKey(playerName);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (player == 0)
		return;
	if (team == 0)
		return;
	((Rva002AD19E *)player)->rva002AD19E(team);
}
