// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ?setTimer@ScriptEngine@@IAEXPAVScriptAction@@_N1@Z @0x002094CB 255B
// Evidence: unlock lane, prev evaluateTimer 0x00209486 next pauseTimer
// 0x002095CA in ScriptEngine.cpp, caller 0x0020C76B, callee
// ?bfmeCounter@ScriptEngine@@IAEPAUScriptCounter@@VAsciiString@@@Z pinned,
// globals g_parseDurationMsecScale (?g_parseDurationMsecScale@@3MA) and
// float g_00BBE358, IAT ceil, row GetGameLogicRandomValue, file literal
// ScriptEngine.cpp. Identity: ScriptEngine::setTimer
// (action, millisecondTimer, random) from class declaration in ScriptEngine.cpp.
#include "ascii_string.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double);

extern float g_parseDurationMsecScale;

int GetGameLogicRandomValue(int low, int high, char *file, int line);

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
	void setTimer(ScriptAction *action, bool millisecondTimer, bool random);
};

void ScriptEngine::setTimer(ScriptAction *action, bool millisecondTimer, bool random)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
	int result;
	if (millisecondTimer) {
		float value = action->getParameter(1)->m_real;
		if (random) {
			float max = action->getParameter(2)->m_real;
			value = (float)GetGameLogicRandomValue((int)value, (int)max, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0x9c4);
		}
		float prod = g_parseDurationMsecScale * value;
		prod *= 1e+03f;
		float tmp = (float)ceil(prod);
		result = fast_float2long_round(tmp);
		counter->m_isMillisecondTimer = true;
	} else {
		int value = action->getParameter(1)->m_int;
		if (random) {
			int max = action->getParameter(2)->m_int;
			value = GetGameLogicRandomValue(value, max, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0x9cc);
		}
		result = value;
		counter->m_isMillisecondTimer = false;
	}
	counter->m_value = result;
	counter->m_isCountdownTimer = true;
}
