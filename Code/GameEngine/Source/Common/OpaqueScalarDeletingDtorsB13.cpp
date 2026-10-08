// cl: /O1 /DNDEBUG /MD /EHs
//
// Opaque scalar deleting destructors, batch B13: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Other owner identities are not recovered. The address-derived
// Rva0057682F view below records only the layout inferred from its target
// constructor, vtable, and destructor thunk; its original class identity and
// field types remain unknown.
//
//   wrapper     dtor        vtable#slot
//   0x00574E4E  0x00574C1B  0x00C6E4A4#0
//   0x00574E86  0x00574CC1  0x00C6E528#1
//   0x0057569A  0x005CD3A5  0x00C6E5F0#0, 0x00C74F68#0, 0x00C74F84#0, 0x00C74FA0#0, 0x00C74FBC#0, 0x00C74FD8#0
//   0x00575E32  0x00575D45  0x00C6E664#0
//   0x005760E9  0x00575F38  0x00C6E720#1
//   0x005767A4  0x005764F9  0x00C6E78C#0
//   0x005767C0  0x00576591  0x00C6E798#0
//   0x005767E7  0x00576803  0x00C6E7A4#0
//   0x00576813  0x0057682F  0x00C6E7B0#0
//   0x00576BC1  0x00576B5E  0x00C6E7D4#0
//   0x00577073  0x00576F48  0x00C6E858#4
//   0x005770D6  0x005770F2  0x00C6E884#0
//   0x00577356  0x005770F7  0x00C6E8F8#1
//   0x00577372  0x005772BF  0x00C6E960#0
//   0x00577891  0x00577838  0x00C6E978#0
//   0x00578409  0x00578189  0x00C6EA80#0
//   0x00583092  0x00582FC1  0x00C6FA9C#0
//   0x00597FA9  0x00597BD4  0x00C70C24#2
//   0x005993B1  0x005990DF  0x00C70D44#2
//   0x0059E28F  0x0059E242  0x00C70F88#0

struct EmitVtableTag;

class Rva00574C1B
{
public:
	Rva00574C1B(EmitVtableTag *);
public:
	virtual ~Rva00574C1B();
};

// ?<Rva00574C1B::Rva00574C1B> absent-from-retail
Rva00574C1B::Rva00574C1B(EmitVtableTag *)
{
}

class Rva00574CC1
{
public:
	Rva00574CC1(EmitVtableTag *);
public:
	virtual ~Rva00574CC1();
};

// ?<Rva00574CC1::Rva00574CC1> absent-from-retail
Rva00574CC1::Rva00574CC1(EmitVtableTag *)
{
}

class Rva005CCDDD
{
public:
	Rva005CCDDD();
	virtual ~Rva005CCDDD();
private:
	char m_pad[4];
	void *m_member08;
};

class UnicodeString;
class Rva005CCE13
{
public:
	void rva005CCE13(const UnicodeString &arg);
};
class Rva005CCB73
{
public:
	void rva005CCB73(void *arg);
};

class Rva005CD3A5 : public Rva005CCDDD
{
public:
	Rva005CD3A5(EmitVtableTag *);
	Rva005CD3A5(const UnicodeString &arg0, void *arg1);
public:
	virtual ~Rva005CD3A5();
};

// ?<Rva005CD3A5::Rva005CD3A5> absent-from-retail
Rva005CD3A5::Rva005CD3A5(EmitVtableTag *)
{
}

// Target evidence: constructor 0x00575406 installs the vtable also used by
// deleting dtor 0x0057569A, calls the base constructor at 0x005CCD94 (whose
// vtable is 0x00C74F44), forwards a UnicodeString reference through the
// already-rowed 0x005CCE13 thunk, then forwards an opaque pointer through
// 0x005CCB73. The base relationship is a structural inference from those
// vtable stores and call order; the class identity and pointer meaning remain
// unknown.
Rva005CD3A5::Rva005CD3A5(const UnicodeString &arg0, void *arg1)
	: Rva005CCDDD()
{
	((Rva005CCE13 *)this)->rva005CCE13(arg0);
	((Rva005CCB73 *)this)->rva005CCB73(arg1);
}

