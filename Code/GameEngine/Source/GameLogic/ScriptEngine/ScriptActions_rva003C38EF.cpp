// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::rva003C38EF
// @0x003C38EF (84B): sets or clears an object status on every member of the
// parameter-named team (rowed getTeamNamed, member walk with the null skip
// as in ScriptActions_rva003C375A.cpp, rowed Object::setStatus).
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
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
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
	void rva003C38EF(Parameter *pTeam, ObjectStatusTypes status, bool set);
};

void ScriptActions::rva003C38EF(Parameter *pTeam, ObjectStatusTypes status, bool set)
{
	Team *team = TheScriptEngine->getTeamNamed(pTeam->getString(), false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		obj->setStatus(status, set);
	}
}
