// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva005C3F02@@QAE@PAX0@Z @0x005C40E7 (74B)

class Rva005C3F02;

class Rva005C3A37Elem
{
public:
	Rva005C3A37Elem(Rva005C3F02 *owner, void *a1, void *a2);
	void rva005C3B3E();
	char m_pad[0x48];
};

class Rva005C3F02
{
public:
	virtual ~Rva005C3F02();
	Rva005C3F02(void *a1, void *a2);
	void rva005C3E81();

private:
	Rva005C3A37Elem *m_elem;
};

Rva005C3F02::Rva005C3F02(void *a1, void *a2)
{
	m_elem = new Rva005C3A37Elem(this, a1, a2);
}

// 0x005C3E81 (8B): forwards to the element's per-frame method 0x005C3B3E
// (tail jump); called per button slot by StrategicHUD::CommandUIImpl::Update.
void Rva005C3F02::rva005C3E81()
{
	m_elem->rva005C3B3E();
}
