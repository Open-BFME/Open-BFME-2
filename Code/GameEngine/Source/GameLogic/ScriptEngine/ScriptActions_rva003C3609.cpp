// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptActions::rva003C3609, retail 0x003C3609 (110B; dispatcher call
// 0x003CE888): for the parameter-named team, asks TheGameLogic's +0x184
// member for a handle and, when there is one, applies it to every member
// (both through GameLogic's 11-byte forwarders, pinned from these calls).
// Same team lookup and member walk as ScriptActions_rva003C375A.cpp; this
// loop has no null skip, matching retail's cmp-memory loop test.
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

class Object;

// TheGameLogic's forwarders to its +0x184 member (0x0023D0B7 returns a
// handle, 0x0023D0C2 applies it to an object); pinned from this body.
class GameLogic
{
public:
	int rva0023D0B7();
	void rva0023D0C2(Object *obj, int handle);
};
extern GameLogic *TheGameLogic;

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
	void rva003C3609(Parameter *pTeam);
};

void ScriptActions::rva003C3609(Parameter *pTeam)
{
	Team *team = g_Va009FE16C->getTeamNamed(pTeam->getString(), false);
	if (team == 0)
		return;
	int handle = TheGameLogic->rva0023D0B7();
	if (handle == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); ((Rva001705A0DlinkIterator<Object> *)&it)->advance())
		TheGameLogic->rva0023D0C2(it.cur(), handle);
}
