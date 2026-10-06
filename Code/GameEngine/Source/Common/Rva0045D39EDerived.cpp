// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva0045D39E::~
// Rva0045D39E at 0x0045D39E (matched opaque MI-grandchild dtor in
// Rva0024A797Grandchildren.cpp: middle plus two extra bases, vptrs
// +0x00/+0x0C/+0x10/+0x20/+0x24; only declared in full here so each
// tail-call resolves to the ledger address instead of a same-TU definition).
// Each class below derives singly from it (inheriting the five-vptr layout)
// and overrides every vptr before tail-calling the base destructor. Vtable
// values are DIR32 auto-patches. Owner identities are unproven (opaque Rva
// names). One ledger row per destructor, landed one commit at a time.

extern "C" const void *const vtbl_00C49D70[];  // ??_7ClearanceTestingSlowDeathBehavior@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C49D70=??_7ClearanceTestingSlowDeathBehavior@@6B@")

class Rva0045D39E_Root
{
public:
	virtual ~Rva0045D39E_Root();

private:
	char m_pad04[8];
};

class Rva0045D39E_Mid
{
public:
	virtual void f1();
};

class Rva0045D39E_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0045D39E_E1
{
public:
	virtual void fe();
};

class Rva0045D39E_E2
{
public:
	virtual void ff();
};

class Rva0045D39E : public Rva0045D39E_Root, public Rva0045D39E_Mid, public Rva0045D39E_B2, public Rva0045D39E_E1, public Rva0045D39E_E2
{
public:
	virtual ~Rva0045D39E();
};

class Rva0045EA3F : public Rva0045D39E
{
public:
	virtual ~Rva0045EA3F();
};

Rva0045EA3F::~Rva0045EA3F()
{
}

class Rva00461EEB : public Rva0045D39E
{
public:
	virtual ~Rva00461EEB();
};

Rva00461EEB::~Rva00461EEB()
{
}

class Rva00483C35 : public Rva0045D39E
{
public:
	virtual ~Rva00483C35();

private:
	char m_pad0028[0x50 - 0x28];
	int m_extra0050;
};

Rva00483C35::~Rva00483C35()
{
	m_extra0050 = ((unsigned int)vtbl_00C49D70);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0045D39E_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
