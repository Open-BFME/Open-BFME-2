// cl: /O1
//
// ScriptActions constructor, retail 0x003BD56C (22 bytes). ScriptEngine::init
// creates it with operator new(0x10) and stores it in TheScriptActions. The
// global's slot-14 call is the default case of the action-type switch at
// 0x0020C7EC (ZH executeAction).
//
// Donor: ZH ScriptActions::ScriptActions. BFME2 keeps m_suppressNewWindows
// (+0x0C) and drops ZH's m_unnamedUnit assignment. The SubsystemInterface base
// constructor is the pinned 0x001B4E63. Only the final vtable store (0xC1FE48)
// survives /O1.

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

class ScriptActionsInterface : public SubsystemInterface
{
};

class ScriptActions : public ScriptActionsInterface
{
public:
	ScriptActions();
	virtual ~ScriptActions();
	virtual void init();

private:
	bool m_suppressNewWindows; // +0x0C
};

ScriptActions::ScriptActions()
{
	m_suppressNewWindows = false;
}
