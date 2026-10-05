// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
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
extern ScriptEngine *g_Va009FE16C;

static int __cdecl Cb(Object *, void *)
{
	return 1;
}

void __stdcall Rva003C388EDo(Parameter *parm, bool flag)
{
	Team *team = g_Va009FE16C->getTeamNamed(parm->m_string, false);
	if (team == 0)
		return;
	team->rva0039DD12(Cb, (void *)flag);
}
