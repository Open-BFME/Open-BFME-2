// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva00493DEF::~
// Rva00493DEF at 0x00493DEF (pinned opaque MI base: SEH, three vptrs
// including the shared 0xBEFCF8 secondary; identity unproven). Each class
// below derives (in order) from the opaque base, a shared empty polymorphic
// base, and its own empty polymorphic base, giving vptrs at +0x00/+0x0C/+0x10;
// the empty bases have implicit trivial destructors, so the derived
// destructor stores all three vptrs and tail-calls the base destructor. The
// +0x0C secondary is shared across the family (0xBEFCF8). Owner identities
// are unproven (opaque Rva names). One ledger row per destructor, landed one
// commit at a time.

class Rva00493DEF
{
public:
	virtual ~Rva00493DEF();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};



class Rva004C29BB_B2
{
public:
	virtual void f2();
};

class Rva004C29BB : public Rva00493DEF, public MiBase1, public Rva004C29BB_B2
{
public:
	virtual ~Rva004C29BB();
};

Rva004C29BB::~Rva004C29BB()
{
}

class Rva004C3108_B2
{
public:
	virtual void f2();
};

class Rva004C3108 : public Rva00493DEF, public MiBase1, public Rva004C3108_B2
{
public:
	virtual ~Rva004C3108();
};

Rva004C3108::~Rva004C3108()
{
}

















class Rva004C67A0_B2
{
public:
	virtual void f2();
};

class Rva004C67A0 : public Rva00493DEF, public MiBase1, public Rva004C67A0_B2
{
public:
	virtual ~Rva004C67A0();
};

Rva004C67A0::~Rva004C67A0()
{
}















class Rva004C8A16_B2
{
public:
	virtual void f2();
};

class Rva004C8A16 : public Rva00493DEF, public MiBase1, public Rva004C8A16_B2
{
public:
	virtual ~Rva004C8A16();
};

Rva004C8A16::~Rva004C8A16()
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva004C2656_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C29BB_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C3108_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C67A0_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C8A16_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
