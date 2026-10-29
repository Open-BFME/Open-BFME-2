// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?doTeamStopSequentialScript@ScriptActions@@QAEXABVAsciiString@@@Z @0x003C0C3E 51B (dump range 18).
// Team forward through the doSetTeamState argument idiom: copies the name
// through the rowed StringBase copy ctor, resolves the team through rowed
// ScriptEngine 0x003584E9 getTeamNamed, and forwards it to the pinned
// ScriptEngine 0x002064CB member (a jump-stub) when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doTeamStopSequentialScript(const AsciiString &team)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		TheScriptEngine->rva002064CB(t);
}
