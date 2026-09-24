// cl: /O1
//
// ScriptConditions constructor, retail 0x003E5513 (18 bytes). ScriptEngine::init
// creates it with operator new(0xC) and stores it in TheScriptConditions. The
// global's slot-15 call evaluates conditions at 0x0020CB4C.
//
// Donor: ZH ScriptConditions::ScriptConditions, an empty body. Only the
// SubsystemInterface base call (0x001B4E63) and the vtable store (0xC35B38)
// remain.

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;

private:
	bool m_subsystemFlag;  // +0x04
	int  m_subsystemValue; // +0x08
};

class ScriptConditionsInterface : public SubsystemInterface
{
};

class ScriptConditions : public ScriptConditionsInterface
{
public:
	ScriptConditions();
	virtual ~ScriptConditions();
	virtual void init();
};

ScriptConditions::ScriptConditions()
{
}
