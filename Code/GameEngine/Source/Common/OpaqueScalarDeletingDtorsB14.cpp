// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B14: 28-byte wrappers that
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
//   0x0059E736  0x0059E5AE  0x00C71094#0
//   0x0059EAA3  0x0059EA42  0x00C71138#0
//   0x005A0B62  0x005A0009  0x00C71414#0
//   0x005AE38A  0x005AE30A  0x00C726A0#0
//   0x005AE76E  0x005AE66B  0x00C72760#0
//   0x005B1A50  0x005B190D  0x00C72A80#0
//   0x005B4541  0x005B3D94  0x00C72F3C#0
//   0x005B576B  0x005B5420  0x00C73450#0
//   0x005B6166  0x005B5CF4  0x00C735C0#0
//   0x005BA272  0x005BA23A  0x00C73D34#0
//   0x005BA303  0x005BA2CB  0x00C73DCC#0
//   0x005BA92E  0x005BA593  0x00C73E24#0
//   0x005C4336  0x005C4230  0x00C744E8#0
//   0x005C43E7  0x005C47A3  0x00C63398#0, 0x00C745A0#0, 0x00C74698#0, 0x00C7475C#0
//   0x005C49B8  0x005C48E5  0x00C7477C#0
//   0x005C4A75  0x005C4A91  0x00C747A8#0
//   0x005C6D80  0x005C6C7B  0x00C74918#0
//   0x005C9753  0x005C9659  0x00C74B70#0
//   0x005CC44C  0x005CC37C  0x00C74E38#0
//   0x005CC63A  0x005CC656  0x00C74E70#0

struct EmitVtableTag;

class Rva0059E5AE
{
public:
	Rva0059E5AE(EmitVtableTag *);
public:
	virtual ~Rva0059E5AE();
};

// ?<Rva0059E5AE::Rva0059E5AE> absent-from-retail
Rva0059E5AE::Rva0059E5AE(EmitVtableTag *)
{
}

class Rva0059EA42
{
public:
	Rva0059EA42(EmitVtableTag *);
public:
	virtual ~Rva0059EA42();
};

// ?<Rva0059EA42::Rva0059EA42> absent-from-retail
Rva0059EA42::Rva0059EA42(EmitVtableTag *)
{
}

class Rva005A0009
{
public:
	Rva005A0009(EmitVtableTag *);
public:
	virtual ~Rva005A0009();
};

// ?<Rva005A0009::Rva005A0009> absent-from-retail
Rva005A0009::Rva005A0009(EmitVtableTag *)
{
}

class Rva005AE30A
{
public:
	Rva005AE30A(EmitVtableTag *);
public:
	virtual ~Rva005AE30A();
};

// ?<Rva005AE30A::Rva005AE30A> absent-from-retail
Rva005AE30A::Rva005AE30A(EmitVtableTag *)
{
}

class Rva005AE66B
{
public:
	Rva005AE66B(EmitVtableTag *);
public:
	virtual ~Rva005AE66B();
};

// ?<Rva005AE66B::Rva005AE66B> absent-from-retail
Rva005AE66B::Rva005AE66B(EmitVtableTag *)
{
}

class Rva005B3D94
{
public:
	Rva005B3D94(EmitVtableTag *);
public:
	virtual ~Rva005B3D94();
};

// ?<Rva005B3D94::Rva005B3D94> absent-from-retail
Rva005B3D94::Rva005B3D94(EmitVtableTag *)
{
}

class Rva005B5420
{
public:
	Rva005B5420(EmitVtableTag *);
public:
	virtual ~Rva005B5420();
};

// ?<Rva005B5420::Rva005B5420> absent-from-retail
Rva005B5420::Rva005B5420(EmitVtableTag *)
{
}

class Rva005B5CF4
{
public:
	Rva005B5CF4(EmitVtableTag *);
public:
	virtual ~Rva005B5CF4();
};

// ?<Rva005B5CF4::Rva005B5CF4> absent-from-retail
Rva005B5CF4::Rva005B5CF4(EmitVtableTag *)
{
}

class Rva005BA23A
{
public:
	Rva005BA23A(EmitVtableTag *);
public:
	virtual ~Rva005BA23A();
};

// ?<Rva005BA23A::Rva005BA23A> absent-from-retail
Rva005BA23A::Rva005BA23A(EmitVtableTag *)
{
}

class Rva005BA2CB
{
public:
	Rva005BA2CB(EmitVtableTag *);
public:
	virtual ~Rva005BA2CB();
};

// ?<Rva005BA2CB::Rva005BA2CB> absent-from-retail
Rva005BA2CB::Rva005BA2CB(EmitVtableTag *)
{
}

class Rva005BA593
{
public:
	Rva005BA593(EmitVtableTag *);
public:
	virtual ~Rva005BA593();
};

// ?<Rva005BA593::Rva005BA593> absent-from-retail
Rva005BA593::Rva005BA593(EmitVtableTag *)
{
}

class Rva005C4230
{
public:
	Rva005C4230(EmitVtableTag *);
public:
	virtual ~Rva005C4230();
};

// ?<Rva005C4230::Rva005C4230> absent-from-retail
Rva005C4230::Rva005C4230(EmitVtableTag *)
{
}

class Rva005C47A3
{
public:
	Rva005C47A3(EmitVtableTag *);
public:
	virtual ~Rva005C47A3();
};

// ?<Rva005C47A3::Rva005C47A3> absent-from-retail
Rva005C47A3::Rva005C47A3(EmitVtableTag *)
{
}

class Rva005C48E5
{
public:
	Rva005C48E5(EmitVtableTag *);
public:
	virtual ~Rva005C48E5();
};

// ?<Rva005C48E5::Rva005C48E5> absent-from-retail
Rva005C48E5::Rva005C48E5(EmitVtableTag *)
{
}

class Rva005C4A91
{
public:
	Rva005C4A91(EmitVtableTag *);
public:
	virtual ~Rva005C4A91();
};

// ?<Rva005C4A91::Rva005C4A91> absent-from-retail
Rva005C4A91::Rva005C4A91(EmitVtableTag *)
{
}

class Rva005C6C7B
{
public:
	Rva005C6C7B(EmitVtableTag *);
public:
	virtual ~Rva005C6C7B();
};

// ?<Rva005C6C7B::Rva005C6C7B> absent-from-retail
Rva005C6C7B::Rva005C6C7B(EmitVtableTag *)
{
}

class Rva005C9659
{
public:
	Rva005C9659(EmitVtableTag *);
public:
	virtual ~Rva005C9659();
};

// ?<Rva005C9659::Rva005C9659> absent-from-retail
Rva005C9659::Rva005C9659(EmitVtableTag *)
{
}

class Rva005CC37C
{
public:
	Rva005CC37C(EmitVtableTag *);
public:
	virtual ~Rva005CC37C();
};

// ?<Rva005CC37C::Rva005CC37C> absent-from-retail
Rva005CC37C::Rva005CC37C(EmitVtableTag *)
{
}

class Rva005CC656
{
public:
	Rva005CC656(EmitVtableTag *);
public:
	virtual ~Rva005CC656();
};

// ?<Rva005CC656::Rva005CC656> absent-from-retail
Rva005CC656::Rva005CC656(EmitVtableTag *)
{
}
