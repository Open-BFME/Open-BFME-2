// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B03: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x00148DC3  0x00148BC2  0x00BD3568#0
//   0x0014DCAC  0x0014DC9E  0x00BD3898#0
//   0x00150A5B  0x001505CD  0x00BD3A34#0
//   0x001684BA  0x001684D6  0x00BD41C8#1
//   0x0018010E  0x0017FFCA  0x00BD4F50#9
//   0x001D93B2  0x001D92C0  0x00BD9CB0#0
//   0x001DF3D5  0x001DF057  0x00BDC5B8#0
//   0x001E1241  0x001E125D  0x00BDD95C#0
//   0x001E28EA  0x001E2906  0x00BDD978#0
//   0x001E2C92  0x001E2AD9  0x00BDD97C#0
//   0x001E7EAE  0x001E72B4  0x00BDE970#0
//   0x001EB815  0x0037DEE4  0x00BDF158#0
//   0x001ED52D  0x001ED41B  0x00BDF260#0
//   0x001F4B47  0x001F4B01  0x00BE171C#0
//   0x001F61E5  0x001F4D22  0x00BE174C#0
//   0x001FA779  0x001F9D98  0x00BE18C8#0
//   0x001FC17F  0x001FBD17  0x00BE1A10#0
//   0x001FC3A3  0x001FC0F1  0x00BE1A38#0
//   0x001FE772  0x001FE06A  0x00BE1BE8#0

struct EmitVtableTag;

class Rva00148BC2
{
public:
	Rva00148BC2(EmitVtableTag *);
public:
	virtual ~Rva00148BC2();
};

// ?<Rva00148BC2::Rva00148BC2> absent-from-retail
Rva00148BC2::Rva00148BC2(EmitVtableTag *)
{
}

class Rva0014DC9E
{
public:
	Rva0014DC9E(EmitVtableTag *);
public:
	virtual ~Rva0014DC9E();
};

// ?<Rva0014DC9E::Rva0014DC9E> absent-from-retail
Rva0014DC9E::Rva0014DC9E(EmitVtableTag *)
{
}

class Rva001505CD
{
public:
	Rva001505CD(EmitVtableTag *);
public:
	virtual ~Rva001505CD();
};

// ?<Rva001505CD::Rva001505CD> absent-from-retail
Rva001505CD::Rva001505CD(EmitVtableTag *)
{
}

class Rva001684D6Base0
{
public:
	virtual ~Rva001684D6Base0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x8) in its vtable is target evidence for it.
class Rva001684D6Base8
{
public:
	virtual ~Rva001684D6Base8();
};
// Slot 2 of its vtable 0x00BD41C8 (0x001686EB) is a Clone: new 0x108 bytes
// and the copy constructor 0x00168527, which starts with the RenderObjClass
// copy at 0x0013BF00. Size from that allocation.
class Rva001684D6 : public Rva001684D6Base0, public Rva001684D6Base8
{
public:
	Rva001684D6(EmitVtableTag *);
	Rva001684D6(const Rva001684D6 &src);
	virtual Rva001684D6 *Clone() const;
public:
	virtual ~Rva001684D6();
private:
	char m_unmodelled_0C[0x108 - 0x0C];
};

Rva001684D6 *Rva001684D6::Clone() const
{
	return new Rva001684D6(*this);
}

// ?<Rva001684D6::Rva001684D6> absent-from-retail
Rva001684D6::Rva001684D6(EmitVtableTag *)
{
}

class Rva0017FFCA
{
public:
	Rva0017FFCA(EmitVtableTag *);
public:
	virtual ~Rva0017FFCA();
};

// ?<Rva0017FFCA::Rva0017FFCA> absent-from-retail
Rva0017FFCA::Rva0017FFCA(EmitVtableTag *)
{
}

class Rva001D92C0
{
public:
	Rva001D92C0(EmitVtableTag *);
public:
	virtual ~Rva001D92C0();
};

// ?<Rva001D92C0::Rva001D92C0> absent-from-retail
Rva001D92C0::Rva001D92C0(EmitVtableTag *)
{
}

class Rva001DF057Base0 { public: virtual ~Rva001DF057Base0(); private: char m_unmodelled[0x8]; };
// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x001DF0F1 in its vtable is target evidence for it.
class Rva001DF057BaseC { public: virtual ~Rva001DF057BaseC(); };
class Rva001DF057 : public Rva001DF057Base0, public Rva001DF057BaseC
{
public:
	Rva001DF057(EmitVtableTag *);
public:
	virtual ~Rva001DF057();
};

// ?<Rva001DF057::Rva001DF057> absent-from-retail
Rva001DF057::Rva001DF057(EmitVtableTag *)
{
}

