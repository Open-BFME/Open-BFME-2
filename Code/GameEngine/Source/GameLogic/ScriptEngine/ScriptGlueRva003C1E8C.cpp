// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE
//
// ?Rva003C1E8CSet@@YGXABVAsciiString@@H@Z @0x003C1E8C 54B: team experience
// grant. Resolves the team through rowed ScriptEngine 0x003584E9
// getTeamNamed and applies the all-of iterate 0x0039DD12 with the callback
// 0x002886C2, passing the int through the user data.
// ?Rva002886C2@@YAHPAVObject@@PAX@Z @0x002886C2 39B: the callback converts
// the user data to a float and grants it to the tracker at Object +0x264
// through the pinned 0x0039B315 (amount then true true true false), then
// continues the iteration. Evidence: callee REL32s and the call frame read
// from retail; the tracker class name comes from the pin.
#include "ascii_string.h"

typedef bool Bool;
class Object;
typedef int (__cdecl *TeamPredicate)(Object *obj, void *userData);

class Team
{
public:
	int rva0039DD12(TeamPredicate pred, void *userData) const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
};
extern ScriptEngine *TheScriptEngine;

class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);
};

struct Rva002886C2Object
{
	char m_pad[0x264];
	ExperienceTracker *m_264;
};

int __cdecl Rva002886C2(Object *obj, void *userData)
{
	((Rva002886C2Object *)obj)->m_264->rva0039B315((float)(int)userData, true, true, true, false);
	return 1;
}

void __stdcall Rva003C1E8CSet(const AsciiString &team, int v)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
		t->rva0039DD12(Rva002886C2, (void *)v);
}
