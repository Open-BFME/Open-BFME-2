// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?doTeamForceEmotion@ScriptActions@@IAEXPAVParameter@@HM@Z @0x003C375A (102B): a
// script action (dispatcher call 0x003CE964) that, for an emotion index in
// [0, 12), looks the team up by its parameter's name (+0x10 string) through
// the rowed getTeamNamed and hands (index, value, 0) to each member's
// emotion-tracker forwarder, the rowed Object::rva0028ECA8. Member walk and
// null skip as in ScriptActions_doTeamSetRepulsor.cpp.
#include "ascii_string.h"

class Object;
class Team;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
class Object
{
public:
	void rva0028ECA8(int index, float value, int arg);
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class Parameter;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
	Object *getUnitNamed(Parameter *unitParam);
};
extern class ScriptEngine *TheScriptEngine;

// A script parameter: its string at +0x10, as in Zero Hour's Parameter.
class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_pad[0x10];
	AsciiString m_string; // +0x10
};

class ScriptActions
{
protected:
	void doUnitForceEmotion(Parameter *pUnit, int index, float value);
	void doTeamForceEmotion(Parameter *pTeam, int index, float value);
};

// ScriptActions::doUnitForceEmotion, retail 0x003BD2CE (56B): the single-unit
// form - the unit resolved from its parameter by the rowed getUnitNamed.
void ScriptActions::doUnitForceEmotion(Parameter *pUnit, int index, float value)
{
	if (index < 0 || index >= 12)
		return;
	Object *obj = TheScriptEngine->getUnitNamed(pUnit);
	if (!obj)
		return;
	obj->rva0028ECA8(index, value, 0);
}

void ScriptActions::doTeamForceEmotion(Parameter *pTeam, int index, float value)
{
	if (index < 0 || index >= 12)
		return;
	Team *team = TheScriptEngine->getTeamNamed(pTeam->getString(), false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		obj->rva0028ECA8(index, value, 0);
	}
}
