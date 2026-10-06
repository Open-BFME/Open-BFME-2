// ?evaluateCondition@ScriptEngine@@QAE_NPAVCondition@@@Z
// partial score=0.99 date=2026-10-06
// ?evaluateCondition@ScriptEngine@@QAE_NPAVCondition@@@Z
// partial score=0.99 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ScriptEngine::evaluateCondition, retail 0x002096E2 (102B), from the
// WorldBuilder lead (ScriptEngine.cpp) and Zero Hour's ScriptEngine.cpp: the
// built-in condition types (false, counter, flag, true, timer expired) are
// evaluated here, everything else by TheScriptConditions (0x00E02E04, vtable
// slot 0x38). BFME2 first requires the condition's mask (0x003B275A) to
// intersect the script engine's current one (0x00203693, 2 or 1 by the game
// logic mode); both keep their rowed address-derived names.

typedef bool Bool;
typedef int Int;

class Rva003B275A
{
public:
	Int rva003B275A();
};

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0,
		COUNTER,
		FLAG,
		CONDITION_TRUE,
		TIMER_EXPIRED
	};
	ConditionType getConditionType() const { return m_conditionType; }

private:
	void *m_vtbl;
	ConditionType m_conditionType;
};

class ScriptConditionsInterface
{
public:
#define SC_SLOT(n) virtual void slot##n();
	SC_SLOT(0) SC_SLOT(1) SC_SLOT(2) SC_SLOT(3) SC_SLOT(4) SC_SLOT(5) SC_SLOT(6)
	SC_SLOT(7) SC_SLOT(8) SC_SLOT(9) SC_SLOT(10) SC_SLOT(11) SC_SLOT(12) SC_SLOT(13)
#undef SC_SLOT
	virtual Bool evaluateCondition(Condition *pCondition); // 0x38
};
extern ScriptConditionsInterface *TheScriptConditions;

class Rva00203693Host
{
public:
	Int rva00203693();
};

class ScriptEngine
{
public:
	Bool evaluateCondition(Condition *pCondition);
	Bool evaluateTimer(Condition *pCondition);

protected:
	Bool evaluateCounter(Condition *pCondition);
	Bool evaluateFlag(Condition *pCondition);
};

Bool ScriptEngine::evaluateCondition(Condition *pCondition)
{
	Int mask = ((Rva00203693Host *)this)->rva00203693();
	Int conditionMask = ((Rva003B275A *)pCondition)->rva003B275A();
	if (!(conditionMask & mask))
		return false;
	switch (pCondition->getConditionType())
	{
	case Condition::CONDITION_FALSE:
		return false;
	case Condition::COUNTER:
		return evaluateCounter(pCondition);
	case Condition::FLAG:
		return evaluateFlag(pCondition);
	case Condition::CONDITION_TRUE:
		return true;
	case Condition::TIMER_EXPIRED:
		return evaluateTimer(pCondition);
	default:
		return TheScriptConditions->evaluateCondition(pCondition);
	}
}
