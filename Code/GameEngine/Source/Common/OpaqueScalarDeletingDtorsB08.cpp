// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B08: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x0008FFC4  0x000A43C8  0x00BC7DC8#0
//   0x001F45C3  0x000E14BD  0x00BC6F2C#0
//   0x000411A0  0x000411BC  0x00BC16C4#2
//   0x00072FC5  0x00072FE1  0x00BC6568#1
//   0x000416CB  0x000416E7  0x00BC2420#0
//   0x000657E6  0x006109C0  0x00BC5C6C#0
//   0x0006F1DD  0x0006F1F9  0x00BC6244#1
//   0x00079111  0x000D089D  0x00BC6870#0
//   0x000AB0B8  0x000AB0D4  0x00BC9468#0
//   0x00256B78  0x00256B94  0x00BF3E30#0

struct EmitVtableTag;

class Rva000A43C8
{
public:
	Rva000A43C8(EmitVtableTag *);
public:
	virtual ~Rva000A43C8();
};

// ?<Rva000A43C8::Rva000A43C8> absent-from-retail
Rva000A43C8::Rva000A43C8(EmitVtableTag *)
{
}

class Rva000E14BD
{
public:
	Rva000E14BD(EmitVtableTag *);
public:
	virtual ~Rva000E14BD();
};

// ?<Rva000E14BD::Rva000E14BD> absent-from-retail
Rva000E14BD::Rva000E14BD(EmitVtableTag *)
{
}

class Rva000411BC
{
public:
	Rva000411BC(EmitVtableTag *);
public:
	virtual ~Rva000411BC();
};

// ?<Rva000411BC::Rva000411BC> absent-from-retail
Rva000411BC::Rva000411BC(EmitVtableTag *)
{
}

class Rva00072FE1
{
public:
	Rva00072FE1(EmitVtableTag *);
public:
	virtual ~Rva00072FE1();
};

// ?<Rva00072FE1::Rva00072FE1> absent-from-retail
Rva00072FE1::Rva00072FE1(EmitVtableTag *)
{
}

class Rva000416E7
{
public:
	Rva000416E7(EmitVtableTag *);
public:
	virtual ~Rva000416E7();
};

// ?<Rva000416E7::Rva000416E7> absent-from-retail
Rva000416E7::Rva000416E7(EmitVtableTag *)
{
}

class Rva006109C0
{
public:
	Rva006109C0(EmitVtableTag *);
public:
	virtual ~Rva006109C0();
};

// ?<Rva006109C0::Rva006109C0> absent-from-retail
Rva006109C0::Rva006109C0(EmitVtableTag *)
{
}

class W3DShroudMaterialPassClass
{
public:
	W3DShroudMaterialPassClass(EmitVtableTag *);
public:
	virtual ~W3DShroudMaterialPassClass();
};

// ?<W3DShroudMaterialPassClass::W3DShroudMaterialPassClass> absent-from-retail
W3DShroudMaterialPassClass::W3DShroudMaterialPassClass(EmitVtableTag *)
{
}

class Rva000D089D
{
public:
	Rva000D089D(EmitVtableTag *);
public:
	virtual ~Rva000D089D();
};

// ?<Rva000D089D::Rva000D089D> absent-from-retail
Rva000D089D::Rva000D089D(EmitVtableTag *)
{
}

class Rva000AB0D4
{
public:
	Rva000AB0D4(EmitVtableTag *);
public:
	virtual ~Rva000AB0D4();
};

// ?<Rva000AB0D4::Rva000AB0D4> absent-from-retail
Rva000AB0D4::Rva000AB0D4(EmitVtableTag *)
{
}

class Rva00256B94
{
public:
	Rva00256B94(EmitVtableTag *);
public:
	virtual ~Rva00256B94();
};

// ?<Rva00256B94::Rva00256B94> absent-from-retail
Rva00256B94::Rva00256B94(EmitVtableTag *)
{
}
