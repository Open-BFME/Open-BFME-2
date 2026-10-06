// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003BFD5ASet@@YGXABVAsciiString@@@Z @0x003BFD5A 46B (dump range 18).
// Team nullary setter through the doSetTeamState argument idiom: copies
// the name through the rowed StringBase copy ctor, resolves the team
// through rowed ScriptEngine 0x003584E9 getTeamNamed, and applies the
// pinned 0x003A1D1A member when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team
{
public:
	void rva003A1D1A();
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BFD5ASet(const AsciiString &team)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->rva003A1D1A();
}
