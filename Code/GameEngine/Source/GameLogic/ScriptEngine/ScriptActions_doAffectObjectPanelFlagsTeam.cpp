// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptActions::doAffectObjectPanelFlagsTeam, retail 0x003C5C93 (102B;
// dispatcher call 0x003CD8F0): Zero Hour's body - the team by name, then
// changeObjectPanelFlagForSingleObject (0x003C4C07, pinned) on each member.
// BFME2 calls iterate_TeamMemberList once and assigns it to the declared
// iterator (the 24-byte copy after the call), where Zero Hour also
// initialised the iterator with a first call.
#include "ascii_string.h"

class Object;

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

class ScriptActions
{
protected:
	void changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString &flagToChange, bool newVal);
	void doAffectObjectPanelFlagsTeam(const AsciiString &teamName, const AsciiString &flagName, bool enable);
};

void ScriptActions::doAffectObjectPanelFlagsTeam(const AsciiString &teamName, const AsciiString &flagName, bool enable)
{
	Team *team = g_Va009FE16C->getTeamNamed((AsciiString &)teamName, false);
	if (!team)
		return;
	DLINK_ITERATOR<Object> iter;
	for (iter = team->iterate_TeamMemberList(); !iter.done(); ((Rva001705A0DlinkIterator<Object> *)&iter)->advance())
	{
		Object *obj = iter.cur();
		changeObjectPanelFlagForSingleObject(obj, flagName, enable);
	}
}
