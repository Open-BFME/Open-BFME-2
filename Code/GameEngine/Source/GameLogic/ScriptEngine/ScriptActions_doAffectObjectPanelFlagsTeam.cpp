// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doAffectObjectPanelFlagsTeam, retail 0x003C5C93 (102B;
// dispatcher call 0x003CD8F0): Zero Hour's body - the team by name, then
// changeObjectPanelFlagForSingleObject (0x003C4C07, pinned) on each member.
// BFME2 calls iterate_TeamMemberList once and assigns it to the declared
// iterator (the 24-byte copy after the call), where Zero Hour also
// initialised the iterator with a first call.
//
// ScriptActions::doSetCounterToThreatFinderThreat, retail 0x003C5E10 (267B;
// ret 0x10). Name, parameter order and statement order from WorldBuilder's
// ScriptActions.cpp twin (wb 0x1016790 region): the counter (pinned
// bfmeCounter 0x0020874B, by value), the player mask (rowed 0x00357475) and
// player (rowed getPlayerFromMask 0x002A7B91), "Enemies"/"Allies" to 0/1
// (WB's invalid-type and invalid-player branches only assert), then the
// threat finder by name from the manager at VA 0x00E02E48 (g_manager; the
// find is the ICF body at 0x0041F474, placeholder-pinned), whose
// getThreatForPlayer (pinned 0x003ED0C4) fills a 0x44-byte record whose
// first float goes to the counter. A missing finder appends WB's warning.
#include "ascii_string.h"

class Object;
class Player;

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
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class Parameter;

struct ScriptCounter
{
	int m_value;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
	Object *getUnitNamed(Parameter *unitParam);
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
	void AppendDebugMessage(const AsciiString &msg, bool shouldPause);
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	friend class ScriptActions;
};
extern class ScriptEngine *TheScriptEngine;

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

// WB ThreatFinderUpdate.cpp: the record getThreatForPlayer returns by value.
struct ThreatInfo
{
	float m_threat;
	unsigned char m_pad[0x40];
};

class ThreatFinder
{
public:
	ThreatInfo getThreatForPlayer(Player *player, int threatType, Player *other);
};

class Rva003ED2A3Manager
{
public:
	ThreatFinder *rva0041F474(const AsciiString &name) const;
};
extern Rva003ED2A3Manager *g_manager;

class ScriptActions
{
protected:
	void changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString &flagToChange, bool newVal);
	void doAffectObjectPanelFlagsUnit(Parameter *unitParam, const AsciiString &flagName, bool enable);
	void doAffectObjectPanelFlagsTeam(const AsciiString &teamName, const AsciiString &flagName, bool enable);
	void doSetCounterToThreatFinderThreat(const AsciiString &counterName, const AsciiString &threatFinderName,
		const AsciiString &threatType, const AsciiString &playerName);
};

// ScriptActions::doAffectObjectPanelFlagsUnit, retail 0x003C5C69 (42B),
// directly before the team version as in Zero Hour; BFME2 resolves the
// unit from its parameter through the rowed getUnitNamed.
void ScriptActions::doAffectObjectPanelFlagsUnit(Parameter *unitParam, const AsciiString &flagName, bool enable)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitParam);
	if (!obj)
		return;
	changeObjectPanelFlagForSingleObject(obj, flagName, enable);
}

void ScriptActions::doAffectObjectPanelFlagsTeam(const AsciiString &teamName, const AsciiString &flagName, bool enable)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (!team)
		return;
	DLINK_ITERATOR<Object> iter;
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		changeObjectPanelFlagForSingleObject(obj, flagName, enable);
	}
}

void ScriptActions::doSetCounterToThreatFinderThreat(const AsciiString &counterName,
	const AsciiString &threatFinderName, const AsciiString &threatType, const AsciiString &playerName)
{
	ScriptCounter *counter = TheScriptEngine->bfmeCounter(counterName);
	if (!counter)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (!mask)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return;
	int type;
	if (threatType.compare("Enemies") == 0)
		type = 0;
	else if (threatType.compare("Allies") == 0)
		type = 1;
	else
		return;
	ThreatFinder *finder = g_manager->rva0041F474(threatFinderName);
	if (finder) {
		counter->m_value = (int)finder->getThreatForPlayer(player, type, 0).m_threat;
	} else {
		AsciiString msg = "WARNING - Threat Finder not found during script execution: ";
		msg.concat(threatFinderName);
		msg.concat(".");
		TheScriptEngine->AppendDebugMessage(msg, false);
	}
}
