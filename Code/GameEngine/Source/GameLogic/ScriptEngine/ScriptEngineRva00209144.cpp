// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ?setCounter@ScriptEngine@@IAEXPAVScriptAction@@H_N1@Z, retail 0x00209144, 436 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// Evidence: unlock lane, prev evaluateCounter 0x00208F61 next addCounter
// 0x002092F8 in ScriptEngineEvaluateCounter.cpp, caller 0x0020C5C7, callees
// bfmeCounter pinned plus rva002086C5 row plus GetGameLogicRandomValueReal
// GetGameClientRandomValueReal GetGameLogicRandomValue GetGameClientRandomValue
// rows, globals g_parseDurationMsecScale and g_00BBE358, IAT ceil, file literal
// ScriptEngine.cpp. Identity: ScriptEngine method (ecx is ScriptEngine*) with
// 4 stack args (ret 0x10), honest address name.
#include "ascii_string.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double);

extern float g_parseDurationMsecScale;

int GetGameLogicRandomValue(int low, int high, char *file, int line);
int GetGameClientRandomValue(int low, int high, char *file, int line);
float GetGameLogicRandomValueReal(float low, float high, char *file, int line);
float GetGameClientRandomValueReal(float low, float high, char *file, int line);

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
public:
	void *rva002086C5(AsciiString name);
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void setCounter(ScriptAction *action, int randomKind, bool copyFrom, bool isFloat);
};

void ScriptEngine::setCounter(ScriptAction *action, int randomKind, bool copyFrom, bool isFloat)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
	if (!counter)
		return;
	if (copyFrom) {
		const void *found = rva002086C5(action->getParameter(1)->m_string);
		if (found) {
			counter->m_value = *(int *)found;
			return;
			counter->m_isMillisecondTimer = false;
		}
	}
	if (isFloat) {
		float value;
		if (randomKind != 0) {
			const float lo = action->getParameter(1)->m_real;
			const float hi = action->getParameter(2)->m_real;
			if (randomKind == 1)
				value = GetGameLogicRandomValueReal(lo, hi, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0x804);
			else
				value = GetGameClientRandomValueReal(lo, hi, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0x808);
		} else {
			value = action->getParameter(1)->m_real;
		}
		float prod = g_parseDurationMsecScale * value;
		prod *= 1e+03f;
		float tmp = (float)ceil(prod);
		counter->m_value = fast_float2long_round(tmp);
		counter->m_isMillisecondTimer = true;
	} else {
		int value;
		if (0 != randomKind) {
			unsigned int lo = action->getParameter(1)->m_int;
			unsigned int hi = action->getParameter(2)->m_int;
			if (randomKind == 1)
				value = GetGameLogicRandomValue(lo, hi, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0x81e);
			else
				value = GetGameClientRandomValue(lo, hi, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0x822);
		} else {
			value = action->getParameter(1)->m_int;
		}
		counter->m_isMillisecondTimer = false;
		counter->m_value = value;
	}
}
