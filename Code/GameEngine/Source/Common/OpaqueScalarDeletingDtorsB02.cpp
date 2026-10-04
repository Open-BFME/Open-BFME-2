// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B02: 28-byte wrappers that
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
//   0x003AD257  0x003AD273  0x00C1CC28#0
//   0x003AD42F  0x003AD2AE  0x00C1D00C#0
//   0x003AD3F7  0x003ACB6F  0x00C1C578#0
//   0x003AE270  0x003ADFB2  0x00C1D31C#0
//   0x0010EFF0  0x0010F00C  0x00BCFA64#0
//   0x001E0A3B  0x001E009E  0x00BDD754#0
//   0x003AEFF6  0x003ABC0B  0x00C1D654#0
//   0x000EF981  0x002DB8BA  0x00BCEEF0#9
//   0x00254B56  0x004C70A8  0x00C5CA44#0
//   0x003AD413  0x003ACB74  0x00C1CF18#0
//   0x003AEF18  0x003A972D  0x00C1D5E8#0
//   0x001042CF  0x00740555  0x00BC8900#1
//   0x002549A5  0x004851A8  0x00C5956C#0
//   0x003FDC25  0x003FDC41  0x00C37C68#0
//   0x001A47BC  0x001A47D8  0x00BD6CD0#1
//   0x001F03ED  0x001F0409  0x00BE09E8#0
//   0x003ACEBA  0x003ACED6  0x00C1CD14#0
//   0x003ACEDB  0x003ACEF7  0x00C1C4C8#0
//   0x003AF10B  0x003ABC21  0x00C1D708#0
//   0x003F4261  0x005FED52  0x00C37064#1
//   0x000EFAD2  0x00108B4D  0x00BCEFA0#0
//   0x00108D17  0x00108650  0x00BCF9AC#0
//   0x0010EFD4  0x0010EFCD  0x00BCFAA4#0
//   0x0013218B  0x00131D07  0x00BD2630#9
//   0x00135F19  0x00135E35  0x00BD28F0#9

struct EmitVtableTag;

class Rva003AD273Base0
{
public:
	virtual ~Rva003AD273Base0();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) in its vtable is target evidence for it.
class Rva003AD273Base18
{
public:
	virtual ~Rva003AD273Base18();
};
class Rva003AD273 : public Rva003AD273Base0, public Rva003AD273Base18
{
public:
	Rva003AD273(EmitVtableTag *);
public:
	virtual ~Rva003AD273();
};

// ?<Rva003AD273::Rva003AD273> absent-from-retail
Rva003AD273::Rva003AD273(EmitVtableTag *)
{
}

