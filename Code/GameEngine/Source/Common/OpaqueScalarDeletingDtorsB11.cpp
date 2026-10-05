// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B11: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x00488D40  0x00488D5C  0x00C4B5C8#0
//   0x004AC021  0x004ABFD9  0x00C549F8#0
//   0x004AD538  0x004C6CC1  0x00C5F778#0
//   0x004C182F  0x004C1B7B  0x00C5BC48#0
//   0x004E0E5C  0x004E0D67  0x00C61618#0
//   0x004E4750  0x004E4655  0x00C62260#0
//   0x004EAB6E  0x004EA3B8  0x00C628A0#2
//   0x004EB778  0x004EB5E9  0x00C62928#0
//   0x004EF28F  0x004EED02  0x00C62AC4#0
//   0x004FB1FD  0x004FB130  0x00C63438#0
//   0x004FBD1E  0x004FBCBE  0x00C634E4#0
//   0x004FC563  0x004FC4D1  0x00C63530#0
//   0x004FD85E  0x004FD1BC  0x00C63564#0
//   0x004FF2D2  0x004FF2C0  0x00C63B34#0
//   0x005105BB  0x005105D7  0x00C65604#0
//   0x0051062D  0x0050FDDC  0x00C655BC#0
//   0x00510649  0x00510665  0x00C655C4#0
//   0x00511031  0x00510D0C  0x00C6568C#0
//   0x0051265C  0x005125ED  0x00C659A0#0
//   0x0051342D  0x00512E49  0x00C65B6C#0

struct EmitVtableTag;

class Rva00488D5C
{
public:
	Rva00488D5C(EmitVtableTag *);
public:
	virtual ~Rva00488D5C();
};

// ?<Rva00488D5C::Rva00488D5C> absent-from-retail
Rva00488D5C::Rva00488D5C(EmitVtableTag *)
{
}

class Rva004ABFD9
{
public:
	Rva004ABFD9(EmitVtableTag *);
public:
	virtual ~Rva004ABFD9();
};

// ?<Rva004ABFD9::Rva004ABFD9> absent-from-retail
Rva004ABFD9::Rva004ABFD9(EmitVtableTag *)
{
}

class Rva004C6CC1
{
public:
	Rva004C6CC1(EmitVtableTag *);
public:
	virtual ~Rva004C6CC1();
};

// ?<Rva004C6CC1::Rva004C6CC1> absent-from-retail
Rva004C6CC1::Rva004C6CC1(EmitVtableTag *)
{
}

class Rva004C1B7B
{
public:
	Rva004C1B7B(EmitVtableTag *);
public:
	virtual ~Rva004C1B7B();
};

// ?<Rva004C1B7B::Rva004C1B7B> absent-from-retail
Rva004C1B7B::Rva004C1B7B(EmitVtableTag *)
{
}

class Rva004E0D67
{
public:
	Rva004E0D67(EmitVtableTag *);
public:
	virtual ~Rva004E0D67();
};

// ?<Rva004E0D67::Rva004E0D67> absent-from-retail
Rva004E0D67::Rva004E0D67(EmitVtableTag *)
{
}

class Rva004E4655
{
public:
	Rva004E4655(EmitVtableTag *);
public:
	virtual ~Rva004E4655();
};

// ?<Rva004E4655::Rva004E4655> absent-from-retail
Rva004E4655::Rva004E4655(EmitVtableTag *)
{
}

class Rva004EA3B8
{
public:
	Rva004EA3B8(EmitVtableTag *);
public:
	virtual ~Rva004EA3B8();
};

// ?<Rva004EA3B8::Rva004EA3B8> absent-from-retail
Rva004EA3B8::Rva004EA3B8(EmitVtableTag *)
{
}

class Rva004EB5E9
{
public:
	Rva004EB5E9(EmitVtableTag *);
public:
	virtual ~Rva004EB5E9();
};

// ?<Rva004EB5E9::Rva004EB5E9> absent-from-retail
Rva004EB5E9::Rva004EB5E9(EmitVtableTag *)
{
}

class Rva004EED02
{
public:
	Rva004EED02(EmitVtableTag *);
public:
	virtual ~Rva004EED02();
};

// ?<Rva004EED02::Rva004EED02> absent-from-retail
Rva004EED02::Rva004EED02(EmitVtableTag *)
{
}

class Rva004FB130
{
public:
	Rva004FB130(EmitVtableTag *);
public:
	virtual ~Rva004FB130();
};

// ?<Rva004FB130::Rva004FB130> absent-from-retail
Rva004FB130::Rva004FB130(EmitVtableTag *)
{
}

class Rva004FBCBE
{
public:
	Rva004FBCBE(EmitVtableTag *);
public:
	virtual ~Rva004FBCBE();
};

// ?<Rva004FBCBE::Rva004FBCBE> absent-from-retail
Rva004FBCBE::Rva004FBCBE(EmitVtableTag *)
{
}

class Rva004FC4D1
{
public:
	Rva004FC4D1(EmitVtableTag *);
public:
	virtual ~Rva004FC4D1();
};

// ?<Rva004FC4D1::Rva004FC4D1> absent-from-retail
Rva004FC4D1::Rva004FC4D1(EmitVtableTag *)
{
}

class Rva004FD1BC
{
public:
	Rva004FD1BC(EmitVtableTag *);
public:
	virtual ~Rva004FD1BC();
};

// ?<Rva004FD1BC::Rva004FD1BC> absent-from-retail
Rva004FD1BC::Rva004FD1BC(EmitVtableTag *)
{
}

class Rva004FF2C0
{
public:
	Rva004FF2C0(EmitVtableTag *);
public:
	virtual ~Rva004FF2C0();
};

// ?<Rva004FF2C0::Rva004FF2C0> absent-from-retail
Rva004FF2C0::Rva004FF2C0(EmitVtableTag *)
{
}

class Rva005105D7
{
public:
	Rva005105D7(EmitVtableTag *);
public:
	virtual ~Rva005105D7();
};

// ?<Rva005105D7::Rva005105D7> absent-from-retail
Rva005105D7::Rva005105D7(EmitVtableTag *)
{
}

class Rva0050FDDC
{
public:
	Rva0050FDDC(EmitVtableTag *);
public:
	virtual ~Rva0050FDDC();
};

// ?<Rva0050FDDC::Rva0050FDDC> absent-from-retail
Rva0050FDDC::Rva0050FDDC(EmitVtableTag *)
{
}

class Rva00510665
{
public:
	Rva00510665(EmitVtableTag *);
public:
	virtual ~Rva00510665();
};

// ?<Rva00510665::Rva00510665> absent-from-retail
Rva00510665::Rva00510665(EmitVtableTag *)
{
}

class Rva00510D0C
{
public:
	Rva00510D0C(EmitVtableTag *);
public:
	virtual ~Rva00510D0C();
};

// ?<Rva00510D0C::Rva00510D0C> absent-from-retail
Rva00510D0C::Rva00510D0C(EmitVtableTag *)
{
}

class Rva005125ED
{
public:
	Rva005125ED(EmitVtableTag *);
public:
	virtual ~Rva005125ED();
};

// ?<Rva005125ED::Rva005125ED> absent-from-retail
Rva005125ED::Rva005125ED(EmitVtableTag *)
{
}

class Rva00512E49
{
public:
	Rva00512E49(EmitVtableTag *);
public:
	virtual ~Rva00512E49();
};

// ?<Rva00512E49::Rva00512E49> absent-from-retail
Rva00512E49::Rva00512E49(EmitVtableTag *)
{
}
