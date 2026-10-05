// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B15: 28-byte wrappers that
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
//   0x005CC65B  0x005CC677  0x00C74E8C#0
//   0x005CCF2B  0x005CCDDD  0x00C74F44#0
//   0x005CDB43  0x005CDA3D  0x00C75038#0
//   0x005CDF2D  0x005CDDA4  0x00C750BC#0
//   0x005CE7A3  0x005CE4FA  0x00C75158#0
//   0x005CE8C0  0x005CE874  0x00C75184#0
//   0x005CF062  0x005CEE07  0x00C75214#0
//   0x005CF1F4  0x005CEE9F  0x00C7522C#0
//   0x005CF210  0x005CEF2F  0x00C7523C#0
//   0x005CF7FA  0x005CF7BF  0x00C75254#0
//   0x005CFCB5  0x005CF8E3  0x00C75298#0
//   0x005CFD8A  0x005CFDA6  0x00C752C4#0
//   0x005CFDDC  0x005CF9FF  0x00C752CC#0
//   0x005CFDF8  0x005CFA43  0x00C752D4#0
//   0x005CFE14  0x005CFA87  0x00C752DC#0
//   0x005CFEC3  0x005CFEDF  0x00C752E4#0
//   0x005CFF9C  0x005CFFB8  0x00C752EC#0
//   0x005D08E1  0x005D0643  0x00C75538#0
//   0x005D0A67  0x005D06CB  0x00C75554#0
//   0x005D0A83  0x005D073A  0x00C75568#0

struct EmitVtableTag;

class Rva005CC677
{
public:
	Rva005CC677(EmitVtableTag *);
public:
	virtual ~Rva005CC677();
};

// ?<Rva005CC677::Rva005CC677> absent-from-retail
Rva005CC677::Rva005CC677(EmitVtableTag *)
{
}

class Rva005CCDDD
{
public:
	Rva005CCDDD(EmitVtableTag *);
public:
	virtual ~Rva005CCDDD();
};

// ?<Rva005CCDDD::Rva005CCDDD> absent-from-retail
Rva005CCDDD::Rva005CCDDD(EmitVtableTag *)
{
}

class Rva005CDA3D
{
public:
	Rva005CDA3D(EmitVtableTag *);
public:
	virtual ~Rva005CDA3D();
};

// ?<Rva005CDA3D::Rva005CDA3D> absent-from-retail
Rva005CDA3D::Rva005CDA3D(EmitVtableTag *)
{
}

class Rva005CDDA4
{
public:
	Rva005CDDA4(EmitVtableTag *);
public:
	virtual ~Rva005CDDA4();
};

// ?<Rva005CDDA4::Rva005CDDA4> absent-from-retail
Rva005CDDA4::Rva005CDDA4(EmitVtableTag *)
{
}

class Rva005CE4FA
{
public:
	Rva005CE4FA(EmitVtableTag *);
public:
	virtual ~Rva005CE4FA();
};

// ?<Rva005CE4FA::Rva005CE4FA> absent-from-retail
Rva005CE4FA::Rva005CE4FA(EmitVtableTag *)
{
}

class Rva005CE874
{
public:
	Rva005CE874(EmitVtableTag *);
public:
	virtual ~Rva005CE874();
};

// ?<Rva005CE874::Rva005CE874> absent-from-retail
Rva005CE874::Rva005CE874(EmitVtableTag *)
{
}

class Rva005CEE07
{
public:
	Rva005CEE07(EmitVtableTag *);
public:
	virtual ~Rva005CEE07();
};

// ?<Rva005CEE07::Rva005CEE07> absent-from-retail
Rva005CEE07::Rva005CEE07(EmitVtableTag *)
{
}

class Rva005CEE9F
{
public:
	Rva005CEE9F(EmitVtableTag *);
public:
	virtual ~Rva005CEE9F();
};

// ?<Rva005CEE9F::Rva005CEE9F> absent-from-retail
Rva005CEE9F::Rva005CEE9F(EmitVtableTag *)
{
}

class Rva005CEF2F
{
public:
	Rva005CEF2F(EmitVtableTag *);
public:
	virtual ~Rva005CEF2F();
};

// ?<Rva005CEF2F::Rva005CEF2F> absent-from-retail
Rva005CEF2F::Rva005CEF2F(EmitVtableTag *)
{
}

class Rva005CF7BF
{
public:
	Rva005CF7BF(EmitVtableTag *);
public:
	virtual ~Rva005CF7BF();
};

// ?<Rva005CF7BF::Rva005CF7BF> absent-from-retail
Rva005CF7BF::Rva005CF7BF(EmitVtableTag *)
{
}

class Rva005CF8E3
{
public:
	Rva005CF8E3(EmitVtableTag *);
public:
	virtual ~Rva005CF8E3();
};

// ?<Rva005CF8E3::Rva005CF8E3> absent-from-retail
Rva005CF8E3::Rva005CF8E3(EmitVtableTag *)
{
}

class Rva005CFDA6
{
public:
	Rva005CFDA6(EmitVtableTag *);
public:
	virtual ~Rva005CFDA6();
};

// ?<Rva005CFDA6::Rva005CFDA6> absent-from-retail
Rva005CFDA6::Rva005CFDA6(EmitVtableTag *)
{
}

class Rva005CF9FF
{
public:
	Rva005CF9FF(EmitVtableTag *);
public:
	virtual ~Rva005CF9FF();
};

// ?<Rva005CF9FF::Rva005CF9FF> absent-from-retail
Rva005CF9FF::Rva005CF9FF(EmitVtableTag *)
{
}

class Rva005CFA43
{
public:
	Rva005CFA43(EmitVtableTag *);
public:
	virtual ~Rva005CFA43();
};

// ?<Rva005CFA43::Rva005CFA43> absent-from-retail
Rva005CFA43::Rva005CFA43(EmitVtableTag *)
{
}

class Rva005CFA87
{
public:
	Rva005CFA87(EmitVtableTag *);
public:
	virtual ~Rva005CFA87();
};

// ?<Rva005CFA87::Rva005CFA87> absent-from-retail
Rva005CFA87::Rva005CFA87(EmitVtableTag *)
{
}

class Rva005CFEDF
{
public:
	Rva005CFEDF(EmitVtableTag *);
public:
	virtual ~Rva005CFEDF();
};

// ?<Rva005CFEDF::Rva005CFEDF> absent-from-retail
Rva005CFEDF::Rva005CFEDF(EmitVtableTag *)
{
}

class Rva005CFFB8
{
public:
	Rva005CFFB8(EmitVtableTag *);
public:
	virtual ~Rva005CFFB8();
};

// ?<Rva005CFFB8::Rva005CFFB8> absent-from-retail
Rva005CFFB8::Rva005CFFB8(EmitVtableTag *)
{
}

class Rva005D0643
{
public:
	Rva005D0643(EmitVtableTag *);
public:
	virtual ~Rva005D0643();
};

// ?<Rva005D0643::Rva005D0643> absent-from-retail
Rva005D0643::Rva005D0643(EmitVtableTag *)
{
}

class Rva005D06CB
{
public:
	Rva005D06CB(EmitVtableTag *);
public:
	virtual ~Rva005D06CB();
};

// ?<Rva005D06CB::Rva005D06CB> absent-from-retail
Rva005D06CB::Rva005D06CB(EmitVtableTag *)
{
}

class Rva005D073A
{
public:
	Rva005D073A(EmitVtableTag *);
public:
	virtual ~Rva005D073A();
};

// ?<Rva005D073A::Rva005D073A> absent-from-retail
Rva005D073A::Rva005D073A(EmitVtableTag *)
{
}
