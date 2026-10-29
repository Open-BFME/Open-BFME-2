// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?doTeamDelete@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BFAC3 49B (dump range 18).
// Team int setter through the doSetTeamState argument idiom: copies the
// name through the rowed StringBase copy ctor, resolves the team through
// rowed ScriptEngine 0x003584E9 getTeamNamed, and applies the pinned
// 0x003A10FE (int) member when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team
{
public:
	// LINK: 0x003A10FE is rowed as Team::deleteTeam(bool) (Team rows); the old int-flag call stays through a member-pointer cast.
	void deleteTeam(bool v);
};
typedef void (Team::*TeamDeleteIntShape)(int);

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doTeamDelete(const AsciiString &team, int v)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		(t->*reinterpret_cast<TeamDeleteIntShape>(&Team::deleteTeam))(v);
}
