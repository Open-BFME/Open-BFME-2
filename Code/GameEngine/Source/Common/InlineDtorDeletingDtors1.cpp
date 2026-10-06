// cl: /O1 /DNDEBUG /MD
// Scalar deleting destructors of opaque polymorphic classes whose
// destructor is inline and empty: each 29B body stores a vtable, frees
// through operator delete 0x0002FD60 on flag bit 0 and returns this. Each
// is the destructor slot (index read from .rdata, listed beside it) of the
// vtable it stores. The dummy tag constructors (no retail counterpart) only
// make this TU emit each vtable and with it the deleting destructor. Owner
// identities and layouts are not recovered.

struct EmitVtableTag;

// ??_GRva00468A46@@UAEPAXI@Z @0x00468A46 29B: slot 0 of the vtable it stores, VA 0x00C44890
class Rva00468A46
{
public:
	Rva00468A46(EmitVtableTag *);
	virtual ~Rva00468A46() {}
};

// ?<Rva00468A46::Rva00468A46> absent-from-retail
Rva00468A46::Rva00468A46(EmitVtableTag *)
{
}

// ??_GRva0048195F@@UAEPAXI@Z @0x0048195F 29B: slot 0 of the vtable it stores, VA 0x00C49174
class Rva0048195F
{
public:
	Rva0048195F(EmitVtableTag *);
	virtual ~Rva0048195F() {}
};

// ?<Rva0048195F::Rva0048195F> absent-from-retail
Rva0048195F::Rva0048195F(EmitVtableTag *)
{
}

// ??_GRva004BDA0C@@UAEPAXI@Z @0x004BDA0C 29B: slot 0 of the vtable it stores, VA 0x00C5AEB0
class Rva004BDA0C
{
public:
	Rva004BDA0C(EmitVtableTag *);
	virtual ~Rva004BDA0C() {}
};

// ?<Rva004BDA0C::Rva004BDA0C> absent-from-retail
Rva004BDA0C::Rva004BDA0C(EmitVtableTag *)
{
}

// ??_GRva004EA01D@@UAEPAXI@Z @0x004EA01D 29B: slot 2 of the vtable it stores, VA 0x00C62888
class Rva004EA01D
{
public:
	Rva004EA01D(EmitVtableTag *);
	virtual ~Rva004EA01D() {}
};

// ?<Rva004EA01D::Rva004EA01D> absent-from-retail
Rva004EA01D::Rva004EA01D(EmitVtableTag *)
{
}

// ??_GRva0052B668@@UAEPAXI@Z @0x0052B668 29B: slot 0 of the vtable it stores, VA 0x00C686BC
class Rva0052B668
{
public:
	Rva0052B668(EmitVtableTag *);
	virtual ~Rva0052B668() {}
};

// ?<Rva0052B668::Rva0052B668> absent-from-retail
Rva0052B668::Rva0052B668(EmitVtableTag *)
{
}

// ??_GRva00549C74@@UAEPAXI@Z @0x00549C74 29B: slot 0 of the vtable it stores, VA 0x00C6A68C
class Rva00549C74
{
public:
	Rva00549C74(EmitVtableTag *);
	virtual ~Rva00549C74() {}
};

// ?<Rva00549C74::Rva00549C74> absent-from-retail
Rva00549C74::Rva00549C74(EmitVtableTag *)
{
}

// ??_GRva0054E79D@@UAEPAXI@Z @0x0054E79D 29B: slot 0 of the vtable it stores, VA 0x00C6A894
class Rva0054E79D
{
public:
	Rva0054E79D(EmitVtableTag *);
	virtual ~Rva0054E79D() {}
};

// ?<Rva0054E79D::Rva0054E79D> absent-from-retail
Rva0054E79D::Rva0054E79D(EmitVtableTag *)
{
}

// ??_GRva0054F922@@UAEPAXI@Z @0x0054F922 29B: slot 0 of the vtable it stores, VA 0x00C6AB10
class Rva0054F922
{
public:
	Rva0054F922(EmitVtableTag *);
	virtual ~Rva0054F922() {}
};

// ?<Rva0054F922::Rva0054F922> absent-from-retail
Rva0054F922::Rva0054F922(EmitVtableTag *)
{
}

// ??_GRva0055057D@@UAEPAXI@Z @0x0055057D 29B: slot 0 of the vtable it stores, VA 0x00C6ABC0
class Rva0055057D
{
public:
	Rva0055057D(EmitVtableTag *);
	virtual ~Rva0055057D() {}
};

// ?<Rva0055057D::Rva0055057D> absent-from-retail
Rva0055057D::Rva0055057D(EmitVtableTag *)
{
}

// ??_GRva005753E9@@UAEPAXI@Z @0x005753E9 29B: slot 10 of the vtable it stores, VA 0x00C6E5C4
class Rva005753E9
{
public:
	Rva005753E9(EmitVtableTag *);
	virtual ~Rva005753E9() {}
	void rva0057544B();
};

// ?<Rva005753E9::Rva005753E9> absent-from-retail
Rva005753E9::Rva005753E9(EmitVtableTag *)
{
}

class Rva005CCB4CCall
{
public:
	bool rva005CCB4C();
};
class Rva005CCB3EByteChaseField
{
public:
	unsigned char get() const;
};
class Rva005CCB5B
{
public:
	void rva005CCB5B();
};
class Rva005CCB7B
{
public:
	void rva005CCB7B(bool value);
};

