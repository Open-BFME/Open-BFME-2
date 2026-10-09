// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE
//
// ?Rva003C1EC2Set@@YGXABVAsciiString@@H@Z @0x003C1EC2 72B: team experience
// set. Resolves the team through rowed ScriptEngine 0x003584E9 getTeamNamed
// and applies the all-of iterate 0x0039DD12 twice: callback 0x002886E9 with
// the int as user data, then the rowed callback 0x00288726 with null.
// ?Rva002886E9@@YAHPAVObject@@PAX@Z @0x002886E9 33B: converts the user data
// to a float and applies it to the object at Object +0x264 through the
// pinned 0x0039B3D1 (amount then false), then continues the iteration.
// Evidence: callee REL32s and call frames read from retail.
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

class Rva003BD306Target
{
public:
	void rva0039B3D1(float amount, bool flag);
};

struct Rva002886E9Object
{
	char m_pad[0x264];
	Rva003BD306Target *m_264;
};

int __cdecl Rva00288726(Object *obj, void *userData);

int __cdecl Rva002886E9(Object *obj, void *userData)
{
	((Rva002886E9Object *)obj)->m_264->rva0039B3D1((float)(int)userData, false);
	return 1;
}

void __stdcall Rva003C1EC2Set(const AsciiString &team, int v)
{
	Team *t = TheScriptEngine->getTeamNamed(team, false);
	if (t != 0)
	{
		t->rva0039DD12(Rva002886E9, (void *)v);
		t->rva0039DD12(Rva00288726, 0);
	}
}
