// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// TeamFactory::createInactiveTeam, retail 0x003A3B7E (317 bytes):
// ?createInactiveTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@0@Z
// Identity (target): WorldBuilder's debug Team.cpp:513
// TeamFactory::createInactiveTeam; retail's callee order matches Zero
// Hour's body: findTeamPrototype (0x0039FE6C), the ERROR_BAD_ARG throw,
// the singleton's existing team, operator new and Team::Team (0x003A39A7),
// and on both paths the production-condition script lookup (0x003573C4)
// and its action run (0x0020D451) when the prototype executes actions.
// BFME 2 deltas (target): the prototype is keyed by (owner name, team
// name); the script lookup takes the owner name (+0x10) and returns a scope
// string, which the action run receives with the action (Script +0x34), the
// script, the condition name and 0. Layout (target): prototype flags +0x18
// (bit 0 singleton), production condition +0x23C, execute-actions +0x240,
// instance list +0x334; the factory's team id counter at +0xC0.
#include "ascii_string.h"

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0001),
	ERROR_BAD_ARG = (ERROR_BASE + 0x0002)
};

class Team;
class TeamFactory;

class Script
{
public:
	void *getAction() const { return m_action; }

private:
	unsigned char m_pad00[0x34];
	void *m_action; // +0x34
};

class ScriptEngine
{
public:
	Script *rva003573C4(const AsciiString &owner, const AsciiString &name, AsciiString *outName);
	void rva0020D451(AsciiString &scope, void *action, Script *script, const AsciiString &scriptName, int flags);
};

extern ScriptEngine *TheScriptEngine;

class TeamPrototype
{
public:
	bool getIsSingleton() const { return (m_flags & 1) != 0; }
	Team *getFirstItemIn_TeamInstanceList() const { return m_dlinkhead_TeamInstanceList; }
	const AsciiString &getOwnerName() const { return m_owner; }
	const AsciiString &getProductionCondition() const { return m_productionCondition; }
	bool getExecuteActions() const { return m_executeActions; }

private:
	unsigned char m_pad00[0x10];
	AsciiString m_owner; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	int m_flags; // +0x18
	unsigned char m_pad1C[0x23C - 0x1C];
	AsciiString m_productionCondition; // +0x23C
	bool m_executeActions; // +0x240
	unsigned char m_pad241[0x334 - 0x241];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

class Team
{
public:
	Team(TeamPrototype *proto, int id);

private:
	unsigned char m_pad00[0x13C];
};

class TeamFactory
{
public:
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
	TeamPrototype *findTeamPrototype(const AsciiString &owner, const AsciiString &name);

private:
	unsigned char m_pad00[0xC0];
	int m_uniqueTeamID; // +0xC0
};

Team *TeamFactory::createInactiveTeam(const AsciiString &owner, const AsciiString &name)
{
	TeamPrototype *tp = findTeamPrototype(owner, name);
	if (!tp)
		throw ERROR_BAD_ARG;

	Team *t = 0;
	if (tp->getIsSingleton())
	{
		t = tp->getFirstItemIn_TeamInstanceList();
		if (t)
		{
			if (tp->getExecuteActions())
			{
				AsciiString scope;
				Script *script = TheScriptEngine->rva003573C4(tp->getOwnerName(), tp->getProductionCondition(), &scope);
				if (script)
					TheScriptEngine->rva0020D451(scope, script->getAction(), script, tp->getProductionCondition(), 0);
			}
			return t;
		}
	}

	t = new Team(tp, ++m_uniqueTeamID);
	if (tp->getExecuteActions())
	{
		AsciiString scope;
		Script *script = TheScriptEngine->rva003573C4(tp->getOwnerName(), tp->getProductionCondition(), &scope);
		if (script)
			TheScriptEngine->rva0020D451(scope, script->getAction(), script, tp->getProductionCondition(), 0);
	}
	return t;
}