// Target evidence: this is slot 13 of the table at 0x00C6E5C4, whose slot 10
// contains the rowed deleting dtor at 0x005753E9. The existing 0x005CCB5B,
// 0x005CCB3E, and 0x005CCB7B rows show the target helper chain. The vtable
// association is structural; the method's purpose and class identity remain
// unproven beyond the address-derived Rva005753E9 view.
void Rva005753E9::rva0057544B()
{
	if (!((Rva005CCB4CCall *)this)->rva005CCB4C())
		return ((Rva005CCB5B *)this)->rva005CCB5B();
	((Rva005CCB7B *)this)->rva005CCB7B(
		!((Rva005CCB3EByteChaseField *)this)->get());
}

// ??_GRva005754FF@@UAEPAXI@Z @0x005754FF 29B: slot 0 of the vtable it stores, VA 0x00C6E60C
class Rva005754FF
{
public:
	Rva005754FF(EmitVtableTag *);
	virtual ~Rva005754FF() {}
};

// ?<Rva005754FF::Rva005754FF> absent-from-retail
Rva005754FF::Rva005754FF(EmitVtableTag *)
{
}

// ??_GRva0059EB41@@UAEPAXI@Z @0x0059EB41 29B: slot 2 of the vtable it stores, VA 0x00C711BC
class Rva0059EB41
{
public:
	Rva0059EB41(EmitVtableTag *);
	virtual ~Rva0059EB41() {}
};

// ?<Rva0059EB41::Rva0059EB41> absent-from-retail
Rva0059EB41::Rva0059EB41(EmitVtableTag *)
{
}

// ??_GRva005A66EC@@UAEPAXI@Z @0x005A66EC 29B: slot 0 of the vtable it stores, VA 0x00C71AE0
class Rva005A66EC
{
public:
	Rva005A66EC(EmitVtableTag *);
	virtual ~Rva005A66EC() {}
};

// ?<Rva005A66EC::Rva005A66EC> absent-from-retail
Rva005A66EC::Rva005A66EC(EmitVtableTag *)
{
}

// ??_GRva005CB243@@UAEPAXI@Z @0x005CB243 29B: slot 0 of the vtable it stores, VA 0x00C74CA4
class Rva005CB243
{
public:
	Rva005CB243(EmitVtableTag *);
	virtual ~Rva005CB243() {}
};

// ?<Rva005CB243::Rva005CB243> absent-from-retail
Rva005CB243::Rva005CB243(EmitVtableTag *)
{
}

// ??_GRva005CE8F5@@UAEPAXI@Z @0x005CE8F5 29B: slot 0 of the vtable it stores, VA 0x00C751A8
class Rva005CE8F5
{
public:
	Rva005CE8F5(EmitVtableTag *);
	virtual ~Rva005CE8F5() {}
};

// ?<Rva005CE8F5::Rva005CE8F5> absent-from-retail
Rva005CE8F5::Rva005CE8F5(EmitVtableTag *)
{
}

// ??_GRva005CF826@@UAEPAXI@Z @0x005CF826 29B: slot 0 of the vtable it stores, VA 0x00C75278
class Rva005CF826
{
public:
	Rva005CF826(EmitVtableTag *);
	virtual ~Rva005CF826() {}
};

// ?<Rva005CF826::Rva005CF826> absent-from-retail
Rva005CF826::Rva005CF826(EmitVtableTag *)
{
}

// ??_GRva005D1035@@UAEPAXI@Z @0x005D1035 29B: slot 0 of the vtable it stores, VA 0x00C7559C
class Rva005D1035
{
public:
	Rva005D1035(EmitVtableTag *);
	virtual ~Rva005D1035() {}
};

// ?<Rva005D1035::Rva005D1035> absent-from-retail
Rva005D1035::Rva005D1035(EmitVtableTag *)
{
}

// ??_GRva005E567D@@UAEPAXI@Z @0x005E567D 29B: slot 0 of the vtable it stores, VA 0x00C77D30
class Rva005E567D
{
public:
	Rva005E567D(EmitVtableTag *);
	virtual ~Rva005E567D() {}
};

// ?<Rva005E567D::Rva005E567D> absent-from-retail
Rva005E567D::Rva005E567D(EmitVtableTag *)
{
}

// ??_GRva005E9FA4@@UAEPAXI@Z @0x005E9FA4 29B: slot 0 of the vtable it stores, VA 0x00C780F4
class Rva005E9FA4
{
public:
	Rva005E9FA4(EmitVtableTag *);
	virtual ~Rva005E9FA4() {}
};

// ?<Rva005E9FA4::Rva005E9FA4> absent-from-retail
Rva005E9FA4::Rva005E9FA4(EmitVtableTag *)
{
}

// ??_GRva00602645@@UAEPAXI@Z @0x00602645 29B: slot 0 of the vtable it stores, VA 0x00C7A84C
class Rva00602645
{
public:
	Rva00602645(EmitVtableTag *);
	virtual ~Rva00602645() {}
};

// ?<Rva00602645::Rva00602645> absent-from-retail
Rva00602645::Rva00602645(EmitVtableTag *)
{
}

// ??_GRva00604A42@@UAEPAXI@Z @0x00604A42 29B: slot 0 of the vtable it stores, VA 0x00C7A974
class Rva00604A42
{
public:
	Rva00604A42(EmitVtableTag *);
	virtual ~Rva00604A42() {}
};

// ?<Rva00604A42::Rva00604A42> absent-from-retail
Rva00604A42::Rva00604A42(EmitVtableTag *)
{
}
