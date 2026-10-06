// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva004BC4FC::~
// Rva004BC4FC at 0x004BC4FC (matched opaque MI base dtor in
// Rva004BB68EDerived.cpp; only declared here so each tail-call resolves to
// the ledger address instead of a same-TU definition). Each class below
// derives singly from the MI base (inheriting its +0x00/+0x0C/+0x10 vptr
// layout, including the family-shared +0x0C secondary 0xC5A040) and
// overrides all three vptrs before tail-calling the base destructor.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva004BC4FC_Root
{
public:
	virtual ~Rva004BC4FC_Root();

private:
	char m_pad04[8];
};

class Rva004BC4FC_Mid
{
public:
	virtual void f1();
};

class Rva004BC4FC_B2
{
public:
	virtual void f2();
};

class Rva004BC4FC : public Rva004BC4FC_Root, public Rva004BC4FC_Mid, public Rva004BC4FC_B2
{
public:
	virtual ~Rva004BC4FC();
};

class Rva004BC83F : public Rva004BC4FC
{
public:
	virtual ~Rva004BC83F();
};

Rva004BC83F::~Rva004BC83F()
{
}

class Rva004BC96F : public Rva004BC4FC
{
public:
	virtual ~Rva004BC96F();
};

Rva004BC96F::~Rva004BC96F()
{
}

class Rva004BCB0D : public Rva004BC4FC
{
public:
	virtual ~Rva004BCB0D();
};

Rva004BCB0D::~Rva004BCB0D()
{
}

class Rva004BCC43 : public Rva004BC4FC
{
public:
	virtual ~Rva004BCC43();
};

Rva004BCC43::~Rva004BCC43()
{
}

class Rva004BCE62 : public Rva004BC4FC
{
public:
	virtual ~Rva004BCE62();
};

Rva004BCE62::~Rva004BCE62()
{
}

class Rva004BD207 : public Rva004BC4FC
{
public:
	virtual ~Rva004BD207();
};

Rva004BD207::~Rva004BD207()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva004BC4FC_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
