// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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
	void rva003A38E9(int a, int b);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BECCDSet(const AsciiString &team, int a, int b)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->rva003A38E9(a, b);
}
