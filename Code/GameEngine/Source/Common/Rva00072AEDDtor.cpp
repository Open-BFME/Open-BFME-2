// cl: /Ob2 /MD /EHsc
// ??1Rva0072AED@@UAE@XZ retail 0x00072AED 56B
// No own vptr store (novtable): the counted ref at +8 is
// dropped (decrement the count at +4 of the pointee, destroy through its
// slot 0 at zero) under EH state 0, then the inline base dtor restores
// BC650C. Callers: rowed ??_GRva0072AED 0x00072FA9 and thunk 0x00072FE1.
// Names address-derived.

class Rva0072AEDCounted
{
public:
	virtual void destroy();
	int m_count;
};

class Rva0072AEDRef
{
public:
	Rva0072AEDRef(const Rva0072AEDRef &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_count;
	}

	~Rva0072AEDRef()
	{
		Rva0072AEDCounted *p = m_ptr;
		if (p && --p->m_count == 0)
			p->destroy();
	}

	Rva0072AEDCounted *m_ptr;
};

class Rva0072AEDBase
{
public:
	virtual ~Rva0072AEDBase() {}

private:
	int m_04;
};

class __declspec(novtable) Rva0072AED : public Rva0072AEDBase
{
public:
	virtual ~Rva0072AED();
	Rva0072AEDRef rva00072AC3();

private:
	Rva0072AEDRef m_08; // +0x08
};

// ?rva00072AC3@Rva0072AED@@QAE?AVRva0072AEDRef@@XZ @ 0x00072AC3 (27B),
// Ghidra boundary and exact ret-4 extent. Target bytes copy the reference
// at this+8 into the hidden return buffer and increment its pointee count at
// +4 when non-null. The adjacent rowed destructor supports the same +8/+4
// reference layout; the method's class relationship remains an inference.
Rva0072AEDRef Rva0072AED::rva00072AC3()
{
	return m_08;
}

Rva0072AED::~Rva0072AED()
{
}