class Rva003AD2AEBase0
{
public:
	virtual ~Rva003AD2AEBase0();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

// Secondary base at +0x1C: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x1C) in its vtable is target evidence for it.
class Rva003AD2AEBase1C
{
public:
	virtual ~Rva003AD2AEBase1C();
};
class Rva003AD2AE : public Rva003AD2AEBase0, public Rva003AD2AEBase1C
{
public:
	Rva003AD2AE(EmitVtableTag *);
public:
	virtual ~Rva003AD2AE();
};

// ?<Rva003AD2AE::Rva003AD2AE> absent-from-retail
Rva003AD2AE::Rva003AD2AE(EmitVtableTag *)
{
}

class Rva003ACB6FBase0
{
public:
	virtual ~Rva003ACB6FBase0();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

// Secondary base at +0x1C: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x1C) in its vtable is target evidence for it.
class Rva003ACB6FBase1C
{
public:
	virtual ~Rva003ACB6FBase1C();
};
class Rva003ACB6F : public Rva003ACB6FBase0, public Rva003ACB6FBase1C
{
public:
	Rva003ACB6F(EmitVtableTag *);
public:
	virtual ~Rva003ACB6F();
};

// ?<Rva003ACB6F::Rva003ACB6F> absent-from-retail
Rva003ACB6F::Rva003ACB6F(EmitVtableTag *)
{
}

class Rva003ADFB2Base0
{
public:
	virtual ~Rva003ADFB2Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class Rva003ADFB2BaseC
{
public:
	virtual ~Rva003ADFB2BaseC();
};
class Rva003ADFB2 : public Rva003ADFB2Base0, public Rva003ADFB2BaseC
{
public:
	Rva003ADFB2(EmitVtableTag *);
public:
	virtual ~Rva003ADFB2();
};

// ?<Rva003ADFB2::Rva003ADFB2> absent-from-retail
Rva003ADFB2::Rva003ADFB2(EmitVtableTag *)
{
}

class Rva0010F00C
{
public:
	Rva0010F00C(EmitVtableTag *);
public:
	virtual ~Rva0010F00C();
};

// ?<Rva0010F00C::Rva0010F00C> absent-from-retail
Rva0010F00C::Rva0010F00C(EmitVtableTag *)
{
}

class Rva001E009E
{
public:
	Rva001E009E(EmitVtableTag *);
public:
	virtual ~Rva001E009E();
};

// ?<Rva001E009E::Rva001E009E> absent-from-retail
Rva001E009E::Rva001E009E(EmitVtableTag *)
{
}

class Rva003ABC0BBase0
{
public:
	virtual ~Rva003ABC0BBase0();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

// Secondary base at +0x1C: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x1C) in its vtable is target evidence for it.
class Rva003ABC0BBase1C
{
public:
	virtual ~Rva003ABC0BBase1C();
};
class Rva003ABC0B : public Rva003ABC0BBase0, public Rva003ABC0BBase1C
{
public:
	Rva003ABC0B(EmitVtableTag *);
public:
	virtual ~Rva003ABC0B();
};

// ?<Rva003ABC0B::Rva003ABC0B> absent-from-retail
Rva003ABC0B::Rva003ABC0B(EmitVtableTag *)
{
}

class Rva002DB8BA
{
public:
	Rva002DB8BA(EmitVtableTag *);
public:
	virtual ~Rva002DB8BA();
};

// ?<Rva002DB8BA::Rva002DB8BA> absent-from-retail
Rva002DB8BA::Rva002DB8BA(EmitVtableTag *)
{
}

class Rva004C70A8
{
public:
	Rva004C70A8(EmitVtableTag *);
public:
	virtual ~Rva004C70A8();
};

// ?<Rva004C70A8::Rva004C70A8> absent-from-retail
Rva004C70A8::Rva004C70A8(EmitVtableTag *)
{
}

class Rva003ACB74Base0
{
public:
	virtual ~Rva003ACB74Base0();
private:
	char m_unmodelled_04[0x20 - 0x04];
};

// Secondary base at +0x20: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x20) in its vtable is target evidence for it.
class Rva003ACB74Base20
{
public:
	virtual ~Rva003ACB74Base20();
};
class Rva003ACB74 : public Rva003ACB74Base0, public Rva003ACB74Base20
{
public:
	Rva003ACB74(EmitVtableTag *);
public:
	virtual ~Rva003ACB74();
};

// ?<Rva003ACB74::Rva003ACB74> absent-from-retail
Rva003ACB74::Rva003ACB74(EmitVtableTag *)
{
}

class Rva003A972D
{
public:
	Rva003A972D(EmitVtableTag *);
public:
	virtual ~Rva003A972D();
};

// ?<Rva003A972D::Rva003A972D> absent-from-retail
Rva003A972D::Rva003A972D(EmitVtableTag *)
{
}

class Rva00740555
{
public:
	Rva00740555(EmitVtableTag *);
public:
	virtual ~Rva00740555();
};

// ?<Rva00740555::Rva00740555> absent-from-retail
Rva00740555::Rva00740555(EmitVtableTag *)
{
}

class Rva004851A8
{
public:
	Rva004851A8(EmitVtableTag *);
public:
	virtual ~Rva004851A8();
};

// ?<Rva004851A8::Rva004851A8> absent-from-retail
Rva004851A8::Rva004851A8(EmitVtableTag *)
{
}

class Rva003FDC41
{
public:
	Rva003FDC41(EmitVtableTag *);
public:
	virtual ~Rva003FDC41();
};

// ?<Rva003FDC41::Rva003FDC41> absent-from-retail
Rva003FDC41::Rva003FDC41(EmitVtableTag *)
{
}

class Rva001A47D8
{
public:
	Rva001A47D8(EmitVtableTag *);
public:
	virtual ~Rva001A47D8();
};

// ?<Rva001A47D8::Rva001A47D8> absent-from-retail
Rva001A47D8::Rva001A47D8(EmitVtableTag *)
{
}

class Rva001F0409
{
public:
	Rva001F0409(EmitVtableTag *);
public:
	virtual ~Rva001F0409();
};

// ?<Rva001F0409::Rva001F0409> absent-from-retail
Rva001F0409::Rva001F0409(EmitVtableTag *)
{
}

class Rva003ACED6Base0
{
public:
	virtual ~Rva003ACED6Base0();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) in its vtable is target evidence for it.
class Rva003ACED6Base18
{
public:
	virtual ~Rva003ACED6Base18();
};
class Rva003ACED6 : public Rva003ACED6Base0, public Rva003ACED6Base18
{
public:
	Rva003ACED6(EmitVtableTag *);
public:
	virtual ~Rva003ACED6();
};

// ?<Rva003ACED6::Rva003ACED6> absent-from-retail
Rva003ACED6::Rva003ACED6(EmitVtableTag *)
{
}

class Rva003ACEF7Base0
{
public:
	virtual ~Rva003ACEF7Base0();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) in its vtable is target evidence for it.
class Rva003ACEF7Base18
{
public:
	virtual ~Rva003ACEF7Base18();
};
class Rva003ACEF7 : public Rva003ACEF7Base0, public Rva003ACEF7Base18
{
public:
	Rva003ACEF7(EmitVtableTag *);
public:
	virtual ~Rva003ACEF7();
};

// ?<Rva003ACEF7::Rva003ACEF7> absent-from-retail
Rva003ACEF7::Rva003ACEF7(EmitVtableTag *)
{
}

class Rva003ABC21Base0
{
public:
	virtual ~Rva003ABC21Base0();
private:
	char m_unmodelled_04[0x20 - 0x04];
};

// Secondary base at +0x20: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x20) in its vtable is target evidence for it.
class Rva003ABC21Base20
{
public:
	virtual ~Rva003ABC21Base20();
};
class Rva003ABC21 : public Rva003ABC21Base0, public Rva003ABC21Base20
{
public:
	Rva003ABC21(EmitVtableTag *);
public:
	virtual ~Rva003ABC21();
};

// ?<Rva003ABC21::Rva003ABC21> absent-from-retail
Rva003ABC21::Rva003ABC21(EmitVtableTag *)
{
}

class Rva005FED52
{
public:
	Rva005FED52(EmitVtableTag *);
public:
	virtual ~Rva005FED52();
};

// ?<Rva005FED52::Rva005FED52> absent-from-retail
Rva005FED52::Rva005FED52(EmitVtableTag *)
{
}

class Rva00108B4D
{
public:
	Rva00108B4D(EmitVtableTag *);
public:
	virtual ~Rva00108B4D();
};

// ?<Rva00108B4D::Rva00108B4D> absent-from-retail
Rva00108B4D::Rva00108B4D(EmitVtableTag *)
{
}

class Rva00108650
{
public:
	Rva00108650(EmitVtableTag *);
public:
	virtual ~Rva00108650();
};

// ?<Rva00108650::Rva00108650> absent-from-retail
Rva00108650::Rva00108650(EmitVtableTag *)
{
}

class Rva0010EFCD
{
public:
	Rva0010EFCD(EmitVtableTag *);
public:
	virtual ~Rva0010EFCD();
};

// ?<Rva0010EFCD::Rva0010EFCD> absent-from-retail
Rva0010EFCD::Rva0010EFCD(EmitVtableTag *)
{
}

class Rva00131D07
{
public:
	Rva00131D07(EmitVtableTag *);
public:
	virtual ~Rva00131D07();
};

// ?<Rva00131D07::Rva00131D07> absent-from-retail
Rva00131D07::Rva00131D07(EmitVtableTag *)
{
}

class Rva00135E35
{
public:
	Rva00135E35(EmitVtableTag *);
public:
	virtual ~Rva00135E35();
};

// ?<Rva00135E35::Rva00135E35> absent-from-retail
Rva00135E35::Rva00135E35(EmitVtableTag *)
{
}
