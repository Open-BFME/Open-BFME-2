// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?Rva003C388EDo@@YGXPAVParameter@@_N@Z @0x003C388E 60B: team named then Team predicate iterate. Evidence: rowed getTeamNamed 0x3584E9 rva0039DD12 0x39DD12 StringBase copy 0x365F0 globals g_Va009FE16C; caller 0x003CE9DF; ret 0x8 stdcall.
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
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, bool exact);
};
extern class ScriptEngine *TheScriptEngine;

struct Rva003C388EObject
{
	char m_pad[0x264];
	void *m_264;
};

class Rva003BD306Target
{
public:
	void rva0039B28F(bool on);
};

// Team iterate callback 0x0028870A (28B): pass the action's flag, carried in
// the userdata, to each member's +0x264 object, then continue.
int __cdecl Rva0028870A(Object *obj, void *userData)
{
	((Rva003BD306Target *)((Rva003C388EObject *)obj)->m_264)->rva0039B28F(userData != 0);
	return 1;
}

void __stdcall Rva003C388EDo(Parameter *parm, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed(parm->m_string, false);
	if (team == 0)
		return;
	team->rva0039DD12(Rva0028870A, (void *)flag);
}
