// flags: region default (reverse/retail_inventory/flag_regions.csv)
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

extern "C" const void *const vtbl_00C1FD98[];  // ??_7Rva003BA6A9@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1FD98=??_7Rva003BA6A9@@6B@")

extern class TerrainLogic *TheTerrainLogic;

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

#define Rva00DFEC50 (*(void **)&TheTerrainLogic)

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
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00C1FD98));
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

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?init@ScriptActions@@UAEXXZ=?rva000D20D6@Rva000D20D6@@UAEXXZ")
