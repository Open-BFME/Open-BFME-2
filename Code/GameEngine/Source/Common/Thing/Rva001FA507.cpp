// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001FA507@Rva001FA507@@QAEXH@Z @0x001FA507 (34B)
// Evidence: chain via rowed 0x001F9465; null-checked virtual slot 3 at +0 with int arg then rowed Rva001F9465 on this+4. Caller at 0x001FA828. Honest Rva names.
class Helper001FA507
{
public:
	virtual ~Helper001FA507();
	virtual void pad1();
	virtual void pad2();
	virtual void slot3(int);
};

class Rva001F9465
{
public:
	void rva001F9465(int x);
};

class Rva001FA507
{
public:
	void rva001FA507(int x);
private:
	Helper001FA507 *m_ptr;
	Rva001F9465 m_next;
};
void Rva001FA507::rva001FA507(int x)
{
	Helper001FA507 *p = m_ptr;
	if (p)
		p->slot3(x);
	m_next.rva001F9465(x);
}
