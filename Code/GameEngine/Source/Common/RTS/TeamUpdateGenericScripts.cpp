// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?updateGenericScripts@Team@@QAEXXZ @0x0039F8F7 533B.
// Identity (target): WorldBuilder Team.cpp Team::updateGenericScripts
// (0x00EFAB20) by name and call graph; the one caller is 0x002AE821.
// Donor (Zero Hour Team.cpp): the per-slot m_shouldAttemptGenericScript
// loop, the one-shot clear and the "Generic script '...' run on team"
// debug message. BFME 2 deltas (target): the walk is skipped unless the
// byte at +0x5F is set; getGenericScript (0x0039EC1E) returns the scope
// string; a slot is dropped when the script is missing or inactive (+0x40);
// a positive delay (Script +0x20) gates the evaluation on the per-slot next
// frame at +0x90 and re-arms it after every evaluation as
// frame rate (0x009BA4E4) * delay + TheGameLogic frame; the condition test
// is the rowed ScriptEngine 0x0020A1D0; sequential scripts (+0x10) that are
// one-shot are queued as a SequentialScript (scope, slot name, loop count
// +0x14) through appendSequentialScript, the rest run their action through
// 0x0020D451 with "some Generic Script". Field names past the donor's are
// descriptive.
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"

enum { MAX_GENERIC_SCRIPTS = 32 };

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

class Team;
class Player;

class Script
{
public:
	bool isSequential() const { return m_sequential; }
	int getLoopCount() const { return m_loopCount; }
	int getDelayEvaluationSeconds() const { return m_delaySeconds; }
	bool isOneShot() const { return m_oneShot; }
	void *getAction() const { return m_action; }
	bool isActive() const { return m_isActive; }

private:
	unsigned char m_pad00[0x10];
	bool m_sequential; // +0x10
	int m_loopCount; // +0x14
	unsigned char m_pad18[0x20 - 0x18];
	int m_delaySeconds; // +0x20
	unsigned char m_pad24[0x29 - 0x24];
	bool m_oneShot; // +0x29
	unsigned char m_pad2A[0x34 - 0x2A];
	void *m_action; // +0x34
	unsigned char m_pad38[0x40 - 0x38];
	bool m_isActive; // +0x40
};

class SequentialScript
{
public:
	SequentialScript();
	virtual ~SequentialScript();

	Team *m_teamToExecOn; // +0x04
	int m_objectID; // +0x08
	AsciiString m_bfmeScriptScope; // +0x0C
	AsciiString m_bfmeScriptName; // +0x10
	Script *m_scriptToExecuteSequentially; // +0x14
	int m_currentInstruction; // +0x18
	int m_timesToLoop; // +0x1C
	int m_framesToWait; // +0x20
	bool m_dontAdvanceInstruction; // +0x24
	SequentialScript *m_nextScriptInSequence; // +0x28
};

class ScriptEngine
{
public:
	bool rva0020A1D0(const AsciiString &scope, Script *script, Team *team, Player *player);
	void rva0020D451(AsciiString &scope, void *action, Script *script, const AsciiString &scriptName, int team);
	void appendSequentialScript(const SequentialScript *scriptToSequence);
	void AppendDebugMessage(const AsciiString &strToAdd, bool forcePause);
};

extern ScriptEngine *TheScriptEngine;

class TeamPrototype
{
public:
	Script *getGenericScript(int scriptToRetrieve, AsciiString *outName);
	const AsciiString &getName() const { return m_name; }
	const AsciiString &getGenericScriptName(int i) const { return m_teamGenericScripts[i]; }

private:
	unsigned char m_pad00[0x14];
	AsciiString m_name; // +0x14
	unsigned char m_pad18[0x244 - 0x18];
	AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS]; // +0x244
};

class Team
{
public:
	void updateGenericScripts();
	const AsciiString &getName() const { return !m_proto ? AsciiString::TheEmptyString : m_proto->getName(); }

private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
	unsigned char m_pad34[0x5F - 0x34];
	bool m_isActive; // +0x5F
	unsigned char m_pad60[0x70 - 0x60];
	bool m_shouldAttemptGenericScript[MAX_GENERIC_SCRIPTS]; // +0x70
	unsigned int m_nextGenericScriptFrame[MAX_GENERIC_SCRIPTS]; // +0x90
};

void Team::updateGenericScripts()
{
	if (!m_proto || !m_isActive)
		return;

	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
	{
		if (m_shouldAttemptGenericScript[i])
		{
			AsciiString scope;
			Script *script = m_proto->getGenericScript(i, &scope);
			if (script && script->isActive())
			{
				int delay = script->getDelayEvaluationSeconds();
				if (delay > 0 && m_nextGenericScriptFrame[i] > TheGameLogic->getFrame())
					continue;

				if (TheScriptEngine->rva0020A1D0(scope, script, this, 0))
				{
					if (script->isOneShot())
						m_shouldAttemptGenericScript[i] = false;

					if (script->isSequential())
					{
						if (script->isOneShot())
						{
							SequentialScript *seq = new SequentialScript;
							seq->m_teamToExecOn = this;
							seq->m_bfmeScriptScope = scope;
							seq->m_bfmeScriptName = m_proto->getGenericScriptName(i);
							seq->m_scriptToExecuteSequentially = script;
							seq->m_timesToLoop = script->getLoopCount();
							TheScriptEngine->appendSequentialScript(seq);
						}
					}
					else
					{
						TheScriptEngine->rva0020D451(scope, script->getAction(), script, AsciiString("some Generic Script"), (int)this);
						AsciiString msg = "Generic script '";
						msg.concat(m_proto->getGenericScriptName(i));
						msg.concat("' run on team ");
						msg.concat(getName());
						TheScriptEngine->AppendDebugMessage(msg, false);
					}
				}

				delay = script->getDelayEvaluationSeconds();
				if (delay > 0)
					m_nextGenericScriptFrame[i] = g_Va00DBA4E4 * delay + TheGameLogic->getFrame();
			}
			else
			{
				m_shouldAttemptGenericScript[i] = false;
			}
		}
	}
}
