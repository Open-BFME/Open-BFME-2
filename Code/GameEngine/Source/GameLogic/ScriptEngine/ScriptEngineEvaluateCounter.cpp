// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineEvaluateCounter.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ScriptEngine::evaluateCounter 0x00208F61 (162B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
// ScriptEngine::evaluateCounter at RVA 0x003457F0.
// The 193-byte instruction body and six-entry jump table at 0x003458B4
// occupy 220 bytes, including a three-byte alignment instruction.
// The condition dispatcher and upstream counter comparison switch identify it;
// matched evaluateFlag/evaluateTimer witness the BFME named-counter lookup.
#include "ascii_string.h"

class Parameter
{
public:
	enum
	{
		LESS_THAN, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL
	};
	int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class Condition
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
	bool evaluateCounter(Condition *condition);
	void addCounter(ScriptAction *action);
	void subCounter(ScriptAction *action);
};

bool ScriptEngine::evaluateCounter(Condition *condition)
{
	ScriptCounter *counter = bfmeCounter(
		condition->getParameter(0)->getString());
	int value = condition->getParameter(2)->getInt();
	switch (condition->getParameter(1)->getInt())
	{
	case Parameter::LESS_THAN:
		return counter->m_value < value;
	case Parameter::LESS_EQUAL:
		return counter->m_value <= value;
	case Parameter::EQUAL:
		return counter->m_value == value;
	case Parameter::GREATER_EQUAL:
		return counter->m_value >= value;
	case Parameter::GREATER:
		return counter->m_value > value;
	case Parameter::NOT_EQUAL:
		return counter->m_value != value;
	}
	return false;
}

void ScriptEngine::addCounter(ScriptAction *action)
{
	int value = action->getParameter(0)->getInt();
	bfmeCounter(action->getParameter(1)->getString())->m_value += value;
}

void ScriptEngine::subCounter(ScriptAction *action)
{
	int value = action->getParameter(0)->getInt();
	bfmeCounter(action->getParameter(1)->getString())->m_value -= value;
}
