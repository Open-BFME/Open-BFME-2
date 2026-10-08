// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva004B8CDE::~
// Rva004B8CDE at 0x004B8CDE (pinned opaque MI base: three vptrs tail-jumping
// the 0x49B47C fold; identity unproven). Each class below derives (in order)
// from the opaque base, a shared empty polymorphic base, and its own empty
// polymorphic base, giving vptrs at +0x00/+0x0C/+0x10; the empty bases have
// implicit trivial destructors, so the derived destructor stores all three
// vptrs and tail-calls the base destructor. The +0x0C secondary is shared
// across the family (0xBEF9C0). Owner identities are unproven (opaque Rva
// names). One ledger row per destructor, landed one commit at a time.

class Rva004B8CDE
{
public:
	virtual ~Rva004B8CDE();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004B8C3E_B2
{
public:
	virtual void f2();
};

class Rva004B8C3E : public Rva004B8CDE, public MiBase1, public Rva004B8C3E_B2
{
public:
	virtual ~Rva004B8C3E();
};

Rva004B8C3E::~Rva004B8C3E()
{
}

class Rva004B8DB1_B2
{
public:
	virtual void f2();
};

class Rva004B8DB1 : public Rva004B8CDE, public MiBase1, public Rva004B8DB1_B2
{
public:
	virtual ~Rva004B8DB1();
};

Rva004B8DB1::~Rva004B8DB1()
{
}

class Rva004B8EA8_B2
{
public:
	virtual void f2();
};

class Rva004B8EA8 : public Rva004B8CDE, public MiBase1, public Rva004B8EA8_B2
{
public:
	virtual ~Rva004B8EA8();
};

Rva004B8EA8::~Rva004B8EA8()
{
}

class Rva004B8F92_B2
{
public:
	virtual void f2();
};

class Rva004B8F92 : public Rva004B8CDE, public MiBase1, public Rva004B8F92_B2
{
public:
	virtual ~Rva004B8F92();
};

Rva004B8F92::~Rva004B8F92()
{
}

class Rva004B9287_B2
{
public:
	virtual void f2();
};

class Rva004B9287 : public Rva004B8CDE, public MiBase1, public Rva004B9287_B2
{
public:
	virtual ~Rva004B9287();
};

Rva004B9287::~Rva004B9287()
{
}

class Rva004B9375_B2
{
public:
	virtual void f2();
};

class Rva004B9375 : public Rva004B8CDE, public MiBase1, public Rva004B9375_B2
{
public:
	virtual ~Rva004B9375();
};

Rva004B9375::~Rva004B9375()
{
}

class Rva004B9458_B2
{
public:
	virtual void f2();
};

class Rva004B9458 : public Rva004B8CDE, public MiBase1, public Rva004B9458_B2
{
public:
	virtual ~Rva004B9458();
};

Rva004B9458::~Rva004B9458()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva004B8C3E_B2@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B8DB1_B2@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B8EA8_B2@@UAEXXZ=?onCreate@SupplyWarehouseCreate@@UAEXXZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B8F92_B2@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B9287_B2@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B9375_B2@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B9458_B2@@UAEXXZ=??1Coord2D@@QAE@XZ")
