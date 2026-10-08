// cl: /MD
// ?clear@Rva005F7736@@QAEXXZ, retail 0x005F7736, 26 bytes.
// Clears the single element pointer at +0 via the non-virtual dtor
// 0x005F75C9 plus rowed operator delete 0x0002FD60. Caller is the 14B
// dtor 0x005F7750 in Rva005F7750Dtor.cpp.
void __cdecl operator delete(void *p);

class Rva005F75C9
{
public:
	~Rva005F75C9();
};

class Rva005F7736
{
public:
	void clear();

private:
	Rva005F75C9 *m_ptr;
};

void Rva005F7736::clear()
{
	Rva005F75C9 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F75C9::~Rva005F75C9();
		::operator delete(p);
	}
}
