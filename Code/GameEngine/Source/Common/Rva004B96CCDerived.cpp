// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva004B96CC::~
// Rva004B96CC at 0x004B96CC (pinned opaque MI base; identity unproven). Each
// class below derives (in order) from the opaque base, a shared empty
// polymorphic base, and its own empty polymorphic base, giving vptrs at
// +0x00/+0x0C/+0x10; the empty bases have implicit trivial destructors, so
// the derived destructor stores all three vptrs and tail-calls the base
// destructor. The +0x0C secondary is shared across the family (0xC597F8).
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva004B96CC
{
public:
	virtual ~Rva004B96CC();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004B96E5_B2
{
public:
	virtual void f2();
};

class Rva004B96E5 : public Rva004B96CC, public MiBase1, public Rva004B96E5_B2
{
public:
	virtual ~Rva004B96E5();
};

Rva004B96E5::~Rva004B96E5()
{
}

class Rva004BAB36_B2
{
public:
	virtual void f2();
};

class Rva004BAB36 : public Rva004B96CC, public MiBase1, public Rva004BAB36_B2
{
public:
	virtual ~Rva004BAB36();
};

Rva004BAB36::~Rva004BAB36()
{
}

class Rva004BB0CC_B2
{
public:
	virtual void f2();
};

class Rva004BB0CC : public Rva004B96CC, public MiBase1, public Rva004BB0CC_B2
{
public:
	virtual ~Rva004BB0CC();
};

Rva004BB0CC::~Rva004BB0CC()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva004B96E5_B2@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
