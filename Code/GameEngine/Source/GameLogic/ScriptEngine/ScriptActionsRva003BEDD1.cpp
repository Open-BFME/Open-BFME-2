// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003BEDD1@ScriptActions@@IAEXABVAsciiString@@0@Z @ 0x003BEDD1 (141B). Sets attack priority info on a team and its members.
// Evidence: neighbours ScriptActions_doTeamAttackTeam 0x003BED59 Rva003BEE5EFinish 0x003BEE5E same flags; callees getTeamNamed 0x003584E9 getAttackInfo pinned isEmpty rva0039F094 iterate advance rowed; caller 1 unclaimed.
#include "ascii_string.h"
class Team;
class Object;
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail { public: unsigned char m_carrier[4]; };
class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };
class BfmeObjectDlinkBase { public: Object *dlink_next_TeamMemberList() const; };
class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase, public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier { public: unsigned char m_tail[0x40]; };
template<class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};
class AttackPriorityInfo
{
public:
	unsigned int m_head;
	StringBase<char> m_name;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool = false);
	const AttackPriorityInfo *getAttackInfo(const AsciiString &);
};
extern class ScriptEngine *TheScriptEngine;
class Team
{
public:
	void rva0039F094(AsciiString);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptActions
{
protected:
	void rva003BEDD1(const AsciiString &, const AsciiString &);
};
void ScriptActions::rva003BEDD1(const AsciiString &teamName, const AsciiString &attackName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (team == 0)
		return;
	const AttackPriorityInfo *info = TheScriptEngine->getAttackInfo(attackName);
	StringBase<char> *name = (StringBase<char> *)((char *)info + 4);
	if (name->isEmpty())
	{
	}
	else
	{
		team->rva0039F094(*(AsciiString *)name);
	}
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance())
	{
		Object *obj = it.cur();
		void *holder = *(void **)((char *)obj + 0x258);
		if (holder != 0)
			*(const AttackPriorityInfo **)((char *)holder + 0x70) = info;
	}
}
