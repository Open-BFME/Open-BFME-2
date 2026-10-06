// cl: /MD /EHsc
// ??4Rva004E6A37@@QAEAAV0@V0@@Z @ 0x004E6A4E (77B): owning-pointer assign stealing the by-value source pointer then deleting the old pointee via 0x004E6935 and operator delete 0x0002FD60; compiler destroys the emptied source via 0x004E6A37. Caller evidence at 0x004E6FEC and 0x004E722B; unwind stubs jmp to the dtor.
class Rva004E6935
{
public:
	~Rva004E6935();
};
class Rva004E6A37
{
public:
	Rva004E6935 *m_ptr;
	~Rva004E6A37();
	Rva004E6A37 &operator=(Rva004E6A37 other);
};
void __cdecl operator delete(void *p);
Rva004E6A37 &Rva004E6A37::operator=(Rva004E6A37 other)
{
	Rva004E6935 *old = m_ptr;
	Rva004E6935 *fresh = other.m_ptr;
	other.m_ptr = 0;
	m_ptr = fresh;
	if (old)
	{
		old->Rva004E6935::~Rva004E6935();
		::operator delete(old);
	}
	return *this;
}
