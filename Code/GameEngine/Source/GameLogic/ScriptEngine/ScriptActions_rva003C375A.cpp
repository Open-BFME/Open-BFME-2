// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva003C375A@ScriptActions@@IAEXPAVParameter@@HM@Z @0x003C375A (102B): a
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
template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
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
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
};
extern ScriptEngine *g_Va009FE16C;

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
	void rva003C375A(Parameter *pTeam, int index, float value);
};

void ScriptActions::rva003C375A(Parameter *pTeam, int index, float value)
{
	if (index < 0 || index >= 12)
		return;
	Team *team = g_Va009FE16C->getTeamNamed(pTeam->getString(), false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); ((Rva001705A0DlinkIterator<Object> *)&it)->advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		obj->rva0028ECA8(index, value, 0);
	}
}
