// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native69/69/68-byte clone slots use RET4 for a hidden result object,
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
