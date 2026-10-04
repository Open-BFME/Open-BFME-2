// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva00529B34@Rva00529B34@@QAEXXZ @0x00529B34 26B
// Evidence: chain on 0x0052936C via rowed dtor plus rowed operator delete 0x0002FD60; caller jmp 0x00529FAB; neighbours Rva0052936CDtor/DispDwordFieldGetters.
class Rva0052936C
{
public:
	~Rva0052936C();
};

void __cdecl operator delete(void *p);

class Rva00529B34
{
public:
	void rva00529B34();
private:
	Rva0052936C *m_ptr;
};

void Rva00529B34::rva00529B34()
{
	Rva0052936C *p = m_ptr;
	m_ptr = 0;
	if (!p)
		return;
	delete p;
}
