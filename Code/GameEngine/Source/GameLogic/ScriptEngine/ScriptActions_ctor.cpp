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
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void Rva003BA8AC() = 0;

private:
	bool m_suppressNewWindows; // +0x0C
};

#define Rva00DFEC50 (*(void **)0x00DFEC50)

struct Rva00DFEC50Obj
{
	unsigned char m_pad[0x1914];
	bool m_flag1914;
};

ScriptActions::ScriptActions()
{
	m_suppressNewWindows = false;
}

// ??1ScriptActions@@UAE@XZ, retail 0x003BD582, 22 bytes. Dtor calls the
// rowed Rva003BA8AC clear then tail-jmps to the pinned SubsystemInterface
// base dtor at 0x1B4E74; compiler emits the derived 0xC1FE48 plus base
// 0xC1FD98 vtable stores. Donor is BFME1 ScriptActionsDestructor.cpp.
// Caller is the slot-0 ??_G at 0x3BE5AD (vtable 0x81FE48).

ScriptActions::~ScriptActions()
{
	Rva003BA8AC();
	*(const void **)this = reinterpret_cast<const void *>(0x00C1FD98);
}

void ScriptActions::Rva003BA8AC()
{
	m_suppressNewWindows = false;
	if (Rva00DFEC50 != 0)
	{
		reinterpret_cast<Rva00DFEC50Obj *>(Rva00DFEC50)->m_flag1914 = false;
	}
	m_suppressNewWindows = false;
}
