// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?doTeamDelete@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BFAC3 49B (dump range 18).
// Team int setter through the doSetTeamState argument idiom: copies the
// name through the rowed StringBase copy ctor, resolves the team through
// rowed ScriptEngine 0x003584E9 getTeamNamed, and applies the pinned
// 0x003A10FE Team::deleteTeam when non-null.
#include "ascii_string.h"



#include "../../../Include/Common/TeamBFME2.h"
// 0x003A10FE is Team::deleteTeam(bool); retail pushes the int argument
// unconverted, so the call reads its flag in place.

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doTeamDelete(const AsciiString &team, int v)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->deleteTeam(*reinterpret_cast<bool *>(&v));
}
