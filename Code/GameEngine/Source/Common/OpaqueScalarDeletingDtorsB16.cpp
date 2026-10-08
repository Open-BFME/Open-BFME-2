// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B16: 28-byte wrappers that
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
//   0x005D0A9F  0x005D078B  0x00C75574#0
//   0x005D1007  0x005D0D85  0x00C75590#0
//   0x005D10DD  0x005D10F9  0x00C755AC#0
//   0x005D1319  0x005D12E3  0x00C755B4#0
//   0x005D13A1  0x005D13BD  0x00C755C0#0
//   0x005D1B85  0x005D1ADE  0x00C75694#0
//   0x005D1DAF  0x005D1D38  0x00C75734#0
//   0x005D204F  0x005D2015  0x00C75778#4
//   0x005D2168  0x005D2111  0x00C75790#0
//   0x005D2F62  0x005D2EA8  0x00C75898#3
//   0x005D4E06  0x005D4C61  0x00C75AAC#0
//   0x005DA7D9  0x005DA7F5  0x00C76510#1
//   0x005DB319  0x005DB221  0x00C766B8#0
//   0x005DB7F2  0x005DB681  0x00C76798#0
//   0x005DF160  0x005DCFC9  0x00C76DD4#0
//   0x005E1350  0x005E12D1  0x00C779B4#0
//   0x005E1CDC  0x005E1BD5  0x00C77A60#0
//   0x005E2103  0x005E1FBC  0x00C77A64#0
//   0x005E283B  0x005E278E  0x00C77B28#0
//   0x005E2AF2  0x005E29CD  0x00C77B2C#0

struct EmitVtableTag;

class Rva005D078B
{
public:
	Rva005D078B(EmitVtableTag *);
public:
	virtual ~Rva005D078B();
};

// ?<Rva005D078B::Rva005D078B> absent-from-retail
Rva005D078B::Rva005D078B(EmitVtableTag *)
{
}

class Rva005D0D85
{
public:
	Rva005D0D85(EmitVtableTag *);
public:
	virtual ~Rva005D0D85();
};

// ?<Rva005D0D85::Rva005D0D85> absent-from-retail
Rva005D0D85::Rva005D0D85(EmitVtableTag *)
{
}

class Rva005D10F9
{
public:
	Rva005D10F9(EmitVtableTag *);
public:
	virtual ~Rva005D10F9();
};

// ?<Rva005D10F9::Rva005D10F9> absent-from-retail
Rva005D10F9::Rva005D10F9(EmitVtableTag *)
{
}

class Rva005D12E3
{
public:
	Rva005D12E3(EmitVtableTag *);
public:
	virtual ~Rva005D12E3();
};

// ?<Rva005D12E3::Rva005D12E3> absent-from-retail
Rva005D12E3::Rva005D12E3(EmitVtableTag *)
{
}

class Rva005D13BD
{
public:
	Rva005D13BD(EmitVtableTag *);
public:
	virtual ~Rva005D13BD();
};

// ?<Rva005D13BD::Rva005D13BD> absent-from-retail
Rva005D13BD::Rva005D13BD(EmitVtableTag *)
{
}

class Rva005D1ADE
{
public:
	Rva005D1ADE(EmitVtableTag *);
public:
	virtual ~Rva005D1ADE();
};

// ?<Rva005D1ADE::Rva005D1ADE> absent-from-retail
Rva005D1ADE::Rva005D1ADE(EmitVtableTag *)
{
}

class Rva005D1D38
{
public:
	Rva005D1D38(EmitVtableTag *);
public:
	virtual ~Rva005D1D38();
};

// ?<Rva005D1D38::Rva005D1D38> absent-from-retail
Rva005D1D38::Rva005D1D38(EmitVtableTag *)
{
}

class Rva005D2015
{
public:
	Rva005D2015(EmitVtableTag *);
public:
	virtual ~Rva005D2015();
};

// ?<Rva005D2015::Rva005D2015> absent-from-retail
Rva005D2015::Rva005D2015(EmitVtableTag *)
{
}

class Rva005D2111
{
public:
	Rva005D2111(EmitVtableTag *);
public:
	virtual ~Rva005D2111();
};

