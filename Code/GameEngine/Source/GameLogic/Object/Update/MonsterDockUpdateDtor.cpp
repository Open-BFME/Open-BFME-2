// cl: /MD
//
// ??1MonsterDockUpdate@@MAE@XZ, retail 0x004A13F4, 32 bytes. Protected
// virtual destructor completing the MonsterDockUpdate file-unit (ctor rowed
// at 0x4A139A in MonsterDockUpdateCtor.cpp, pool-key getter rowed at
// 0x4A1414, vtable 0x00851D74). Donor: BFME1
// MonsterDockUpdateDestructor.cpp protected virtual ~MonsterDockUpdate.
// The body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 (0x851D74) plus the +0x0C (0x851B20), +0x10
// (0x851D68) and +0x20 (0x851D18) secondary slots -- then tail-jumps to the
// opaque SEH base destructor (pinned ??1DockUpdate@@UAE@XZ at 0x0058A0F4).
// The base is modelled with its full four-vptr shape here and only declared
// (defined nowhere) so the call resolves via the pin. Vtable values are
// DIR32 auto-patches. Caller: scalar deleting dtor at 0x004A1459.

class Rva0058A0F4_Root
{
public:
	virtual ~Rva0058A0F4_Root();

private:
	char m_pad04[8];
};

class Rva0058A0F4_M1
{
public:
	virtual void f1();
};

class Rva0058A0F4_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0058A0F4_E1
{
public:
	virtual void fe();
};

class DockUpdate : public Rva0058A0F4_Root, public Rva0058A0F4_M1, public Rva0058A0F4_B2, public Rva0058A0F4_E1
{
public:
	virtual ~DockUpdate();
};

class MonsterDockUpdate : public DockUpdate
{
protected:
	virtual ~MonsterDockUpdate();
};

MonsterDockUpdate::~MonsterDockUpdate()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0058A0F4_M1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?fe@Rva0058A0F4_E1@@UAEXXZ=?isClearToApproach@DockUpdate@@UBE_NPBVObject@@@Z")
