// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline
// ScriptConditions counter-compare condition, retail 0x003E7CBA (201B):
// compares the values of two script counters. Ported from Open-BFME-1's
// ScriptConditionsCounterCompareRva00325BC0.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, BFME 1 0x00325BC0), compiled with
// the donor's flags plus /O1, where it places uniquely and builds byte for
// byte. The method name stays address-derived, re-keyed to BFME 2.
#include "StringInline.h"

class Parameter
{
public:
	int getInt() const { return m_integer; }
	const AsciiString &getString() const { return m_string; }
private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parameters[index];
		return 0;
	}
private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parameters[12];
};

struct ScriptCounter
{
	int m_value;
};

class ScriptEngine
{
public:
	void *rva002086C5(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	bool evaluateCounterCompareRva003E7CBA(Condition *condition);
};

bool ScriptConditions::evaluateCounterCompareRva003E7CBA(Condition *condition)
{
	int left = 0;
	ScriptCounter *counter = (ScriptCounter *)TheScriptEngine->rva002086C5(condition->getParameter(0)->getString());
	if (counter)
		left = counter->m_value;

	int right = 0;
	counter = (ScriptCounter *)TheScriptEngine->rva002086C5(condition->getParameter(2)->getString());
	if (counter)
		right = counter->m_value;

	switch (condition->getParameter(1)->getInt()) {
	case 0: return left < right;
	case 1: return left <= right;
	case 2: return left == right;
	case 3: return left >= right;
	case 4: return left > right;
	case 5: return left != right;
	}
	return false;
}
