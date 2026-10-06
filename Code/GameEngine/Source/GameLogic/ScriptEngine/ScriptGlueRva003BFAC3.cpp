// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003BFAC3Set@@YGXABVAsciiString@@H@Z @0x003BFAC3 49B (dump range 18).
// Team int setter through the doSetTeamState argument idiom: copies the
// name through the rowed StringBase copy ctor, resolves the team through
// rowed ScriptEngine 0x003584E9 getTeamNamed, and applies the pinned
// 0x003A10FE (int) member when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team
{
public:
	void rva003A10FE(int v);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BFAC3Set(const AsciiString &team, int v)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->rva003A10FE(v);
}
