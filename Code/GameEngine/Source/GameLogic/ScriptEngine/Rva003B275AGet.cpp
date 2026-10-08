// cl: /DNDEBUG /MD
// ?rva003B275A@Condition@@QAEHXZ 0x003B275A 17B
// Evidence: pushes member at +4 into rowed ScriptEngine::getConditionTemplate
// 0x00203941 through the engine pointer at 0x00DFE16C, returns the template's
// first dword; caller 0x002096E2.
class ConditionTemplate
{
public:
	unsigned char bytes[128];
};

class ScriptEngine
{
public:
	const ConditionTemplate *getConditionTemplate(int id);
};
extern ScriptEngine *TheScriptEngine;

// The receiver is the Condition: +4 is its type, and evaluateCondition
// (0x002096E2) tests the returned mode mask against the engine's.
class Condition
{
	char m_pad[4];
	int m_conditionType;	// +0x04

public:
	int rva003B275A();
};

int Condition::rva003B275A()
{
	return *(const int *)TheScriptEngine->getConditionTemplate(m_conditionType)->bytes;
}
