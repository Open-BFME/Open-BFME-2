// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// ?Rva003C0C3ESet@@YGXABVAsciiString@@@Z @0x003C0C3E 51B (dump range 18).
// Team forward through the doSetTeamState argument idiom: copies the name
// through the rowed StringBase copy ctor, resolves the team through rowed
// ScriptEngine 0x003584E9 getTeamNamed, and forwards it to the pinned
// ScriptEngine 0x002064CB member (a jump-stub) when non-null.
#include "ascii_string.h"

typedef bool Bool;

class Team;
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
	void rva002064CB(Team *t);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C0C3ESet(const AsciiString &team)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		TheScriptEngine->rva002064CB(t);
}
