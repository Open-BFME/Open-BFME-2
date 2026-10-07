// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 68/69-byte clone slots use RET4 for a hidden result object,
// not an explicit pointer argument. Result word0 receives a fresh copy;
// its reference count at4 starts at0 and is incremented for the result.
// Vtables 0x00C7507C/0x00C75108/0x00C75124 name clone slot 1.
// Constructors already establish these owners at 0x005CDB8F, 0x005CDF6C,
// and 0x005CE259, with 20/20/8-byte payloads at +8 and zero count at +4.
// The nontrivial result destructor supplies the native hidden-result ABI;
// this TU does not call it or provide an unverified release implementation.

template <class T> class RvaCloneResult
{
public:
	RvaCloneResult(T *p) : pointer(p)
	{
		if (p) ++p->m_ref;
	}
	~RvaCloneResult();
private:
	T *pointer;
};

class Rva005CDB8F
{
public:
	__forceinline Rva005CDB8F(const Rva005CDB8F &rhs)
		: m_ref(0), m_data(rhs.m_data) {}
	virtual ~Rva005CDB8F();
	virtual RvaCloneResult<Rva005CDB8F> clone() const;
	struct Payload { int v[5]; };
	Rva005CDB8F(const Payload *src);
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CDF6C
{
public:
	__forceinline Rva005CDF6C(const Rva005CDF6C &rhs)
		: m_ref(0), m_data(rhs.m_data) {}
	virtual ~Rva005CDF6C();
	virtual RvaCloneResult<Rva005CDF6C> clone() const;
	struct Payload { int v[5]; };
	Rva005CDF6C(const Payload *src);
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CE259
{
public:
	__forceinline Rva005CE259(const Rva005CE259 &rhs)
		: m_ref(0), m_data(rhs.m_data) {}
	virtual ~Rva005CE259();
	virtual RvaCloneResult<Rva005CE259> clone() const;
	struct Payload { int v[2]; };
	Rva005CE259(const Payload *src);
	int m_ref; // +4
	Payload m_data; // +8
};

// Constructor 0x005677B9 and native vtable 0x00C6CECC slot 1
// establish this 16-byte owner and its 8-byte payload.
class Rva005677B9
{
public:
 __forceinline Rva005677B9(const Rva005677B9 &rhs)
  : m_ref(0), m_data(rhs.m_data) {}
 virtual ~Rva005677B9();
 virtual RvaCloneResult<Rva005677B9> clone() const;
 struct Payload { int v[2]; };
 Rva005677B9(const Payload *src);
 int m_ref; // +4
 Payload m_data; // +8
};

// Constructor 0x00574ABB and native vtable 0x00C6E498 slot 1
// establish this 16-byte owner and its 8-byte payload.
class Rva00574ABB
{
public:
 __forceinline Rva00574ABB(const Rva00574ABB &rhs)
  : m_ref(0), m_data(rhs.m_data) {}
 virtual ~Rva00574ABB();
 virtual RvaCloneResult<Rva00574ABB> clone() const;
 struct Payload { int v[2]; };
 Rva00574ABB(const Payload *src);
 int m_ref; // +4
 Payload m_data; // +8
};

// Constructor 0x005E9742 and native vtable 0x00C78038 slot 1
// establish this 32-byte owner and its 24-byte payload.
class Rva005E9742
{
public:
 __forceinline Rva005E9742(const Rva005E9742 &rhs)
  : m_ref(0), m_data(rhs.m_data) {}
 virtual ~Rva005E9742();
 virtual RvaCloneResult<Rva005E9742> clone() const;
 struct Payload { int v[6]; };
 Rva005E9742(const Payload *src);
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005CDB8F> Rva005CDB8F::clone() const
{
	return RvaCloneResult<Rva005CDB8F>(new Rva005CDB8F(*this));
}

RvaCloneResult<Rva005CDF6C> Rva005CDF6C::clone() const
{
	return RvaCloneResult<Rva005CDF6C>(new Rva005CDF6C(*this));
}

RvaCloneResult<Rva005CE259> Rva005CE259::clone() const
{
	return RvaCloneResult<Rva005CE259>(new Rva005CE259(*this));
}

RvaCloneResult<Rva005677B9> Rva005677B9::clone() const
{
 return RvaCloneResult<Rva005677B9>(new Rva005677B9(*this));
}

RvaCloneResult<Rva00574ABB> Rva00574ABB::clone() const
{
 return RvaCloneResult<Rva00574ABB>(new Rva00574ABB(*this));
}

RvaCloneResult<Rva005E9742> Rva005E9742::clone() const
{
 return RvaCloneResult<Rva005E9742>(new Rva005E9742(*this));
}

