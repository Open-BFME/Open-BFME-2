// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001FA80F@Rva001FA80F@@QAEXH@Z @0x001FA80F (34B)
// Evidence: chain via rowed 0x001FA507; null-checked virtual slot 3 at +0 with int arg then rowed Rva001FA507 on this+4. Caller at 0x001FB23A. Honest Rva names.
class Helper001FA80F
{
public:
	virtual ~Helper001FA80F();
	virtual void pad1();
	virtual void pad2();
	virtual void slot3(int);
};

class Rva001FA507
{
public:
	void rva001FA507(int x);
};

class Rva001FA80F
{
public:
	void rva001FA80F(int x);
private:
	Helper001FA80F *m_ptr;
	Rva001FA507 m_next;
};
void Rva001FA80F::rva001FA80F(int x)
{
	Helper001FA80F *p = m_ptr;
	if (p)
		p->slot3(x);
	m_next.rva001FA507(x);
}
