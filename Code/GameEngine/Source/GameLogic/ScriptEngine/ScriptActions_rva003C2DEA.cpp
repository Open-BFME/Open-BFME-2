// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2DEADo@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C2DEA 119B
// Script sum team member Object+0x618 field then set counter: team via rowed
// getTeamNamed 0x003584E9 by value with false, iterate via rowed 0x00263864,
// advance via rowed 0x00263526, value int at *(iter+0)+4 then +0x618, counter via
// pin bfmeCounter 0x0020874B by value. Evidence: callers 0x003CE22B; neighbours
// Rva003C2CD8 0x003C2CD8 Rva003C2E61 0x003C2E61; globals g_Va009FE16C; copy 0x365F0.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_string;
};

class ObjectMid
{
public:
	char m_pad[0x618];
	int m_618;
};

class Object
{
public:
	char m_pad[4];
	ObjectMid *m_p4;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_rest[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

struct ScriptCounter
{
	int m_value;
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C2DEADo(Parameter *parameter, Parameter *b)
{
	Team *team = TheScriptEngine->getTeamNamed(parameter->m_string, false);
	if (team == 0)
		return;
	int total = 0;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		total += obj->m_p4->m_618;
	}
	ScriptCounter *scriptCounter = TheScriptEngine->bfmeCounter(b->m_string);
	scriptCounter->m_value = total;
}
