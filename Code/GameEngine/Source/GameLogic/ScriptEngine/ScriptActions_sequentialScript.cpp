// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
//
// ScriptActions::doUnitStartSequentialScript, retail 0x003C0A6B (217B; ret 0xC)
// ScriptActions::doTeamStartSequentialScript, retail 0x003C0B44 (250B; ret 0xC)
// Target identity: executeAction case 192 (UNIT_EXECUTE_SEQUENTIAL_SCRIPT_LOOPING)
// calls 0x003C0A6B and case 195 (TEAM_EXECUTE_SEQUENTIAL_SCRIPT_LOOPING) calls
// 0x003C0B44, each with parameter 1's string and parameter 2's int minus one,
// as Zero Hour's ScriptActions.cpp does for doUnitStartSequentialScript and
// doTeamStartSequentialScript. Target differences from the donor: the unit
// variant takes parameter 0 itself (getUnitNamed's Parameter overload
// 0x003588E7), the script lookup is the pinned 0x00357130 that also returns
// the script's scope string, the scope and name are stored in the
// SequentialScript (+0x0C, +0x10; layout from SequentialScriptXfer.cpp), and
// the instance is released with ::delete (virtual dtor with 0 then operator
// delete) rather than deleteInstance. Callees: SequentialScript ctor
// 0x0020479E after operator new(0x2C), appendSequentialScript 0x00207557,
// getTeamNamed 0x003584E9, AI::createGroup 0x002FEC4B, getTeamAsAIGroup
// 0x003A0F62, groupIdle 0x0036FC23.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int ObjectID;

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Parameter;
class Script;
class Team;

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	unsigned char m_pad[0x74];
	ObjectID m_id;	// +0x74
};

class SequentialScript
{
public:
	SequentialScript();
	virtual ~SequentialScript();

	Team *m_teamToExecOn;	// +0x04
	ObjectID m_objectID;	// +0x08
	AsciiString m_bfmeScriptScope;	// +0x0C
	AsciiString m_bfmeScriptName;	// +0x10
	Script *m_scriptToExecuteSequentially;	// +0x14
	Int m_currentInstruction;	// +0x18
	Int m_timesToLoop;	// +0x1C
	Int m_framesToWait;	// +0x20
	bool m_dontAdvanceInstruction;	// +0x24
	SequentialScript *m_nextScriptInSequence;	// +0x28
};

class AIGroup
{
public:
	void groupIdle(CommandSourceType cmdSource);
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *pUnitParm);
	Team *getTeamNamed(AsciiString name, bool exact);
	Script *rva00357130(const AsciiString &scriptName, AsciiString *outScope);
	void appendSequentialScript(const SequentialScript *scriptToSequence);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doUnitStartSequentialScript(Parameter *pUnitParm, const AsciiString &scriptName, Int loopVal);
	void doTeamStartSequentialScript(const AsciiString &teamName, const AsciiString &scriptName, Int loopVal);
};

void ScriptActions::doUnitStartSequentialScript(Parameter *pUnitParm, const AsciiString &scriptName, Int loopVal)
{
	Object *obj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!obj) {
		return;
	}

	AsciiString scope;
	Script *script = TheScriptEngine->rva00357130(scriptName, &scope);
	if (!script) {
		return;
	}

	SequentialScript *seqScript = new SequentialScript;
	seqScript->m_objectID = obj->getID();
	seqScript->m_bfmeScriptScope = scope;
	seqScript->m_bfmeScriptName = scriptName;
	seqScript->m_scriptToExecuteSequentially = script;
	seqScript->m_timesToLoop = loopVal;

	TheScriptEngine->appendSequentialScript(seqScript);

	::delete seqScript;
}

void ScriptActions::doTeamStartSequentialScript(const AsciiString &teamName, const AsciiString &scriptName, Int loopVal)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AsciiString scope;
	Script *script = TheScriptEngine->rva00357130(scriptName, &scope);
	if (!script) {
		return;
	}

	// Idle the team so the seq script will start executing. jba.
	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	team->getTeamAsAIGroup(theGroup);
	theGroup->groupIdle(CMD_FROM_SCRIPT);

	SequentialScript *seqScript = new SequentialScript;
	seqScript->m_teamToExecOn = team;
	seqScript->m_bfmeScriptScope = scope;
	seqScript->m_bfmeScriptName = scriptName;
	seqScript->m_scriptToExecuteSequentially = script;
	seqScript->m_timesToLoop = loopVal;

	TheScriptEngine->appendSequentialScript(seqScript);

	::delete seqScript;
}
