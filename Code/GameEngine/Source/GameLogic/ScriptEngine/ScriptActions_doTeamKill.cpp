// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?doTeamKill@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BFD5A 46B (dump range 18).
// Team nullary setter through the doSetTeamState argument idiom: copies
// the name through the rowed StringBase copy ctor, resolves the team
// through rowed ScriptEngine 0x003584E9 getTeamNamed, and applies the
// pinned 0x003A1D1A member when non-null.
#include "ascii_string.h"

typedef bool Bool;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doTeamKill(const AsciiString &team)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->killTeam();
}
