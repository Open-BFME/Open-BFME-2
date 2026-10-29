// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
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
	// Row 0x003A1626 spelling (returns int, typed template/list arguments).
	int rva003A1626(const class ThingTemplate *a, class Rva00376A62 *b, int v, Team *other);
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern class ThingFactory *TheThingFactory;

void ScriptActions::Rva003C21E5Do(const AsciiString *str1, int x, const AsciiString *str2, const AsciiString *str3)
{
	Team *team1 = TheScriptEngine->getTeamNamed(*str1, true);
	if (team1 == 0)
		return;
	Team *team2 = TheScriptEngine->getTeamNamed(*str3, false);
	if (team2 == 0)
		return;
	void *r1 = (void *)TheThingFactory->findTemplate(*str2);
	ObjectTypes *types = TheScriptEngine->getObjectTypes(*str2);
	team1->rva003A1626((const ThingTemplate *)r1, (Rva00376A62 *)types, x, team2);
}
