// cl: /MD
// ?rva0057702E@Rva0057702E@@QAEXXZ @ 0x0057702E (30B):
// Guarded clear on pointer at +0; nulls it then operator-deletes the virtual
// result at slot 4 with arg 0 or null. Evidence: 7 callers including 115B bodies
// 0x005775C1/0x00577634 plus tail jmps; shared push-eax tail matches ternary.

void __cdecl operator delete(void *p);

struct Rva0057702EBase
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void *f4(int);
};

class Rva0057702E
{
	Rva0057702EBase *m_ptr;

public:
	void rva0057702E();
};

void Rva0057702E::rva0057702E()
{
	Rva0057702EBase *p = m_ptr;
	m_ptr = 0;
	::operator delete(p ? p->f4(0) : 0);
}

// ?rva0057704C@Rva0057704C@@QAEXPAURva0057702EBase@@@Z @0x0057704C 39B: guarded assign on pointer at +0; assigns new when different then operator-deletes virtual slot4 result with 0 or null; callers 0x00577620 115B plus 0x00577693 115B; prev Clear next Acquire; no donor.
class Rva0057704C
{
	Rva0057702EBase *m_ptr;

public:
	void rva0057704C(Rva0057702EBase *n);
};

void Rva0057704C::rva0057704C(Rva0057702EBase *n)
{
	Rva0057702EBase *o = m_ptr;
	if (n != o) {
		m_ptr = n;
		::operator delete(o ? o->f4(0) : 0);
	}
}
