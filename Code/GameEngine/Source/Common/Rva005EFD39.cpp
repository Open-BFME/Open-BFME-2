// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /D_CRTIMP=
// ?rva005EFD39@Rva005EFD39@@QAEXXZ @0x005EFD39 26B: clear of Rva005EFB05* at +0.
// Evidence: calls rowed dtor 0x005EFB05 plus rowed operator delete 0x0002FD60; caller 0x005EFDE4 tail-jmp after vtable store plus add ecx 4.
class Rva005EFB05
{
public:
	~Rva005EFB05();
};
void __cdecl operator delete(void *);
class Rva005EFD39
{
public:
	void rva005EFD39();
private:
	Rva005EFB05 *m_ptr;
};
void Rva005EFD39::rva005EFD39()
{
	Rva005EFB05 *tmp = m_ptr;
	m_ptr = 0;
	if (tmp != 0)
		delete tmp;
}
class Rva005EFDDB
{
public:
	virtual ~Rva005EFDDB();
private:
	Rva005EFD39 m_04;
};
Rva005EFDDB::~Rva005EFDDB()
{
	m_04.rva005EFD39();
}
