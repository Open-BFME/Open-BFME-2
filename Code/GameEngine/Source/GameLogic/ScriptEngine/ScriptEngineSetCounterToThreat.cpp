// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ScriptEngine::setCounterToThreat, retail 0x00209003 (321B; ret 8).
//
// Identity (target): WorldBuilder twin 0xB38250 carries the name
// ScriptEngine::setCounterToThreat and ScriptEngine.cpp asserts at lines
// 1976..2004; the dispatcher executeActions (0x0020C5C7) calls it for action
// types 0x1B7 (false) and 0x1B8 (true). Callees from the WB twin's call list,
// each read at the retail REL32: bfmeCounter 0x0020874B, getTeamNamed
// 0x003584E9 and the unit lookup 0x00358752 on TheScriptEngine, the team and
// object radius helpers 0x003A3736 / 0x002972B1, the threat-finder find
// 0x0041F474 on g_manager and ThreatFinder::getThreatForPlayer 0x003ED0C4.
// The template test is WB's BitFlags<KindOfType>::test, which retail inlines
// to a byte test of bit 0xC3 in the template's kind-of bits at +0x108.
// No Zero Hour donor: the action is BFME2's.
#include "ascii_string.h"

class Player;

class Parameter
{
public:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parms[12];
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	char m_unknown[0x108];
	unsigned char m_kindOf[28];		// +0x108
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Player *getControllingPlayer() const;
	float rva002972B1(float radius);

private:
	char m_unknown0[4];
	const ThingTemplate *m_template;	// +0x04
};

class Team
{
public:
	float rva003A3736(float radius);
};

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

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool unused);
	Object *rva00358752(AsciiString name);	// 0x00358752, unit by name

protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void setCounterToThreat(ScriptAction *pAction, bool useTeam);
};
extern ScriptEngine *TheScriptEngine;

void ScriptEngine::setCounterToThreat(ScriptAction *pAction, bool useTeam)
{
	ScriptCounter *counter = bfmeCounter(pAction->getParameter(0)->m_string);
	if (!counter)
		return;
	float value = 0;
	float radius = pAction->getParameter(2)->m_real;
	if (useTeam) {
		Team *team = TheScriptEngine->getTeamNamed(pAction->getParameter(1)->m_string, false);
		if (team)
			value = team->rva003A3736(radius);
	} else {
		Object *obj = TheScriptEngine->rva00358752(pAction->getParameter(1)->m_string);
		if (obj) {
			if (obj->getTemplate()->isKindOf(0xC3)) {
				ThreatFinder *finder = g_manager->rva0041F474(pAction->getParameter(1)->m_string);
				if (finder) {
					Player *player = obj->getControllingPlayer();
					value = finder->getThreatForPlayer(player, 0, 0).m_threat;
				}
			} else {
				value = obj->rva002972B1(radius);
			}
		}
	}
	counter->m_value = (int)value;
}
