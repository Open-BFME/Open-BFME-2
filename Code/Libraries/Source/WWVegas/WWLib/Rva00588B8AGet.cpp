// cl: /EHsc /MD /D_CRTIMP=
// ?rva00588B8A@Rva0047A040Base9E0@@QAEPAXPAX@Z @0x00588B8A 30B null-safe virtual-slot caller.
// Evidence: 11 callers in 0x477xxx plus 0x588BF3/0x588E44; arg+0x250 null-checked
// twice then vtable slot 0x7C called; callees none direct (virtual only).
// Every call site loads ecx (lea ecx,[outer+0x11D] / [outer+0x9E0], or the
// 0x00588BF3/0x00588E44 this) before the call, so it is a thiscall member of
// the Rva0047A040Base9E0 helper that never reads this, not a stdcall helper.
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
	virtual void *s7c() = 0;
};

struct Rva00588B8AHolder
{
	char m_pad[0x250];
	Rva00588B8AVtbl *m_ptr;
};

class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *p);
};

void *Rva0047A040Base9E0::rva00588B8A(void *p)
{
	if (!p)
		return 0;
	Rva00588B8AVtbl *q = ((Rva00588B8AHolder *)p)->m_ptr;
	if (q)
		return q->s7c();
	return 0;
}
