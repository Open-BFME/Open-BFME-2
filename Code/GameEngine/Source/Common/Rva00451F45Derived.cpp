// cl: /O1 /MD
//
// Opaque single-inheritance destructors tail-calling Rva00451F45::~
// Rva00451F45 at 0x00451F45 (pinned opaque SEH base dtor: four vptrs at
// +0x00/+0x0C/+0x10/+0x20, calls the 0x24A797 middle plus member helpers;
// identity unproven). The base is modelled here with its full four-vptr
// shape (root plus two secondaries, the +0x10 one carrying 12 bytes of
// opaque data so the layout reaches +0x20, plus the +0x20 secondary); each
// class below derives singly from it (inheriting the four-vptr layout) and
// overrides every vptr before tail-calling the base destructor. The base
// itself is only declared here (defined nowhere -- it resolves via the
// pin), because a same-TU definition would capture the call locally instead
// of at the ledger address. Vtable values are DIR32 auto-patches. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

class Rva00451F45_Root
{
public:
	virtual ~Rva00451F45_Root();

private:
	char m_pad04[8];
};

class Rva00451F45_M1
{
public:
	virtual void f1();
};

class Rva00451F45_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva00451F45_E1
{
public:
	virtual void fe();
};

class Rva00451F45 : public Rva00451F45_Root, public Rva00451F45_M1, public Rva00451F45_B2, public Rva00451F45_E1
{
public:
	virtual ~Rva00451F45();
};

class Rva00492C90 : public Rva00451F45
{
public:
	virtual ~Rva00492C90();
};

Rva00492C90::~Rva00492C90()
{
}

class Rva00494E01 : public Rva00451F45
{
public:
	virtual ~Rva00494E01();
};

Rva00494E01::~Rva00494E01()
{
}

class Rva0049C3FC : public Rva00451F45
{
public:
	virtual ~Rva0049C3FC();
};

Rva0049C3FC::~Rva0049C3FC()
{
}

class Rva004AE1AC : public Rva00451F45
{
public:
	virtual ~Rva004AE1AC();
};

Rva004AE1AC::~Rva004AE1AC()
{
}

class Rva004C6943 : public Rva00451F45
{
public:
	virtual ~Rva004C6943();
};

Rva004C6943::~Rva004C6943()
{
}

class Rva004C6C5C : public Rva00451F45
{
public:
	virtual ~Rva004C6C5C();
};

Rva004C6C5C::~Rva004C6C5C()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva00451F45_M1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
// ?f2@Rva00451F45_B2@@UAEXXZ present-unmatched
void Rva00451F45_B2::f2() {}
// ?fe@Rva00451F45_E1@@UAEXXZ present-unmatched
void Rva00451F45_E1::fe() {}
