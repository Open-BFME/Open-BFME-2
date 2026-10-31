// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?doDamageTeamMembers@ScriptActions@@QAEXABVAsciiString@@M@Z @0x003BE9DB 53B (dump range 18).
// Team float setter through the doSetTeamState argument idiom: copies the
// name through the rowed StringBase copy ctor, resolves the team through
// rowed ScriptEngine 0x003584E9 getTeamNamed, and calls the rowed
// Team::damageTeamMembers (0x0039E76C, stack-float shape) when non-null.
#include "ascii_string.h"

typedef bool Bool;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::doDamageTeamMembers(const AsciiString &team, float f)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->damageTeamMembers(f);
}