class Rva00575D45
{
public:
	Rva00575D45(EmitVtableTag *);
public:
	virtual ~Rva00575D45();
};

// ?<Rva00575D45::Rva00575D45> absent-from-retail
Rva00575D45::Rva00575D45(EmitVtableTag *)
{
}

class Rva00575F38
{
public:
	Rva00575F38(EmitVtableTag *);
public:
	virtual ~Rva00575F38();
};

// ?<Rva00575F38::Rva00575F38> absent-from-retail
Rva00575F38::Rva00575F38(EmitVtableTag *)
{
}

class Rva005764F9
{
public:
	Rva005764F9(EmitVtableTag *);
public:
	virtual ~Rva005764F9();
};

// ?<Rva005764F9::Rva005764F9> absent-from-retail
Rva005764F9::Rva005764F9(EmitVtableTag *)
{
}

class Rva005D12E3
{
public:
	Rva005D12E3();
	virtual ~Rva005D12E3();

private:
	void *m_holder;
};
class Rva005CD5FA
{
public:
	void rva005CD5FA(unsigned char value);
};

class Rva00576591 : public Rva005D12E3
{
public:
	Rva00576591(EmitVtableTag *);
	Rva00576591(void *owner);
public:
	virtual ~Rva00576591();

private:
	void *m_owner;
};

// ?<Rva00576591::Rva00576591> absent-from-retail
Rva00576591::Rva00576591(EmitVtableTag *)
{
}

// 0x00576550: constructor overload of the class whose dtor at 0x00576591
// shares vtable 0x00C6E798. The direct base ctor and paired base dtor use
// 0x00C755B4; target bytes store the argument at +8 and notify 0x005CD5FA
// on its +0x30 member. Field meaning remains unknown.
Rva00576591::Rva00576591(void *owner)
	: Rva005D12E3()
	, m_owner(owner)
{
	((Rva005CD5FA *)((char *)owner + 0x30))->rva005CD5FA(0);
}

class Rva00576803
{
public:
	Rva00576803(EmitVtableTag *);
public:
	virtual ~Rva00576803();
};

// ?<Rva00576803::Rva00576803> absent-from-retail
Rva00576803::Rva00576803(EmitVtableTag *)
{
}

// TU-local opaque base view. Target constructor 0x005D1BA1 writes its vptr,
// then members at +0x0C and +0x10; its paired destructor at 0x005D1ADE
// restores vtable 0x00C75694. The exact field identities are unknown.
class Rva005D1ADE
{
public:
	Rva005D1ADE(void *, void *, int);
	virtual ~Rva005D1ADE();
private:
	void *m_unknown04;
	void *m_unknown08;
	void *m_unknown0C;
	void *m_unknown10;
};

class Rva0057682F : public Rva005D1ADE
{
public:
	Rva0057682F(EmitVtableTag *);
	Rva0057682F(void *, void *, int);
public:
	virtual ~Rva0057682F();
private:
	void *m_unknown14;
};

// ?<Rva0057682F::Rva0057682F> absent-from-retail
Rva0057682F::Rva0057682F(EmitVtableTag *) : Rva005D1ADE(0, 0, 0)
{
}

// Target evidence: vtable 0x00C6E7B0 is the slot-0 table used by the deleting
// destructor at 0x00576813; its slot points to the 0x0057682F thunk. That
// thunk tail-jumps to 0x005D1ADE. The base relationship and opaque layout are
// structural inferences; the address-derived class name does not claim the
// original retail identity.
Rva0057682F::Rva0057682F(void *owner, void *baseArg, int mode)
	: Rva005D1ADE(*(void **)(reinterpret_cast<char *>(owner) + 0x14), baseArg, mode),
	  m_unknown14(owner)
{
}

