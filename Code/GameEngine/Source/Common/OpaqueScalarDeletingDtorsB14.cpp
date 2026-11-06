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
// beyond the thunk-proven secondary bases noted where they are declared
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x0059E736  0x0059E5AE  0x00C71094#0
//   0x0059EAA3  0x0059EA42  0x00C71138#0
//   0x005A0B62  0x005A0009  0x00C71414#0
//   0x005AE38A  0x005AE30A  0x00C726A0#0
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

class Rva0059E920
{
public:
	Rva0059E920(EmitVtableTag *);
public:
	virtual ~Rva0059E920();
};

// ?<Rva0059E920::Rva0059E920> absent-from-retail
Rva0059E920::Rva0059E920(EmitVtableTag *)
{
}

// Novtable bases at +0x60 and +0x6C: their tables (0x00C713B8, 0x00C713AC) hold the
// this-adjusting deleting-destructor thunks 0x005A00D6 (sub ecx, 0x60; slot 0)
// and 0x005A00DE (sub ecx, 0x6C; slot 2), target evidence for both; the
// derived Rva005BA23A and Rva005BA2CB tables repeat that shape.
class __declspec(novtable) Rva005A0009Base0 { public: virtual ~Rva005A0009Base0(); private: char m_unmodelled04[0x60 - 0x04]; };
class __declspec(novtable) Rva005A0009Base60 { public: virtual ~Rva005A0009Base60(); private: char m_unmodelled64[0x6C - 0x64]; };
class __declspec(novtable) Rva005A0009Base6C { public: virtual void slot0(); virtual void slot1(); virtual ~Rva005A0009Base6C(); };
class Rva005A0009 : public Rva005A0009Base0, public Rva005A0009Base60, public Rva005A0009Base6C
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

class Rva005BA23A : public Rva005A0009
{
public:
	Rva005BA23A(EmitVtableTag *);
public:
	virtual ~Rva005BA23A();
};

// ?<Rva005BA23A::Rva005BA23A> absent-from-retail
Rva005BA23A::Rva005BA23A(EmitVtableTag *tag)
	: Rva005A0009(tag)
{
}

class Rva005BA2CB : public Rva005A0009
{
public:
	Rva005BA2CB(EmitVtableTag *);
public:
	virtual ~Rva005BA2CB();
};

// ?<Rva005BA2CB::Rva005BA2CB> absent-from-retail
Rva005BA2CB::Rva005BA2CB(EmitVtableTag *tag)
	: Rva005A0009(tag)
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

// Rva005CC37C's two tables (data ledger): Rva005CC37CBase at +0 (vptr plus one word) and
// Rva005CC37CHolder at +0x8, whose slot 0 is a this-adjusting (sub ecx, 8)
// deleting-destructor thunk -- target evidence for that base and offset.
class Rva005CC37CBase { public: virtual ~Rva005CC37CBase() {} private: char m_unmodelled04[4]; };
class __declspec(novtable) Rva005CC37CHolder { public: virtual ~Rva005CC37CHolder(); };
class Rva005CC37C : public Rva005CC37CBase, public Rva005CC37CHolder
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

// Complete destructors the deleting destructors above call, by retail target: 0x0059E5AE,
// 0x005B3D94 (AptCreateAHero::Powers); slots 0 and 1 of the +0x6C table 0x00C713AC are both the
// rowed 11-byte stub 0x0059EF57.
#pragma comment(linker, "/alternatename:??1Rva0059E5AE@@UAE@XZ=??1Rva0059E6D3Data@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva005B3D94@@UAE@XZ=??1Powers@AptCreateAHero@@UAE@XZ")
#pragma comment(linker, "/alternatename:?slot0@Rva005A0009Base6C@@UAEXXZ=?rva0059EF57@Rva0059EF57@@QAEXHHH@Z")
#pragma comment(linker, "/alternatename:?slot1@Rva005A0009Base6C@@UAEXXZ=?rva0059EF57@Rva0059EF57@@QAEXHHH@Z")
