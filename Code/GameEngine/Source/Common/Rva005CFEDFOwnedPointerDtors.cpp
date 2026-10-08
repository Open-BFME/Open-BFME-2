// cl: /O1 /DNDEBUG /MD /EHsc
//
// Owning-pointer member dtors and the three compiler-generated class dtors
// that call them. Address-derived names throughout; identities unproven.
//
// ??1Rva005EC422@@QAE@XZ @0x005EC4AA 5B and ??1Rva005EBC74@@QAE@XZ
// @0x005EBCC9 5B: each is a bare tail-jump into the rowed owning-pointer
// reset of the same class (?clear@Rva005EC422 0x005EC422,
// ?clear@Rva005EBC74 0x005EBC74, OwnedPointerResets.cpp), i.e. a dtor that
// resets its pointer. Callers: the three dtors below.
//
// ??1Rva005CFEDF@@UAE@XZ @0x005CFEDF 48B, ??1Rva005CFFB8@@UAE@XZ @0x005CFFB8
// 48B and ??1Rva005D10F9@@UAE@XZ @0x005D10F9 48B: no own vptr store (the
// implicit dtor); destroy the owning-pointer member at +0x08 through the
// dtors above under EH state 0 for the base, whose inline dtor then resets
// to its vtable. Bases: 0x00C75290 (Rva005CF872 { ??_G, slot 1, slot 2 },
// as in the rowed Rva005CFDA6Dtor.cpp) for 0x005CFEDF/0x005CFFB8, and
// 0x00C7559C (Rva005D1035 { ??_G, __purecall }) for 0x005D10F9. Own vtables
// 0x00C752E4, 0x00C752EC and 0x00C755AC (two slots each; 0x00C755AC#1 is the
// rowed 0x005D1129, which works the +0x08 member). Callers: the rowed ??_G
// wrappers 0x005CFEC3, 0x005CFF9C and 0x005D10DD.

// noinline: the class dtors below call this row out of line in retail.
class Rva005EC422
{
public:
	__declspec(noinline) ~Rva005EC422();
	void clear();

private:
	void *m_ptr;
};

Rva005EC422::~Rva005EC422()
{
	clear();
}

class Rva005EBC74
{
public:
	~Rva005EBC74();
	void clear();

private:
	void *m_ptr;
};

Rva005EBC74::~Rva005EBC74()
{
	clear();
}

class Rva005CF872
{
public:
	virtual ~Rva005CF872() {}
	virtual void slot1();
	virtual void slot2();

private:
	int m_04;
};

class Rva005D1035
{
public:
	virtual ~Rva005D1035() {}
	virtual void slot1() = 0;

private:
	int m_04;
};

class Rva005CFEDF : public Rva005CF872
{
public:
	Rva005CFEDF();
	virtual void slot1();

private:
	Rva005EBC74 m_08;
};

class Rva005CFFB8 : public Rva005CF872
{
public:
	Rva005CFFB8();
	virtual void slot1();

private:
	Rva005EC422 m_08;
};

class Rva005D10F9 : public Rva005D1035
{
public:
	Rva005D10F9();
	virtual void slot1();

private:
	Rva005EC422 m_08;
};

// The implicit virtual dtors (no own vptr store) are emitted with the
// vtables these out-of-line ctors need.
// ?<Rva005CFEDF::Rva005CFEDF> absent-from-retail
Rva005CFEDF::Rva005CFEDF()
{
}

// ?<Rva005CFFB8::Rva005CFFB8> absent-from-retail
Rva005CFFB8::Rva005CFFB8()
{
}

// ?<Rva005D10F9::Rva005D10F9> absent-from-retail
Rva005D10F9::Rva005D10F9()
{
}
