// cl: /O1 /MD
// ?rva005D32AA@Rva005D32AA@@QAEXXZ @0x005D32AA 26B
// Clears owned Rva005D309D pointer and deletes it.
// Evidence: dtor 0x005D309D just landed plus operator delete 0x0002FD60;
// caller jmp at 0x005D32D4; ret void thiscall no args.
class Rva005D309D
{
public:
	~Rva005D309D();
};

void __cdecl operator delete(void *p);

class Rva005D32AA
{
public:
	void rva005D32AA();
private:
	Rva005D309D *m_ptr;
};

void Rva005D32AA::rva005D32AA()
{
	Rva005D309D *p = m_ptr;
	m_ptr = 0;
	delete p;
}
