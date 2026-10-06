// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva004C131B::~
// Rva004C131B at 0x004C131B (row in Rva00493DEFDerived.cpp). Each class below
// derives (in order) from the base, a shared empty polymorphic base, and its
// own empty polymorphic base, giving vptrs at +0x00/+0x0C/+0x10; the empty
// bases have implicit trivial destructors, so the derived destructor stores
// all three vptrs and tail-calls the base destructor. The +0x0C secondary is
// shared (0xC5AD78). Owner identities are unproven (opaque Rva names). One
// ledger row per destructor, landed one commit at a time.

class Rva004C131B
{
public:
	virtual ~Rva004C131B();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004C1604_B2
{
public:
	virtual void f2();
};

class Rva004C1604 : public Rva004C131B, public MiBase1, public Rva004C1604_B2
{
public:
	virtual ~Rva004C1604();
};

Rva004C1604::~Rva004C1604()
{
}

class Rva004C1866_B2
{
public:
	virtual void f2();
};

class Rva004C1866 : public Rva004C131B, public MiBase1, public Rva004C1866_B2
{
public:
	virtual ~Rva004C1866();
};

Rva004C1866::~Rva004C1866()
{
}
