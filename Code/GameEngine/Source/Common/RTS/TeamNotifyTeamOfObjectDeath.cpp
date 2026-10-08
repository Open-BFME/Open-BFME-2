// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?notifyTeamOfObjectDeath@Team@@QAEXPAVObject@@@Z, retail 0x0039F835 (194 bytes).
// Donor (Zero Hour Team.cpp Team::notifyTeamOfObjectDeath): with a template
// info whose m_scriptOnUnitDestroyed is set, have TheScriptEngine run it for
// this team.
// Target evidence: WorldBuilder lead names 0x0039F835
// Team::notifyTeamOfObjectDeath; its one caller (0x002986E9) passes the dying
// Object after reading its team at Object+0x304. Retail takes the template
// info at m_proto (+0x30) +0x12C, tests the script AsciiString at info+0xD8
// with the out-of-line StringBase::isEmpty, and calls TheScriptEngine
// (0x00DFE16C) 0x0020C140 -- unnamed, pinned by address -- with
// (prototype name or the empty string, script, this) where the donor calls
// runScript(script, this).
// BFME 2 delta (target): before the script, when no member is both alive
// (Object+0x438 bit 0 clear) and AI-driven (Object+0x258), it raises Lua
// object event 7 for the dying object through the 0x00E01DBC dispatch,
// with a stack event list, exactly as the matched
// AIUpdateInterface::setCompletedWaypoint raises event 2.
#include "ascii_string.h"

class Object
{
public:
	bool isEffectivelyDead() const { return (m_privateStatus & 0x01) != 0; }
	void *getAIUpdateInterface() const { return m_ai; }

private:
	char m_pad[0x258];
	void *m_ai; // +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus; // +0x438
};

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
struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class Team;

class ScriptEngine
{
public:
	void rva0020C140(const AsciiString &name, const AsciiString &script, Team *team);
};
extern ScriptEngine *g_Va009FE16C;

struct TeamTemplateInfo
{
	char m_pad[0xD8];
	AsciiString m_scriptOnUnitDestroyed; // +0xD8
};

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	const TeamTemplateInfo *getTemplateInfo() const { return &m_teamTemplate; }

private:
	char m_pad[0x10];
	AsciiString m_name; // +0x10
	char m_pad14[0x12C - 0x14];
	TeamTemplateInfo m_teamTemplate; // +0x12C
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	const AsciiString &getPrototypeName() const
	{
		return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getName();
	}
	void notifyTeamOfObjectDeath(Object *obj);

private:
	char m_pad[0x30];
	TeamPrototype *m_proto; // +0x30
};

void Team::notifyTeamOfObjectDeath(Object *obj)
{
	if (!m_proto)
		return;
	const TeamTemplateInfo *pInfo = m_proto->getTemplateInfo();
	if (!pInfo)
		return;

	for (DLINK_ITERATOR<Object> it = iterate_TeamMemberList(); !it.done();
		it.advance())
	{
		Object *member = it.cur();
		if (!member->isEffectivelyDead() && member->getAIUpdateInterface())
			goto runScripts;
	}
	{
		BfmeDelayedLuaEventList list;
		reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(7, obj, &list);
	}

runScripts:
	if (((const StringBase<char> *)&pInfo->m_scriptOnUnitDestroyed)->isEmpty())
		return;

	g_Va009FE16C->rva0020C140(getPrototypeName(), pInfo->m_scriptOnUnitDestroyed, this);
}
