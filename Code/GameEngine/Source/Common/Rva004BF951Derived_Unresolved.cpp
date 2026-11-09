// cl: /MD
// Split from Rva004BF951Derived.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Opaque multiple-inheritance destructors tail-calling Rva004BF951::~
// Rva004BF951 at 0x004BF951 (pinned opaque MI base dtor: SEH; identity
// unproven). Each class below derives (in order) from the opaque base, a
// shared empty polymorphic base, and its own empty polymorphic base, giving
// vptrs at +0x00/+0x0C/+0x10; the empty bases have implicit trivial
// destructors, so the derived destructor stores all three vptrs and
// tail-calls the base destructor. The +0x0C secondary is shared across most
// of the family (0xC5AD78; one body uses 0xC5B770, patched per row).
// Owner identities are unproven (opaque Rva names). The HighlanderBody,
// OathbreakerBody and PorcupineFormationBodyModule members of this family
// (0x004C07B1, 0x004C1EF7, 0x004C2016: their +0x10 table's slot 0 is the
// rowed attemptDamage of that class) are rowed in their constructor units. One ledger row per
// destructor, landed one commit at a time.

class Rva004BF951
{
public:
	virtual ~Rva004BF951();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004C089E_B2
{
public:
	virtual void f2() = 0;
};

class Rva004C089E : public Rva004BF951, public MiBase1, public Rva004C089E_B2
{
public:
	virtual ~Rva004C089E();
};

Rva004C089E::~Rva004C089E()
{
}



class Rva004C131B_B2
{
public:
	virtual void f2() = 0;
};

class Rva004C131B : public Rva004BF951, public MiBase1, public Rva004C131B_B2
{
public:
	virtual ~Rva004C131B();
};

Rva004C131B::~Rva004C131B()
{
}

class Rva004C1BAB_B2
{
public:
	virtual void f2() = 0;

private:
	char m_pad04[0xEC];
};

class Rva004C1BAB_B3
{
public:
	virtual void f3();
};

class Rva004C1BAB : public Rva004BF951, public MiBase1, public Rva004C1BAB_B2, public Rva004C1BAB_B3
{
public:
	virtual ~Rva004C1BAB();
};

Rva004C1BAB::~Rva004C1BAB()
{
}
#pragma comment(linker, "/alternatename:?f3@Rva004C1BAB_B3@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
