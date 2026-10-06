// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F823D@Rva001F823D@@QAEXXZ 0x001F823D 23B
// Evidence: chain from rowed 0x001F64D2; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F64D2 on this+4. Caller jmp at 0x001F899C. Honest Rva names.

class Helper001F823D
{
public:
	virtual ~Helper001F823D();
	virtual void tick();
};

class Rva001F64D2
{
public:
	void rva001F64D2();
};

class Rva001F823D
{
public:
	void rva001F823D();
private:
	Helper001F823D *m_ptr;
	Rva001F64D2 m_next;
};

void Rva001F823D::rva001F823D()
{
	Helper001F823D *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F64D2();
}
