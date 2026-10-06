// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva005CFDA6@@UAE@XZ @0x005CFDA6 54B
// Opaque dtor called by the rowed ??_G 0x005CFD8A (vtable 0x00C752C4#0).
// Target facts: no own vptr store (the implicit dtor); destroys the second
// base at +0x08 through the rowed ??1Rva005E9F3F 0x005E9F3F (null-checked
// this+8 adjust) under EH state 0 for the primary base, whose inline dtor
// then resets to its vtable 0x00C75290 (Rva005CF872 { ??_G, slot 1, slot 2 }).
// Identity unproven; address-derived names.

class Rva005CF872
{
public:
	virtual ~Rva005CF872() {}
	virtual void slot1();
	virtual void slot2();

private:
	int m_04;
};

class Rva005E9F3F
{
public:
	virtual ~Rva005E9F3F();

private:
	void *m_04;
};

class Rva005CFDA6 : public Rva005CF872, public Rva005E9F3F
{
public:
	Rva005CFDA6();
	virtual void slot1();
	virtual void slot2();
};

// The implicit virtual dtor (no own vptr store) is emitted with the vtable
// this out-of-line ctor needs.
// ?<Rva005CFDA6::Rva005CFDA6> absent-from-retail
Rva005CFDA6::Rva005CFDA6()
{
}