class Rva00576B5E
{
public:
	Rva00576B5E(EmitVtableTag *);
public:
	virtual ~Rva00576B5E();
};

// ?<Rva00576B5E::Rva00576B5E> absent-from-retail
Rva00576B5E::Rva00576B5E(EmitVtableTag *)
{
}

class Rva00576F48
{
public:
	Rva00576F48(EmitVtableTag *);
public:
	virtual ~Rva00576F48();
};

// ?<Rva00576F48::Rva00576F48> absent-from-retail
Rva00576F48::Rva00576F48(EmitVtableTag *)
{
}

class Rva005770F2
{
public:
	Rva005770F2(EmitVtableTag *);
public:
	virtual ~Rva005770F2();
};

// ?<Rva005770F2::Rva005770F2> absent-from-retail
Rva005770F2::Rva005770F2(EmitVtableTag *)
{
}

class Rva005770F7
{
public:
	Rva005770F7(EmitVtableTag *);
public:
	virtual ~Rva005770F7();
};

// ?<Rva005770F7::Rva005770F7> absent-from-retail
Rva005770F7::Rva005770F7(EmitVtableTag *)
{
}

class Rva005772BF
{
public:
	Rva005772BF(EmitVtableTag *);
public:
	virtual ~Rva005772BF();
};

// ?<Rva005772BF::Rva005772BF> absent-from-retail
Rva005772BF::Rva005772BF(EmitVtableTag *)
{
}

class Rva00577838
{
public:
	Rva00577838(EmitVtableTag *);
public:
	virtual ~Rva00577838();
};

// ?<Rva00577838::Rva00577838> absent-from-retail
Rva00577838::Rva00577838(EmitVtableTag *)
{
}

class Rva00578189
{
public:
	Rva00578189(EmitVtableTag *);
public:
	virtual ~Rva00578189();
};

// ?<Rva00578189::Rva00578189> absent-from-retail
Rva00578189::Rva00578189(EmitVtableTag *)
{
}

class Rva00582FC1
{
public:
	Rva00582FC1(EmitVtableTag *);
public:
	virtual ~Rva00582FC1();
};

// ?<Rva00582FC1::Rva00582FC1> absent-from-retail
Rva00582FC1::Rva00582FC1(EmitVtableTag *)
{
}

class Rva00597BD4
{
public:
	Rva00597BD4(EmitVtableTag *);
public:
	virtual ~Rva00597BD4();
};

// ?<Rva00597BD4::Rva00597BD4> absent-from-retail
Rva00597BD4::Rva00597BD4(EmitVtableTag *)
{
}

class Rva005990DF
{
public:
	Rva005990DF(EmitVtableTag *);
public:
	virtual ~Rva005990DF();
};

// ?<Rva005990DF::Rva005990DF> absent-from-retail
Rva005990DF::Rva005990DF(EmitVtableTag *)
{
}

// Target destructor proves cleanup on this, then free of the vector's first
// pointer and an external base destructor. Original owner identity is unknown.
extern "C" void __cdecl free(void *);
struct Rva0059E242Buffer
{
    void *begin, *end, *capacity;
    ~Rva0059E242Buffer() { if (begin != 0) free(begin); }
};
class Rva0053947D
{
public:
    virtual ~Rva0053947D();
private:
    char m_unmodelled04[16];
};
class Rva0052B23D { public: void rva0052B23D(); };

class Rva0059E242 : public Rva0053947D
{
public:
	Rva0059E242(EmitVtableTag *);
public:
	virtual ~Rva0059E242();
private:
    char m_unmodelled[24];
    Rva0059E242Buffer m_buffer;
};

// ?<Rva0059E242::Rva0059E242> absent-from-retail
Rva0059E242::Rva0059E242(EmitVtableTag *)
{
}

Rva0059E242::~Rva0059E242()
{
    ((Rva0052B23D *)this)->rva0052B23D();
}
