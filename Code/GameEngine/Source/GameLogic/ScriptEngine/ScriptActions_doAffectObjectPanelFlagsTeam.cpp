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

// Zero Hour and BFME1 9cbfb551 ScriptActions.cpp establish the seven flag
// actions. BFME1's clean unit was compiled under BFME2 settings as a lead.
// Native3C4C07..3C4D5C and WBFFA7A0 independently add propagation of the
// Indestructible flag through horde members. The retail object fields are
// contain+250 / body+254 / AI+258, with recruitable at AI+3BE.
// The containment accessor returns a pointer at slot31. Slot70 fills an
// eight-byte non-POD result: its second word points at a one-word list with
// next/previous/object nodes. The first result word and original return type
// remain opaque; retail performs no cleanup of it. These views express only
// the observed native ABI and list traversal, not a recovered class contract.
extern const char *TheObjectFlagsNames[];
enum ObjectScriptStatusBit {OBJECT_STATUS_SCRIPT_DISABLED=1,OBJECT_STATUS_SCRIPT_UNPOWERED=2,OBJECT_STATUS_SCRIPT_UNSELLABLE=4,OBJECT_STATUS_SCRIPT_TARGETABLE=16};
class Object {public:void setScriptStatus(ObjectScriptStatusBit,bool);bool isSelectable()const;void setSelectable(bool);};
struct PanelFlagNode {PanelFlagNode *next,*prev;Object *object;};
struct PanelFlagList {PanelFlagNode *sentinel;};
struct PanelFlagListResult {PanelFlagListResult();void *unused;PanelFlagList *list;};
class PanelFlagContainView {public:
#define V(n) virtual void pad##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
 virtual void *hordeView();V(32)
 V(33)
 V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43)
 V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53)
 V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
 V(64) V(65) V(66) V(67) V(68) V(69)
#undef V
 virtual PanelFlagListResult members();
};
// Separate ABI views: the body setter is slot33; containment uses slots31/70.
class PanelFlagBodyView {public:
#define V(n) virtual void pad##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32)
#undef V
 virtual void setIndestructible(bool);
};
struct PanelFlagRecruit {char unknown[0x3be];bool recruitable;};
struct PanelFlagObjectView {char unknown[0x250];PanelFlagContainView *contain;PanelFlagBodyView *body;PanelFlagRecruit *ai;};
void ScriptActions::changeObjectPanelFlagForSingleObject(Object *obj,
	const AsciiString &flagToChange, bool newVal)
{
	bool propagate = false;
	if (flagToChange.compare(TheObjectFlagsNames[0]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[1]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_UNPOWERED, !newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[2]) == 0) {
		PanelFlagBodyView *body = ((PanelFlagObjectView *)obj)->body;
		if (body)
			body->setIndestructible(newVal);
		propagate = true;
	} else if (flagToChange.compare(TheObjectFlagsNames[3]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_UNSELLABLE, newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[4]) == 0) {
		if (obj->isSelectable() != newVal)
			obj->setSelectable(newVal);
	} else if (flagToChange.compare(TheObjectFlagsNames[5]) == 0) {
		if (((PanelFlagObjectView *)obj)->ai)
			((PanelFlagObjectView *)obj)->ai->recruitable = newVal;
	} else if (flagToChange.compare(TheObjectFlagsNames[6]) == 0) {
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_TARGETABLE, newVal);
	} else {
		return;
	}
	if (propagate) {
		PanelFlagObjectView *view = (PanelFlagObjectView *)obj;
		PanelFlagContainView *contain = view->contain;
		if (contain && contain->hordeView()) {
			PanelFlagListResult members = view->contain->members();
			for (PanelFlagNode *node = members.list->sentinel->next;
				node != members.list->sentinel; node = node->next) {
				if (node->object)
					changeObjectPanelFlagForSingleObject(node->object, flagToChange, newVal);
			}
		}
	}
}
