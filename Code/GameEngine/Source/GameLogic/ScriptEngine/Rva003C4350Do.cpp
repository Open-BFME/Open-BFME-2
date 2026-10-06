// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003C4350Do@@YGXABVAsciiString@@0PAVObject@@@Z @0x003C4350 83B.
// Script free function finding Player by name key and Team named then
// calling rowed rva002ADFC7 store. Evidence: prev doTeamAttackNamed and
// next Rva003C43A3Do share /O1 /EHsc and ScriptEngine global 0xDFE16C;
// callees nameToKey 0x9FA65 and findPlayer 0x2A7A41 and getTeamNamed
// 0x3584E9 and rva002ADFC7 0x2ADFC7 match retail call order.
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
class Rva002ADFC7
{
public:
	void rva002ADFC7(const Team *t, Object *o);
};
#define TheNameKeyGen TheNameKeyGenerator
void __stdcall Rva003C4350Do(const AsciiString &playerName, const AsciiString &teamName, Object *obj)
{
	NameKeyType key = TheNameKeyGen->nameToKey(playerName);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (player == 0)
		return;
	if (team == 0)
		return;
	((Rva002ADFC7 *)player)->rva002ADFC7(team, obj);
}
