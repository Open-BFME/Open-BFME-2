// cl: /DNDEBUG /MD /GX
//
// ??1HordeWorkerAIUpdate@@UAE@XZ, retail 0x0049AC94 (49 bytes).
// Behavior-side destructor (class of rowed ctor 0x49AD15, vtable 0x008508C8):
// restores the five vptrs at +0x00/+0x0C/+0x10/+0x20/+0x24 (DBaseRoot/M1/B2/
// M3/M4 shape, DeployStyleAIUpdateDtor precedent) plus the +0x3E4 word via
// the inherited extra, then tail-jumps to the rowed base dtor
// ??1HordeAIUpdate@@UAE@XZ at 0x0049A64B. Sole caller is the scalar-deleting
// dtor at 0x0049AD9B.

// Same complete secondary-interface table installed by both Horde constructors.
// The existing data-row owner supplies its twenty verified function entries.
extern const void *const g_00C50868[];

class Thing;
class ModuleData;

class DBaseRoot
{
public:
	virtual ~DBaseRoot();

private:
	char m_pad04[8];
};

class DBaseM1
{
public:
	virtual void f1();
};

class DBaseB2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

struct AICommandParms;

// The AI command interface: its only slot is aiDoCommand.
class DBaseM3
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
};

class DBaseM4
{
public:
	virtual void f4();
};

class Rva0026E836 : public DBaseRoot, public DBaseM1, public DBaseB2, public DBaseM3, public DBaseM4
{
public:
	virtual ~Rva0026E836();
};

class HordeAIUpdate : public Rva0026E836
{
public:
	virtual ~HordeAIUpdate();

protected:
	char m_pad0028[0x3E4 - 0x28];
	const void *m_extra03E4;
};

class HordeWorkerAIUpdate : public HordeAIUpdate
{
public:
	virtual ~HordeWorkerAIUpdate();
	// Rowed at 0x0049B231 (HordeAIUpdatePrivateCommands.cpp).
	virtual void aiDoCommand(const AICommandParms *parms);
};

HordeWorkerAIUpdate::~HordeWorkerAIUpdate()
{
	m_extra03E4 = g_00C50868;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@DBaseM1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
