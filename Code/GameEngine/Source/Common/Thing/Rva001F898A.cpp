// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F898A@Rva001F898A@@QAEXXZ 0x001F898A 23B
// Evidence: chain from rowed 0x001F823D; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F823D on this+4. Caller jmp at 0x001F8E1E. Honest Rva names.

class Helper001F898A
{
public:
	virtual ~Helper001F898A();
	virtual void tick();
};

class Rva001F823D
{
public:
	void rva001F823D();
};

class Rva001F898A
{
public:
	void rva001F898A();
private:
	Helper001F898A *m_ptr;
	Rva001F823D m_next;
};

void Rva001F898A::rva001F898A()
{
	Helper001F898A *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F823D();
}
