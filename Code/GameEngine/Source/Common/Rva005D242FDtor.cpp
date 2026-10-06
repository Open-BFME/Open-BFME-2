// cl: /MD
//
// ??1Rva005D242F@@UAE@XZ retail 0x005D242F 26 bytes.
// Stores vtable 0x008757D8 then if linked word at +0x18 equals member at +0xC
// clears it to -1 then tail-jmps to rowed base dtor ??1Rva005C3F02@@UAE@XZ
// at 0x005C3F02. Caller is deleting dtor at 0x005D2495. Base member at +8 is
// a pointer to a struct with int at +0x18; derived member at +0xC is int.
// Honest address name; owner class unproven.
struct Rva005D242FLinked
{
	int m00, m04, m08, m0C, m10, m14;
	int m18;
};

class Rva005C3F02
{
public:
	virtual ~Rva005C3F02();
protected:
	int m04;
	Rva005D242FLinked *m08;
};

class Rva005D242F : public Rva005C3F02
{
public:
	virtual ~Rva005D242F();
	virtual void rva005D2449();
	virtual void rva005D24B1();
private:
	int m0C;
};

Rva005D242F::~Rva005D242F()
{
	if (m08->m18 == m0C)
		m08->m18 = -1;
}

template <typename T> class StringBase
{
	friend class Rva005D242F;
	void validate() const;
};

void Rva005D242F::rva005D2449()
{
	((StringBase<unsigned short> *)this)->validate();
	if (m08->m18 == m0C)
		m08->m18 = -1;
}

class Rva005C39AA
{
public:
	void rva005C39AA();
};

struct Rva005D24B1Elem
{
	Rva005C39AA *m_ptr;
	char m_pad[0x18];
};

struct Rva005D242FLinkedEx
{
	int m00, m04, m08, m0C, m10, m14;
	int m18;
	int m1C;
	Rva005D24B1Elem m_elems[1];
};

void Rva005D242F::rva005D24B1()
{
	((StringBase<unsigned short> *)this)->validate();
	if (m08->m18 != m0C)
	{
		if (m08->m18 >= 0)
			((Rva005D242FLinkedEx *)m08)->m_elems[m08->m18].m_ptr->rva005C39AA();
		m08->m18 = m0C;
	}
}
