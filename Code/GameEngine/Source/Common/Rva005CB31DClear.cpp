// cl: /MD
// ??1Rva005CB31D@@QAE@XZ retail 0x005CB31D 26B
// Holder dtor releasing Rva005E0B0F ptr at +0. Retail nulls first via
// and [ecx] 0 then calls rowed ??1Rva005E0B0F@@UAE@XZ and rowed ??3 delete.
// Evidence: outer dtor 0x005CB4E6 destroys three members at +0x10 +0x14 +0x18
// via this address with EH states 1 0 -1 which only member dtors produce.
class Rva005E0B0F
{
public:
	virtual ~Rva005E0B0F();
};

void __cdecl operator delete(void *);

class Rva005CB31D
{
public:
	~Rva005CB31D();
	void rva005CB337(Rva005E0B0F *p);

private:
	Rva005E0B0F *m_ptr;
};

Rva005CB31D::~Rva005CB31D()
{
	Rva005E0B0F *p = m_ptr;
	m_ptr = 0;
	if (p != 0) {
		p->Rva005E0B0F::~Rva005E0B0F();
		operator delete(p);
	}
}

// ?rva005CB337@Rva005CB31D@@QAEXPAVRva005E0B0F@@@Z retail 0x005CB337 35B
// Setter for the same holder: store new ptr then release old via rowed dtor+delete.
// Evidence: follows 0x005CB31D exactly; callers at 0x005CB5B1 0x005CB64F 0x005CB6E4
// in 0x005CB52B set three members; same callee 0x005E0B0F and delete 0x0002FD60.
void Rva005CB31D::rva005CB337(Rva005E0B0F *p)
{
	Rva005E0B0F *old = m_ptr;
	if (p != old) {
		m_ptr = p;
		if (old != 0) {
			old->Rva005E0B0F::~Rva005E0B0F();
			operator delete(old);
		}
	}
}
