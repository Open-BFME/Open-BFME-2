// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BECCDSet@@YGXABVAsciiString@@HH@Z @0x003BECCD 52B (dump range 18).
// Team pair setter through the doSetTeamState argument idiom: copies the
// name through the rowed StringBase copy ctor, resolves the team through
// rowed ScriptEngine 0x003584E9 getTeamNamed, and applies the pinned
// 0x003A38E9 (int, int) member when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team
{
public:
	void rva003A38E9(const AsciiString &a, unsigned char b);
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BECCDSet(const AsciiString &team, const AsciiString &asciiString, bool b)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->rva003A38E9(asciiString, b);
}
