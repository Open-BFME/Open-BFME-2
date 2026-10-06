// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva0048593D::~
// Rva0048593D at 0x0048593D (matched opaque MI base dtor in
// DieModuleDerived.cpp: DieModule root plus shared and own empty bases,
// vptrs +0x00/+0x0C/+0x10; only declared here so the tail-call resolves to
// the ledger address instead of a same-TU definition). The class below
// derives singly from the MI base (inheriting its three-vptr layout) and
// overrides all three vptrs (0xC4A8D4/+0x0C 0xC4A818/+0x10 0xC4A810, DIR32
// auto-patches) before tail-calling the base destructor. Owner identities
// are unproven (opaque Rva names). One ledger row per destructor, landed one
// commit at a time.

class Rva0048593D_Root
{
public:
	virtual ~Rva0048593D_Root();

private:
	char m_pad04[8];
};

class Rva0048593D_Mid
{
public:
	virtual void f1();
};

class Rva0048593D_B2
{
public:
	virtual void f2();
};

class Rva0048593D : public Rva0048593D_Root, public Rva0048593D_Mid, public Rva0048593D_B2
{
public:
	virtual ~Rva0048593D();
};

class Rva00485983 : public Rva0048593D
{
public:
	virtual ~Rva00485983();
};

Rva00485983::~Rva00485983()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0048593D_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
