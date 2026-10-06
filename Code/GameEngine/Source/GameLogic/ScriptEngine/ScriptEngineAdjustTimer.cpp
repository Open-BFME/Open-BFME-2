// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ?adjustTimer@ScriptEngine@@IAEXPAVScriptAction@@_N1@Z @0x00209639 169B
// Evidence: unlock lane, prev ScriptEngine::restartTimer 0x002095FF in
// ScriptEngine.cpp, caller 0x0020C5C7 (ScriptEngine timer dispatch), callee
// ?bfmeCounter@ScriptEngine@@IAEPAUScriptCounter@@VAsciiString@@@Z pinned,
// globals g_parseDurationMsecScale (?g_parseDurationMsecScale@@3MA) and
// float g_00BBE358, IAT ceil. Identity: ScriptEngine::adjustTimer
// (action, millisecondTimer, add) from class declaration in ScriptEngine.cpp.
#include "ascii_string.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double);

extern float g_parseDurationMsecScale;
extern float g_00BBE358;

// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

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

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void adjustTimer(ScriptAction *action, bool millisecondTimer, bool add);
};

void ScriptEngine::adjustTimer(ScriptAction *action, bool millisecondTimer, bool add)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(1)->m_string);
	if (millisecondTimer) {
		float value = action->getParameter(0)->m_real;
		if (!add)
			value = -value;
		float prod = g_parseDurationMsecScale * value;
		prod *= g_00BBE358;
		float tmp = (float)ceil(prod);
		counter->m_value += fast_float2long_round(tmp);
	} else {
		int value = action->getParameter(0)->m_int;
		if (!add)
			value = -value;
		counter->m_value += value;
	}
}
