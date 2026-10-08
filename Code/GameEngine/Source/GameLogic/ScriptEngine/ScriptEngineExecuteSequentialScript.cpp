// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
//
// ScriptEngine::executeSequentialScript, retail 0x0020A073 (349B; ret 8).
//
// Identity (target): WorldBuilder twin 0xB3C750 carries the name
// ScriptEngine::executeSequentialScript and ScriptEngine.cpp asserts at lines
// 2949 ("Target Team is not found for sequential script") and 2971 ("Obj is
// not found for sequential script"). Callees from the WB call list, each read
// at the retail REL32: evaluateConditions 0x00209748, getCurrentPlayer
// 0x00205C93, the SequentialScript ctor 0x0020479E after operator new(0x2C),
// the copy ctor 0x003B3507 of the script's sequential target record at +0x10
// (layout bool bool int bool AsciiString, Rva003B3536Load.cpp), getTeamNamed
// 0x003584E9 and the unit lookup 0x00358752 on this, AI::createGroup,
// getTeamAsAIGroup, groupIdle, resolveName 0x002046C0 and
// appendSequentialScript 0x00207557.
// Donor: Zero Hour has no such method; the team branch is its
// doTeamStartSequentialScript (createGroup, getTeamAsAIGroup, groupIdle
// CMD_FROM_SCRIPT) and the SequentialScript fill and ::delete follow the
// BFME2 ScriptActions twins in ScriptActions_sequentialScript.cpp. Script
// +0x40 is m_isActive (ScriptXfer.cpp); +0x29 sits beside isSubroutine at
// +0x2A as Zero Hour's isOneShot does; +0x38 is read only as a pointer test.
// Retail registers no unwind state for the new expression: the ctor is in
// the home TU and known not to throw, which throw() states here.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int ObjectID;

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Player;
class Team;

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	unsigned char m_pad[0x74];
	ObjectID m_id;	// +0x74
};

// The script's sequential target: the team or unit name and the loop count.
class Rva003B3536
{
public:
	Rva003B3536(const Rva003B3536 &other);

	bool m_a;			// +0
	bool m_b;			// +1
	int m_c;			// +4, times to loop
	bool m_d;			// +8, target is a unit
	AsciiString m_e;	// +0xC, target name
};

class Script
{
public:
	void *m_vtbl;
	char m_unknown04[0x10 - 0x04];
	Rva003B3536 m_sequentialTarget;		// +0x10
	char m_unknown20[0x29 - 0x20];
	bool m_isOneShot;					// +0x29
	char m_unknown2A[0x38 - 0x2A];
	void *m_bfme38;						// +0x38
	char m_unknown3C[0x40 - 0x3C];
	bool m_isActive;					// +0x40
};

class SequentialScript
{
public:
	SequentialScript() throw();
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
	bool evaluateConditions(Script *pScript, Team *thisTeam, Player *player);
	Player *getCurrentPlayer();
	Team *getTeamNamed(AsciiString name, bool exact);
	Object *rva00358752(AsciiString name);	// 0x00358752, unit by name
	AsciiString rva002046C0(const AsciiString &name);	// 0x002046C0, resolveName
	void appendSequentialScript(const SequentialScript *scriptToSequence);
	void executeSequentialScript(Script *pScript, const AsciiString &scriptName);
};

void ScriptEngine::executeSequentialScript(Script *pScript, const AsciiString &scriptName)
{
	if (evaluateConditions(pScript, 0, 0)) {
		if (getCurrentPlayer()) {
			SequentialScript *seqScript = new SequentialScript;
			Rva003B3536 target(pScript->m_sequentialTarget);
			if (!target.m_d) {
				Team *team = getTeamNamed(target.m_e, false);
				if (!team) {
					pScript->m_isActive = false;
					return;
				}
				AIGroup *theGroup = TheAI->createGroup();
				if (!theGroup)
					return;
				team->getTeamAsAIGroup(theGroup);
				theGroup->groupIdle(CMD_FROM_SCRIPT);
				seqScript->m_teamToExecOn = team;
			} else if (target.m_d) {
				Object *obj = rva00358752(target.m_e);
				if (!obj) {
					pScript->m_isActive = false;
					return;
				}
				seqScript->m_objectID = obj->getID();
			}
			seqScript->m_bfmeScriptName = scriptName;
			seqScript->m_bfmeScriptScope = rva002046C0(seqScript->m_bfmeScriptName);
			seqScript->m_scriptToExecuteSequentially = pScript;
			seqScript->m_timesToLoop = target.m_c;
			appendSequentialScript(seqScript);
			::delete seqScript;
		}
		if (pScript->m_isOneShot)
			pScript->m_isActive = false;
	} else {
		if (pScript->m_bfme38)
			pScript->m_isActive = false;
	}
}
