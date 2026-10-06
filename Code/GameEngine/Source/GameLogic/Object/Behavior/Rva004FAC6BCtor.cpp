// cl: /DNDEBUG /MD
// ??0Rva004FAC6B@@QAE@XZ @0x004FAC6B 21B: honest ctor with member at +4.
// Evidence: calls rowed Rva00330757Member ctor 0x00330757 for member at +4; installs vtable 0x008633C0; called by derived ctor 0x004FADF4 which overrides vtable to 0x008633FC; prev row is dtor in same subsystem.
class Rva00330757Member
{
public:
	Rva00330757Member();
};

class __declspec(novtable) Rva004FAC6BBase0
{
public:
	virtual void base0();
};

class Rva004FAC6B : public Rva004FAC6BBase0, public Rva00330757Member
{
public:
	Rva004FAC6B();
	virtual ~Rva004FAC6B();
};

Rva004FAC6B::Rva004FAC6B()
{
}

// ??0Rva00578C2E@@QAE@XZ, retail 0x00578C2E, 21 bytes: the same constructor for a
// sibling class over the same bases, differing from ??0Rva004FAC6B's bytes only
// in the vftable it stores (VA 0xbe2b78). Its destructor is inline and empty so
// the emitted vftable needs nothing new. Identity is not recovered.
class Rva00578C2E : public Rva004FAC6BBase0, public Rva00330757Member
{
public:
	Rva00578C2E();
	virtual ~Rva00578C2E() {}
};

Rva00578C2E::Rva00578C2E()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?base0@Rva004FAC6BBase0@@UAEXXZ=__purecall")
