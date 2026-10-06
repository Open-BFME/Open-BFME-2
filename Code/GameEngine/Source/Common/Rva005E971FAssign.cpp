// cl: /MD
// ?rva005E971F@Rva005E971F@@QAEXPAVRva005E9625@@@Z, RVA 0x005E971F, 35 bytes.
// Guarded assign of Rva005E9625 pointer at +0: if new != old then store new then delete old via rowed dtor.
// Evidence: calls rowed dtor 0x005E9625 in Rva005E9625Dtor.cpp plus rowed delete 0x0002FD60; neighbours 0x005E9625 0x005E9742; caller 0x005E9D78.
class Rva005E9625
{
public:
	virtual ~Rva005E9625();
};
void __cdecl operator delete(void *);
class Rva005E971F
{
public:
	void rva005E971F(Rva005E9625 *p);
	void rva005E9705();
private:
	Rva005E9625 *m_ptr; // +0
};
void Rva005E971F::rva005E971F(Rva005E9625 *p)
{
	Rva005E9625 *old = m_ptr;
	if (p != old) {
		m_ptr = p;
		if (old) {
			old->Rva005E9625::~Rva005E9625();
			operator delete(old);
		}
	}
}
void Rva005E971F::rva005E9705()
{
	Rva005E9625 *old = m_ptr;
	m_ptr = 0;
	if (old) {
		old->Rva005E9625::~Rva005E9625();
		operator delete(old);
	}
}
