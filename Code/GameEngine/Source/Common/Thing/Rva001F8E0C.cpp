// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F8E0C@Rva001F8E0C@@QAEXXZ 0x001F8E0C 23B
// Evidence: chain from rowed 0x001F898A; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F898A on this+4. Caller jmp at 0x001F9460. Honest Rva names.

class Helper001F8E0C
{
public:
	virtual ~Helper001F8E0C();
	virtual void tick();
};

class Rva001F898A
{
public:
	void rva001F898A();
};

class Rva001F8E0C
{
public:
	void rva001F8E0C();
private:
	Helper001F8E0C *m_ptr;
	Rva001F898A m_next;
};

void Rva001F8E0C::rva001F8E0C()
{
	Helper001F8E0C *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F898A();
}
