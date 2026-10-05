// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B17: 28-byte wrappers that
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
//   0x005E3677  0x005E362F  0x00C77BD0#0
//   0x005E5A66  0x00576FCE  0x00C6E3E8#0, 0x00C6E620#0, 0x00C6E8A8#0, 0x00C77D90#0
//   0x005E6237  0x005E5FA8  0x00C77DE8#0
//   0x005E67E2  0x005E66A4  0x00C77E04#0
//   0x005E8240  0x005E80FD  0x00C77F54#0
//   0x005E8E64  0x005E8D71  0x00C77F88#0
//   0x005E9279  0x005E91A9  0x00C77FF0#0
//   0x005E9F4D  0x005E9F3F  0x00C780A8#0
//   0x005EA68B  0x005E9F7B  0x00C75374#0, 0x00C77AD8#0, 0x00C781B8#0
//   0x005EA83E  0x005EA85A  0x00C781DC#0
//   0x005EB761  0x005EB753  0x00C7823C#0
//   0x005EE0D8  0x005EE05E  0x00C786A8#0
//   0x005F02C4  0x005F00FB  0x00C78A78#0
//   0x005F1757  0x005F1749  0x00C78EFC#0
//   0x005F41B7  0x005F4179  0x00C79448#0
//   0x005F4ECC  0x005F4EE8  0x00C794E4#0
//   0x005F5678  0x005F566A  0x00C7953C#0
//   0x005F5882  0x005F5819  0x00C79570#0
//   0x005F5C5B  0x005F5BF2  0x00C795B4#0
//   0x005F5F0F  0x005F5EA6  0x00C795F0#0

struct EmitVtableTag;

class Rva005E362F
{
public:
	Rva005E362F(EmitVtableTag *);
public:
	virtual ~Rva005E362F();
};

// ?<Rva005E362F::Rva005E362F> absent-from-retail
Rva005E362F::Rva005E362F(EmitVtableTag *)
{
}

class Rva00576FCE
{
public:
	Rva00576FCE(EmitVtableTag *);
public:
	virtual ~Rva00576FCE();
};

// ?<Rva00576FCE::Rva00576FCE> absent-from-retail
Rva00576FCE::Rva00576FCE(EmitVtableTag *)
{
}

class Rva005E5FA8
{
public:
	Rva005E5FA8(EmitVtableTag *);
public:
	virtual ~Rva005E5FA8();
};

// ?<Rva005E5FA8::Rva005E5FA8> absent-from-retail
Rva005E5FA8::Rva005E5FA8(EmitVtableTag *)
{
}

class Rva005E66A4
{
public:
	Rva005E66A4(EmitVtableTag *);
public:
	virtual ~Rva005E66A4();
};

// ?<Rva005E66A4::Rva005E66A4> absent-from-retail
Rva005E66A4::Rva005E66A4(EmitVtableTag *)
{
}

class Rva005E80FD
{
public:
	Rva005E80FD(EmitVtableTag *);
public:
	virtual ~Rva005E80FD();
};

// ?<Rva005E80FD::Rva005E80FD> absent-from-retail
Rva005E80FD::Rva005E80FD(EmitVtableTag *)
{
}

class Rva005E8D71
{
public:
	Rva005E8D71(EmitVtableTag *);
public:
	virtual ~Rva005E8D71();
};

// ?<Rva005E8D71::Rva005E8D71> absent-from-retail
Rva005E8D71::Rva005E8D71(EmitVtableTag *)
{
}

class Rva005E91A9
{
public:
	Rva005E91A9(EmitVtableTag *);
public:
	virtual ~Rva005E91A9();
};

// ?<Rva005E91A9::Rva005E91A9> absent-from-retail
Rva005E91A9::Rva005E91A9(EmitVtableTag *)
{
}

class Rva005E9F3F
{
public:
	Rva005E9F3F(EmitVtableTag *);
public:
	virtual ~Rva005E9F3F();
};

// ?<Rva005E9F3F::Rva005E9F3F> absent-from-retail
Rva005E9F3F::Rva005E9F3F(EmitVtableTag *)
{
}

class Rva005E9F7B
{
public:
	Rva005E9F7B(EmitVtableTag *);
public:
	virtual ~Rva005E9F7B();
};

// ?<Rva005E9F7B::Rva005E9F7B> absent-from-retail
Rva005E9F7B::Rva005E9F7B(EmitVtableTag *)
{
}

class Rva005EA85A
{
public:
	Rva005EA85A(EmitVtableTag *);
public:
	virtual ~Rva005EA85A();
};

// ?<Rva005EA85A::Rva005EA85A> absent-from-retail
Rva005EA85A::Rva005EA85A(EmitVtableTag *)
{
}

class Rva005EB753
{
public:
	Rva005EB753(EmitVtableTag *);
public:
	virtual ~Rva005EB753();
};

// ?<Rva005EB753::Rva005EB753> absent-from-retail
Rva005EB753::Rva005EB753(EmitVtableTag *)
{
}

class Rva005EE05E
{
public:
	Rva005EE05E(EmitVtableTag *);
public:
	virtual ~Rva005EE05E();
};

// ?<Rva005EE05E::Rva005EE05E> absent-from-retail
Rva005EE05E::Rva005EE05E(EmitVtableTag *)
{
}

class Rva005F00FB
{
public:
	Rva005F00FB(EmitVtableTag *);
public:
	virtual ~Rva005F00FB();
};

// ?<Rva005F00FB::Rva005F00FB> absent-from-retail
Rva005F00FB::Rva005F00FB(EmitVtableTag *)
{
}

class Rva005F1749
{
public:
	Rva005F1749(EmitVtableTag *);
public:
	virtual ~Rva005F1749();
};

// ?<Rva005F1749::Rva005F1749> absent-from-retail
Rva005F1749::Rva005F1749(EmitVtableTag *)
{
}

class Rva005F4179
{
public:
	Rva005F4179(EmitVtableTag *);
public:
	virtual ~Rva005F4179();
};

// ?<Rva005F4179::Rva005F4179> absent-from-retail
Rva005F4179::Rva005F4179(EmitVtableTag *)
{
}

class Rva005F4EE8
{
public:
	Rva005F4EE8(EmitVtableTag *);
public:
	virtual ~Rva005F4EE8();
};

// ?<Rva005F4EE8::Rva005F4EE8> absent-from-retail
Rva005F4EE8::Rva005F4EE8(EmitVtableTag *)
{
}

class Rva005F566A
{
public:
	Rva005F566A(EmitVtableTag *);
public:
	virtual ~Rva005F566A();
};

// ?<Rva005F566A::Rva005F566A> absent-from-retail
Rva005F566A::Rva005F566A(EmitVtableTag *)
{
}

class Rva005F5819
{
public:
	Rva005F5819(EmitVtableTag *);
public:
	virtual ~Rva005F5819();
};

// ?<Rva005F5819::Rva005F5819> absent-from-retail
Rva005F5819::Rva005F5819(EmitVtableTag *)
{
}

class Rva005F5BF2
{
public:
	Rva005F5BF2(EmitVtableTag *);
public:
	virtual ~Rva005F5BF2();
};

// ?<Rva005F5BF2::Rva005F5BF2> absent-from-retail
Rva005F5BF2::Rva005F5BF2(EmitVtableTag *)
{
}

class Rva005F5EA6
{
public:
	Rva005F5EA6(EmitVtableTag *);
public:
	virtual ~Rva005F5EA6();
};

// ?<Rva005F5EA6::Rva005F5EA6> absent-from-retail
Rva005F5EA6::Rva005F5EA6(EmitVtableTag *)
{
}
