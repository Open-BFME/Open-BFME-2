// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva003BED01@ScriptActions@@IAEXPAVParameter@@ABVAsciiString@@@Z @ 0x003BED01 (88B). Binds a unit to a team with a virtual hook.
// Evidence: neighbours doSetTeamState 0x003BEC9B doTeamAttackTeam 0x003BED59 same flags; callees getUnitNamed getTeamNamed isEmpty rva00298AE4 iterate rowed getAttackInfo pinned; caller 1 unclaimed.
#include "ascii_string.h"
class Parameter;
class Team;
class Object;
class BfmeUnitHook
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(Team *team);
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
	Team *getTeamNamed(AsciiString, bool = false);
};
extern ScriptEngine *g_Va009FE16C;
class Object
{
public:
	void rva00298AE4(Team *team);
};
class Team
{
};
class ScriptActions
{
protected:
	void rva003BED01(Parameter *, const AsciiString &);
};
void ScriptActions::rva003BED01(Parameter *unitParam, const AsciiString &teamName)
{
	Object *unit = g_Va009FE16C->getUnitNamed(unitParam);
	Team *team = g_Va009FE16C->getTeamNamed(teamName, true);
	if (unit == 0)
		return;
	if (team == 0)
		return;
	BfmeUnitHook *hook = *(BfmeUnitHook **)((char *)unit + 0x250);
	if (hook != 0)
		hook->slot21(team);
	unit->rva00298AE4(team);
}