// ?<Rva005D2111::Rva005D2111> absent-from-retail
Rva005D2111::Rva005D2111(EmitVtableTag *)
{
}

class Rva005D2EA8
{
public:
	Rva005D2EA8(EmitVtableTag *);
public:
	virtual ~Rva005D2EA8();
};

// ?<Rva005D2EA8::Rva005D2EA8> absent-from-retail
Rva005D2EA8::Rva005D2EA8(EmitVtableTag *)
{
}

class Rva005D4C61
{
public:
	Rva005D4C61(EmitVtableTag *);
public:
	virtual ~Rva005D4C61();
};

// ?<Rva005D4C61::Rva005D4C61> absent-from-retail
Rva005D4C61::Rva005D4C61(EmitVtableTag *)
{
}

class Rva005DA7F5
{
public:
	Rva005DA7F5(EmitVtableTag *);
public:
	virtual ~Rva005DA7F5();
};

// ?<Rva005DA7F5::Rva005DA7F5> absent-from-retail
Rva005DA7F5::Rva005DA7F5(EmitVtableTag *)
{
}

class Rva005DB221
{
public:
	Rva005DB221(EmitVtableTag *);
public:
	virtual ~Rva005DB221();
};

// ?<Rva005DB221::Rva005DB221> absent-from-retail
Rva005DB221::Rva005DB221(EmitVtableTag *)
{
}

class Rva005DB681
{
public:
	Rva005DB681(EmitVtableTag *);
public:
	virtual ~Rva005DB681();
};

// ?<Rva005DB681::Rva005DB681> absent-from-retail
Rva005DB681::Rva005DB681(EmitVtableTag *)
{
}

class Rva005DCFC9
{
public:
	Rva005DCFC9(EmitVtableTag *);
public:
	virtual ~Rva005DCFC9();
};

// ?<Rva005DCFC9::Rva005DCFC9> absent-from-retail
Rva005DCFC9::Rva005DCFC9(EmitVtableTag *)
{
}

class Rva005E12D1
{
public:
	Rva005E12D1(EmitVtableTag *);
public:
	virtual ~Rva005E12D1();
};

// ?<Rva005E12D1::Rva005E12D1> absent-from-retail
Rva005E12D1::Rva005E12D1(EmitVtableTag *)
{
}

class Rva005E1BD5
{
public:
	Rva005E1BD5(EmitVtableTag *);
public:
	virtual ~Rva005E1BD5();
};

// ?<Rva005E1BD5::Rva005E1BD5> absent-from-retail
Rva005E1BD5::Rva005E1BD5(EmitVtableTag *)
{
}

class Rva005E1FBC
{
public:
	Rva005E1FBC(EmitVtableTag *);
public:
	virtual ~Rva005E1FBC();
};

// ?<Rva005E1FBC::Rva005E1FBC> absent-from-retail
Rva005E1FBC::Rva005E1FBC(EmitVtableTag *)
{
}

class Rva005E278E
{
public:
	Rva005E278E(EmitVtableTag *);
public:
	virtual ~Rva005E278E();
};

// ?<Rva005E278E::Rva005E278E> absent-from-retail
Rva005E278E::Rva005E278E(EmitVtableTag *)
{
}

class Rva005E29CD
{
public:
	Rva005E29CD(EmitVtableTag *);
public:
	virtual ~Rva005E29CD();
};

// ?<Rva005E29CD::Rva005E29CD> absent-from-retail
Rva005E29CD::Rva005E29CD(EmitVtableTag *)
{
}

// ??0Rva005D4E22@@QAE@PA_NPAVAsciiString@@@Z, retail 0x005D4E22, 21 bytes.
// The 8-byte string-out binding the army details clip hands to its Apt extern
// handlers (callers 0x005F36E6, 0x005F3756, each with a cleared flag and an
// AsciiString to fill): stores both pointers and clears the flag. A
// constructor: it returns this.
class AsciiString;
class Rva005D4E22
{
public:
	Rva005D4E22(bool *flag, AsciiString *value);
private:
	bool *m_flag;
	AsciiString *m_value;
};
Rva005D4E22::Rva005D4E22(bool *flag, AsciiString *value)
	: m_flag(flag), m_value(value)
{
	*flag = false;
}
