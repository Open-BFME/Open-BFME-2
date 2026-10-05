// cl: /EHsc /Oy- /O1 /Ob2
// Family-1 refcounted clones (67B each): each holder's clone() allocates
// 0x14 bytes, runs the forceinline copy (refcount zero, vtable store, 12-byte
// payload block copy via the Pay sub-object), wraps the pointer in a
// RvaF1Handle (null-checked AddRef) and returns it by value. The copy's
// zero-before-vtable order is what MSVC 7.1 emits for an init-list copy
// starting with the refcount; the payload block copies as movsd only through
// the Pay sub-object. The Handle destructor is declared-not-defined
// scaffolding that produces the EH-state init; the Handle constructor is
// defined (must inline) and marked present-unmatched. Holder vtable pins
// carry the retail table addresses. Holder, payload and handle identities
// are unproven; address-derived names throughout.
struct RvaF1Pay
{
	int m_00;
	int m_04;
	int m_08;
};

struct RvaF1Handle
{
	void *m_p;
	RvaF1Handle(void *p);
	~RvaF1Handle();
};

// ?RvaF1HandleCtor present-unmatched
__forceinline RvaF1Handle::RvaF1Handle(void *p) : m_p(p)
{
	if (p)
		++((int *)p)[1];
}

struct Rva005CE46F
{
	virtual ~Rva005CE46F();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005CE46F(const Rva005CE46F &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005CE46F::clone() const
{
	return RvaF1Handle(new Rva005CE46F(*this));
}

struct Rva005CED6C
{
	virtual ~Rva005CED6C();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005CED6C(const Rva005CED6C &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005CED6C::clone() const
{
	return RvaF1Handle(new Rva005CED6C(*this));
}

struct Rva005E5E7A
{
	virtual ~Rva005E5E7A();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005E5E7A(const Rva005E5E7A &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005E5E7A::clone() const
{
	return RvaF1Handle(new Rva005E5E7A(*this));
}

struct Rva005E5EBD
{
	virtual ~Rva005E5EBD();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005E5EBD(const Rva005E5EBD &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005E5EBD::clone() const
{
	return RvaF1Handle(new Rva005E5EBD(*this));
}

struct Rva005E5F00
{
	virtual ~Rva005E5F00();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005E5F00(const Rva005E5F00 &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005E5F00::clone() const
{
	return RvaF1Handle(new Rva005E5F00(*this));
}

struct Rva005E99D8
{
	virtual ~Rva005E99D8();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005E99D8(const Rva005E99D8 &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005E99D8::clone() const
{
	return RvaF1Handle(new Rva005E99D8(*this));
}

struct Rva005E9A1B
{
	virtual ~Rva005E9A1B();
	int m_refCount;
	RvaF1Pay m_pay;
	__forceinline Rva005E9A1B(const Rva005E9A1B &src) : m_refCount(0), m_pay(src.m_pay) {}
	RvaF1Handle clone() const;
};

RvaF1Handle Rva005E9A1B::clone() const
{
	return RvaF1Handle(new Rva005E9A1B(*this));
}
