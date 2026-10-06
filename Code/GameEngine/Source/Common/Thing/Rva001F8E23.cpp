// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F8E23@Rva001F8E23@@QAEXH@Z 0x001F8E23 34B
// Evidence: chain from rowed 0x001F89A1; null-checked virtual slot 3 at +0 with int arg then rowed Rva001F89A1 on this+4. Caller at 0x001F947E. Honest Rva names.
class Helper001F8E23
{
public:
	virtual ~Helper001F8E23();
	virtual void pad1();
	virtual void pad2();
	virtual void slot3(int);
};

class Rva001F89A1
{
public:
	void rva001F89A1(int x);
};

class Rva001F8E23
{
public:
	void rva001F8E23(int x);
private:
	Helper001F8E23 *m_ptr;
	Rva001F89A1 m_next;
};

void Rva001F8E23::rva001F8E23(int x)
{
	Helper001F8E23 *p = m_ptr;
	if (p)
		p->slot3(x);
	m_next.rva001F89A1(x);
}
