// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ScriptConditions counter-compare condition, retail 0x003E7CBA (201B):
// compares the values of two script counters. Ported from Open-BFME-1's
// ScriptConditionsCounterCompareRva00325BC0.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, BFME 1 0x00325BC0), compiled with
// the donor's flags plus /O1, where it places uniquely and builds byte for
// byte. The method name stays address-derived, re-keyed to BFME 2.
//
// ?evaluateCounterSeconds@ScriptConditions@@IAE_NPAVCondition@@@Z @ 0x003E7D83 209B
// Ported from Open-BFME-1's ScriptConditions_evaluateCounterSeconds.cpp
// (BFME 1 0x00325D00), name carried from the donor. Target evidence:
// jump-table case 112 calls 0x003E7D83 with the Condition, which
// initConditionTemplates names COUNTER_SECONDS (counter, comparison, real).
// The counter's value (0 without one) is compared six ways with the
// seconds converted to frames: the 0.005 frames-per-msec global at
// 0x00DBA4EC times the real times 1000, rounded up through the msvcrt
// ceil import and narrowed by BaseType.h's fast_float2long_round (retail's
// fstp dword / fld / fistp dword; a C cast emits _ftol2).
#include "ascii_string.h"
#include <math.h>

class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};

class Condition
{
public:
	bool isInverted() const { return m_inverted; }
	Parameter *getParameter(int ndx) const { if (ndx >= 0 && ndx < m_numParms) return m_parms[ndx]; return 0; }
	int getCustomData() const { return m_customData; }
	void setCustomData(int val) { m_customData = val; }
	unsigned int getCustomFrame() const { return m_customFrame; }
	void setCustomFrame(unsigned int frame) { m_customFrame = frame; }
	int getType() const { return m_type; }
	int getNumParameters() const { return m_numParms; }
	char m_pad00[0x4];
private:
	int m_type; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[13]; // +0x0C
	char m_pad40[0x4];
	int m_customData; // +0x44
	unsigned int m_customFrame; // +0x48
	char m_pad4C[0x1];
	bool m_inverted; // +0x4D
	char m_pad4E[0x2];
};

struct ScriptCounter
{
	int m_value;
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern float g_parseDurationMsecScale;

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateCounterCounter(Condition *condition)
{
	int left = 0;
	ScriptCounter *counter = (ScriptCounter *)TheScriptEngine->rva002086C5(condition->getParameter(0)->getString());
	if (counter)
		left = counter->m_value;

	int right = 0;
	counter = (ScriptCounter *)TheScriptEngine->rva002086C5(condition->getParameter(2)->getString());
	if (counter)
		right = counter->m_value;

	switch (condition->getParameter(1)->m_int) {
	case 0: return left < right;
	case 1: return left <= right;
	case 2: return left == right;
	case 3: return left >= right;
	case 4: return left > right;
	case 5: return left != right;
	}
	return false;
}

bool ScriptConditions::evaluateCounterSeconds(Condition *pCondition)
{
	int count = 0;
	ScriptCounter *counter = (ScriptCounter *)TheScriptEngine->rva002086C5(pCondition->getParameter(0)->getString());
	if (counter)
		count = counter->m_value;
	float frames = g_parseDurationMsecScale * pCondition->getParameter(2)->getReal() * 1000.0f;
	int value = fast_float2long_round((float)ceil((double)frames));
	switch (pCondition->getParameter(1)->m_int) {
	case 0: return count < value;
	case 1: return count <= value;
	case 2: return count == value;
	case 3: return count >= value;
	case 4: return count > value;
	case 5: return count != value;
	}
	return false;
}
