// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C388EDo@ScriptActions@@QAEXPAVParameter@@_N@Z @0x003C388E 60B: team named then Team predicate iterate. Evidence: rowed getTeamNamed 0x3584E9 rva0039DD12 0x39DD12 StringBase copy 0x365F0 globals g_Va009FE16C; caller 0x003CE9DF; ret 0x8 stdcall.
#include "ascii_string.h"

class Object;
class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};
typedef int (__cdecl *TeamPredicate)(Object *obj, void *userData);
class Team
{
public:
	int rva0039DD12(TeamPredicate pred, void *userData) const;
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

struct Rva003C388EObject
{
	char m_pad[0x264];
	void *m_264;
};

class Rva003BD306Target
{
public:
	// LINK: rowed as rva0039B28F(bool) (Rva003BD306 sibling row); the old bool call shape is kept through a member-pointer cast.
	void rva0039B28F(bool on);
};

// Team iterate callback 0x0028870A (28B): pass the action's flag, carried in
// the userdata, to each member's +0x264 object, then continue.
int __cdecl Rva0028870A(Object *obj, void *userData)
{
	((Rva003BD306Target *)((Rva003C388EObject *)obj)->m_264)->rva0039B28F(userData != 0);
	return 1;
}

void ScriptActions::Rva003C388EDo(Parameter *parm, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed(parm->m_string, false);
	if (team == 0)
		return;
	team->rva0039DD12(Rva0028870A, (void *)flag);
}
