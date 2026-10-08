// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Two ScriptActions team setters: look the team up by name through
// TheScriptEngine's rowed getTeamNamed (name by value, false) and walk its
// members with the rowed iterate_TeamMemberList and pinned advance,
// skipping null members as Zero Hour's loops do (that test is what keeps
// the member in ecx from the loop test into the call; earlier banked
// spellings without it missed exactly there).
//   0x003BEED1 (79B): Zero Hour's doTeamSetRepulsor - executeAction's case
//                     0xEC (initActionTemplates index 236, TEAM_SET_REPULSOR)
//                     reaches it; Object::setStatus(8, flag) on each member.
//   0x003C05DE (79B): the same walk with Object::setScriptStatus(0x20, flag)
//                     (dispatcher call 0x003CBE04); name address-derived.
// Neither reads `this`, as in Zero Hour.
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
	OBJECT_STATUS_BFME_8 = 8
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_BFME_20 = 0x20
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	void setScriptStatus(ObjectScriptStatusBit bit, bool set);
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

class ScriptActions
{
protected:
	void doTeamSetRepulsor(const AsciiString &teamName, bool repulsor);
	void rva003C05DE(const AsciiString &teamName, bool flag);
};

void ScriptActions::doTeamSetRepulsor(const AsciiString &teamName, bool repulsor)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		obj->setStatus(OBJECT_STATUS_BFME_8, repulsor);
	}
}

void ScriptActions::rva003C05DE(const AsciiString &teamName, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_BFME_20, flag);
	}
}
