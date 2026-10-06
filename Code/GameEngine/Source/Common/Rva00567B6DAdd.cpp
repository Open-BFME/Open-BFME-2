// cl: /MD /EHsc
// ?Rva00567B6DAdd@@YAXPAVRva005C3F02@@PBUPayload@Rva005677B9@@@Z, retail 0x00567B6D, 106 bytes.
// Caller 0x00568021 passes container in first arg and 2-dword payload in second; twin new-0x10 plus refcount-add pattern of 0x005CE2BA family.

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;

	TreeHintRef00217D4C(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->references;
	}

	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}

	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class Rva005677B9 : public TargetRef00217D4C
{
public:
	struct Payload { int v[2]; };
	Rva005677B9(const Payload *src) throw();
	virtual ~Rva005677B9();
private:
	Payload m_data;
};

class Rva005C3A37Elem
{
public:
	void Add(TreeHintRef00217D4C ref);
};

class Rva005C3F02
{
public:
	void rva005C3E31(TreeHintRef00217D4C ref);
private:
	int m_pad00;
	Rva005C3A37Elem *m_elem;
};

void __cdecl Rva00567B6DAdd(Rva005C3F02 *dst, const Rva005677B9::Payload *src)
{
	Rva005677B9 *p = new Rva005677B9(src);
	TreeHintRef00217D4C tmp((TargetRef00217D4C *)p);
	dst->rva005C3E31(tmp);
}
