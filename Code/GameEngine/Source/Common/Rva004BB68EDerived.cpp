// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva004BB68E::~
// Rva004BB68E at 0x004BB68E (pinned opaque MI base; identity unproven). Each
// class below derives (in order) from the opaque base, a shared empty
// polymorphic base, and its own empty polymorphic base, giving vptrs at
// +0x00/+0x0C/+0x10; the empty bases have implicit trivial destructors, so
// the derived destructor stores all three vptrs and tail-calls the base
// destructor. The +0x0C secondary is shared across the family (0xC5A040).
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva004BB68E
{
public:
	virtual ~Rva004BB68E();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004BB949_B2
{
public:
	virtual void f2();
};

class Rva004BB949 : public Rva004BB68E, public MiBase1, public Rva004BB949_B2
{
public:
	virtual ~Rva004BB949();
};

Rva004BB949::~Rva004BB949()
{
}

class Rva004BC325_B2
{
public:
	virtual void f2();
};

class Rva004BC325 : public Rva004BB68E, public MiBase1, public Rva004BC325_B2
{
public:
	virtual ~Rva004BC325();
};

Rva004BC325::~Rva004BC325()
{
}

class Rva004BC4FC_B2
{
public:
	virtual void f2();
};

class Rva004BC4FC : public Rva004BB68E, public MiBase1, public Rva004BC4FC_B2
{
public:
	virtual ~Rva004BC4FC();
};

Rva004BC4FC::~Rva004BC4FC()
{
}

class Rva004BD5ED_B2
{
public:
	virtual void f2();
};

class Rva004BD5ED : public Rva004BB68E, public MiBase1, public Rva004BD5ED_B2
{
public:
	virtual ~Rva004BD5ED();
};

Rva004BD5ED::~Rva004BD5ED()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva004BD5ED_B2@@UAEXXZ=?bfmeGo1026F@BfmeF1026@@QAEXHHH@Z")
