// cl: /O1 /MD /EHsc /DNDEBUG
//
// ??0Rva005C3F02@@QAE@PAX0@Z @0x005C40E7 (74B)

class Rva005C3F02;

class Rva005C3A37Elem
{
public:
	Rva005C3A37Elem(Rva005C3F02 *owner, void *a1, void *a2);
	char m_pad[0x48];
};

class Rva005C3F02
{
public:
	virtual ~Rva005C3F02();
	Rva005C3F02(void *a1, void *a2);

private:
	Rva005C3A37Elem *m_elem;
};

Rva005C3F02::Rva005C3F02(void *a1, void *a2)
{
	m_elem = new Rva005C3A37Elem(this, a1, a2);
}
