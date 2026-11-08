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
extern int BfmeLogicFramesPerSecond;

class Team;
class Player;

#include "../../../Include/GameLogic/ScriptClass.h"

class Team;
class Rva0020D451Engine
{
public:
	void rva0020D451(const AsciiString &scope, void *action, void *script, void *scriptName, Team *team);	// rowed 0x0020D451
};

class Xfer;
class SequentialScript
{
public:
	SequentialScript();
	virtual ~SequentialScript();
protected:
	virtual void loadPostProcess();
public:
	virtual const char *GetSnapshotName();
protected:
	virtual void xfer(Xfer *xfer);
public:

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

#include "../../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

#include "../../../Include/Common/Team.h"

#include "../../../Include/Common/TeamBFME2.h"

void Team::updateGenericScripts()
{
	if (!m_proto || !m_5F)
		return;

	for (int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
	{
		if (m_shouldAttemptGenericScript[i])
		{
			AsciiString scope;
			Script *script = m_proto->getGenericScript(i, &scope);
			if (script && script->isActive())
			{
				int delay = script->getDelayEvalSeconds();
				if (delay > 0 && m_90[i] > TheGameLogic->getFrame())
					continue;

				if (TheScriptEngine->rva0020A1D0(scope, script, this, 0))
				{
					if (script->isOneShot())
						m_shouldAttemptGenericScript[i] = false;

					if (script->m_subrecord.m_field00)
					{
						if (script->isOneShot())
						{
							SequentialScript *seq = new SequentialScript;
							seq->m_teamToExecOn = this;
							seq->m_bfmeScriptScope = scope;
							seq->m_bfmeScriptName = m_proto->m_teamGenericScripts[i];
							seq->m_scriptToExecuteSequentially = script;
							seq->m_timesToLoop = script->m_subrecord.m_field04;
							TheScriptEngine->appendSequentialScript(seq);
						}
					}
					else
					{
						((Rva0020D451Engine *)TheScriptEngine)->rva0020D451(scope, script->getAction(), script, (void *)&AsciiString("some Generic Script"), (Team *)this);
						AsciiString msg = "Generic script '";
						msg.concat(m_proto->m_teamGenericScripts[i]);
						reinterpret_cast<StringBase<char> *>(&msg)->concat("' run on team ");
						msg.concat(!m_proto ? AsciiString::TheEmptyString : m_proto->getName());
						TheScriptEngine->AppendDebugMessage(msg, false);
					}
				}

				delay = script->getDelayEvalSeconds();
				if (delay > 0)
					m_90[i] = BfmeLogicFramesPerSecond * delay + TheGameLogic->getFrame();
			}
			else
			{
				m_shouldAttemptGenericScript[i] = false;
			}
		}
	}
}
