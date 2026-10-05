// cl: /O1 /MD /EHsc
//
// ?rva005C3E31@Rva005C3F02@@QAEXUTreeHintRef00217D4C@@@Z @0x005C3E31 (72B)

struct TargetRef00217D4C {
	virtual void *destroy(unsigned flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;

	inline TreeHintRef00217D4C(const TreeHintRef00217D4C &other)
		: m_ptr(other.m_ptr)
	{
		if (m_ptr) {
			m_ptr->references++;
		}
	}

	inline ~TreeHintRef00217D4C()
	{
		if (m_ptr) {
			ReleaseTreeHintRef00217D4C(m_ptr);
		}
	}
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

void Rva005C3F02::rva005C3E31(TreeHintRef00217D4C ref)
{
	m_elem->Add(ref);
}
