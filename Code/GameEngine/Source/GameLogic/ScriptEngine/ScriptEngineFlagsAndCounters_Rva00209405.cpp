//
// ?setFlag@ScriptEngine@@IAEXPAVScriptAction@@_N@Z
// retail 0x00209405, 129 bytes. Dedicated TU ported from the Open-BFME-1
// donor
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineFlagsAndCounters.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other
// definitions (addCounter and subCounter) are omitted.
//
// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringinline /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
// The three script-action entry points that write a named flag or counter:
//
//   0x00345CA0  addCounter  71 bytes
//   0x00345D00  subCounter  71 bytes
//   0x00345EB0  setFlag    165 bytes, either from a literal or from another flag
//
// The two counter halves are the same body with one operator changed, and
// setFlag is their flag-side equivalent. All three take the name out of a
// ScriptAction parameter and hand it to a by-value lookup.
//
// ScriptCounter carries the millisecond flag at +0x05 here even though none of
// these three touches it: ScriptEngineTimers.cpp's setTimer writes it, and the
// counter is one record whatever reads it. addCounter and subCounter had
// stopped at the countdown flag because that is as far as their own bodies see.
//
// ScriptAction is the array-of-pointers spelling that setTimer and adjustTimer
// pinned by reaching indices 1 and 2; these three use indices 0 and 1 and agree.

#include "StringInline.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	// Retail inlines these reads. Accessing the existing fields directly
	// avoids emitting getter COMDATs for this partial Parameter layout.
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_parameterCount;
	Parameter *m_parameters[12];
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;					// +0x04
	bool m_isMillisecondTimer;					// +0x05
};

// The read-only flag lookup setFlag reaches here is the ledger's matched
// ?rva0020881A@ScriptEngine@@QAEPAXVAsciiString@@@Z body at 0x0020881A (134
// bytes), which the ledger also pins as bfmeFlagForRead@ScriptEngine because
// this call site is one of its callers. The donor reaches it through an ILT
// thunk whose retail address does not resolve; the REL32 displacement read off
// this body's call at 0x0020945A lands on 0x0020881A, so that is the callee
// named here.
class BFMEScriptEngineFlagLookup
{
public:
	bool *findFlag(AsciiString name);
};

typedef bool *(BFMEScriptEngineFlagLookup::*FindFlagFunction)(AsciiString);

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	bool *bfmeFlagForWrite(AsciiString name);
	bool *bfmeFlagForRead(AsciiString name);
	void setFlag(ScriptAction *action, bool copyFromFlag);
};

void ScriptEngine::setFlag(ScriptAction *action, bool copyFromFlag)
{
	ScriptAction *sourceAction = action;
	bool *flag = bfmeFlagForWrite(sourceAction->getParameter(0)->m_string);
	bool value = false;
	if (copyFromFlag)
	{
		bool *source = bfmeFlagForRead(sourceAction->getParameter(1)->m_string);
		if (source)
			value = *source;
	}
	else
	{
		value = sourceAction->getParameter(1)->m_integer != 0;
	}
	*flag = value;
}