class Rva001E125D
{
public:
	Rva001E125D(EmitVtableTag *);
public:
	virtual ~Rva001E125D();
};

// ?<Rva001E125D::Rva001E125D> absent-from-retail
Rva001E125D::Rva001E125D(EmitVtableTag *)
{
}

class Rva001E2906Base0
{
public:
	virtual ~Rva001E2906Base0();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

// Secondary base at +0x28: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x28) in its vtable is target evidence for it.
class Rva001E2906Base28
{
public:
	virtual ~Rva001E2906Base28();
};
class Rva001E2906 : public Rva001E2906Base0, public Rva001E2906Base28
{
public:
	Rva001E2906(EmitVtableTag *);
public:
	virtual ~Rva001E2906();
};

// ?<Rva001E2906::Rva001E2906> absent-from-retail
Rva001E2906::Rva001E2906(EmitVtableTag *)
{
}

class Rva001E2AD9
{
public:
	Rva001E2AD9(EmitVtableTag *);
public:
	virtual ~Rva001E2AD9();
};

// ?<Rva001E2AD9::Rva001E2AD9> absent-from-retail
Rva001E2AD9::Rva001E2AD9(EmitVtableTag *)
{
}

class Rva001E72B4
{
public:
	Rva001E72B4(EmitVtableTag *);
public:
	virtual ~Rva001E72B4();
};

// ?<Rva001E72B4::Rva001E72B4> absent-from-retail
Rva001E72B4::Rva001E72B4(EmitVtableTag *)
{
}

class Rva0037DEE4
{
public:
	Rva0037DEE4(EmitVtableTag *);
public:
	virtual ~Rva0037DEE4();
};

// ?<Rva0037DEE4::Rva0037DEE4> absent-from-retail
Rva0037DEE4::Rva0037DEE4(EmitVtableTag *)
{
}

class Rva001ED41BBase0
{
public:
	virtual ~Rva001ED41BBase0();
};

// Secondary base at +0x4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x4) in its vtable is target evidence for it.
class Rva001ED41BBase4
{
public:
	virtual ~Rva001ED41BBase4();
};
class Rva001ED41B : public Rva001ED41BBase0, public Rva001ED41BBase4
{
public:
	Rva001ED41B(EmitVtableTag *);
public:
	virtual ~Rva001ED41B();
};

// ?<Rva001ED41B::Rva001ED41B> absent-from-retail
Rva001ED41B::Rva001ED41B(EmitVtableTag *)
{
}

class Rva001F4B01
{
public:
	Rva001F4B01(EmitVtableTag *);
public:
	virtual ~Rva001F4B01();
};

// ?<Rva001F4B01::Rva001F4B01> absent-from-retail
Rva001F4B01::Rva001F4B01(EmitVtableTag *)
{
}

class Rva001F4D22
{
public:
	Rva001F4D22(EmitVtableTag *);
public:
	virtual ~Rva001F4D22();
};

// ?<Rva001F4D22::Rva001F4D22> absent-from-retail
Rva001F4D22::Rva001F4D22(EmitVtableTag *)
{
}

class Rva001F9D98Base0 { public: virtual ~Rva001F9D98Base0(); private: char m_unmodelled[0x8]; };
// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x001F9EA7 in its vtable is target evidence for it.
class Rva001F9D98BaseC { public: virtual ~Rva001F9D98BaseC(); };
class Rva001F9D98 : public Rva001F9D98Base0, public Rva001F9D98BaseC
{
public:
	Rva001F9D98(EmitVtableTag *);
public:
	virtual ~Rva001F9D98();
};

// ?<Rva001F9D98::Rva001F9D98> absent-from-retail
Rva001F9D98::Rva001F9D98(EmitVtableTag *)
{
}

class Rva001FBD17
{
public:
	Rva001FBD17(EmitVtableTag *);
public:
	virtual ~Rva001FBD17();
};

// ?<Rva001FBD17::Rva001FBD17> absent-from-retail
Rva001FBD17::Rva001FBD17(EmitVtableTag *)
{
}

class Rva001FC0F1
{
public:
	Rva001FC0F1(EmitVtableTag *);
public:
	virtual ~Rva001FC0F1();
};

// ?<Rva001FC0F1::Rva001FC0F1> absent-from-retail
Rva001FC0F1::Rva001FC0F1(EmitVtableTag *)
{
}

class Rva001FE06A
{
public:
	Rva001FE06A(EmitVtableTag *);
public:
	virtual ~Rva001FE06A();
};

// ?<Rva001FE06A::Rva001FE06A> absent-from-retail
Rva001FE06A::Rva001FE06A(EmitVtableTag *)
{
}
