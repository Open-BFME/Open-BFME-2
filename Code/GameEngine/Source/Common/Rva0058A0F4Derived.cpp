// cl: /MD
//
// Opaque single-inheritance destructors tail-calling DockUpdate::~
// DockUpdate at 0x0058A0F4 (pinned opaque SEH base dtor: four vptrs at
// +0x00/+0x0C/+0x10/+0x20, frees string members via 0x30830; identity
// unproven). The base is modelled here with its full four-vptr shape (root
// plus two secondaries, the +0x10 one carrying 12 bytes of opaque data so
// the layout reaches +0x20, plus the +0x20 secondary); each class below
// derives singly from it (inheriting the four-vptr layout) and overrides
// every vptr before tail-calling the base destructor. The base itself is
// only declared here (defined nowhere -- it resolves via the pin), because
// a same-TU definition would capture the call locally instead of at the
// ledger address. Vtable values are DIR32 auto-patches. Owner identities are
// unproven (opaque Rva names). One ledger row per destructor, landed one
// commit at a time.

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

class Rva004A0E0C : public DockUpdate
{
public:
	virtual ~Rva004A0E0C();
};

Rva004A0E0C::~Rva004A0E0C()
{
}

class Rva004A11D4 : public DockUpdate
{
public:
	virtual ~Rva004A11D4();
};

Rva004A11D4::~Rva004A11D4()
{
}

class Rva004A7D55 : public DockUpdate
{
public:
	virtual ~Rva004A7D55();
};

Rva004A7D55::~Rva004A7D55()
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
