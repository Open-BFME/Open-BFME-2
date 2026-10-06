// cl: /EHsc /MD /D_CRTIMP=
// ?Rva00588B8AGet@@YGHPAX@Z @0x00588B8A 30B null-safe virtual-slot caller.
// Evidence: 11 callers in 0x477xxx plus 0x588BF3/0x588E44; arg+0x250 null-checked
// twice then vtable slot 0x7C called; callees none direct (virtual only).
// Prev 0x58814C flags copied; TU-local vtable shim follows Mouse slot precedent.

class Rva00588B8AVtbl
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0c() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1c() = 0;
	virtual void s20() = 0;
	virtual void s24() = 0;
	virtual void s28() = 0;
	virtual void s2c() = 0;
	virtual void s30() = 0;
	virtual void s34() = 0;
	virtual void s38() = 0;
	virtual void s3c() = 0;
	virtual void s40() = 0;
	virtual void s44() = 0;
	virtual void s48() = 0;
	virtual void s4c() = 0;
	virtual void s50() = 0;
	virtual void s54() = 0;
	virtual void s58() = 0;
	virtual void s5c() = 0;
	virtual void s60() = 0;
	virtual void s64() = 0;
	virtual void s68() = 0;
	virtual void s6c() = 0;
	virtual void s70() = 0;
	virtual void s74() = 0;
	virtual void s78() = 0;
	virtual int s7c() = 0;
};

struct Rva00588B8AHolder
{
	char m_pad[0x250];
	Rva00588B8AVtbl *m_ptr;
};

int __stdcall Rva00588B8AGet(void *p)
{
	if (!p)
		return 0;
	Rva00588B8AVtbl *q = ((Rva00588B8AHolder *)p)->m_ptr;
	if (q)
		return q->s7c();
	return 0;
}
