// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
//
// ?Rva003C21E5Do@@YGXPBVAsciiString@@HPBV0@@Z @0x003C21E5 123B (dump range 18).
// Two-team wiring: team-name copy (true flag), getTeamNamed, second
// team-name copy (false flag, esp-save to dead slot), getTeamNamed, template
// lookup plus object-types lookup off the third name, then the pinned Team
// 0x003A1626 member with (second team, int, types, template). Straight line,
// identities unproven beyond byte roles.
#include "ascii_string.h"

class Team;
class ObjectTypes;

class Team
{
public:
	void rva003A1626(void *a, void *b, int v, Team *other);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
	ObjectTypes *getObjectTypes(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern class ThingFactory *TheThingFactory;

void __stdcall Rva003C21E5Do(const AsciiString *str1, int x, const AsciiString *str2, const AsciiString *str3)
{
	Team *team1 = TheScriptEngine->getTeamNamed(*str1, true);
	if (team1 == 0)
		return;
	Team *team2 = TheScriptEngine->getTeamNamed(*str3, false);
	if (team2 == 0)
		return;
	void *r1 = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(str2);
	ObjectTypes *types = TheScriptEngine->getObjectTypes(*str2);
	team1->rva003A1626(r1, types, x, team2);
}
